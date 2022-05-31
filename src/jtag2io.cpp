/*
 *	avarice - The "avarice" program.
 *	Copyright (C) 2001 Scott Finneran
 *      Copyright (C) 2002, 2003, 2004 Intel Corporation
 *	Copyright (C) 2005, 2006, 2007 Joerg Wunsch
 *
 *	This program is free software; you can redistribute it and/or modify
 *	it under the terms of the GNU General Public License Version 2
 *      as published by the Free Software Foundation.
 *
 *	This program is distributed in the hope that it will be useful,
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *	GNU General Public License for more details.
 *
 *	You should have received a copy of the GNU General Public License
 *	along with this program; if not, write to the Free Software
 *	Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111, USA.
 *
 * This file implements the basic IO handling for the mkII protocol.
 */

#include <cstdio>
#include <cstring>

#include "jtag2.h"

#include <boost/crc.hpp>
// Based on boost::crc_ccitt_true_t but with a different start value
using Crc16 = boost::crc_optimal< 16, 0x1021, 0xffff, 0, true, true >;

jtag2_io_exception::jtag2_io_exception(unsigned int code) {
    static char buffer[50];
    response_code = code;

    switch (code) {
    case RSP_DEBUGWIRE_SYNC_FAILED:
        reason = "DEBUGWIRE SYNC FAILED";
        break;
    case RSP_FAILED:
        reason = "FAILED";
        break;
    case RSP_GET_BREAK:
        reason = "GET BREAK";
        break;
    case RSP_ILLEGAL_BREAKPOINT:
        reason = "ILLEGAL BREAKPOINT";
        break;
    case RSP_ILLEGAL_COMMAND:
        reason = "ILLEGAL COMMAND";
        break;
    case RSP_ILLEGAL_EMULATOR_MODE:
        reason = "ILLEGAL EMULATOR MODE";
        break;
    case RSP_ILLEGAL_JTAG_ID:
        reason = "ILLEGAL JTAG ID";
        break;
    case RSP_ILLEGAL_MCU_STATE:
        reason = "ILLEGAL MCU STATE";
        break;
    case RSP_ILLEGAL_MEMORY_TYPE:
        reason = "ILLEGAL MEMORY TYPE";
        break;
    case RSP_ILLEGAL_MEMORY_RANGE:
        reason = "ILLEGAL MEMORY RANGE";
        break;
    case RSP_ILLEGAL_PARAMETER:
        reason = "ILLEGAL PARAMETER";
        break;
    case RSP_ILLEGAL_POWER_STATE:
        reason = "ILLEGAL POWER STATE";
        break;
    case RSP_ILLEGAL_VALUE:
        reason = "ILLEGAL VALUE";
        break;
    case RSP_NO_TARGET_POWER:
        reason = "NO TARGET POWER";
        break;
    case RSP_SET_N_PARAMETERS:
        reason = "SET N PARAMETERS";
        break;
    default:
        snprintf(buffer, sizeof(buffer), "Unknown response code 0x%0x", code);
        reason = buffer;
    }
}

Jtag2::~Jtag2() {
    // Terminate connection to JTAG box.
    if (signedIn) {
        try {
            if (debug_active)
                doSimpleJtagCommand(CMND_RESTORE_TARGET);
        } catch (jtag_exception &) {
            // just proceed with the sign-off
        }
        doSimpleJtagCommand(CMND_SIGN_OFF);
        signedIn = false;
    }
}

/*
 * Send one frame.  Adds the required preamble and CRC, and ensures
 * the frame could be written correctly.
 */
void Jtag2::sendFrame(const uchar *command, int commandSize) {
    auto buf = std::make_unique<uchar[]>(commandSize + 10);

    buf[0] = MESSAGE_START;
    u16_to_b2(buf.get() + 1, command_sequence);
    u32_to_b4(buf.get() + 3, commandSize);
    buf[7] = TOKEN;
    memcpy(buf.get() + 8, command, commandSize);

    Crc16 crc;
    crc.process_bytes(buf.get(), commandSize + 8);
    const auto calculated_cs = crc.checksum();
    auto& msg_cs = *reinterpret_cast<uint16_t*>(buf.get() + commandSize + 8);
    msg_cs = calculated_cs;

    int count = safewrite(buf.get(), commandSize + 10);

    if (count < 0)
        throw jtag_exception();
    else if (count != commandSize + 10)
        // this shouldn't happen
        throw jtag_exception("Invalid write size");
}

/*
 * Receive one frame, return it in &msg.  Received sequence number is
 * returned in &seqno.  Any valid frame will be returned, regardless
 * whether it matches the expected sequence number, including event
 * notification frames (seqno == 0xffff).
 *
 * Caller must eventually free the buffer.
 */
int Jtag2::recvFrame(unsigned char *&msg, unsigned short &seqno) {
    enum states {
        sSTART,
        sSEQNUM1,
        sSEQNUM2,
        sSIZE1,
        sSIZE2,
        sSIZE3,
        sSIZE4,
        sTOKEN,
        sDATA,
        sCSUM1,
        sCSUM2,
        sDONE
    } state = sSTART;
    size_t msglen = 0;
    unsigned int l = 0;
    unsigned int headeridx = 0;
    unsigned char c = 0;
    unsigned char header[8];
    unsigned short r_seqno = 0;
    unsigned short checksum = 0;
    std::unique_ptr<uchar[]> buf;

    msg = nullptr;

    while (state != sDONE) {
        if (state == sDATA) {
            debugOut("sDATA: reading %u bytes\n", msglen);
            const auto rv = timeout_read(buf.get() + 8, msglen, JTAG_RESPONSE_TIMEOUT);
            debugOutBufHex("read: ", buf.get() + 8, msglen);
            if (rv == 0)
                /* timeout */
                break;
        } else {
            const auto rv = timeout_read(&c, 1, JTAG_RESPONSE_TIMEOUT);
            if (rv == 0) {
                /* timeout */
                debugOut("recv: timeout\n");
                break;
            }
            debugOut("recv: 0x%02x\n", c);
        }
        checksum ^= c;

        if (state < sDATA)
            header[headeridx++] = c;

        switch (state) {
        case sSTART:
            if (c == MESSAGE_START) {
                state = sSEQNUM1;
            } else {
                headeridx = 0;
            }
            break;
        case sSEQNUM1:
            r_seqno = c;
            state = sSEQNUM2;
            break;
        case sSEQNUM2:
            r_seqno |= ((unsigned)c << 8);
            state = sSIZE1;
            break;
        case sSIZE1:
            state = sSIZE2;
            goto domsglen;
        case sSIZE2:
            state = sSIZE3;
            goto domsglen;
        case sSIZE3:
            state = sSIZE4;
            goto domsglen;
        case sSIZE4:
            state = sTOKEN;
        domsglen:
            msglen >>= 8;
            msglen |= ((unsigned)c << 24);
            break;
        case sTOKEN:
            if (c == TOKEN) {
                state = sDATA;
                if (msglen > MAX_MESSAGE) {
                    printf("msglen %lu exceeds max message size %lu, ignoring message\n", msglen,
                           MAX_MESSAGE);
                    state = sSTART;
                    headeridx = 0;
                } else {
                    buf = std::make_unique<uchar[]>(msglen + 10);
                    memcpy(buf.get(), header, 8);
                }
            } else {
                state = sSTART;
                headeridx = 0;
            }
            break;
        case sDATA:
            /* The entire payload has been read above. */
            l = msglen + 8;
            state = sCSUM1;
            break;
        case sCSUM1:
            buf[l++] = c;
            state = sCSUM2;
            break;
        case sCSUM2: {
            buf[l++] = c;
            Crc16 crc;
            crc.process_bytes(buf.get(), msglen + 8);
            const auto calculated_cs = crc.checksum();
            const auto& received_cs = *reinterpret_cast<uint16_t*>(buf.get() + msglen + 8);
            if (calculated_cs == received_cs) {
                debugOut("CRC OK");
                state = sDONE;
            } else {
                debugOut("checksum error");
                return -1;
            }
            break;
        }
        default:
            debugOut("unknown state");
            return -1;
        }
    }

    seqno = r_seqno;
    msg = buf.release();

    return (int)msglen;
}

/*
 * Try receiving frames, until we get the reply we are expecting.
 * Caller must delete[] the msg after processing it.
 */
int Jtag2::recv(uchar *&msg) {
    unsigned short r_seqno;
    int rv;

    for (;;) {
        if ((rv = recvFrame(msg, r_seqno)) <= 0)
            return rv;
        debugOut("\nGot message seqno %d (command_sequence == %d)\n", r_seqno, command_sequence);
        if (r_seqno == command_sequence) {
            if (++command_sequence == 0xffff)
                command_sequence = 0;
            /*
             * We move the payload to the beginning of the buffer, to make
             * the job easier for the caller.  We have to return the
             * original pointer though, as the caller must free() it.
             */
            memmove(msg, msg + 8, rv);
            return rv;
        }
        if (r_seqno == 0xffff) {
            debugOut("\ngot asynchronous event: 0x%02x\n", msg[8]);
            // XXX should we queue that event up somewhere?
            // How to process it?  Register event handlers
            // for interesting events?
            // For now, the only place that cares is jtagContinue
            // and it just calls recvFrame and handles events directly.
        } else {
            debugOut("\ngot wrong sequence number, %u != %u\n", r_seqno, command_sequence);
        }
        delete[] msg;
    }
}

/** Send a command to the jtag, and check result.

    Increase *tries, abort if reaches MAX_JTAG_COMM_ATTEMPS

    Reads first response byte. If no response is received within
    JTAG_RESPONSE_TIMEOUT, returns false. If response is
    positive returns true, otherwise returns false.

    If response is positive, message (including response code) is
    returned in &msg, caller must delete [] it.  The message size is
    returned in &msgsize.
**/

bool Jtag2::sendJtagCommand(const uchar *command, int commandSize, int &tries, uchar *&msg,
                            int &msgsize, bool verify) {
    if (tries++ >= MAX_JTAG_COMM_ATTEMPS)
        throw jtag_exception("JTAG communication failed");

    debugOut("\ncommand[0x%02x, %d]: ", command[0], tries);
    debugOutBufHex("", command, commandSize);

    sendFrame(command, commandSize);

    msgsize = recv(msg);
    if (verify && msgsize == 0)
        throw jtag_exception("no response received");
    else if (msgsize < 1)
        return false;

    debugOutBufHex("response: ", msg, msgsize);

    const auto c = msg[0];
    return (c >= RSP_OK) && (c < RSP_FAILED);
}

void Jtag2::doJtagCommand(const uchar *command, int commandSize, uchar *&response,
                          int &responseSize, bool retryOnTimeout) {
    int sizeseen = 0;
    uchar code = 0;

    for (int tryCount = 0; tryCount < 8; tryCount++) {
        if (sendJtagCommand(command, commandSize, tryCount, response, responseSize, false))
            return;

        if (!retryOnTimeout) {
            if (responseSize == 0)
                throw jtag_timeout_exception();
            else
                throw jtag2_io_exception(response[0]);
        }

        if (responseSize > 0 && response[0] > RSP_FAILED)
            // no point in retrying failures other than FAILED
            throw jtag2_io_exception(response[0]);

        if (responseSize > 0) {
            sizeseen = responseSize;
            code = response[0];
        }

        if (tryCount == 4 && responseSize == 0 && is_usb) {
            /* signal the USB daemon to reset the EPs */
            debugOut("Resetting EPs...\n");
            resetUSB();
        }
    }
    if (sizeseen > 0)
        throw jtag2_io_exception(code);
    else
        throw jtag_timeout_exception();
}

void Jtag2::doSimpleJtagCommand(uchar command) {
    int tryCount = 0, dummy;
    uchar *replydummy;

    // Send command until we get an OK response
    for (;;) {
        if (sendJtagCommand(&command, 1, tryCount, replydummy, dummy, false)) {
            if (replydummy == nullptr)
                throw jtag2_io_exception();
            if (dummy != 1)
                throw jtag_exception("Unexpected response size in doSimpleJtagCommand");
            if (replydummy[0] != RSP_OK)
                throw jtag2_io_exception(replydummy[0]);
            delete[] replydummy;
            return;
        }
    }
}

/** Set PC and JTAG ICE bitrate to BIT_RATE_xxx specified by 'newBitRate' **/
void Jtag2::changeBitRate(int newBitRate) {
    // Don't try to change the speed of an USB connection.
    // For the AVR Dragon, that would even result in the parameter
    // change below being rejected.
    if (is_usb)
        return;

    uchar jtagrate;

    switch (newBitRate) {
    case 9600:
        jtagrate = PAR_BAUD_9600;
        break;
    case 19200:
        jtagrate = PAR_BAUD_19200;
        break;
    case 38400:
        jtagrate = PAR_BAUD_38400;
        break;
    case 57600:
        jtagrate = PAR_BAUD_57600;
        break;
    case 115200:
    default:
        jtagrate = PAR_BAUD_115200;
        break;
    }
    setJtagParameter(PAR_BAUD_RATE, &jtagrate, 1);
    changeLocalBitRate(newBitRate);
}

/** Set the JTAG ICE device descriptor data for specified device type **/
void Jtag2::setDeviceDescriptor(const jtag_device_def_type &dev) {
    const auto *dev_desc = [&]{
        if (is_xmega && has_full_xmega_support)
            return reinterpret_cast<const uchar*>(dev.xmega_dev_desc);
        else
            return reinterpret_cast<const uchar*>(&dev.jtag2_dev_desc2);
    }();

    try {
        uchar *response;
        int respSize;
        doJtagCommand(dev_desc, devdescrlen, response, respSize);
    } catch (jtag_exception &e) {
        debugOut("JTAG ICE: Failed to set device description: %s\n", e.what());
        throw;
    }
}

/** Attempt to synchronise with JTAG at specified bitrate **/
bool Jtag2::synchroniseAt(int bitrate) {
    debugOut("Attempting synchronisation at bitrate %d\n", bitrate);

    changeLocalBitRate(bitrate);

    int tries = 0;
    uchar *signonmsg, signoncmd = CMND_GET_SIGN_ON;
    int msgsize;

    while (tries < MAX_JTAG_SYNC_ATTEMPS) {
        if (sendJtagCommand(&signoncmd, 1, tries, signonmsg, msgsize, false)) {
            if (signonmsg[0] != RSP_SIGN_ON || msgsize <= 17)
                throw jtag_exception("Unexpected response to sign-on command");
            signonmsg[msgsize - 1] = '\0';
            statusOut("Found a device: %s\n", signonmsg + 16);
            statusOut("Serial number:  %02x:%02x:%02x:%02x:%02x:%02x\n", signonmsg[10],
                      signonmsg[11], signonmsg[12], signonmsg[13], signonmsg[14], signonmsg[15]);
            debugOut("JTAG ICE mkII sign-on message:\n");
            debugOut("Communications protocol version: %u\n", (unsigned)signonmsg[1]);
            debugOut("M_MCU:\n");
            debugOut("  boot-loader FW version:        %u\n", (unsigned)signonmsg[2]);
            debugOut("  firmware version:              %u.%02u\n", (unsigned)signonmsg[4],
                     (unsigned)signonmsg[3]);
            debugOut("  hardware version:              %u\n", (unsigned)signonmsg[5]);
            debugOut("S_MCU:\n");
            debugOut("  boot-loader FW version:        %u\n", (unsigned)signonmsg[6]);
            debugOut("  firmware version:              %u.%02u\n", (unsigned)signonmsg[8],
                     (unsigned)signonmsg[7]);
            debugOut("  hardware version:              %u\n", (unsigned)signonmsg[9]);

            // The AVR Dragon always uses the full device descriptor.
            if (emu_type == Emulator::JTAGICE2) {
                unsigned short fwver = ((unsigned)signonmsg[8] << 8) | (unsigned)signonmsg[7];

                // Check the S_MCU firmware version to know which format
                // of the device descriptor to send.
                auto FWVER = [](int major, int minor){
                    return (major<<8) | minor;
                };

                if (fwver < FWVER(3, 16)) {
                    devdescrlen -= 2;
                    debugOut("Warning: S_MCU firmware version might be "
                             "too old to work correctly\n ");
                } else if (fwver < FWVER(4, 0)) {
                    devdescrlen -= 2;
                }
            }

            has_full_xmega_support = (unsigned)signonmsg[8] >= 7;
            if (is_xmega) {
                if (has_full_xmega_support) {
                    devdescrlen = sizeof(xmega_device_desc_type);
                } else {
                    debugOut("Warning, S_MCU firmware version (%u.%02u) too old to work "
                            "correctly for Xmega devices, >= 7.x required\n",
                            (unsigned)signonmsg[8], (unsigned)signonmsg[7]);
                    softbp_only = true;
                }
            }

            delete[] signonmsg;
            return true;
        }
    }
    return false;
}

/** Attempt to synchronise with JTAG ICE at all possible bit rates **/
void Jtag2::startJtagLink() {
    constexpr int bitrates[] = {19200, 115200, 57600, 38400, 9600};

    for (const auto bitrate : bitrates) {
        if (synchroniseAt(bitrate)) {
            uchar val;

            signedIn = true;

            if (proto == Debugproto::JTAG && apply_nSRST) {
                val = 0x01;
                setJtagParameter(PAR_EXTERNAL_RESET, &val, 1);
            }

            const char *protoName = "unknown";
            switch (proto) {
            case Debugproto::JTAG:
                if (is_xmega)
                    val = EMULATOR_MODE_JTAG_XMEGA;
                else
                    val = EMULATOR_MODE_JTAG;
                protoName = "JTAG";
                break;

            case Debugproto::DW:
                val = EMULATOR_MODE_DEBUGWIRE;
                protoName = "debugWIRE";
                softbp_only = true;
                break;

            case Debugproto::PDI:
                val = EMULATOR_MODE_PDI;
                protoName = "PDI";
                break;
            }
            try {
                setJtagParameter(PAR_EMULATOR_MODE, &val, 1);
                debug_active = true;
            } catch (jtag2_io_exception &) {
                debugOut( "Failed to activate %s debugging protocol\n", protoName);
                throw;
            }

            return;
        }
    }

    throw jtag_exception("Failed to synchronise with the JTAG ICE (is it connected and powered?)");
}

/** Device automatic configuration
 Determines the device being controlled by the JTAG ICE and configures
 the system accordingly.

 May be overridden by command line parameter.

*/
void Jtag2::deviceAutoConfig() {
    uchar *resp;
    int respSize;

    // Auto config
    debugOut("Automatic device detection: ");

    /* Set daisy chain information */
    configDaisyChain();

    unsigned int device_id;
    /* Read in the JTAG device ID to determine device */
    if (proto == Debugproto::DW) {
        getJtagParameter(PAR_TARGET_SIGNATURE, resp, respSize);
        if (respSize < 3)
            throw jtag_exception("Invalid response size to PAR_TARGET_SIGNATURE");
        device_id = resp[1] | (resp[2] << 8);
        delete[] resp;
    } else if (proto == Debugproto::PDI) {
        resp = jtagRead(SIG_SPACE_ADDR_OFFSET, 3);
        device_id = resp[2] | (resp[1] << 8);
        delete[] resp;
    } else {
        getJtagParameter(PAR_JTAGID, resp, respSize);
        if (respSize < 5)
            throw jtag_exception("Invalid response size to PAR_TARGET_SIGNATURE");
        device_id = resp[1] | (resp[2] << 8) | (resp[3] << 16) | resp[4] << 24;
        delete[] resp;

        debugOut("JTAG id = 0x%0X : Ver = 0x%0x : Device = 0x%0x : Manuf = 0x%0x\n", device_id,
                 (device_id & 0xF0000000) >> 28, (device_id & 0x0FFFF000) >> 12,
                 (device_id & 0x00000FFE) >> 1);

        device_id = (device_id & 0x0FFFF000) >> 12;
    }

    deviceDef = &jtag_device_def_type::Find(device_id, expected_dev);
    setDeviceDescriptor(*deviceDef);
}

void Jtag2::initJtagBox() {
    statusOut("JTAG config starting.\n");

    if (!expected_dev.empty()) {
        const auto &pDevice = jtag_device_def_type::Find(0, expected_dev);
        // If a device name has been specified on the command-line,
        // this overrides the is_xmega setting.
        is_xmega = pDevice.xmega_dev_desc != nullptr;
    }

    startJtagLink();
    changeBitRate(115200);

    interruptProgram();

    deviceAutoConfig();

    deleteAllBreakpoints();

    statusOut("JTAG config complete.\n");
}

void Jtag2::initJtagOnChipDebugging(unsigned long bitrate) {
    statusOut("Preparing the target device for On Chip Debugging.\n");

    if (proto == Debugproto::JTAG) {
        uchar br;
        if (bitrate >= 6400000)
            br = 0;
        else if (bitrate >= 2800000)
            br = 1;
        else if (bitrate >= 20900)
            br = (unsigned char)(5.35e6 / (double)bitrate);
        else
            br = 255;
        // Set JTAG bitrate
        setJtagParameter(PAR_OCD_JTAG_CLK, &br, 1);
    }

    // Ensure on-chip debug enable fuse is enabled ie '0'

    // The enableProgramming()/disableProgramming() pair might seem to
    // be not needed (as the fuse read/write operations would enforce
    // going to programming mode anyway), but for devices that don't
    // feature an OCDEN fuse (i.e., Xmega devices),
    // jtagActivateOcdenFuse() bails out immediately.  At least with
    // firmware 7.13, the ICE seems to become totally upset then when
    // debugging an Xmega device without having went through a
    // programming-mode cycle before.  Upon a reset command, it
    // confirms the reset, but the target happily proceeds in RUNNING
    // state.
    enableProgramming();
    jtagActivateOcdenFuse();
    disableProgramming();

    resetProgram(false);
    uchar timers = 0; // stopped
    if (!is_xmega)
        setJtagParameter(PAR_TIMERS_RUNNING, &timers, 1);
}

void Jtag2::configDaisyChain() {
    if (dchain) {
        setJtagParameter(PAR_DAISY_CHAIN_INFO, reinterpret_cast<const uchar*>(&dchain), sizeof(dchain));
    }
}
