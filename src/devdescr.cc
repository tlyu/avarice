/*
 *	avarice - The "avarice" program.
 *	Copyright (C) 2001 Scott Finneran
 *      Copyright (C) 2002, 2003, 2004 Intel Corporation
 *	Copyright (C) 2005-2008 Joerg Wunsch
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
 * This file contains the JTAG ICE device descriptors of all supported
 * MCU types for both, the mkI and mkII protocol.
 *
 * $Id$
 */

#include "jtag.h"
#include "pragma.h"

#include <algorithm>
#include <cstring>
#include <cstdio>

#define fill_b4(u)                                                                                 \
    { ((u)&0xffUL), (((u)&0xff00UL) >> 8), (((u)&0xff0000UL) >> 16), (((u)&0xff000000UL) >> 24) }
#define fill_b2(u)                                                                                 \
    { ((u)&0xff), (((u)&0xff00) >> 8) }

/* Device descriptor magic from Atmel's documents. Let's hope it's more
   accurate than the rest of that text... */

// This is a sparse table:
PRAGMA_DIAG_IGNORED("-Wmissing-field-initializers")

namespace {
constexpr jtag_device_def_type deviceDefinitions[] =
    {
        {
            "atmega16",
            0x9403,
            128,
            128, // 16K flash
            4,
            128,  // 512 bytes EEPROM
            0x54, // 21 interrupt vectors
            DEVFL_NONE,
            atmega16_io_registers,
            false,
            0x03,
            0x8000, // fuses
            0x51,   // osccal
            2,      // OCD revision
            {JTAG_C_SET_DEVICE_DESCRIPTOR,
             {0xCF, 0xAF, 0xFF, 0xFF, 0xFE, 0xFF, 0xFF, 0xFF},
             {0x87, 0x26, 0xFF, 0xEF, 0xFE, 0xFF, 0x3F, 0xFA},
             {0x00, 0x00, 0x00, 0x00, 0x00, 0x2F, 0x00, 0x00},
             {0x00, 0x00, 0x00, 0x00, 0x00, 0x2F, 0x00, 0x00},
             {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
              0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
             {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
              0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
             {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
              0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
             {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
              0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
             0x31,
             0x57,
             0x00,
             {128, 0},
             0,
             {0x80, 0x1F, 0x00, 0x00},
             0,
             {JTAG_EOM}},
            {
                CMND_SET_DEVICE_DESCRIPTOR,
                {0xFF, 0x6F, 0xFF, 0xFF, 0xFE, 0xFF, 0xFD, 0xFF}, // ucReadIO
                {0X00, 0X00, 0X00, 0X00, 0X01, 0X00, 0X00, 0X00}, // ucReadIOShadow
                {0x8F, 0x26, 0xB6, 0xFD, 0xFE, 0xFF, 0xBD, 0xFA}, // ucWriteIO
                {0X00, 0X00, 0X00, 0X00, 0X01, 0X00, 0X00, 0X00}, // ucWriteIOShadow
                {0},                                              // ucReadExtIO
                {0},                                              // ucReadIOExtShadow
                {0},                                              // ucWriteExtIO
                {0},                                              // ucWriteIOExtShadow
                0x31,                                             // ucIDRAddress
                0x57,                                             // ucSPMCRAddress
                0,                                                // ucRAMPZAddress
                fill_b2(128),                                     // uiFlashPageSize
                4,                                                // ucEepromPageSize
                fill_b4(0x1F80),                                  // ulBootAddress
                fill_b2(0),                                       // uiUpperExtIOLoc
                fill_b4(0x4000),                                  // ulFlashSize
                {0},                                              // ucEepromInst
                {0},                                              // ucFlashInst
                0x3e,                                             // ucSPHaddr
                0x3d,                                             // ucSPLaddr
                fill_b2(0x4000 / 128),                            // uiFlashpages
                0,                                                // ucDWDRAddress
                0,                                                // ucDWBasePC
                1,                                                // ucAllowFullPageBitstream
                fill_b2(0),    // uiStartSmallestBootLoaderSection
                1,             // EnablePageProgramming
                0,             // ucCacheType
                fill_b2(0x60), // uiSramStartAddr
                0,             // ucResetType
                0,             // ucPCMaskExtended
                0,             // ucPCMaskHigh
                0,             // ucEindAddress
                fill_b2(0x1c), // EECRAddress
            },
            {0}, // Xmega device descr.
        },
        {
            "atmega162",
            0x9404,
            128,
            128, // 16K flash
            4,
            128,  // 512 bytes EEPROM
            0x70, // 28 interrupt vectors
            DEVFL_NONE,
            atmega162_io_registers,
            false,
            0x07,
            0x8000, // fuses
            0x24,   // osccal
            2,      // OCD revision
            {JTAG_C_SET_DEVICE_DESCRIPTOR,
             {0xF7, 0x6F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF},
             {0xF3, 0x66, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFA},
             {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
             {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
             {0x02, 0x18, 0x00, 0x30, 0xF3, 0x0F, 0x00, 0x00, 0x00, 0x00,
              0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
             {0x02, 0x18, 0x00, 0x20, 0xF3, 0x0F, 0x00, 0x00, 0x00, 0x00,
              0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
             {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
              0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
             {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
              0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
             0x04,
             0x57,
             0x00,
             {128, 0},
             4,
             {0x80, 0x1F, 0x00, 0x00},
             0x8B,
             {JTAG_EOM}},
            {
                CMND_SET_DEVICE_DESCRIPTOR,
                {0xE7, 0x6F, 0xFF, 0xFF, 0xFE, 0xFF, 0xFF, 0xEF}, // ucReadIO
                {0xC3, 0x26, 0xB6, 0xFD, 0xFE, 0xFF, 0xFF, 0xEA}, // ucReadIOShadow
                {0X00, 0X00, 0X00, 0X00, 0X01, 0X00, 0X00, 0X10}, // ucWriteIO
                {0X00, 0X00, 0X00, 0X00, 0X01, 0X00, 0X00, 0X10}, // ucWriteIOShadow
                {0},                                              // ucReadExtIO
                {0},                                              // ucReadIOExtShadow
                {0},                                              // ucWriteExtIO
                {0},                                              // ucWriteIOExtShadow
                0x04,                                             // ucIDRAddress
                0x57,                                             // ucSPMCRAddress
                0,                                                // ucRAMPZAddress
                fill_b2(128),                                     // uiFlashPageSize
                4,                                                // ucEepromPageSize
                fill_b4(0x1F80),                                  // ulBootAddress
                fill_b2(0xBB),                                    // uiUpperExtIOLoc
                fill_b4(0x4000),                                  // ulFlashSize
                {0},                                              // ucEepromInst
                {0},                                              // ucFlashInst
                0x3e,                                             // ucSPHaddr
                0x3d,                                             // ucSPLaddr
                fill_b2(0x4000 / 128),                            // uiFlashpages
                0,                                                // ucDWDRAddress
                0,                                                // ucDWBasePC
                1,                                                // ucAllowFullPageBitstream
                fill_b2(0),     // uiStartSmallestBootLoaderSection
                1,              // EnablePageProgramming
                0,              // ucCacheType
                fill_b2(0x100), // uiSramStartAddr
                0,              // ucResetType
                0,              // ucPCMaskExtended
                0,              // ucPCMaskHigh
                0,              // ucEindAddress
                fill_b2(0x1c),  // EECRAddress
            },
            {0}, // Xmega device descr.
        },
        {
            "atmega169",
            0x9405,
            128,
            128, // 16K flash
            4,
            128,  // 512 bytes EEPROM
            0x5c, // 23 interrupt vectors
            DEVFL_NONE,
            atmega169_io_registers,
            false,
            0x07,
            0x8000, // fuses
            0x66,   // osccal
            2,      // OCD revision
            {JTAG_C_SET_DEVICE_DESCRIPTOR,
             {0xFF, 0xFF, 0xFF, 0xF0, 0xDF, 0x3C, 0xBB, 0xE0},
             {0xB6, 0x6D, 0x1B, 0xE0, 0xDF, 0x3C, 0xBA, 0xE0},
             {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
             {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
             {0x43, 0xDA, 0x00, 0xFF, 0xF7, 0x0F, 0x00, 0x00, 0x00, 0x00,
              0x4D, 0x07, 0x37, 0x00, 0x00, 0x00, 0xF0, 0xF0, 0xDE, 0x7B},
             {0x43, 0xDA, 0x00, 0xFF, 0xF7, 0x0F, 0x00, 0x00, 0x00, 0x00,
              0x4D, 0x05, 0x36, 0x00, 0x00, 0x00, 0xE0, 0xF0, 0xDE, 0x7B},
             {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
              0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
             {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
              0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
             0x31,
             0x57,
             0x00,
             {128, 0},
             4,
             {0x80, 0x1F, 0x00, 0x00},
             0xFE,
             {JTAG_EOM}},
            {
                CMND_SET_DEVICE_DESCRIPTOR,
                {0xFF, 0xFF, 0xFF, 0xF0, 0xDF, 0x3C, 0xB9, 0xE0}, // ucReadIO
                {0},                                              // ucReadIOShadow
                {0xB6, 0x6D, 0x1B, 0xE0, 0xDF, 0x1C, 0xB8, 0xE0}, // ucWriteIO
                {0},                                              // ucWriteIOShadow
                {0x53, 0xDA, 0x01, 0xDF, 0xF7, 0x0F, 0x00, 0x00, 0x00, 0x00,
                 0x4D, 0x07, 0x37, 0x00, 0x00, 0x00, 0xF0, 0xF0, 0xDE, 0x7B}, // ucReadExtIO
                {0},                                                          // ucReadIOExtShadow
                {0x53, 0xDA, 0x01, 0xD8, 0xF7, 0x0F, 0x00, 0x00, 0x00, 0x00,
                 0x4D, 0x05, 0x36, 0x00, 0x00, 0x00, 0xE0, 0xF0, 0xDE, 0x7B}, // ucWriteExtIO
                {0},                                                          // ucWriteIOExtShadow
                0x31,                                                         // ucIDRAddress
                0x57,                                                         // ucSPMCRAddress
                0,                                                            // ucRAMPZAddress
                fill_b2(128),                                                 // uiFlashPageSize
                4,                                                            // ucEepromPageSize
                fill_b4(0x1F80),                                              // ulBootAddress
                fill_b2(0xFE),                                                // uiUpperExtIOLoc
                fill_b4(0x4000),                                              // ulFlashSize
                {0},                                                          // ucEepromInst
                {0},                                                          // ucFlashInst
                0x3e,                                                         // ucSPHaddr
                0x3d,                                                         // ucSPLaddr
                fill_b2(0x4000 / 128),                                        // uiFlashpages
                0,                                                            // ucDWDRAddress
                0,                                                            // ucDWBasePC
                1,              // ucAllowFullPageBitstream
                fill_b2(0),     // uiStartSmallestBootLoaderSection
                1,              // EnablePageProgramming
                0,              // ucCacheType
                fill_b2(0x100), // uiSramStartAddr
                0,              // ucResetType
                0,              // ucPCMaskExtended
                0,              // ucPCMaskHigh
                0,              // ucEindAddress
                fill_b2(0x1f),  // EECRAddress
            },
            {0}, // Xmega device descr.
        },
        {
            "atmega323",
            0x9501,
            128,
            256, // 32K flash
            4,
            256,  // 1K EEPROM
            0x50, // 20 interrupt vectors
            DEVFL_NONE,
            atmega323_io_registers,
            false,
            0x03,
            0x8000, // fuses
            0x51,   // osccal
            2,      // OCD revision
            {JTAG_C_SET_DEVICE_DESCRIPTOR,
             {0xCF, 0xAF, 0xFF, 0xFF, 0xFE, 0xFF, 0xFF, 0xFF},
             {0x87, 0x26, 0xFF, 0xEF, 0xFE, 0xFF, 0x3F, 0xFA},
             {0x00, 0x00, 0x00, 0x00, 0x00, 0x2F, 0x00, 0x00},
             {0x00, 0x00, 0x00, 0x00, 0x00, 0x2F, 0x00, 0x00},
             {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
              0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
             {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
              0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
             {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
              0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
             {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
              0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
             0x31,
             0x57,
             0x00,
             {128, 0},
             0,
             {0x00, 0x3F, 0x00, 0x00},
             0,
             {JTAG_EOM}},
            {
                CMND_SET_DEVICE_DESCRIPTOR,
                {0xFF, 0x6F, 0xFF, 0xFF, 0xFE, 0xFF, 0xFD, 0xFF}, // ucReadIO
                {0X00, 0X00, 0X00, 0X00, 0X01, 0X00, 0X00, 0X00}, // ucReadIOShadow
                {0x8F, 0x26, 0xB6, 0xFD, 0xFE, 0xFF, 0xBD, 0xFA}, // ucWriteIO
                {0X00, 0X00, 0X00, 0X00, 0X01, 0X00, 0X00, 0X00}, // ucWriteIOShadow
                {0},                                              // ucReadExtIO
                {0},                                              // ucReadIOExtShadow
                {0},                                              // ucWriteExtIO
                {0},                                              // ucWriteIOExtShadow
                0x31,                                             // ucIDRAddress
                0x57,                                             // ucSPMCRAddress
                0,                                                // ucRAMPZAddress
                fill_b2(128),                                     // uiFlashPageSize
                4,                                                // ucEepromPageSize
                fill_b4(0x3F00),                                  // ulBootAddress
                fill_b2(0),                                       // uiUpperExtIOLoc
                fill_b4(0x8000),                                  // ulFlashSize
                {0},                                              // ucEepromInst
                {0},                                              // ucFlashInst
                0x3e,                                             // ucSPHaddr
                0x3d,                                             // ucSPLaddr
                fill_b2(0x8000 / 128),                            // uiFlashpages
                0,                                                // ucDWDRAddress
                0,                                                // ucDWBasePC
                1,                                                // ucAllowFullPageBitstream
                fill_b2(0),    // uiStartSmallestBootLoaderSection
                1,             // EnablePageProgramming
                0,             // ucCacheType
                fill_b2(0x60), // uiSramStartAddr
                0,             // ucResetType
                0,             // ucPCMaskExtended
                0,             // ucPCMaskHigh
                0,             // ucEindAddress
                fill_b2(0x1c), // EECRAddress
            },
            {0}, // Xmega device descr.
        },
        {
            "atmega32",
            0x9502,
            128,
            256, // 32K flash
            4,
            256,  // 1K EEPROM
            0x54, // 21 interrupt vectors
            DEVFL_NONE,
            atmega32_io_registers,
            false,
            0x03,
            0x8000, // fuses
            0x51,   // osccal
            2,      // OCD revision
            {JTAG_C_SET_DEVICE_DESCRIPTOR,
             {0xFF, 0x6F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF},
             {0xFF, 0x66, 0xFF, 0xFF, 0xFF, 0xFF, 0xBF, 0xFA},
             {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
             {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
             {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
              0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
             {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
              0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
             {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
              0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
             {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
              0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
             0x31,
             0x57,
             0x00,
             {128, 0},
             4,
             {0x00, 0x3F, 0x00, 0x00},
             0,
             {JTAG_EOM}},
            {
                CMND_SET_DEVICE_DESCRIPTOR,
                {0xFF, 0x6F, 0xFF, 0xFF, 0xFE, 0xFF, 0xFD, 0xFF}, // ucReadIO
                {0X00, 0X00, 0X00, 0X00, 0X01, 0X00, 0X00, 0X00}, // ucReadIOShadow
                {0x8F, 0x26, 0xB6, 0xFD, 0xFE, 0xFF, 0xBD, 0xFA}, // ucWriteIO
                {0X00, 0X00, 0X00, 0X00, 0X01, 0X00, 0X00, 0X00}, // ucWriteIOShadow
                {0},                                              // ucReadExtIO
                {0},                                              // ucReadIOExtShadow
                {0},                                              // ucWriteExtIO
                {0},                                              // ucWriteIOExtShadow
                0x31,                                             // ucIDRAddress
                0x57,                                             // ucSPMCRAddress
                0,                                                // ucRAMPZAddress
                fill_b2(128),                                     // uiFlashPageSize
                4,                                                // ucEepromPageSize
                fill_b4(0x3F00),                                  // ulBootAddress
                fill_b2(0),                                       // uiUpperExtIOLoc
                fill_b4(0x8000),                                  // ulFlashSize
                {0},                                              // ucEepromInst
                {0},                                              // ucFlashInst
                0x3e,                                             // ucSPHaddr
                0x3d,                                             // ucSPLaddr
                fill_b2(0x8000 / 128),                            // uiFlashpages
                0,                                                // ucDWDRAddress
                0,                                                // ucDWBasePC
                1,                                                // ucAllowFullPageBitstream
                fill_b2(0),    // uiStartSmallestBootLoaderSection
                1,             // EnablePageProgramming
                0,             // ucCacheType
                fill_b2(0x60), // uiSramStartAddr
                0,             // ucResetType
                0,             // ucPCMaskExtended
                0,             // ucPCMaskHigh
                0,             // ucEindAddress
                fill_b2(0x1c), // EECRAddress
            },
            {0}, // Xmega device descr.
        },
        {
            "atmega64",
            0x9602,
            256,
            256, // 64K flash
            8,
            256,  // 2K bytes EEPROM
            0x8c, // 35 interrupt vectors
            DEVFL_NONE,
            atmega64_io_registers,
            false,
            0x07,
            0x8000, // fuses
            0x6f,   // osccal
            2,      // OCD revision
            {JTAG_C_SET_DEVICE_DESCRIPTOR,
             {0xCF, 0x2F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF},
             {0xCF, 0x27, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE},
             {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
             {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
             {0x3E, 0xB5, 0x1F, 0x37, 0xFF, 0x1F, 0x21, 0x2F, 0x00, 0x00,
              0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
             {0x3E, 0xB5, 0x0F, 0x27, 0xFF, 0x1F, 0x21, 0x27, 0x00, 0x00,
              0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
             {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
              0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
             {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
              0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
             0x22,
             0x68,
             0x00,
             {0, 1},
             8,
             {0x00, 0x7E, 0x00, 0x00},
             0x9D,
             {JTAG_EOM}},
            {
                CMND_SET_DEVICE_DESCRIPTOR,
                {0xFF, 0x6F, 0xFF, 0xFF, 0xFB, 0xFF, 0xFF, 0xF7},            // ucReadIO
                {0},                                                         // ucReadIOShadow
                {0x8C, 0x26, 0xB6, 0xFD, 0xFB, 0xFF, 0xBF, 0xF6},            // ucWriteIO
                {0},                                                         // ucWriteIOShadow
                {0x3E, 0xB5, 0x1F, 0x37, 0xFF, 0x5F, 0x21, 0x2F, /* ... */}, // ucReadExtIO
                {0},                                                         // ucReadIOExtShadow
                {0x36, 0xB5, 0x0F, 0x27, 0xFF, 0x5F, 0x21, 0x27, /* ... */}, // ucWriteExtIO
                {0},                                                         // ucWriteIOExtShadow
                0x22,                                                        // ucIDRAddress
                0x68,                                                        // ucSPMCRAddress
                0,                                                           // ucRAMPZAddress
                fill_b2(256),                                                // uiFlashPageSize
                8,                                                           // ucEepromPageSize
                fill_b4(0x7E00),                                             // ulBootAddress
                fill_b2(0x9D),                                               // uiUpperExtIOLoc
                fill_b4(0x10000),                                            // ulFlashSize
                {0},                                                         // ucEepromInst
                {0},                                                         // ucFlashInst
                0x3e,                                                        // ucSPHaddr
                0x3d,                                                        // ucSPLaddr
                fill_b2(0x10000 / 256),                                      // uiFlashpages
                0,                                                           // ucDWDRAddress
                0,                                                           // ucDWBasePC
                1,              // ucAllowFullPageBitstream
                fill_b2(0),     // uiStartSmallestBootLoaderSection
                1,              // EnablePageProgramming
                0,              // ucCacheType
                fill_b2(0x100), // uiSramStartAddr
                0,              // ucResetType
                0,              // ucPCMaskExtended
                0,              // ucPCMaskHigh
                0,              // ucEindAddress
                fill_b2(0x1c),  // EECRAddress
            },
            {0}, // Xmega device descr.
        },
        {
            "atmega128",
            0x9702,
            256,
            512, // 128K flash
            8,
            512,  // 4K bytes EEPROM
            0x8c, // 35 interrupt vectors
            DEVFL_NO_SOFTBP,
            atmega128_io_registers,
            false,
            0x07,
            0x8000, // fuses
            0x6f,   // osccal
            1,      // OCD revision
            {JTAG_C_SET_DEVICE_DESCRIPTOR,
             {0xCF, 0x2F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF},
             {0xCF, 0x27, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE},
             {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
             {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
             {0x3E, 0xB5, 0x1F, 0x37, 0xFF, 0x1F, 0x21, 0x2F, 0x00, 0x00,
              0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
             {0x3E, 0xB5, 0x0F, 0x27, 0xFF, 0x1F, 0x21, 0x27, 0x00, 0x00,
              0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
             {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
              0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
             {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
              0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
             0x22,
             0x68,
             0x3B,
             {0, 1},
             8,
             {0x00, 0xFE, 0x00, 0x00},
             0x9D,
             {JTAG_EOM}},
            {
                CMND_SET_DEVICE_DESCRIPTOR,
                {0xFF, 0x6F, 0xFF, 0xFF, 0xFB, 0xFF, 0xFF, 0xFF},            // ucReadIO
                {0},                                                         // ucReadIOShadow
                {0x8C, 0x26, 0xB6, 0xFD, 0xFB, 0xFF, 0xBF, 0xFE},            // ucWriteIO
                {0},                                                         // ucWriteIOShadow
                {0x3E, 0xB5, 0x1F, 0x37, 0xFF, 0x1F, 0x21, 0x2F, /* ... */}, // ucReadExtIO
                {0},                                                         // ucReadIOExtShadow
                {0x36, 0xB5, 0x0F, 0x27, 0xFF, 0x1F, 0x21, 0x27, /* ... */}, // ucWriteExtIO
                {0},                                                         // ucWriteIOExtShadow
                0x22,                                                        // ucIDRAddress
                0x68,                                                        // ucSPMCRAddress
                0x3B,                                                        // ucRAMPZAddress
                fill_b2(256),                                                // uiFlashPageSize
                8,                                                           // ucEepromPageSize
                fill_b4(0xFE00),                                             // ulBootAddress
                fill_b2(0x9D),                                               // uiUpperExtIOLoc
                fill_b4(0x20000),                                            // ulFlashSize
                {0},                                                         // ucEepromInst
                {0},                                                         // ucFlashInst
                0x3e,                                                        // ucSPHaddr
                0x3d,                                                        // ucSPLaddr
                fill_b2(0x20000 / 256),                                      // uiFlashpages
                0,                                                           // ucDWDRAddress
                0,                                                           // ucDWBasePC
                1,              // ucAllowFullPageBitstream
                fill_b2(0),     // uiStartSmallestBootLoaderSection
                1,              // EnablePageProgramming
                0,              // ucCacheType
                fill_b2(0x100), // uiSramStartAddr
                0,              // ucResetType
                0,              // ucPCMaskExtended
                0,              // ucPCMaskHigh
                0,              // ucEindAddress
                fill_b2(0x1c),  // EECRAddress
            },
            {0}, // Xmega device descr.
        },
        {
            "at90can128",
            0x9781,
            256,
            512, // 128K flash
            8,
            512,  // 4K bytes EEPROM
            0x94, // 37 interrupt vectors
            DEVFL_NONE,
            at90can128_io_registers,
            false,
            0x07,
            0x8000, // fuses
            0x66,   // osccal
            3,      // OCD revision
            {JTAG_C_SET_DEVICE_DESCRIPTOR,
             {0xFF, 0xFF, 0xFF, 0xF1, 0xDF, 0x7C, 0xBB, 0xE8},
             {0xFF, 0xFF, 0xFF, 0xF1, 0xDF, 0x7C, 0xBB, 0xE8},
             {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
             {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
             {0x43, 0xC3, 0x33, 0xBF, 0xF7, 0x3F, 0xF7, 0x3F, 0x00, 0x00,
              0x4D, 0x1F, 0x77, 0x77, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0x07},
             {0x43, 0xC3, 0x33, 0xBC, 0x77, 0x77, 0xF7, 0x3F, 0x00, 0x00,
              0x4D, 0x1F, 0x00, 0x00, 0x00, 0xCD, 0x3C, 0xF0, 0xFF, 0x04},
             {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
              0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
             {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
              0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
             0x22,
             0x57,
             0x3B,
             {0, 1},
             8,
             {0x00, 0xFE, 0x00, 0x00},
             0xFA,
             {JTAG_EOM}},
            {
                CMND_SET_DEVICE_DESCRIPTOR,
                {0xFF, 0xFF, 0xFF, 0xF1, 0xDF, 0x3C, 0xB9, 0xE8}, // ucReadIO
                {0},                                              // ucReadIOShadow
                {0xB6, 0x6D, 0x1B, 0xE0, 0xDF, 0x1C, 0xB8, 0xE8}, // ucWriteIO
                {0},                                              // ucWriteIOShadow
                {0x43, 0xC6, 0x33, 0xDF, 0xF7, 0x3F, 0xF7, 0x3F, 0x00, 0x00,
                 0x4D, 0x1F, 0x37, 0x37, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0x07}, // ucReadExtIO
                {0},                                                          // ucReadIOExtShadow
                {0x43, 0xC6, 0x33, 0xD8, 0xF7, 0x3F, 0xF7, 0x3F, 0x00, 0x00,
                 0x4D, 0x0F, 0x36, 0x36, 0x00, 0xC9, 0x3C, 0xF0, 0xFF, 0x04}, // ucWriteExtIO
                {0},                                                          // ucWriteIOExtShadow
                0x31,                                                         // ucIDRAddress
                0x57,                                                         // ucSPMCRAddress
                0x3B,                                                         // ucRAMPZAddress
                fill_b2(256),                                                 // uiFlashPageSize
                8,                                                            // ucEepromPageSize
                fill_b4(0xFE00),                                              // ulBootAddress
                fill_b2(0xFA),                                                // uiUpperExtIOLoc
                fill_b4(0x20000),                                             // ulFlashSize
                {0},                                                          // ucEepromInst
                {0},                                                          // ucFlashInst
                0x3e,                                                         // ucSPHaddr
                0x3d,                                                         // ucSPLaddr
                fill_b2(0x20000 / 256),                                       // uiFlashpages
                0,                                                            // ucDWDRAddress
                0,                                                            // ucDWBasePC
                0,              // ucAllowFullPageBitstream
                fill_b2(0),     // uiStartSmallestBootLoaderSection
                1,              // EnablePageProgramming
                0,              // ucCacheType
                fill_b2(0x100), // uiSramStartAddr
                0,              // ucResetType
                0,              // ucPCMaskExtended
                0,              // ucPCMaskHigh
                0,              // ucEindAddress
                fill_b2(0x1f),  // EECRAddress
            },
            {0}, // Xmega device descr.
        },
        {
            "atmega164p",
            0x940a,
            128,
            128, // 16384 bytes flash
            4,
            128,    // 512 bytes EEPROM
            31 * 4, // 31 interrupt vectors
            DEVFL_MKII_ONLY,
            atmega164p_io_registers,
            false,
            0x07,
            0x8000, // fuses
            0x66,   // osccal
            3,      // OCD revision
            {
                0 // no mkI support
            },
            {
                CMND_SET_DEVICE_DESCRIPTOR,
                {0xFF, 0x0F, 0xE0, 0xF8, 0xFF, 0x3D, 0xB9, 0xE8}, // ucReadIO
                {0X00, 0X00, 0X00, 0X00, 0X01, 0X00, 0X00, 0X00}, // ucReadIOShadow
                {0xB6, 0x0D, 0x00, 0xE0, 0xFF, 0x1D, 0xB8, 0xE8}, // ucWriteIO
                {0X00, 0X00, 0X00, 0X00, 0X01, 0X00, 0X00, 0X00}, // ucWriteIOShadow
                {0x53, 0xFB, 0x09, 0xDF, 0xF3, 0x0F, 0x00, 0x00, 0x00, 0x00,
                 0x5F, 0x3F, 0x37, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // ucReadExtIO
                {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // ucReadIOExtShadow
                {0x51, 0xFB, 0x09, 0xD8, 0xF3, 0x0F, 0x00, 0x00, 0x00, 0x00,
                 0x5F, 0x2F, 0x36, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // ucWriteExtIO
                {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // ucWriteIOExtShadow
                0x31,                                                         // ucIDRAddress
                0x57,                                                         // ucSPMCRAddress
                0x3B,                                                         // ucRAMPZAddress
                fill_b2(128),                                                 // uiFlashPageSize
                4,                                                            // ucEepromPageSize
                fill_b4(0x1f80),                                              // ulBootAddress
                fill_b2(0x00C6),                                              // uiUpperExtIOLoc
                fill_b4(16384),                                               // ulFlashSize
                {0x00},                                                       // ucEepromInst
                {0x00},                                                       // ucFlashInst
                0x3E,                                                         // ucSPHaddr
                0x3D,                                                         // ucSPLaddr
                fill_b2(16384 / 128),                                         // uiFlashpages
                0x00,                                                         // ucDWDRAddress
                0x00,                                                         // ucDWBasePC
                0x00,           // ucAllowFullPageBitstream
                fill_b2(0x00),  // uiStartSmallestBootLoaderSection
                1,              // EnablePageProgramming
                0,              // ucCacheType
                fill_b2(0x100), // uiSramStartAddr
                0,              // ucResetType
                0,              // ucPCMaskExtended
                0,              // ucPCMaskHigh
                0,              // ucEindAddress
                fill_b2(0x1F),  // EECRAddress
            },
            {0}, // Xmega device descr.
        },
        {
            "atmega324p",
            0x9508,
            128,
            256, // 32768 bytes flash
            4,
            256,    // 1024 bytes EEPROM
            31 * 4, // 31 interrupt vectors
            DEVFL_MKII_ONLY,
            atmega324p_io_registers,
            false,
            0x07,
            0x8000, // fuses
            0x66,   // osccal
            3,      // OCD revision
            {
                0 // no mkI support
            },
            {
                CMND_SET_DEVICE_DESCRIPTOR,
                {0xFF, 0x0F, 0xE0, 0xF8, 0xFF, 0x3D, 0xB9, 0xE8}, // ucReadIO
                {0X00, 0X00, 0X00, 0X00, 0X01, 0X00, 0X00, 0X00}, // ucReadIOShadow
                {0xB6, 0x0D, 0x00, 0xE0, 0xFF, 0x1D, 0xB8, 0xE8}, // ucWriteIO
                {0X00, 0X00, 0X00, 0X00, 0X01, 0X00, 0X00, 0X00}, // ucWriteIOShadow
                {0x53, 0xFB, 0x09, 0xDF, 0xF3, 0x0F, 0x00, 0x00, 0x00, 0x00,
                 0x5F, 0x3F, 0x37, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // ucReadExtIO
                {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // ucReadIOExtShadow
                {0x51, 0xFB, 0x09, 0xD8, 0xF3, 0x0F, 0x00, 0x00, 0x00, 0x00,
                 0x5F, 0x2F, 0x36, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // ucWriteExtIO
                {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // ucWriteIOExtShadow
                0x31,                                                         // ucIDRAddress
                0x57,                                                         // ucSPMCRAddress
                0x3B,                                                         // ucRAMPZAddress
                fill_b2(128),                                                 // uiFlashPageSize
                4,                                                            // ucEepromPageSize
                fill_b4(0x3f00),                                              // ulBootAddress
                fill_b2(0x00C6),                                              // uiUpperExtIOLoc
                fill_b4(32768),                                               // ulFlashSize
                {0x00},                                                       // ucEepromInst
                {0x00},                                                       // ucFlashInst
                0x3E,                                                         // ucSPHaddr
                0x3D,                                                         // ucSPLaddr
                fill_b2(32768 / 128),                                         // uiFlashpages
                0x00,                                                         // ucDWDRAddress
                0x00,                                                         // ucDWBasePC
                0x00,           // ucAllowFullPageBitstream
                fill_b2(0x00),  // uiStartSmallestBootLoaderSection
                1,              // EnablePageProgramming
                0,              // ucCacheType
                fill_b2(0x100), // uiSramStartAddr
                0,              // ucResetType
                0,              // ucPCMaskExtended
                0,              // ucPCMaskHigh
                0,              // ucEindAddress
                fill_b2(0x1F),  // EECRAddress
            },
            {0}, // Xmega device descr.
        },
        {
            "atmega644",
            0x9609,
            256,
            256, // 64K flash
            8,
            256,    // 2K bytes EEPROM
            28 * 4, // 28 interrupt vectors
            DEVFL_MKII_ONLY,
            atmega644_io_registers,
            false,
            0x07,
            0x8000, // fuses
            0x66,   // osccal
            3,      // OCD revision
            {
                0 // no mkI support
            },
            {
                CMND_SET_DEVICE_DESCRIPTOR,
                {0xFF, 0x0F, 0xE0, 0xF8, 0xFF, 0x3D, 0xB9, 0xE8}, // ucReadIO
                {0},                                              // ucReadIOShadow
                {0xB6, 0x0D, 0x00, 0xE0, 0xFF, 0x1D, 0xB8, 0xE8}, // ucWriteIO
                {0},                                              // ucWriteIOShadow
                {0x53, 0xFB, 0x9, 0xDF, 0xF7, 0xF, 0x0, 0x0, 0x0, 0x0, 0x5F, 0x3F,
                 0x37}, // ucReadExtIO
                {0},    // ucReadIOExtShadow
                {0x53, 0xFB, 0x9, 0xD8, 0xF7, 0xF, 0x0, 0x0, 0x0, 0x0, 0x5F, 0x2F,
                 0x36},                 // ucWriteExtIO
                {0},                    // ucWriteIOExtShadow
                0x31,                   // ucIDRAddress
                0x57,                   // ucSPMCRAddress
                0,                      // ucRAMPZAddress
                fill_b2(256),           // uiFlashPageSize
                8,                      // ucEepromPageSize
                fill_b4(0x7E00),        // ulBootAddress
                fill_b2(0xC6),          // uiUpperExtIOLoc
                fill_b4(0x10000),       // ulFlashSize
                {0},                    // ucEepromInst
                {0},                    // ucFlashInst
                0x3e,                   // ucSPHaddr
                0x3d,                   // ucSPLaddr
                fill_b2(0x10000 / 256), // uiFlashpages
                0,                      // ucDWDRAddress
                0,                      // ucDWBasePC
                0,                      // ucAllowFullPageBitstream
                fill_b2(0),             // uiStartSmallestBootLoaderSection
                1,                      // EnablePageProgramming
                0,                      // ucCacheType
                fill_b2(0x100),         // uiSramStartAddr
                0,                      // ucResetType
                0,                      // ucPCMaskExtended
                0,                      // ucPCMaskHigh
                0,                      // ucEindAddress
                fill_b2(0x1f),          // EECRAddress
            },
            {0}, // Xmega device descr.
        },
        {
            "atmega325",
            0x9505,
            128,
            256, // 32768 bytes flash
            4,
            256,    // 1024 bytes EEPROM
            22 * 4, // 22 interrupt vectors
            DEVFL_MKII_ONLY,
            atmega325_io_registers,
            false,
            0x07,
            0x8000, // fuses
            0x66,   // osccal
            3,      // OCD revision
            {
                0 // no mkI support
            },
            {
                CMND_SET_DEVICE_DESCRIPTOR,
                {0xFF, 0xFF, 0xFF, 0xF0, 0xDF, 0x3C, 0xB9, 0xE0}, // ucReadIO
                {0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00}, // ucReadIOShadow
                {0xB6, 0x6D, 0x1B, 0xE0, 0xDF, 0x1C, 0xB8, 0xE0}, // ucWriteIO
                {0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00}, // ucWriteIOShadow
                {0x53, 0xDA, 0x01, 0xDF, 0xF7, 0x0F, 0x00, 0x00, 0x00, 0x00,
                 0x4D, 0x07, 0x37, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // ucReadExtIO
                {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // ucReadIOExtShadow
                {0x53, 0xDA, 0x01, 0xD8, 0xF7, 0x0F, 0x00, 0x00, 0x00, 0x00,
                 0x4D, 0x05, 0x36, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // ucWriteExtIO
                {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // ucWriteIOExtShadow
                0x31,                                                         // ucIDRAddress
                0x57,                                                         // ucSPMCRAddress
                0,                                                            // ucRAMPZAddress
                fill_b2(128),                                                 // uiFlashPageSize
                4,                                                            // ucEepromPageSize
                fill_b4(0x3F00),                                              // ulBootAddress
                fill_b2(0xC6),                                                // uiUpperExtIOLoc
                fill_b4(32768),                                               // ulFlashSize
                {0x00},                                                       // ucEepromInst
                {0x00},                                                       // ucFlashInst
                0x3E,                                                         // ucSPHaddr
                0x3D,                                                         // ucSPLaddr
                fill_b2(32768 / 128),                                         // uiFlashpages
                0x00,                                                         // ucDWDRAddress
                0x40,                                                         // ucDWBasePC
                0x00,           // ucAllowFullPageBitstream
                fill_b2(0x00),  // uiStartSmallestBootLoaderSection
                1,              // EnablePageProgramming
                0,              // ucCacheType
                fill_b2(0x100), // uiSramStartAddr
                0,              // ucResetType
                0,              // ucPCMaskExtended
                0x40,           // ucPCMaskHigh
                0,              // ucEindAddress
                fill_b2(0x1F),  // EECRAddress
            },
            {0}, // Xmega device descr.
        },
        {
            "atmega3250",
            0x9506,
            128,
            256, // 32768 bytes flash
            4,
            256,    // 1024 bytes EEPROM
            25 * 4, // 25 interrupt vectors
            DEVFL_MKII_ONLY,
            atmega3250_io_registers,
            false,
            0x07,
            0x8000, // fuses
            0x66,   // osccal
            3,      // OCD revision
            {
                0 // no mkI support
            },
            {
                CMND_SET_DEVICE_DESCRIPTOR,
                {0xFF, 0xFF, 0xFF, 0xF0, 0xDF, 0x3C, 0xB9, 0xE0}, // ucReadIO
                {0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00}, // ucReadIOShadow
                {0xB6, 0x6D, 0x1B, 0xE0, 0xDF, 0x1C, 0xB8, 0xE0}, // ucWriteIO
                {0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00}, // ucWriteIOShadow
                {0x53, 0xFA, 0x09, 0xDF, 0xF7, 0x0F, 0x00, 0x00, 0x00, 0x00,
                 0x4D, 0x07, 0x37, 0x00, 0x00, 0x3F, 0x00, 0x00, 0x00, 0x00}, // ucReadExtIO
                {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // ucReadIOExtShadow
                {0x53, 0xFA, 0x09, 0xD8, 0xF7, 0x0F, 0x00, 0x00, 0x00, 0x00,
                 0x4D, 0x05, 0x36, 0x00, 0x00, 0x3F, 0x00, 0x00, 0x00, 0x00}, // ucWriteExtIO
                {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // ucWriteIOExtShadow
                0x31,                                                         // ucIDRAddress
                0x57,                                                         // ucSPMCRAddress
                0,                                                            // ucRAMPZAddress
                fill_b2(128),                                                 // uiFlashPageSize
                4,                                                            // ucEepromPageSize
                fill_b4(0x3F00),                                              // ulBootAddress
                fill_b2(0xDD),                                                // uiUpperExtIOLoc
                fill_b4(32768),                                               // ulFlashSize
                {0x00},                                                       // ucEepromInst
                {0x00},                                                       // ucFlashInst
                0x3E,                                                         // ucSPHaddr
                0x3D,                                                         // ucSPLaddr
                fill_b2(32768 / 128),                                         // uiFlashpages
                0x00,                                                         // ucDWDRAddress
                0x40,                                                         // ucDWBasePC
                0x00,           // ucAllowFullPageBitstream
                fill_b2(0x00),  // uiStartSmallestBootLoaderSection
                1,              // EnablePageProgramming
                0,              // ucCacheType
                fill_b2(0x100), // uiSramStartAddr
                0,              // ucResetType
                0,              // ucPCMaskExtended
                0x40,           // ucPCMaskHigh
                0,              // ucEindAddress
                fill_b2(0x1F),  // EECRAddress
            },
            {0}, // Xmega device descr.
        },
        {
            "atmega645",
            0x9605,
            256,
            256, // 65536 bytes flash
            8,
            256,    // 2048 bytes EEPROM
            22 * 4, // 22 interrupt vectors
            DEVFL_MKII_ONLY,
            atmega645_io_registers,
            false,
            0x07,
            0x8000, // fuses
            0x66,   // osccal
            3,      // OCD revision
            {
                0 // no mkI support
            },
            {
                CMND_SET_DEVICE_DESCRIPTOR,
                {0xFF, 0xFF, 0xFF, 0xF0, 0xDF, 0x3C, 0xB9, 0xE0}, // ucReadIO
                {0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00}, // ucReadIOShadow
                {0xB6, 0x6D, 0x1B, 0xE0, 0xDF, 0x1C, 0xB8, 0xE0}, // ucWriteIO
                {0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00}, // ucWriteIOShadow
                {0x53, 0xDA, 0x01, 0xDF, 0xF7, 0x0F, 0x00, 0x00, 0x00, 0x00,
                 0x4D, 0x07, 0x37, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // ucReadExtIO
                {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // ucReadIOExtShadow
                {0x53, 0xDA, 0x01, 0xD8, 0xF7, 0x0F, 0x00, 0x00, 0x00, 0x00,
                 0x4D, 0x05, 0x36, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // ucWriteExtIO
                {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // ucWriteIOExtShadow
                0x31,                                                         // ucIDRAddress
                0x57,                                                         // ucSPMCRAddress
                0,                                                            // ucRAMPZAddress
                fill_b2(256),                                                 // uiFlashPageSize
                8,                                                            // ucEepromPageSize
                fill_b4(0x7E00),                                              // ulBootAddress
                fill_b2(0xC6),                                                // uiUpperExtIOLoc
                fill_b4(65536),                                               // ulFlashSize
                {0x00},                                                       // ucEepromInst
                {0x00},                                                       // ucFlashInst
                0x3E,                                                         // ucSPHaddr
                0x3D,                                                         // ucSPLaddr
                fill_b2(65536 / 256),                                         // uiFlashpages
                0x00,                                                         // ucDWDRAddress
                0x40,                                                         // ucDWBasePC
                0x00,           // ucAllowFullPageBitstream
                fill_b2(0x00),  // uiStartSmallestBootLoaderSection
                1,              // EnablePageProgramming
                0,              // ucCacheType
                fill_b2(0x100), // uiSramStartAddr
                0,              // ucResetType
                0,              // ucPCMaskExtended
                0x00,           // ucPCMaskHigh
                0,              // ucEindAddress
                fill_b2(0x1F),  // EECRAddress
            },
            {0}, // Xmega device descr.
        },
        {
            "atmega6450",
            0x9606,
            256,
            256, // 65536 bytes flash
            8,
            256,    // 2048 bytes EEPROM
            25 * 4, // 25 interrupt vectors
            DEVFL_MKII_ONLY,
            atmega6450_io_registers,
            false,
            0x07,
            0x8000, // fuses
            0x66,   // osccal
            3,      // OCD revision
            {
                0 // no mkI support
            },
            {
                CMND_SET_DEVICE_DESCRIPTOR,
                {0xFF, 0xFF, 0xFF, 0xF0, 0xDF, 0x3C, 0xB9, 0xE0}, // ucReadIO
                {0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00}, // ucReadIOShadow
                {0xB6, 0x6D, 0x1B, 0xE0, 0xDF, 0x1C, 0xB8, 0xE0}, // ucWriteIO
                {0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00}, // ucWriteIOShadow
                {0x53, 0xFA, 0x09, 0xDF, 0xF7, 0x0F, 0x00, 0x00, 0x00, 0x00,
                 0x4D, 0x07, 0x37, 0x00, 0x00, 0x3F, 0x00, 0x00, 0x00, 0x00}, // ucReadExtIO
                {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // ucReadIOExtShadow
                {0x53, 0xFA, 0x09, 0xD8, 0xF7, 0x0F, 0x00, 0x00, 0x00, 0x00,
                 0x4D, 0x05, 0x36, 0x00, 0x00, 0x3F, 0x00, 0x00, 0x00, 0x00}, // ucWriteExtIO
                {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // ucWriteIOExtShadow
                0x31,                                                         // ucIDRAddress
                0x57,                                                         // ucSPMCRAddress
                0,                                                            // ucRAMPZAddress
                fill_b2(256),                                                 // uiFlashPageSize
                8,                                                            // ucEepromPageSize
                fill_b4(0x7E00),                                              // ulBootAddress
                fill_b2(0xDD),                                                // uiUpperExtIOLoc
                fill_b4(65536),                                               // ulFlashSize
                {0x00},                                                       // ucEepromInst
                {0x00},                                                       // ucFlashInst
                0x3E,                                                         // ucSPHaddr
                0x3D,                                                         // ucSPLaddr
                fill_b2(65536 / 256),                                         // uiFlashpages
                0x00,                                                         // ucDWDRAddress
                0x40,                                                         // ucDWBasePC
                0x00,           // ucAllowFullPageBitstream
                fill_b2(0x00),  // uiStartSmallestBootLoaderSection
                1,              // EnablePageProgramming
                0,              // ucCacheType
                fill_b2(0x100), // uiSramStartAddr
                0,              // ucResetType
                0,              // ucPCMaskExtended
                0x00,           // ucPCMaskHigh
                0,              // ucEindAddress
                fill_b2(0x1F),  // EECRAddress
            },
            {0}, // Xmega device descr.
        },
        {
            "atmega329",
            0x9503,
            128,
            256, // 32K flash
            4,
            256,    // 1K bytes EEPROM
            23 * 4, // 23 interrupt vectors
            DEVFL_MKII_ONLY,
            atmega329_io_registers,
            false,
            0x07,
            0x8000, // fuses
            0x66,   // osccal
            3,      // OCD revision
            {
                0 // no mkI support
            },
            {
                CMND_SET_DEVICE_DESCRIPTOR,
                {0xFF, 0xFF, 0xFF, 0xF0, 0xDF, 0x3C, 0xB9, 0xE0}, // ucReadIO
                {0},                                              // ucReadIOShadow
                {0xB6, 0x6D, 0x1B, 0xE0, 0xDF, 0x1C, 0xB8, 0xE0}, // ucWriteIO
                {0},                                              // ucWriteIOShadow
                {0x53, 0xDA, 0x01, 0xDF, 0xF7, 0x0F, 0x00, 0x00, 0x00, 0x00,
                 0x4D, 0x07, 0x37, 0x00, 0x00, 0x00, 0xF0, 0xF0, 0xDE, 0x7B}, // ucReadExtIO
                {0},                                                          // ucReadIOExtShadow
                {0x53, 0xDA, 0x01, 0xD8, 0xF7, 0x0F, 0x00, 0x00, 0x00, 0x00,
                 0x4D, 0x05, 0x36, 0x00, 0x00, 0x00, 0xE0, 0xF0, 0xDE, 0x7B}, // ucWriteExtIO
                {0},                                                          // ucWriteIOExtShadow
                0x31,                                                         // ucIDRAddress
                0x57,                                                         // ucSPMCRAddress
                0,                                                            // ucRAMPZAddress
                fill_b2(128),                                                 // uiFlashPageSize
                4,                                                            // ucEepromPageSize
                fill_b4(0x3F00),                                              // ulBootAddress
                fill_b2(0xFE),                                                // uiUpperExtIOLoc
                fill_b4(0x8000),                                              // ulFlashSize
                {0},                                                          // ucEepromInst
                {0},                                                          // ucFlashInst
                0x3e,                                                         // ucSPHaddr
                0x3d,                                                         // ucSPLaddr
                fill_b2(0x8000 / 128),                                        // uiFlashpages
                0,                                                            // ucDWDRAddress
                0x40,                                                         // ucDWBasePC
                0,              // ucAllowFullPageBitstream
                fill_b2(0),     // uiStartSmallestBootLoaderSection
                1,              // EnablePageProgramming
                0,              // ucCacheType
                fill_b2(0x100), // uiSramStartAddr
                0,              // ucResetType
                0,              // ucPCMaskExtended
                0x0,            // ucPCMaskHigh
                0,              // ucEindAddress
                fill_b2(0x1f),  // EECRAddress
            },
            {0}, // Xmega device descr.
        },
        {
            "atmega3290",
            0x9504,
            128,
            256, // 32K flash
            4,
            256,    // 1K bytes EEPROM
            25 * 4, // 25 interrupt vectors
            DEVFL_MKII_ONLY,
            atmega3290_io_registers,
            false,
            0x07,
            0x8000, // fuses
            0x66,   // osccal
            3,      // OCD revision
            {
                0 // no mkI support
            },
            {
                CMND_SET_DEVICE_DESCRIPTOR,
                {0xFF, 0xFF, 0xFF, 0xF0, 0xDF, 0x3C, 0xB9, 0xE0}, // ucReadIO
                {0},                                              // ucReadIOShadow
                {0xB6, 0x6D, 0x1B, 0xE0, 0xDF, 0x1C, 0xB8, 0xE0}, // ucWriteIO
                {0},                                              // ucWriteIOShadow
                {0x53, 0xFA, 0x09, 0xDF, 0xF7, 0x0F, 0x00, 0x00, 0x00, 0x00,
                 0x4D, 0x07, 0x37, 0x00, 0x00, 0x3F, 0xF0, 0xF0, 0xFF, 0xFF}, // ucReadExtIO
                {0},                                                          // ucReadIOExtShadow
                {0x53, 0xFA, 0x09, 0xD8, 0xF7, 0x0F, 0x00, 0x00, 0x00, 0x00,
                 0x4D, 0x05, 0x36, 0x00, 0x00, 0x3F, 0xE0, 0xF0, 0xFF, 0xFF}, // ucWriteExtIO
                {0},                                                          // ucWriteIOExtShadow
                0x31,                                                         // ucIDRAddress
                0x57,                                                         // ucSPMCRAddress
                0,                                                            // ucRAMPZAddress
                fill_b2(128),                                                 // uiFlashPageSize
                4,                                                            // ucEepromPageSize
                fill_b4(0x3F00),                                              // ulBootAddress
                fill_b2(0xFE),                                                // uiUpperExtIOLoc
                fill_b4(0x8000),                                              // ulFlashSize
                {0},                                                          // ucEepromInst
                {0},                                                          // ucFlashInst
                0x3e,                                                         // ucSPHaddr
                0x3d,                                                         // ucSPLaddr
                fill_b2(0x8000 / 128),                                        // uiFlashpages
                0,                                                            // ucDWDRAddress
                0x40,                                                         // ucDWBasePC
                0,              // ucAllowFullPageBitstream
                fill_b2(0),     // uiStartSmallestBootLoaderSection
                1,              // EnablePageProgramming
                0,              // ucCacheType
                fill_b2(0x100), // uiSramStartAddr
                0,              // ucResetType
                0,              // ucPCMaskExtended
                0x0,            // ucPCMaskHigh
                0,              // ucEindAddress
                fill_b2(0x1f),  // EECRAddress
            },
            {0}, // Xmega device descr.
        },
        {
            "atmega649",
            0x9603,
            256,
            256, // 64K flash
            8,
            256,    // 2K bytes EEPROM
            23 * 4, // 23 interrupt vectors
            DEVFL_MKII_ONLY,
            atmega649_io_registers,
            false,
            0x07,
            0x8000, // fuses
            0x66,   // osccal
            3,      // OCD revision
            {
                0 // no mkI support
            },
            {
                CMND_SET_DEVICE_DESCRIPTOR,
                {0xFF, 0xFF, 0xFF, 0xF0, 0xDF, 0x3C, 0xB9, 0xE0}, // ucReadIO
                {0},                                              // ucReadIOShadow
                {0xB6, 0x6D, 0x1B, 0xE0, 0xDF, 0x1C, 0xB8, 0xE0}, // ucWriteIO
                {0},                                              // ucWriteIOShadow
                {0x53, 0xDA, 0x01, 0xDF, 0xF7, 0x0F, 0x00, 0x00, 0x00, 0x00,
                 0x4D, 0x07, 0x37, 0x00, 0x00, 0x00, 0xF0, 0xF0, 0xDE, 0x7B}, // ucReadExtIO
                {0},                                                          // ucReadIOExtShadow
                {0x53, 0xDA, 0x01, 0xD8, 0xF7, 0x0F, 0x00, 0x00, 0x00, 0x00,
                 0x4D, 0x05, 0x36, 0x00, 0x00, 0x00, 0xE0, 0xF0, 0xDE, 0x7B}, // ucWriteExtIO
                {0},                                                          // ucWriteIOExtShadow
                0x31,                                                         // ucIDRAddress
                0x57,                                                         // ucSPMCRAddress
                0,                                                            // ucRAMPZAddress
                fill_b2(256),                                                 // uiFlashPageSize
                8,                                                            // ucEepromPageSize
                fill_b4(0x7E00),                                              // ulBootAddress
                fill_b2(0xFE),                                                // uiUpperExtIOLoc
                fill_b4(0x10000),                                             // ulFlashSize
                {0},                                                          // ucEepromInst
                {0},                                                          // ucFlashInst
                0x3e,                                                         // ucSPHaddr
                0x3d,                                                         // ucSPLaddr
                fill_b2(0x10000 / 256),                                       // uiFlashpages
                0,                                                            // ucDWDRAddress
                0x40,                                                         // ucDWBasePC
                0,              // ucAllowFullPageBitstream
                fill_b2(0),     // uiStartSmallestBootLoaderSection
                1,              // EnablePageProgramming
                0,              // ucCacheType
                fill_b2(0x100), // uiSramStartAddr
                0,              // ucResetType
                0,              // ucPCMaskExtended
                0x0,            // ucPCMaskHigh
                0,              // ucEindAddress
                fill_b2(0x1f),  // EECRAddress
            },
            {0}, // Xmega device descr.
        },
        {
            "atmega6490",
            0x9604,
            256,
            256, // 64K flash
            8,
            256,    // 2K bytes EEPROM
            25 * 4, // 25 interrupt vectors
            DEVFL_MKII_ONLY,
            atmega6490_io_registers,
            false,
            0x07,
            0x8000, // fuses
            0x66,   // osccal
            3,      // OCD revision
            {
                0 // no mkI support
            },
            {
                CMND_SET_DEVICE_DESCRIPTOR,
                {0xFF, 0xFF, 0xFF, 0xF0, 0xDF, 0x3C, 0xB9, 0xE0}, // ucReadIO
                {0},                                              // ucReadIOShadow
                {0xB6, 0x6D, 0x1B, 0xE0, 0xDF, 0x1C, 0xB8, 0xE0}, // ucWriteIO
                {0},                                              // ucWriteIOShadow
                {0x53, 0xFA, 0x09, 0xDF, 0xF7, 0x0F, 0x00, 0x00, 0x00, 0x00,
                 0x4D, 0x07, 0x37, 0x00, 0x00, 0x3F, 0xF0, 0xF0, 0xFF, 0xFF}, // ucReadExtIO
                {0},                                                          // ucReadIOExtShadow
                {0x53, 0xFA, 0x09, 0xD8, 0xF7, 0x0F, 0x00, 0x00, 0x00, 0x00,
                 0x4D, 0x05, 0x36, 0x00, 0x00, 0x3F, 0xE0, 0xF0, 0xFF, 0xFF}, // ucWriteExtIO
                {0},                                                          // ucWriteIOExtShadow
                0x31,                                                         // ucIDRAddress
                0x57,                                                         // ucSPMCRAddress
                0,                                                            // ucRAMPZAddress
                fill_b2(256),                                                 // uiFlashPageSize
                8,                                                            // ucEepromPageSize
                fill_b4(0x7E00),                                              // ulBootAddress
                fill_b2(0xFF),                                                // uiUpperExtIOLoc
                fill_b4(0x10000),                                             // ulFlashSize
                {0},                                                          // ucEepromInst
                {0},                                                          // ucFlashInst
                0x3e,                                                         // ucSPHaddr
                0x3d,                                                         // ucSPLaddr
                fill_b2(0x10000 / 256),                                       // uiFlashpages
                0,                                                            // ucDWDRAddress
                0x40,                                                         // ucDWBasePC
                0,              // ucAllowFullPageBitstream
                fill_b2(0),     // uiStartSmallestBootLoaderSection
                1,              // EnablePageProgramming
                0,              // ucCacheType
                fill_b2(0x100), // uiSramStartAddr
                0,              // ucResetType
                0,              // ucPCMaskExtended
                0x0,            // ucPCMaskHigh
                0,              // ucEindAddress
                fill_b2(0x1f),  // EECRAddress
            },
            {0}, // Xmega device descr.
        },
        {
            "atmega640",
            0x9608,
            256,
            256, // 64K flash
            8,
            512,  // 4K bytes EEPROM
            0xe4, // 57 interrupt vectors
            DEVFL_MKII_ONLY,
            atmega640_io_registers,
            false,
            0x07,
            0x8000, // fuses
            0x66,   // osccal
            3,      // OCD revision
            {
                0 // no mkI support
            },
            {
                CMND_SET_DEVICE_DESCRIPTOR,
                {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x3D, 0xB9, 0xF8}, // ucReadIO
                {0},                                              // ucReadIOShadow
                {0xFF, 0xFF, 0x1F, 0xE0, 0xFF, 0x1D, 0xA9, 0xF8}, // ucWriteIO
                {0},                                              // ucWriteIOShadow
                {0x73, 0xFF, 0x3F, 0xFF, 0xF7, 0x3F, 0xF7, 0x3F, 0xF7, 0x3F,
                 0x5F, 0x3F, 0x37, 0x37, 0x36, 0x00, 0x00, 0x00, 0x00, 0x00,
                 0xFF, 0x0F, 0x00, 0x00, 0xF7, 0x3F, 0x36, 0x00}, // ucReadExtIO
                {0},                                              // ucReadIOExtShadow
                {0x73, 0xFF, 0x3F, 0xF8, 0xF7, 0x3F, 0xF7, 0x3F, 0xF7, 0x3F,
                 0x5F, 0x2F, 0x36, 0x36, 0x36, 0x00, 0x00, 0x00, 0x00, 0x00,
                 0xFF, 0x0F, 0x00, 0x00, 0xF7, 0x3F, 0x36, 0x00}, // ucWriteExtIO
                {0},                                              // ucWriteIOExtShadow
                0x31,                                             // ucIDRAddress
                0x57,                                             // ucSPMCRAddress
                0x3B,                                             // ucRAMPZAddress
                fill_b2(256),                                     // uiFlashPageSize
                8,                                                // ucEepromPageSize
                fill_b4(0x7E00),                                  // ulBootAddress
                fill_b2(0x0136),                                  // uiUpperExtIOLoc
                fill_b4(0x20000),                                 // ulFlashSize
                {0},                                              // ucEepromInst
                {0},                                              // ucFlashInst
                0x3e,                                             // ucSPHaddr
                0x3d,                                             // ucSPLaddr
                fill_b2(0x10000 / 256),                           // uiFlashpages
                0,                                                // ucDWDRAddress
                0,                                                // ucDWBasePC
                0,                                                // ucAllowFullPageBitstream
                fill_b2(0),     // uiStartSmallestBootLoaderSection
                1,              // EnablePageProgramming
                0,              // ucCacheType
                fill_b2(0x200), // uiSramStartAddr
                0,              // ucResetType
                0,              // ucPCMaskExtended
                0,              // ucPCMaskHigh
                0x3c,           // ucEindAddress
                fill_b2(0x1F),  // EECRAddress
            },
            {0}, // Xmega device descr.
        },
        {
            "atmega1280",
            0x9703,
            256,
            512, // 128K flash
            8,
            512,  // 4K bytes EEPROM
            0xe4, // 57 interrupt vectors
            DEVFL_MKII_ONLY,
            atmega1280_io_registers,
            false,
            0x07,
            0x8000, // fuses
            0x66,   // osccal
            3,      // OCD revision
            {
                0 // no mkI support
            },
            {
                CMND_SET_DEVICE_DESCRIPTOR,
                {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x3D, 0xB9, 0xF8}, // ucReadIO
                {0},                                              // ucReadIOShadow
                {0xFF, 0xFF, 0x1F, 0xE0, 0xFF, 0x1D, 0xA9, 0xF8}, // ucWriteIO
                {0},                                              // ucWriteIOShadow
                {0x73, 0xFF, 0x3F, 0xFF, 0xF7, 0x3F, 0xF7, 0x3F, 0xF7, 0x3F,
                 0x5F, 0x3F, 0x37, 0x37, 0x36, 0x00, 0x00, 0x00, 0x00, 0x00,
                 0xFF, 0x0F, 0x00, 0x00, 0xF7, 0x3F, 0x36, 0x00}, // ucReadExtIO
                {0},                                              // ucReadIOExtShadow
                {0x73, 0xFF, 0x3F, 0xF8, 0xF7, 0x3F, 0xF7, 0x3F, 0xF7, 0x3F,
                 0x5F, 0x2F, 0x36, 0x36, 0x36, 0x00, 0x00, 0x00, 0x00, 0x00,
                 0xFF, 0x0F, 0x00, 0x00, 0xF7, 0x3F, 0x36, 0x00}, // ucWriteExtIO
                {0},                                              // ucWriteIOExtShadow
                0x31,                                             // ucIDRAddress
                0x57,                                             // ucSPMCRAddress
                0x3B,                                             // ucRAMPZAddress
                fill_b2(256),                                     // uiFlashPageSize
                8,                                                // ucEepromPageSize
                fill_b4(0xFE00),                                  // ulBootAddress
                fill_b2(0x0136),                                  // uiUpperExtIOLoc
                fill_b4(0x20000),                                 // ulFlashSize
                {0},                                              // ucEepromInst
                {0},                                              // ucFlashInst
                0x3e,                                             // ucSPHaddr
                0x3d,                                             // ucSPLaddr
                fill_b2(0x20000 / 256),                           // uiFlashpages
                0,                                                // ucDWDRAddress
                0,                                                // ucDWBasePC
                0,                                                // ucAllowFullPageBitstream
                fill_b2(0),     // uiStartSmallestBootLoaderSection
                1,              // EnablePageProgramming
                0,              // ucCacheType
                fill_b2(0x200), // uiSramStartAddr
                0,              // ucResetType
                0,              // ucPCMaskExtended
                0,              // ucPCMaskHigh
                0x3c,           // ucEindAddress
                fill_b2(0x1F),  // EECRAddress
            },
            {0}, // Xmega device descr.
        },
        {
            "atmega1281",
            0x9704,
            256,
            512, // 128K flash
            8,
            512,  // 4K bytes EEPROM
            0xe4, // 57 interrupt vectors
            DEVFL_MKII_ONLY,
            atmega1281_io_registers,
            false,
            0x07,
            0x8000, // fuses
            0x66,   // osccal
            3,      // OCD revision
            {
                0 // no mkI support
            },
            {
                CMND_SET_DEVICE_DESCRIPTOR,
                {0xFF, 0xFF, 0xFF, 0xF9, 0xFF, 0x3D, 0xB9, 0xF8}, // ucReadIO
                {0},                                              // ucReadIOShadow
                {0xFF, 0xFF, 0x1F, 0xE0, 0xFF, 0x1D, 0xA9, 0xF8}, // ucWriteIO
                {0},                                              // ucWriteIOShadow
                {0x73, 0xFF, 0x3F, 0xFF, 0xF7, 0x3F, 0xF7, 0x3F, 0xF7, 0x3F,
                 0x5F, 0x3F, 0x37, 0x37, 0x36, 0x00, 0x00, 0x00, 0x00, 0x00,
                 0xFF, 0x0F, 0x00, 0x00, 0xF7, 0x3F, 0x36, 0x00}, // ucReadExtIO
                {0},                                              // ucReadIOExtShadow
                {0x73, 0xFF, 0x3F, 0xF8, 0xF7, 0x3F, 0xF7, 0x3F, 0xF7, 0x3F,
                 0x5F, 0x2F, 0x36, 0x36, 0x36, 0x00, 0x00, 0x00, 0x00, 0x00,
                 0xFF, 0x0F, 0x00, 0x00, 0xF7, 0x3F, 0x36, 0x00}, // ucWriteExtIO
                {0},                                              // ucWriteIOExtShadow
                0x31,                                             // ucIDRAddress
                0x57,                                             // ucSPMCRAddress
                0x3B,                                             // ucRAMPZAddress
                fill_b2(256),                                     // uiFlashPageSize
                8,                                                // ucEepromPageSize
                fill_b4(0xFE00),                                  // ulBootAddress
                fill_b2(0x0136),                                  // uiUpperExtIOLoc
                fill_b4(0x20000),                                 // ulFlashSize
                {0},                                              // ucEepromInst
                {0},                                              // ucFlashInst
                0x3e,                                             // ucSPHaddr
                0x3d,                                             // ucSPLaddr
                fill_b2(0x20000 / 256),                           // uiFlashpages
                0,                                                // ucDWDRAddress
                0,                                                // ucDWBasePC
                0,                                                // ucAllowFullPageBitstream
                fill_b2(0),     // uiStartSmallestBootLoaderSection
                1,              // EnablePageProgramming
                0,              // ucCacheType
                fill_b2(0x200), // uiSramStartAddr
                0,              // ucResetType
                0,              // ucPCMaskExtended
                0,              // ucPCMaskHigh
                0x3c,           // ucEindAddress
                fill_b2(0x1F),  // EECRAddress
            },
            {0}, // Xmega device descr.
        },
        {
            "atmega2560",
            0x9801,
            256,
            1024, // 256K flash
            8,
            512,  // 4K bytes EEPROM
            0xe4, // 57 interrupt vectors
            DEVFL_MKII_ONLY,
            atmega2560_io_registers,
            false,
            0x07,
            0x8000, // fuses
            0x66,   // osccal
            4,      // OCD revision
            {
                0 // no mkI support
            },
            {
                CMND_SET_DEVICE_DESCRIPTOR,
                {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x3D, 0xB9, 0xF8}, // ucReadIO
                {0},                                              // ucReadIOShadow
                {0xFF, 0xFF, 0x1F, 0xE0, 0xFF, 0x1D, 0xA9, 0xF8}, // ucWriteIO
                {0},                                              // ucWriteIOShadow
                {
                    0x73, 0xFF, 0x3F, 0xFF, 0xF7, 0x3F, 0xF7, 0x3F, 0xF7,
                    0x3F, 0x5F, 0x3F, 0x37, 0x37, 0x37, 0x00, 0x00, 0x00,
                    0x00, 0x00, 0xFF, 0x0F, 0x00, 0x00, 0xF7, 0x3F, 0x37}, // ucReadExtIO
                {0},                                                       // ucReadIOExtShadow
                {
                    0x73, 0xFF, 0x3F, 0xF8, 0xF7, 0x3F, 0xF7, 0x3F, 0xF7,
                    0x3F, 0x5F, 0x2F, 0x36, 0x36, 0x36, 0x00, 0x00, 0x00,
                    0x00, 0x00, 0xFF, 0x0F, 0x00, 0x00, 0xF7, 0x3F, 0x36}, // ucWriteExtIO
                {0},                                                       // ucWriteIOExtShadow
                0x31,                                                      // ucIDRAddress
                0x57,                                                      // ucSPMCRAddress
                0x3B,                                                      // ucRAMPZAddress
                fill_b2(256),                                              // uiFlashPageSize
                8,                                                         // ucEepromPageSize
                fill_b4(0x1FE00),                                          // ulBootAddress
                fill_b2(0x0136),                                           // uiUpperExtIOLoc
                fill_b4(0x40000),                                          // ulFlashSize
                {0},                                                       // ucEepromInst
                {0},                                                       // ucFlashInst
                0x3e,                                                      // ucSPHaddr
                0x3d,                                                      // ucSPLaddr
                fill_b2(0x40000 / 256),                                    // uiFlashpages
                0,                                                         // ucDWDRAddress
                0,                                                         // ucDWBasePC
                0,              // ucAllowFullPageBitstream
                fill_b2(0),     // uiStartSmallestBootLoaderSection
                1,              // EnablePageProgramming
                0,              // ucCacheType
                fill_b2(0x200), // uiSramStartAddr
                0,              // ucResetType
                0,              // ucPCMaskExtended
                0,              // ucPCMaskHigh
                0x3c,           // ucEindAddress
                fill_b2(0x1F),  // EECRAddress
            },
            {0}, // Xmega device descr.
        },
        {
            "atmega2561",
            0x9802,
            256,
            1024, // 256K flash
            8,
            512,  // 4K bytes EEPROM
            0xe4, // 57 interrupt vectors
            DEVFL_MKII_ONLY,
            atmega2561_io_registers,
            false,
            0x07,
            0x8000, // fuses
            0x66,   // osccal
            4,      // OCD revision
            {
                0 // no mkI support
            },
            {
                CMND_SET_DEVICE_DESCRIPTOR,
                {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x3D, 0xB9, 0xF8}, // ucReadIO
                {0},                                              // ucReadIOShadow
                {0xFF, 0xFF, 0x1F, 0xE0, 0xFF, 0x1D, 0xA9, 0xF8}, // ucWriteIO
                {0},                                              // ucWriteIOShadow
                {
                    0x73, 0xFF, 0x3F, 0xFF, 0xF7, 0x3F, 0xF7, 0x3F, 0xF7,
                    0x3F, 0x5F, 0x3F, 0x37, 0x37, 0x37, 0x00, 0x00, 0x00,
                    0x00, 0x00, 0xFF, 0x0F, 0x00, 0x00, 0xF7, 0x3F, 0x37}, // ucReadExtIO
                {0},                                                       // ucReadIOExtShadow
                {
                    0x73, 0xFF, 0x3F, 0xF8, 0xF7, 0x3F, 0xF7, 0x3F, 0xF7,
                    0x3F, 0x5F, 0x2F, 0x36, 0x36, 0x36, 0x00, 0x00, 0x00,
                    0x00, 0x00, 0xFF, 0x0F, 0x00, 0x00, 0xF7, 0x3F, 0x36}, // ucWriteExtIO
                {0},                                                       // ucWriteIOExtShadow
                0x31,                                                      // ucIDRAddress
                0x57,                                                      // ucSPMCRAddress
                0x3B,                                                      // ucRAMPZAddress
                fill_b2(256),                                              // uiFlashPageSize
                8,                                                         // ucEepromPageSize
                fill_b4(0x1FE00),                                          // ulBootAddress
                fill_b2(0x0136),                                           // uiUpperExtIOLoc
                fill_b4(0x40000),                                          // ulFlashSize
                {0},                                                       // ucEepromInst
                {0},                                                       // ucFlashInst
                0x3e,                                                      // ucSPHaddr
                0x3d,                                                      // ucSPLaddr
                fill_b2(0x40000 / 256),                                    // uiFlashpages
                0,                                                         // ucDWDRAddress
                0,                                                         // ucDWBasePC
                0,              // ucAllowFullPageBitstream
                fill_b2(0),     // uiStartSmallestBootLoaderSection
                1,              // EnablePageProgramming
                0,              // ucCacheType
                fill_b2(0x200), // uiSramStartAddr
                0,              // ucResetType
                0,              // ucPCMaskExtended
                0,              // ucPCMaskHigh
                0x3c,           // ucEindAddress
                fill_b2(0x1F),  // EECRAddress
            },
            {0}, // Xmega device descr.
        },
        {
            "atmega48",
            0x9205,
            64,
            64, // 4K flash
            4,
            64,     // 256 bytes EEPROM
            26 * 2, // 26 interrupt vectors
            DEVFL_MKII_ONLY,
            atmega48_io_registers,
            false,
            0x07,
            0x0000, // fuses
            0x66,   // osccal
            1,      // OCD revision
            {
                0 // no mkI support
            },
            {
                CMND_SET_DEVICE_DESCRIPTOR,
                {0xF8, 0x0F, 0xE0, 0xF8, 0xFB, 0x3D, 0xB9, 0xE0}, // ucReadIO
                {0},                                              // ucReadIOShadow
                {0xB0, 0x0D, 0x00, 0xE0, 0xFB, 0x1D, 0xB8, 0xE0}, // ucWriteIO
                {0},                                              // ucWriteIOShadow
                {0x53, 0xFB, 0x01, 0xDF, 0xF3, 0x0F, 0x00, 0x00, 0x00, 0x00,
                 0x5F, 0x3F, 0x37, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // ucReadExtIO
                {0},                                                          // ucReadIOExtShadow
                {0x10, 0xFB, 0x01, 0xD8, 0xF3, 0x0F, 0x00, 0x00, 0x00, 0x00,
                 0x5F, 0x2F, 0x36, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // ucWriteExtIO
                {0},                                                          // ucWriteIOExtShadow
                0,                                                            // ucIDRAddress
                0,                                                            // ucSPMCRAddress
                0,                                                            // ucRAMPZAddress
                fill_b2(64),                                                  // uiFlashPageSize
                4,                                                            // ucEepromPageSize
                fill_b4(0),                                                   // ulBootAddress
                fill_b2(0xC6),                                                // uiUpperExtIOLoc
                fill_b4(0x1000),                                              // ulFlashSize
                {0xBD, 0xF2, 0xBD, 0xE1, 0xBB, 0xCF, 0xB4, 0x00, 0xBE, 0x01,
                 0xB6, 0x01, 0xBC, 0x00, 0xBB, 0xBF, 0x99, 0xF9, 0xBB, 0xAF}, // ucEepromInst
                {0xB6, 0x01, 0x11},                                           // ucFlashInst
                0x3e,                                                         // ucSPHaddr
                0x3d,                                                         // ucSPLaddr
                fill_b2(0x1000 / 64),                                         // uiFlashpages
                0x31,                                                         // ucDWDRAddress
                0x18,                                                         // ucDWBasePC
                0,              // ucAllowFullPageBitstream
                fill_b2(0),     // uiStartSmallestBootLoaderSection
                1,              // EnablePageProgramming
                0,              // ucCacheType
                fill_b2(0x100), // uiSramStartAddr
                0,              // ucResetType
                0,              // ucPCMaskExtended
                0,              // ucPCMaskHigh
                0,              // ucEindAddress
                fill_b2(0x1F),  // EECRAddress
            },
            {0}, // Xmega device descr.
        },
        {
            "atmega88",
            0x930A,
            64,
            128, // 8192 bytes flash
            4,
            128,    // 512 bytes EEPROM
            26 * 2, // 26 interrupt vectors
            DEVFL_MKII_ONLY,
            atmega88_io_registers,
            false,
            0x07,
            0x0000, // fuses
            0x66,   // osccal
            1,      // OCD revision
            {
                0 // no mkI support
            },
            {
                CMND_SET_DEVICE_DESCRIPTOR,
                {0xF8, 0x0F, 0xE0, 0xF8, 0xFF, 0x3D, 0xB9, 0xE0}, // ucReadIO
                {0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00}, // ucReadIOShadow
                {0xB0, 0x0D, 0x00, 0xE0, 0xFF, 0x1D, 0xB8, 0xE0}, // ucWriteIO
                {0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00}, // ucWriteIOShadow
                {0x53, 0xFB, 0x01, 0xDF, 0xF7, 0x0F, 0x00, 0x00, 0x00, 0x00,
                 0x5F, 0x3F, 0x37, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // ucReadExtIO
                {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // ucReadIOExtShadow
                {0x10, 0xFB, 0x01, 0xD8, 0xF7, 0x0F, 0x00, 0x00, 0x00, 0x00,
                 0x5F, 0x2F, 0x36, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // ucWriteExtIO
                {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // ucWriteIOExtShadow
                0x00,                                                         // ucIDRAddress
                0X00,                                                         // ucSPMCRAddress
                0,                                                            // ucRAMPZAddress
                fill_b2(64),                                                  // uiFlashPageSize
                4,                                                            // ucEepromPageSize
                fill_b4(0x0F80),                                              // ulBootAddress
                fill_b2(0xC6),                                                // uiUpperExtIOLoc
                fill_b4(8192),                                                // ulFlashSize
                {0xBD, 0xF2, 0xBD, 0xE1, 0xBB, 0xCF, 0xB4, 0x00, 0xBE, 0x01,
                 0xB6, 0x01, 0xBC, 0x00, 0xBB, 0xBF, 0x99, 0xF9, 0xBB, 0xAF}, // ucEepromInst
                {0xB6, 0x01, 0x11},                                           // ucFlashInst
                0x3E,                                                         // ucSPHaddr
                0x3D,                                                         // ucSPLaddr
                fill_b2(8192 / 64),                                           // uiFlashpages
                0x31,                                                         // ucDWDRAddress
                0x10,                                                         // ucDWBasePC
                0x00,           // ucAllowFullPageBitstream
                fill_b2(0xF80), // uiStartSmallestBootLoaderSection
                1,              // EnablePageProgramming
                0,              // ucCacheType
                fill_b2(0x100), // uiSramStartAddr
                0,              // ucResetType
                0,              // ucPCMaskExtended
                0,              // ucPCMaskHigh
                0,              // ucEindAddress
                fill_b2(0x1F),  // EECRAddress
            },
            {0}, // Xmega device descr.
        },
        {
            "atmega168",
            0x9406,
            128,
            128, // 16384 bytes flash
            4,
            128,    // 512 bytes EEPROM
            26 * 4, // 26 interrupt vectors
            DEVFL_MKII_ONLY,
            atmega168_io_registers,
            false,
            0x07,
            0x0000, // fuses
            0x66,   // osccal
            1,      // OCD revision
            {
                0 // no mkI support
            },
            {
                CMND_SET_DEVICE_DESCRIPTOR,
                {0xF8, 0x0F, 0xE0, 0xF8, 0xFF, 0x3D, 0xB9, 0xE0}, // ucReadIO
                {0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00}, // ucReadIOShadow
                {0xB0, 0x0D, 0x00, 0xE0, 0xFF, 0x1D, 0xB8, 0xE0}, // ucWriteIO
                {0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00}, // ucWriteIOShadow
                {0x53, 0xFB, 0x01, 0xDF, 0xF7, 0x0F, 0x00, 0x00, 0x00, 0x00,
                 0x5F, 0x3F, 0x37, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // ucReadExtIO
                {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // ucReadIOExtShadow
                {0x10, 0xFB, 0x01, 0xD8, 0xF7, 0x0F, 0x00, 0x00, 0x00, 0x00,
                 0x5F, 0x2F, 0x36, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // ucWriteExtIO
                {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // ucWriteIOExtShadow
                0x31,                                                         // ucIDRAddress
                0X57,                                                         // ucSPMCRAddress
                0,                                                            // ucRAMPZAddress
                fill_b2(128),                                                 // uiFlashPageSize
                4,                                                            // ucEepromPageSize
                fill_b4(0x1F80),                                              // ulBootAddress
                fill_b2(0xC6),                                                // uiUpperExtIOLoc
                fill_b4(16384),                                               // ulFlashSize
                {0xBD, 0xF2, 0xBD, 0xE1, 0xBB, 0xCF, 0xB4, 0x00, 0xBE, 0x01,
                 0xB6, 0x01, 0xBC, 0x00, 0xBB, 0xBF, 0x99, 0xF9, 0xBB, 0xAF}, // ucEepromInst
                {0xB6, 0x01, 0x11},                                           // ucFlashInst
                0x3E,                                                         // ucSPHaddr
                0x3D,                                                         // ucSPLaddr
                fill_b2(16384 / 128),                                         // uiFlashpages
                0x31,                                                         // ucDWDRAddress
                0x00,                                                         // ucDWBasePC
                0x00,            // ucAllowFullPageBitstream
                fill_b2(0x1F80), // uiStartSmallestBootLoaderSection
                1,               // EnablePageProgramming
                0,               // ucCacheType
                fill_b2(0x100),  // uiSramStartAddr
                0,               // ucResetType
                0,               // ucPCMaskExtended
                0,               // ucPCMaskHigh
                0,               // ucEindAddress
                fill_b2(0x1F),   // EECRAddress
            },
            {0}, // Xmega device descr.
        },
        {
            "attiny13",
            0x9007,
            32,
            32, // 1024 bytes flash
            1,
            64,     // 64 bytes EEPROM
            10 * 2, // 10 interrupt vectors
            DEVFL_MKII_ONLY,
            attiny13_io_registers,
            false,
            0x03,
            0x0000, // fuses
            0x51,   // osccal
            0,      // OCD revision
            {
                0 // no mkI support
            },
            {
                CMND_SET_DEVICE_DESCRIPTOR,
                {0xF8, 0x01, 0xF0, 0x71, 0x42, 0x83, 0xFE, 0xAF}, // ucReadIO
                {0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00}, // ucReadIOShadow
                {0x88, 0x00, 0xB0, 0x71, 0x00, 0x83, 0x7C, 0xAA}, // ucWriteIO
                {0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00}, // ucWriteIOShadow
                {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // ucReadExtIO
                {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // ucReadIOExtShadow
                {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // ucWriteExtIO
                {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // ucWriteIOExtShadow
                0x00,                                                         // ucIDRAddress
                0X00,                                                         // ucSPMCRAddress
                0,                                                            // ucRAMPZAddress
                fill_b2(32),                                                  // uiFlashPageSize
                1,                                                            // ucEepromPageSize
                fill_b4(0x0000),                                              // ulBootAddress
                fill_b2(0x00),                                                // uiUpperExtIOLoc
                fill_b4(1024),                                                // ulFlashSize
                {0xBB, 0xFE, 0xBB, 0xEE, 0xBB, 0xCC, 0xB2, 0x0D, 0xBC, 0x0E,
                 0xB4, 0x0E, 0xBA, 0x0D, 0xBB, 0xBC, 0x99, 0xE1, 0xBB, 0xAC}, // ucEepromInst
                {0xB4, 0x0E, 0x1E},                                           // ucFlashInst
                0,                                                            // ucSPHaddr
                0x3D,                                                         // ucSPLaddr
                fill_b2(1024 / 32),                                           // uiFlashpages
                0x2E,                                                         // ucDWDRAddress
                0x00,                                                         // ucDWBasePC
                0x00,          // ucAllowFullPageBitstream
                fill_b2(0x00), // uiStartSmallestBootLoaderSection
                1,             // EnablePageProgramming
                0,             // ucCacheType
                fill_b2(0x60), // uiSramStartAddr
                0,             // ucResetType
                0,             // ucPCMaskExtended
                0,             // ucPCMaskHigh
                0,             // ucEindAddress
                fill_b2(0x1C), // EECRAddress
            },
            {0}, // Xmega device descr.
        },
        {
            "attiny2313",
            0x910A,
            32,
            64, // 2048 bytes flash
            4,
            32,     // 128 bytes EEPROM
            19 * 2, // 19 interrupt vectors
            DEVFL_MKII_ONLY,
            attiny2313_io_registers,
            false,
            0x07,
            0x0000, // fuses
            0x51,   // osccal
            0,      // OCD revision
            {
                0 // no mkI support
            },
            {
                CMND_SET_DEVICE_DESCRIPTOR,
                {0x0E, 0xEF, 0xFF, 0x7F, 0x3F, 0xFF, 0x7F, 0xBF}, // ucReadIO
                {0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00}, // ucReadIOShadow
                {0x0E, 0xA6, 0xBE, 0x7D, 0x39, 0xFF, 0x7D, 0xBA}, // ucWriteIO
                {0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00}, // ucWriteIOShadow
                {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // ucReadExtIO
                {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // ucReadIOExtShadow
                {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // ucWriteExtIO
                {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // ucWriteIOExtShadow
                0x00,                                                         // ucIDRAddress
                0X00,                                                         // ucSPMCRAddress
                0,                                                            // ucRAMPZAddress
                fill_b2(32),                                                  // uiFlashPageSize
                4,                                                            // ucEepromPageSize
                fill_b4(0x0000),                                              // ulBootAddress
                fill_b2(0x00),                                                // uiUpperExtIOLoc
                fill_b4(2048),                                                // ulFlashSize
                {0xBB, 0xFE, 0xBB, 0xEE, 0xBB, 0xCC, 0xB2, 0x0D, 0xBA, 0x0F,
                 0xB2, 0x0F, 0xBA, 0x0D, 0xBB, 0xBC, 0x99, 0xE1, 0xBB, 0xAC}, // ucEepromInst
                {0xB2, 0x0F, 0x1F},                                           // ucFlashInst
                0,                                                            // ucSPHaddr
                0x3D,                                                         // ucSPLaddr
                fill_b2(2048 / 32),                                           // uiFlashpages
                0x1F,                                                         // ucDWDRAddress
                0x00,                                                         // ucDWBasePC
                0x00,          // ucAllowFullPageBitstream
                fill_b2(0x00), // uiStartSmallestBootLoaderSection
                1,             // EnablePageProgramming
                0,             // ucCacheType
                fill_b2(0x60), // uiSramStartAddr
                0,             // ucResetType
                0,             // ucPCMaskExtended
                0,             // ucPCMaskHigh
                0,             // ucEindAddress
                fill_b2(0x1C), // EECRAddress
            },
            {0}, // Xmega device descr.
        },
        {
            "attiny4313",
            0x920D,
            64,
            64, // 4096 bytes flash
            4,
            64,     // 256 bytes EEPROM
            21 * 2, // 21 interrupt vectors
            DEVFL_MKII_ONLY,
            nullptr, // registers not yet defined
            false,
            0x07,
            0x0000, // fuses
            0x51,   // osccal
            0,      // OCD revision
            {
                0 // no mkI support
            },
            {
                CMND_SET_DEVICE_DESCRIPTOR,
                {0x0E, 0xEF, 0xFF, 0x7F, 0x3F, 0xFF, 0x7F, 0xFF}, // ucReadIO
                {0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00}, // ucReadIOShadow
                {0x0E, 0xA6, 0xBE, 0x7D, 0x39, 0xFF, 0x7D, 0xFA}, // ucWriteIO
                {0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00}, // ucWriteIOShadow
                {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // ucReadExtIO
                {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // ucReadIOExtShadow
                {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // ucWriteExtIO
                {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // ucWriteIOExtShadow
                0x00,                                                         // ucIDRAddress
                0X00,                                                         // ucSPMCRAddress
                0,                                                            // ucRAMPZAddress
                fill_b2(64),                                                  // uiFlashPageSize
                4,                                                            // ucEepromPageSize
                fill_b4(0x0000),                                              // ulBootAddress
                fill_b2(0x00),                                                // uiUpperExtIOLoc
                fill_b4(4096),                                                // ulFlashSize
                {0xBB, 0xFF, 0xBB, 0xEE, 0xBB, 0xCC, 0xB2, 0x0D, 0xBC, 0x07,
                 0xB4, 0x07, 0xBA, 0x0D, 0xBB, 0xBC, 0x99, 0xE1, 0xBB, 0xAC}, // ucEepromInst
                {0xB4, 0x07, 0x17},                                           // ucFlashInst
                0x3E,                                                         // ucSPHaddr
                0x3D,                                                         // ucSPLaddr
                fill_b2(4096 / 64),                                           // uiFlashpages
                0x27,                                                         // ucDWDRAddress
                0x00,                                                         // ucDWBasePC
                0x00,          // ucAllowFullPageBitstream
                fill_b2(0x00), // uiStartSmallestBootLoaderSection
                1,             // EnablePageProgramming
                0,             // ucCacheType
                fill_b2(0x60), // uiSramStartAddr
                0,             // ucResetType
                0,             // ucPCMaskExtended
                0,             // ucPCMaskHigh
                0,             // ucEindAddress
                fill_b2(0x1C), // EECRAddress
            },
        },
        {
            "at90pwm2",
            0x9381,
            64,
            128, // 8192 bytes flash
            4,
            128,    // 512 bytes EEPROM
            32 * 2, // 32 interrupt vectors
            DEVFL_MKII_ONLY,
            at90pwm2_io_registers,
            false,
            0x07,
            0x0000, // fuses
            0x66,   // osccal
            1,      // OCD revision
            {
                0 // no mkI support
            },
            {
                CMND_SET_DEVICE_DESCRIPTOR,
                {0xF8, 0x7F, 0x60, 0xFE, 0xFF, 0x33, 0xBD, 0xE0}, // ucReadIO
                {0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00}, // ucReadIOShadow
                {0xF8, 0x7F, 0x40, 0xEE, 0xFF, 0x33, 0xBC, 0xE0}, // ucWriteIO
                {0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00}, // ucWriteIOShadow
                {0x53, 0xC2, 0xC0, 0xDF, 0xF7, 0x0F, 0x00, 0x00, 0x3F, 0xE4,
                 0x00, 0x00, 0x36, 0x37, 0x01, 0xFC, 0x05, 0xFC, 0x07, 0xFC}, // ucReadExtIO
                {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // ucReadIOExtShadow
                {0x11, 0xC2, 0xC0, 0xD8, 0xF7, 0x0F, 0x00, 0x00, 0x3F, 0xE4,
                 0x00, 0x00, 0x36, 0x33, 0x01, 0xFC, 0x05, 0xFC, 0x07, 0xFC}, // ucWriteExtIO
                {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // ucWriteIOExtShadow
                0x00,                                                         // ucIDRAddress
                0X00,                                                         // ucSPMCRAddress
                0,                                                            // ucRAMPZAddress
                fill_b2(64),                                                  // uiFlashPageSize
                4,                                                            // ucEepromPageSize
                fill_b4(0x0F80),                                              // ulBootAddress
                fill_b2(0xFF),                                                // uiUpperExtIOLoc
                fill_b4(8192),                                                // ulFlashSize
                {0xBD, 0xF2, 0xBD, 0xE1, 0xBB, 0xCF, 0xB4, 0x00, 0xBE, 0x01,
                 0xB6, 0x01, 0xBC, 0x00, 0xBB, 0xBF, 0x99, 0xF9, 0xBB, 0xAF}, // ucEepromInst
                {0xB6, 0x01, 0x11},                                           // ucFlashInst
                0x3E,                                                         // ucSPHaddr
                0x3D,                                                         // ucSPLaddr
                fill_b2(8192 / 64),                                           // uiFlashpages
                0x31,                                                         // ucDWDRAddress
                0x00,                                                         // ucDWBasePC
                0x00,            // ucAllowFullPageBitstream
                fill_b2(0xF80),  // uiStartSmallestBootLoaderSection
                1,               // EnablePageProgramming
                0,               // ucCacheType
                fill_b2(0x0100), // uiSramStartAddr
                0,               // ucResetType
                0,               // ucPCMaskExtended
                0,               // ucPCMaskHigh
                0,               // ucEindAddress
                fill_b2(0x1F),   // EECRAddress
            },
            {0}, // Xmega device descr.
        },
        {
            "at90pwm3",
            0x9381,
            64,
            128, // 8192 bytes flash
            4,
            128,    // 512 bytes EEPROM
            32 * 2, // 32 interrupt vectors
            DEVFL_MKII_ONLY,
            at90pwm3_io_registers,
            false,
            0x07,
            0x0000, // fuses
            0x66,   // osccal
            1,      // OCD revision
            {
                0 // no mkI support
            },
            {
                CMND_SET_DEVICE_DESCRIPTOR,
                {0xF8, 0x7F, 0x60, 0xFE, 0xFF, 0x33, 0xBD, 0xE0}, // ucReadIO
                {0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00}, // ucReadIOShadow
                {0xF8, 0x7F, 0x40, 0xEE, 0xFF, 0x33, 0xBC, 0xE0}, // ucWriteIO
                {0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00}, // ucWriteIOShadow
                {0x53, 0xC2, 0xC0, 0xDF, 0xF7, 0x0F, 0x00, 0x00, 0x3F, 0xE4,
                 0x00, 0x00, 0x36, 0x37, 0x01, 0xFC, 0x05, 0xFC, 0x07, 0xFC}, // ucReadExtIO
                {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // ucReadIOExtShadow
                {0x11, 0xC2, 0xC0, 0xD8, 0xF7, 0x0F, 0x00, 0x00, 0x3F, 0xE4,
                 0x00, 0x00, 0x36, 0x33, 0x01, 0xFC, 0x05, 0xFC, 0x07, 0xFC}, // ucWriteExtIO
                {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // ucWriteIOExtShadow
                0x00,                                                         // ucIDRAddress
                0X00,                                                         // ucSPMCRAddress
                0,                                                            // ucRAMPZAddress
                fill_b2(64),                                                  // uiFlashPageSize
                4,                                                            // ucEepromPageSize
                fill_b4(0x0F80),                                              // ulBootAddress
                fill_b2(0xFF),                                                // uiUpperExtIOLoc
                fill_b4(8192),                                                // ulFlashSize
                {0xBD, 0xF2, 0xBD, 0xE1, 0xBB, 0xCF, 0xB4, 0x00, 0xBE, 0x01,
                 0xB6, 0x01, 0xBC, 0x00, 0xBB, 0xBF, 0x99, 0xF9, 0xBB, 0xAF}, // ucEepromInst
                {0xB6, 0x01, 0x11},                                           // ucFlashInst
                0x3E,                                                         // ucSPHaddr
                0x3D,                                                         // ucSPLaddr
                fill_b2(8192 / 64),                                           // uiFlashpages
                0x31,                                                         // ucDWDRAddress
                0x00,                                                         // ucDWBasePC
                0x00,            // ucAllowFullPageBitstream
                fill_b2(0xF80),  // uiStartSmallestBootLoaderSection
                1,               // EnablePageProgramming
                0,               // ucCacheType
                fill_b2(0x0100), // uiSramStartAddr
                0,               // ucResetType
                0,               // ucPCMaskExtended
                0,               // ucPCMaskHigh
                0,               // ucEindAddress
                fill_b2(0x1F),   // EECRAddress
            },
            {0}, // Xmega device descr.
        },
        {
            "at90pwm2b",
            0x9383,
            64,
            128, // 8192 bytes flash
            4,
            128,    // 512 bytes EEPROM
            32 * 2, // 32 interrupt vectors
            DEVFL_MKII_ONLY,
            at90pwm2b_io_registers,
            false,
            0x07,
            0x0000, // fuses
            0x66,   // osccal
            1,      // OCD revision
            {
                0 // no mkI support
            },
            {
                CMND_SET_DEVICE_DESCRIPTOR,
                {0xF8, 0x7F, 0x60, 0xFE, 0xFF, 0x33, 0xBD, 0xE0}, // ucReadIO
                {0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00}, // ucReadIOShadow
                {0xF8, 0x7F, 0x40, 0xEE, 0xFF, 0x33, 0xBC, 0xE0}, // ucWriteIO
                {0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00}, // ucWriteIOShadow
                {0x53, 0xC2, 0xC0, 0xDF, 0xF7, 0x0F, 0x00, 0x00, 0x3F, 0xE4,
                 0x00, 0x00, 0x36, 0x37, 0x01, 0xFC, 0x05, 0xFC, 0x07, 0xFC}, // ucReadExtIO
                {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // ucReadIOExtShadow
                {0x11, 0xC2, 0xC0, 0xD8, 0xF7, 0x0F, 0x00, 0x00, 0x3F, 0xE4,
                 0x00, 0x00, 0x36, 0x33, 0x01, 0xFC, 0x05, 0xFC, 0x07, 0xFC}, // ucWriteExtIO
                {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // ucWriteIOExtShadow
                0x00,                                                         // ucIDRAddress
                0X00,                                                         // ucSPMCRAddress
                0,                                                            // ucRAMPZAddress
                fill_b2(64),                                                  // uiFlashPageSize
                4,                                                            // ucEepromPageSize
                fill_b4(0x0F80),                                              // ulBootAddress
                fill_b2(0xFF),                                                // uiUpperExtIOLoc
                fill_b4(8192),                                                // ulFlashSize
                {0xBD, 0xF2, 0xBD, 0xE1, 0xBB, 0xCF, 0xB4, 0x00, 0xBE, 0x01,
                 0xB6, 0x01, 0xBC, 0x00, 0xBB, 0xBF, 0x99, 0xF9, 0xBB, 0xAF}, // ucEepromInst
                {0xB6, 0x01, 0x11},                                           // ucFlashInst
                0x3E,                                                         // ucSPHaddr
                0x3D,                                                         // ucSPLaddr
                fill_b2(8192 / 64),                                           // uiFlashpages
                0x31,                                                         // ucDWDRAddress
                0x00,                                                         // ucDWBasePC
                0x00,            // ucAllowFullPageBitstream
                fill_b2(0xF80),  // uiStartSmallestBootLoaderSection
                1,               // EnablePageProgramming
                0,               // ucCacheType
                fill_b2(0x0100), // uiSramStartAddr
                0,               // ucResetType
                0,               // ucPCMaskExtended
                0,               // ucPCMaskHigh
                0,               // ucEindAddress
                fill_b2(0x1F),   // EECRAddress
            },
            {0}, // Xmega device descr.
        },
        {
            "at90pwm3b",
            0x9383,
            64,
            128, // 8192 bytes flash
            4,
            128,    // 512 bytes EEPROM
            32 * 2, // 32 interrupt vectors
            DEVFL_MKII_ONLY,
            at90pwm3b_io_registers,
            false,
            0x07,
            0x0000, // fuses
            0x66,   // osccal
            1,      // OCD revision
            {
                0 // no mkI support
            },
            {
                CMND_SET_DEVICE_DESCRIPTOR,
                {0xF8, 0x7F, 0x60, 0xFE, 0xFF, 0x33, 0xBD, 0xE0}, // ucReadIO
                {0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00}, // ucReadIOShadow
                {0xF8, 0x7F, 0x40, 0xEE, 0xFF, 0x33, 0xBC, 0xE0}, // ucWriteIO
                {0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00}, // ucWriteIOShadow
                {0x53, 0xC2, 0xC0, 0xDF, 0xF7, 0x0F, 0x00, 0x00, 0x3F, 0xE4,
                 0x00, 0x00, 0x36, 0x37, 0x01, 0xFC, 0x05, 0xFC, 0x07, 0xFC}, // ucReadExtIO
                {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // ucReadIOExtShadow
                {0x11, 0xC2, 0xC0, 0xD8, 0xF7, 0x0F, 0x00, 0x00, 0x3F, 0xE4,
                 0x00, 0x00, 0x36, 0x33, 0x01, 0xFC, 0x05, 0xFC, 0x07, 0xFC}, // ucWriteExtIO
                {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // ucWriteIOExtShadow
                0x00,                                                         // ucIDRAddress
                0X00,                                                         // ucSPMCRAddress
                0,                                                            // ucRAMPZAddress
                fill_b2(64),                                                  // uiFlashPageSize
                4,                                                            // ucEepromPageSize
                fill_b4(0x0F80),                                              // ulBootAddress
                fill_b2(0xFF),                                                // uiUpperExtIOLoc
                fill_b4(8192),                                                // ulFlashSize
                {0xBD, 0xF2, 0xBD, 0xE1, 0xBB, 0xCF, 0xB4, 0x00, 0xBE, 0x01,
                 0xB6, 0x01, 0xBC, 0x00, 0xBB, 0xBF, 0x99, 0xF9, 0xBB, 0xAF}, // ucEepromInst
                {0xB6, 0x01, 0x11},                                           // ucFlashInst
                0x3E,                                                         // ucSPHaddr
                0x3D,                                                         // ucSPLaddr
                fill_b2(8192 / 64),                                           // uiFlashpages
                0x31,                                                         // ucDWDRAddress
                0x00,                                                         // ucDWBasePC
                0x00,            // ucAllowFullPageBitstream
                fill_b2(0xF80),  // uiStartSmallestBootLoaderSection
                1,               // EnablePageProgramming
                0,               // ucCacheType
                fill_b2(0x0100), // uiSramStartAddr
                0,               // ucResetType
                0,               // ucPCMaskExtended
                0,               // ucPCMaskHigh
                0,               // ucEindAddress
                fill_b2(0x1F),   // EECRAddress
            },
            {0}, // Xmega device descr.
        },
        {
            "atmega16m1",
            0x9484,
            128,
            128, // 16384 bytes flash
            4,
            128,    // 512 bytes EEPROM
            31 * 4, // 31 interrupt vectors
            DEVFL_MKII_ONLY,
            nullptr, // registers not yet defined
            false,
            0x00,
            0x0000, // fuses
            0x66,   // osccal
            1,      // OCD revision
            {
                0 // no mkI support
            },
            {
                CMND_SET_DEVICE_DESCRIPTOR,
                {0xF8, 0x7F, 0x60, 0xF6, 0xFF, 0x33, 0xB9, 0xE0}, // ucReadIO
                {0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00}, // ucReadIOShadow
                {0xB0, 0x6D, 0x00, 0xE6, 0xFF, 0x13, 0xB8, 0xE0}, // ucWriteIO
                {0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00}, // ucWriteIOShadow
                {0x53, 0xC2, 0xE0, 0xDF, 0xF7, 0x0F, 0xF7, 0x00, 0xFF, 0xFF, 0xFF, 0x1F, 0x00, 0xFF,
                 0x07, 0x5F, 0x1D, 0xF0, 0xFF}, // ucReadExtIO
                {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // ucReadIOExtShadow
                {0x10, 0xC2, 0xE0, 0xD8, 0xF7, 0x0F, 0xF7, 0x00, 0xFF, 0xFF, 0xFF, 0x1F, 0x00, 0xF7,
                 0x07, 0x4D, 0x1C, 0xF0, 0xFF}, // ucWriteExtIO
                {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // ucWriteIOExtShadow
                0x00,                                                         // ucIDRAddress
                0x57,                                                         // ucSPMCRAddress
                0,                                                            // ucRAMPZAddress
                fill_b2(128),                                                 // uiFlashPageSize
                4,                                                            // ucEepromPageSize
                fill_b4(0x1F00),                                              // ulBootAddress
                fill_b2(0x00FA),                                              // uiUpperExtIOLoc
                fill_b4(16384),                                               // ulFlashSize
                {0xBD, 0xF2, 0xBD, 0xE1, 0xBB, 0xCF, 0xB4, 0x00, 0xBE, 0x01,
                 0xB6, 0x01, 0xBC, 0x00, 0xBB, 0xBF, 0x99, 0xF9, 0xBB, 0xAF}, // ucEepromInst
                {0xB6, 0x01, 0x11},                                           // ucFlashInst
                0x3E,                                                         // ucSPHaddr
                0x3D,                                                         // ucSPLaddr
                fill_b2(16384 / 128),                                         // uiFlashpages
                0x31,                                                         // ucDWDRAddress
                0x00,                                                         // ucDWBasePC
                0x00,            // ucAllowFullPageBitstream
                fill_b2(0x1F00), // uiStartSmallestBootLoaderSection
                1,               // EnablePageProgramming
                0,               // ucCacheType
                fill_b2(0x0100), // uiSramStartAddr
                0,               // ucResetType
                0,               // ucPCMaskExtended
                0,               // ucPCMaskHigh
                0,               // ucEindAddress
                fill_b2(0x1F),   // EECRAddress
            },
            {0}, // Xmega device descr.
        },
        {
            "atmega32m1",
            0x9584,
            128,
            256, // 32768 bytes flash
            4,
            256,    // 1024 bytes EEPROM
            31 * 4, // 31 interrupt vectors
            DEVFL_MKII_ONLY,
            atmega32m1_io_registers,
            false,
            0x00,
            0x0000, // fuses
            0x66,   // osccal
            1,      // OCD revision
            {
                0 // no mkI support
            },
            {
                CMND_SET_DEVICE_DESCRIPTOR,
                {0xF8, 0x7F, 0x60, 0xF6, 0xFF, 0x33, 0xB9, 0xE0}, // ucReadIO
                {0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00}, // ucReadIOShadow
                {0xB0, 0x6D, 0x00, 0xE6, 0xFF, 0x13, 0xB8, 0xE0}, // ucWriteIO
                {0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00}, // ucWriteIOShadow
                {0x53, 0xC2, 0xE0, 0xDF, 0xF7, 0x0F, 0xF7, 0x00, 0xFF, 0xFF, 0xFF, 0x1F, 0x00, 0xFF,
                 0x07, 0x5F, 0x1D, 0xF0, 0xFF}, // ucReadExtIO
                {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // ucReadIOExtShadow
                {0x10, 0xC2, 0xE0, 0xD8, 0xF7, 0x0F, 0xF7, 0x00, 0xFF, 0xFF, 0xFF, 0x1F, 0x00, 0xF7,
                 0x07, 0x4D, 0x1C, 0xF0, 0xFF}, // ucWriteExtIO
                {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // ucWriteIOExtShadow
                0x00,                                                         // ucIDRAddress
                0x57,                                                         // ucSPMCRAddress
                0,                                                            // ucRAMPZAddress
                fill_b2(128),                                                 // uiFlashPageSize
                4,                                                            // ucEepromPageSize
                fill_b4(0x3F00),                                              // ulBootAddress
                fill_b2(0x00FA),                                              // uiUpperExtIOLoc
                fill_b4(32768),                                               // ulFlashSize
                {0xBD, 0xF2, 0xBD, 0xE1, 0xBB, 0xCF, 0xB4, 0x00, 0xBE, 0x01,
                 0xB6, 0x01, 0xBC, 0x00, 0xBB, 0xBF, 0x99, 0xF9, 0xBB, 0xAF}, // ucEepromInst
                {0xB6, 0x01, 0x11},                                           // ucFlashInst
                0x3E,                                                         // ucSPHaddr
                0x3D,                                                         // ucSPLaddr
                fill_b2(32768 / 128),                                         // uiFlashpages
                0x31,                                                         // ucDWDRAddress
                0x00,                                                         // ucDWBasePC
                0x00,            // ucAllowFullPageBitstream
                fill_b2(0x3F00), // uiStartSmallestBootLoaderSection
                1,               // EnablePageProgramming
                0,               // ucCacheType
                fill_b2(0x0100), // uiSramStartAddr
                0,               // ucResetType
                0,               // ucPCMaskExtended
                0,               // ucPCMaskHigh
                0,               // ucEindAddress
                fill_b2(0x1F),   // EECRAddress
            },
            {0}, // Xmega device descr.
        },
        {
            "atmega64m1",
            0x9684,
            256,
            256, // 65536 bytes flash
            8,
            256,    // 2048 bytes EEPROM
            31 * 4, // 31 interrupt vectors
            DEVFL_MKII_ONLY,
            nullptr, // registers not yet defined
            false,
            0x00,
            0x0000, // fuses
            0x66,   // osccal
            1,      // OCD revision
            {
                0 // no mkI support
            },
            {
                CMND_SET_DEVICE_DESCRIPTOR,
                {0xF8, 0x7F, 0x60, 0xF6, 0xFF, 0x33, 0xB9, 0xE0}, // ucReadIO
                {0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00}, // ucReadIOShadow
                {0xB0, 0x6D, 0x00, 0xE6, 0xFF, 0x13, 0xB8, 0xE0}, // ucWriteIO
                {0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00}, // ucWriteIOShadow
                {0x53, 0xC2, 0xE0, 0xDF, 0xF7, 0x0F, 0xF7, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF,
                 0x07, 0x5F, 0x1D, 0xF0, 0xFF}, // ucReadExtIO
                {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // ucReadIOExtShadow
                {0x10, 0xC2, 0xE0, 0xD8, 0xF7, 0x0F, 0xF7, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF7,
                 0x07, 0x4D, 0x1C, 0xF0, 0xFF}, // ucWriteExtIO
                {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // ucWriteIOExtShadow
                0x00,                                                         // ucIDRAddress
                0x57,                                                         // ucSPMCRAddress
                0,                                                            // ucRAMPZAddress
                fill_b2(256),                                                 // uiFlashPageSize
                8,                                                            // ucEepromPageSize
                fill_b4(0x7E00),                                              // ulBootAddress
                fill_b2(0x00FA),                                              // uiUpperExtIOLoc
                fill_b4(65536),                                               // ulFlashSize
                {0xBD, 0xF2, 0xBD, 0xE1, 0xBB, 0xCF, 0xB4, 0x00, 0xBE, 0x01,
                 0xB6, 0x01, 0xBC, 0x00, 0xBB, 0xBF, 0x99, 0xF9, 0xBB, 0xAF}, // ucEepromInst
                {0xB6, 0x01, 0x11},                                           // ucFlashInst
                0x3E,                                                         // ucSPHaddr
                0x3D,                                                         // ucSPLaddr
                fill_b2(65536 / 256),                                         // uiFlashpages
                0x31,                                                         // ucDWDRAddress
                0x00,                                                         // ucDWBasePC
                0x00,            // ucAllowFullPageBitstream
                fill_b2(0x7E00), // uiStartSmallestBootLoaderSection
                1,               // EnablePageProgramming
                0,               // ucCacheType
                fill_b2(0x0100), // uiSramStartAddr
                0,               // ucResetType
                0,               // ucPCMaskExtended
                0,               // ucPCMaskHigh
                0,               // ucEindAddress
                fill_b2(0x1F),   // EECRAddress
            },
            {0}, // Xmega device descr.
        },
        {
            "atmega32c1",
            0x9586,
            128,
            256, // 32768 bytes flash
            4,
            256,    // 1024 bytes EEPROM
            31 * 4, // 31 interrupt vectors
            DEVFL_MKII_ONLY,
            atmega32c1_io_registers,
            false,
            0x00,
            0x0000, // fuses
            0x66,   // osccal
            1,      // OCD revision
            {
                0 // no mkI support
            },
            {
                CMND_SET_DEVICE_DESCRIPTOR,
                {0xF8, 0x7F, 0x60, 0xF6, 0xFF, 0x33, 0xB9, 0xE0}, // ucReadIO
                {0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00}, // ucReadIOShadow
                {0xB0, 0x6D, 0x00, 0xE6, 0xFF, 0x13, 0xB8, 0xE0}, // ucWriteIO
                {0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00}, // ucWriteIOShadow
                {0x53, 0xC2, 0xE0, 0xDF, 0xF7, 0x0F, 0xF7, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF,
                 0x07, 0x5F, 0x1D, 0xF0, 0xFF}, // ucReadExtIO
                {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // ucReadIOExtShadow
                {0x10, 0xC2, 0xE0, 0xD8, 0xF7, 0x0F, 0xF7, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF7,
                 0x07, 0x4D, 0x1C, 0xF0, 0xFF}, // ucWriteExtIO
                {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // ucWriteIOExtShadow
                0x00,                                                         // ucIDRAddress
                0x57,                                                         // ucSPMCRAddress
                0,                                                            // ucRAMPZAddress
                fill_b2(128),                                                 // uiFlashPageSize
                4,                                                            // ucEepromPageSize
                fill_b4(0x3F00),                                              // ulBootAddress
                fill_b2(0x00FA),                                              // uiUpperExtIOLoc
                fill_b4(32768),                                               // ulFlashSize
                {0xBD, 0xF2, 0xBD, 0xE1, 0xBB, 0xCF, 0xB4, 0x00, 0xBE, 0x01,
                 0xB6, 0x01, 0xBC, 0x00, 0xBB, 0xBF, 0x99, 0xF9, 0xBB, 0xAF}, // ucEepromInst
                {0xB6, 0x01, 0x11},                                           // ucFlashInst
                0x3E,                                                         // ucSPHaddr
                0x3D,                                                         // ucSPLaddr
                fill_b2(32768 / 128),                                         // uiFlashpages
                0x31,                                                         // ucDWDRAddress
                0x00,                                                         // ucDWBasePC
                0x00,            // ucAllowFullPageBitstream
                fill_b2(0x3F00), // uiStartSmallestBootLoaderSection
                1,               // EnablePageProgramming
                0,               // ucCacheType
                fill_b2(0x0100), // uiSramStartAddr
                0,               // ucResetType
                0,               // ucPCMaskExtended
                0,               // ucPCMaskHigh
                0,               // ucEindAddress
                fill_b2(0x1F),   // EECRAddress
            },
            {0}, // Xmega device descr.
        },
        {
            "atmega64c1",
            0x9686,
            256,
            256, // 65536 bytes flash
            8,
            256,    // 2048 bytes EEPROM
            31 * 4, // 31 interrupt vectors
            DEVFL_MKII_ONLY,
            nullptr, // registers not yet defined
            false,
            0x00,
            0x0000, // fuses
            0x66,   // osccal
            1,      // OCD revision
            {
                0 // no mkI support
            },
            {
                CMND_SET_DEVICE_DESCRIPTOR,
                {0xF8, 0x7F, 0x60, 0xF6, 0xFF, 0x33, 0xB9, 0xE0}, // ucReadIO
                {0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00}, // ucReadIOShadow
                {0xB0, 0x6D, 0x00, 0xE6, 0xFF, 0x13, 0xB8, 0xE0}, // ucWriteIO
                {0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00}, // ucWriteIOShadow
                {0x53, 0xC2, 0xE0, 0xDF, 0xF7, 0x0F, 0xF7, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF,
                 0x07, 0x5F, 0x1D, 0xF0, 0xFF}, // ucReadExtIO
                {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // ucReadIOExtShadow
                {0x10, 0xC2, 0xE0, 0xD8, 0xF7, 0x0F, 0xF7, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF7,
                 0x07, 0x4D, 0x1C, 0xF0, 0xFF}, // ucWriteExtIO
                {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // ucWriteIOExtShadow
                0x00,                                                         // ucIDRAddress
                0x57,                                                         // ucSPMCRAddress
                0,                                                            // ucRAMPZAddress
                fill_b2(256),                                                 // uiFlashPageSize
                8,                                                            // ucEepromPageSize
                fill_b4(0x7E00),                                              // ulBootAddress
                fill_b2(0x00FA),                                              // uiUpperExtIOLoc
                fill_b4(65536),                                               // ulFlashSize
                {0xBD, 0xF2, 0xBD, 0xE1, 0xBB, 0xCF, 0xB4, 0x00, 0xBE, 0x01,
                 0xB6, 0x01, 0xBC, 0x00, 0xBB, 0xBF, 0x99, 0xF9, 0xBB, 0xAF}, // ucEepromInst
                {0xB6, 0x01, 0x11},                                           // ucFlashInst
                0x3E,                                                         // ucSPHaddr
                0x3D,                                                         // ucSPLaddr
                fill_b2(65536 / 256),                                         // uiFlashpages
                0x31,                                                         // ucDWDRAddress
                0x00,                                                         // ucDWBasePC
                0x00,            // ucAllowFullPageBitstream
                fill_b2(0x7E00), // uiStartSmallestBootLoaderSection
                1,               // EnablePageProgramming
                0,               // ucCacheType
                fill_b2(0x0100), // uiSramStartAddr
                0,               // ucResetType
                0,               // ucPCMaskExtended
                0,               // ucPCMaskHigh
                0,               // ucEindAddress
                fill_b2(0x1F),   // EECRAddress
            },
            {0}, // Xmega device descr.
        },
        {
            "attiny24",
            0x910B,
            32,
            64, // 2048 bytes flash
            4,
            32,     // 128 bytes EEPROM
            17 * 2, // 17 interrupt vectors
            DEVFL_MKII_ONLY,
            attiny24_io_registers,
            false,
            0x07,
            0x0000, // fuses
            0x51,   // osccal
            1,      // OCD revision
            {
                0 // no mkI support
            },
            {
                CMND_SET_DEVICE_DESCRIPTOR,
                {0xFB, 0xF9, 0xFD, 0xFF, 0x7F, 0xFF, 0xFF, 0xFF}, // ucReadIO
                {0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00}, // ucReadIOShadow
                {0x8B, 0xB0, 0xFC, 0xFF, 0x7D, 0xFF, 0xFD, 0xFA}, // ucWriteIO
                {0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00}, // ucWriteIOShadow
                {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // ucReadExtIO
                {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // ucReadIOExtShadow
                {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // ucWriteExtIO
                {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // ucWriteIOExtShadow
                0x27,                                                         // ucIDRAddress
                0X57,                                                         // ucSPMCRAddress
                0,                                                            // ucRAMPZAddress
                fill_b2(32),                                                  // uiFlashPageSize
                4,                                                            // ucEepromPageSize
                fill_b4(0x0000),                                              // ulBootAddress
                fill_b2(0x00),                                                // uiUpperExtIOLoc
                fill_b4(2048),                                                // ulFlashSize
                {
                    0xBB, 0xFF, 0xBB, 0xEE, 0xBB, 0xCC, 0xB2, 0x0D, 0xBC, 0x07,
                    0xB4, 0x07, 0xBA, 0x0D, 0xBB, 0xBC, 0x99, 0xE1, 0xBB, 0xAC,
                },                  // ucEepromInst
                {0xB4, 0x07, 0x17}, // ucFlashInst
                0x3E,               // ucSPHaddr
                0x3D,               // ucSPLaddr
                fill_b2(2048 / 32), // uiFlashpages
                0x27,               // ucDWDRAddress
                0x00,               // ucDWBasePC
                0x00,               // ucAllowFullPageBitstream
                fill_b2(0x00),      // uiStartSmallestBootLoaderSection
                1,                  // EnablePageProgramming
                0,                  // ucCacheType
                fill_b2(0x60),      // uiSramStartAddr
                0,                  // ucResetType
                0,                  // ucPCMaskExtended
                0,                  // ucPCMaskHigh
                0,                  // ucEindAddress
                fill_b2(0x1C),      // EECRAddress
            },
            {0}, // Xmega device descr.
        },
        {
            "attiny44",
            0x9207,
            64,
            64, // 4096 bytes flash
            4,
            64,     // 256 bytes EEPROM
            17 * 2, // 17 interrupt vectors
            DEVFL_MKII_ONLY,
            attiny44_io_registers,
            false,
            0x07,
            0x0000, // fuses
            0x51,   // osccal
            1,      // OCD revision
            {
                0 // no mkI support
            },
            {
                CMND_SET_DEVICE_DESCRIPTOR,
                {0xFB, 0xF9, 0xFD, 0xFF, 0x7F, 0xFF, 0xFF, 0xFF}, // ucReadIO
                {0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00}, // ucReadIOShadow
                {0x8B, 0xB0, 0xFC, 0xFF, 0x7D, 0xFF, 0xFD, 0xFA}, // ucWriteIO
                {0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00}, // ucWriteIOShadow
                {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // ucReadExtIO
                {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // ucReadIOExtShadow
                {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // ucWriteExtIO
                {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // ucWriteIOExtShadow
                0x27,                                                         // ucIDRAddress
                0X57,                                                         // ucSPMCRAddress
                0,                                                            // ucRAMPZAddress
                fill_b2(64),                                                  // uiFlashPageSize
                4,                                                            // ucEepromPageSize
                fill_b4(0x0000),                                              // ulBootAddress
                fill_b2(0x00),                                                // uiUpperExtIOLoc
                fill_b4(4096),                                                // ulFlashSize
                {
                    0xBB, 0xFF, 0xBB, 0xEE, 0xBB, 0xCC, 0xB2, 0x0D, 0xBC, 0x07,
                    0xB4, 0x07, 0xBA, 0x0D, 0xBB, 0xBC, 0x99, 0xE1, 0xBB, 0xAC,
                },                  // ucEepromInst
                {0xB4, 0x07, 0x17}, // ucFlashInst
                0x3E,               // ucSPHaddr
                0x3D,               // ucSPLaddr
                fill_b2(4096 / 64), // uiFlashpages
                0x27,               // ucDWDRAddress
                0x00,               // ucDWBasePC
                0x00,               // ucAllowFullPageBitstream
                fill_b2(0x00),      // uiStartSmallestBootLoaderSection
                1,                  // EnablePageProgramming
                0,                  // ucCacheType
                fill_b2(0x60),      // uiSramStartAddr
                0,                  // ucResetType
                0,                  // ucPCMaskExtended
                0,                  // ucPCMaskHigh
                0,                  // ucEindAddress
                fill_b2(0x1C),      // EECRAddress
            },
            {0}, // Xmega device descr.
        },
        {
            "attiny84",
            0x930C,
            64,
            128, // 8192 bytes flash
            4,
            128,    // 512 bytes EEPROM
            17 * 2, // 17 interrupt vectors
            DEVFL_MKII_ONLY,
            attiny84_io_registers,
            false,
            0x07,
            0x0000, // fuses
            0x51,   // osccal
            1,      // OCD revision
            {
                0 // no mkI support
            },
            {
                CMND_SET_DEVICE_DESCRIPTOR,
                {0xFB, 0xF9, 0xFD, 0xFF, 0x7F, 0xFF, 0xFF, 0xFF}, // ucReadIO
                {0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00}, // ucReadIOShadow
                {0x8B, 0xB0, 0xFC, 0xFF, 0x7D, 0xFF, 0xFD, 0xFA}, // ucWriteIO
                {0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00}, // ucWriteIOShadow
                {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // ucReadExtIO
                {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // ucReadIOExtShadow
                {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // ucWriteExtIO
                {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // ucWriteIOExtShadow
                0x27,                                                         // ucIDRAddress
                0X57,                                                         // ucSPMCRAddress
                0,                                                            // ucRAMPZAddress
                fill_b2(64),                                                  // uiFlashPageSize
                4,                                                            // ucEepromPageSize
                fill_b4(0x0000),                                              // ulBootAddress
                fill_b2(0x00),                                                // uiUpperExtIOLoc
                fill_b4(8192),                                                // ulFlashSize
                {
                    0xBB, 0xFF, 0xBB, 0xEE, 0xBB, 0xCC, 0xB2, 0x0D, 0xBC, 0x07,
                    0xB4, 0x07, 0xBA, 0x0D, 0xBB, 0xBC, 0x99, 0xE1, 0xBB, 0xAC,
                },                  // ucEepromInst
                {0xB4, 0x07, 0x17}, // ucFlashInst
                0x3E,               // ucSPHaddr
                0x3D,               // ucSPLaddr
                fill_b2(8192 / 64), // uiFlashpages
                0x27,               // ucDWDRAddress
                0x00,               // ucDWBasePC
                0x00,               // ucAllowFullPageBitstream
                fill_b2(0x00),      // uiStartSmallestBootLoaderSection
                1,                  // EnablePageProgramming
                0,                  // ucCacheType
                fill_b2(0x60),      // uiSramStartAddr
                0,                  // ucResetType
                0,                  // ucPCMaskExtended
                0,                  // ucPCMaskHigh
                0,                  // ucEindAddress
                fill_b2(0x1C),      // EECRAddress
            },
            {0}, // Xmega device descr.
        },
        {
            "attiny25",
            0x9108,
            32,
            64, // 2048 bytes flash
            4,
            32,     // 128 bytes EEPROM
            15 * 2, // 15 interrupt vectors
            DEVFL_MKII_ONLY,
            attiny25_io_registers,
            false,
            0x07,
            0x0000, // fuses
            0x51,   // osccal
            1,      // OCD revision
            {
                0 // no mkI support
            },
            {
                CMND_SET_DEVICE_DESCRIPTOR,
                {0xF8, 0xE1, 0xFF, 0xF1, 0xFB, 0xFF, 0xBF, 0xAF}, // ucReadIO
                {0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00}, // ucReadIOShadow
                {0xC8, 0xE1, 0xFF, 0x71, 0xBB, 0x7F, 0xAD, 0xAB}, // ucWriteIO
                {0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00}, // ucWriteIOShadow
                {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // ucReadExtIO
                {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // ucReadIOExtShadow
                {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // ucWriteExtIO
                {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // ucWriteIOExtShadow
                0x00,                                                         // ucIDRAddress
                0X00,                                                         // ucSPMCRAddress
                0,                                                            // ucRAMPZAddress
                fill_b2(32),                                                  // uiFlashPageSize
                4,                                                            // ucEepromPageSize
                fill_b4(0x0000),                                              // ulBootAddress
                fill_b2(0x00),                                                // uiUpperExtIOLoc
                fill_b4(2048),                                                // ulFlashSize
                {0xBB, 0xFF, 0xBB, 0xEE, 0xBB, 0xCC, 0xB2, 0x0D, 0xBC, 0x02,
                 0xB4, 0x02, 0xBA, 0x0D, 0xBB, 0xBC, 0x99, 0xE1, 0xBB, 0xAC}, // ucEepromInst
                {0xB4, 0x02, 0x12},                                           // ucFlashInst
                0x3E,                                                         // ucSPHaddr
                0x3D,                                                         // ucSPLaddr
                fill_b2(2048 / 32),                                           // uiFlashpages
                0x22,                                                         // ucDWDRAddress
                0x00,                                                         // ucDWBasePC
                0x00,          // ucAllowFullPageBitstream
                fill_b2(0x00), // uiStartSmallestBootLoaderSection
                1,             // EnablePageProgramming
                0,             // ucCacheType
                fill_b2(0x60), // uiSramStartAddr
                0,             // ucResetType
                0,             // ucPCMaskExtended
                0,             // ucPCMaskHigh
                0,             // ucEindAddress
                fill_b2(0x1C), // EECRAddress
            },
            {0}, // Xmega device descr.
        },
        {
            "attiny45",
            0x9206,
            64,
            64, // 4096 bytes flash
            4,
            64,     // 256 bytes EEPROM
            15 * 2, // 15 interrupt vectors
            DEVFL_MKII_ONLY,
            attiny45_io_registers,
            false,
            0x07,
            0x0000, // fuses
            0x51,   // osccal
            1,      // OCD revision
            {
                0 // no mkI support
            },
            {
                CMND_SET_DEVICE_DESCRIPTOR,
                {0xF8, 0xE1, 0xFF, 0xF1, 0xFB, 0xFF, 0xBF, 0xEF}, // ucReadIO
                {0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00}, // ucReadIOShadow
                {0xC8, 0xE1, 0xFF, 0x71, 0xBB, 0x7F, 0xAD, 0xEB}, // ucWriteIO
                {0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00}, // ucWriteIOShadow
                {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // ucReadExtIO
                {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // ucReadIOExtShadow
                {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // ucWriteExtIO
                {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // ucWriteIOExtShadow
                0x00,                                                         // ucIDRAddress
                0X00,                                                         // ucSPMCRAddress
                0,                                                            // ucRAMPZAddress
                fill_b2(64),                                                  // uiFlashPageSize
                4,                                                            // ucEepromPageSize
                fill_b4(0x0000),                                              // ulBootAddress
                fill_b2(0x00),                                                // uiUpperExtIOLoc
                fill_b4(4096),                                                // ulFlashSize
                {0xBB, 0xFF, 0xBB, 0xEE, 0xBB, 0xCC, 0xB2, 0x0D, 0xBC, 0x02,
                 0xB4, 0x02, 0xBA, 0x0D, 0xBB, 0xBC, 0x99, 0xE1, 0xBB, 0xAC}, // ucEepromInst
                {0xB4, 0x02, 0x12},                                           // ucFlashInst
                0x3E,                                                         // ucSPHaddr
                0x3D,                                                         // ucSPLaddr
                fill_b2(4096 / 64),                                           // uiFlashpages
                0x22,                                                         // ucDWDRAddress
                0x00,                                                         // ucDWBasePC
                0x00,          // ucAllowFullPageBitstream
                fill_b2(0x00), // uiStartSmallestBootLoaderSection
                1,             // EnablePageProgramming
                0,             // ucCacheType
                fill_b2(0x60), // uiSramStartAddr
                0,             // ucResetType
                0,             // ucPCMaskExtended
                0,             // ucPCMaskHigh
                0,             // ucEindAddress
                fill_b2(0x1C), // EECRAddress
            },
            {0}, // Xmega device descr.
        },
        {
            "attiny85",
            0x930B,
            64,
            128, // 8192 bytes flash
            4,
            128,    // 512 bytes EEPROM
            15 * 2, // 15 interrupt vectors
            DEVFL_MKII_ONLY,
            attiny85_io_registers,
            false,
            0x07,
            0x0000, // fuses
            0x51,   // osccal
            1,      // OCD revision
            {
                0 // no mkI support
            },
            {
                CMND_SET_DEVICE_DESCRIPTOR,
                {0xF8, 0xE1, 0xFF, 0xF1, 0xFB, 0xFF, 0xBF, 0xEF}, // ucReadIO
                {0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00}, // ucReadIOShadow
                {0xC8, 0xE1, 0xFF, 0x71, 0xBB, 0x7F, 0xAD, 0xEB}, // ucWriteIO
                {0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00}, // ucWriteIOShadow
                {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // ucReadExtIO
                {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // ucReadIOExtShadow
                {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // ucWriteExtIO
                {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // ucWriteIOExtShadow
                0x00,                                                         // ucIDRAddress
                0X00,                                                         // ucSPMCRAddress
                0,                                                            // ucRAMPZAddress
                fill_b2(64),                                                  // uiFlashPageSize
                4,                                                            // ucEepromPageSize
                fill_b4(0x0000),                                              // ulBootAddress
                fill_b2(0x00),                                                // uiUpperExtIOLoc
                fill_b4(8192),                                                // ulFlashSize
                {0xBB, 0xFF, 0xBB, 0xEE, 0xBB, 0xCC, 0xB2, 0x0D, 0xBC, 0x02,
                 0xB4, 0x02, 0xBA, 0x0D, 0xBB, 0xBC, 0x99, 0xE1, 0xBB, 0xAC}, // ucEepromInst
                {0xB4, 0x02, 0x12},                                           // ucFlashInst
                0x3E,                                                         // ucSPHaddr
                0x3D,                                                         // ucSPLaddr
                fill_b2(8192 / 64),                                           // uiFlashpages
                0x22,                                                         // ucDWDRAddress
                0x00,                                                         // ucDWBasePC
                0x00,          // ucAllowFullPageBitstream
                fill_b2(0x00), // uiStartSmallestBootLoaderSection
                1,             // EnablePageProgramming
                0,             // ucCacheType
                fill_b2(0x60), // uiSramStartAddr
                0,             // ucResetType
                0,             // ucPCMaskExtended
                0,             // ucPCMaskHigh
                0,             // ucEindAddress
                fill_b2(0x1C), // EECRAddress
            },
            {0}, // Xmega device descr.
        },
        {
            "attiny261",
            0x910C,
            32,
            64, // 2048 bytes flash
            4,
            32,     // 128 bytes EEPROM
            19 * 2, // 19 interrupt vectors
            DEVFL_MKII_ONLY,
            attiny261_io_registers,
            false,
            0x07,
            0x0000, // fuses
            0x51,   // osccal
            1,      // OCD revision
            {
                0 // no mkI support
            },
            {
                CMND_SET_DEVICE_DESCRIPTOR,
                {0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 0xFB, 0xFF, 0xEF}, // ucReadIO
                {0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00}, // ucReadIOShadow
                {0x8F, 0xBF, 0xBE, 0xFD, 0xFC, 0xBA, 0xFD, 0xEA}, // ucWriteIO
                {0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00}, // ucWriteIOShadow
                {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // ucReadExtIO
                {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // ucReadIOExtShadow
                {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // ucWriteExtIO
                {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // ucWriteIOExtShadow
                0x00,                                                         // ucIDRAddress
                0x57,                                                         // ucSPMCRAddress
                0,                                                            // ucRAMPZAddress
                fill_b2(32),                                                  // uiFlashPageSize
                4,                                                            // ucEepromPageSize
                fill_b4(0),                                                   // ulBootAddress
                fill_b2(0x0000),                                              // uiUpperExtIOLoc
                fill_b4(2048),                                                // ulFlashSize
                {0xBB, 0xFF, 0xBB, 0xEE, 0xBB, 0xCC, 0xB2, 0x0D, 0xBC, 0x00,
                 0xB4, 0x00, 0xBA, 0x0D, 0xBB, 0xBC, 0x99, 0xE1, 0xBB, 0xAC}, // ucEepromInst
                {0xB4, 0x00, 0x10},                                           // ucFlashInst
                0x3E,                                                         // ucSPHaddr
                0x3D,                                                         // ucSPLaddr
                fill_b2(2048 / 32),                                           // uiFlashpages
                0x20,                                                         // ucDWDRAddress
                0x00,                                                         // ucDWBasePC
                0x00,          // ucAllowFullPageBitstream
                fill_b2(0x00), // uiStartSmallestBootLoaderSection
                1,             // EnablePageProgramming
                0,             // ucCacheType
                fill_b2(0x60), // uiSramStartAddr
                0,             // ucResetType
                0,             // ucPCMaskExtended
                0,             // ucPCMaskHigh
                0,             // ucEindAddress
                fill_b2(0x1C), // EECRAddress
            },
            {0}, // Xmega device descr.
        },
        {
            "attiny461",
            0x9208,
            64,
            64, // 4096 bytes flash
            4,
            64,     // 256 bytes EEPROM
            19 * 2, // 19 interrupt vectors
            DEVFL_MKII_ONLY,
            attiny461_io_registers,
            false,
            0x07,
            0x0000, // fuses
            0x51,   // osccal
            1,      // OCD revision
            {
                0 // no mkI support
            },
            {
                CMND_SET_DEVICE_DESCRIPTOR,
                {0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 0xFB, 0xFF, 0xEF}, // ucReadIO
                {0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00}, // ucReadIOShadow
                {0x8F, 0xBF, 0xBE, 0xFD, 0xFC, 0xBA, 0xFD, 0xEA}, // ucWriteIO
                {0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00}, // ucWriteIOShadow
                {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // ucReadExtIO
                {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // ucReadIOExtShadow
                {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // ucWriteExtIO
                {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // ucWriteIOExtShadow
                0x00,                                                         // ucIDRAddress
                0x57,                                                         // ucSPMCRAddress
                0,                                                            // ucRAMPZAddress
                fill_b2(64),                                                  // uiFlashPageSize
                4,                                                            // ucEepromPageSize
                fill_b4(0),                                                   // ulBootAddress
                fill_b2(0x0000),                                              // uiUpperExtIOLoc
                fill_b4(4096),                                                // ulFlashSize
                {0xBB, 0xFF, 0xBB, 0xEE, 0xBB, 0xCC, 0xB2, 0x0D, 0xBC, 0x00,
                 0xB4, 0x00, 0xBA, 0x0D, 0xBB, 0xBC, 0x99, 0xE1, 0xBB, 0xAC}, // ucEepromInst
                {0xB4, 0x00, 0x10},                                           // ucFlashInst
                0x3E,                                                         // ucSPHaddr
                0x3D,                                                         // ucSPLaddr
                fill_b2(4096 / 64),                                           // uiFlashpages
                0x20,                                                         // ucDWDRAddress
                0x00,                                                         // ucDWBasePC
                0x00,          // ucAllowFullPageBitstream
                fill_b2(0x00), // uiStartSmallestBootLoaderSection
                1,             // EnablePageProgramming
                0,             // ucCacheType
                fill_b2(0x60), // uiSramStartAddr
                0,             // ucResetType
                0,             // ucPCMaskExtended
                0,             // ucPCMaskHigh
                0,             // ucEindAddress
                fill_b2(0x1C), // EECRAddress
            },
            {0}, // Xmega device descr.
        },
        {
            "attiny861",
            0x930D,
            64,
            128, // 8192 bytes flash
            4,
            128,    // 512 bytes EEPROM
            19 * 2, // 19 interrupt vectors
            DEVFL_MKII_ONLY,
            attiny861_io_registers,
            false,
            0x07,
            0x0000, // fuses
            0x51,   // osccal
            1,      // OCD revision
            {
                0 // no mkI support
            },
            {
                CMND_SET_DEVICE_DESCRIPTOR,
                {0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 0xFB, 0xFF, 0xEF}, // ucReadIO
                {0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00}, // ucReadIOShadow
                {0x8F, 0xBF, 0xBE, 0xFD, 0xFC, 0xBA, 0xFD, 0xEA}, // ucWriteIO
                {0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00}, // ucWriteIOShadow
                {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // ucReadExtIO
                {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // ucReadIOExtShadow
                {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // ucWriteExtIO
                {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // ucWriteIOExtShadow
                0x00,                                                         // ucIDRAddress
                0x57,                                                         // ucSPMCRAddress
                0,                                                            // ucRAMPZAddress
                fill_b2(64),                                                  // uiFlashPageSize
                4,                                                            // ucEepromPageSize
                fill_b4(0),                                                   // ulBootAddress
                fill_b2(0x0000),                                              // uiUpperExtIOLoc
                fill_b4(8192),                                                // ulFlashSize
                {0xBB, 0xFF, 0xBB, 0xEE, 0xBB, 0xCC, 0xB2, 0x0D, 0xBC, 0x00,
                 0xB4, 0x00, 0xBA, 0x0D, 0xBB, 0xBC, 0x99, 0xE1, 0xBB, 0xAC}, // ucEepromInst
                {0xB4, 0x00, 0x10},                                           // ucFlashInst
                0x3E,                                                         // ucSPHaddr
                0x3D,                                                         // ucSPLaddr
                fill_b2(8192 / 64),                                           // uiFlashpages
                0x20,                                                         // ucDWDRAddress
                0x00,                                                         // ucDWBasePC
                0x00,          // ucAllowFullPageBitstream
                fill_b2(0x00), // uiStartSmallestBootLoaderSection
                1,             // EnablePageProgramming
                0,             // ucCacheType
                fill_b2(0x60), // uiSramStartAddr
                0,             // ucResetType
                0,             // ucPCMaskExtended
                0,             // ucPCMaskHigh
                0,             // ucEindAddress
                fill_b2(0x1C), // EECRAddress
            },
            {0}, // Xmega device descr.
        },
        {
            "at90can32",
            0x9581,
            256,
            128, // 32768 bytes flash
            8,
            128,    // 1024 bytes EEPROM
            37 * 4, // 37 interrupt vectors
            DEVFL_MKII_ONLY,
            at90can32_io_registers,
            false,
            0x07,
            0x8000, // fuses
            0x66,   // osccal
            3,      // OCD revision
            {
                0 // no mkI support
            },
            {
                CMND_SET_DEVICE_DESCRIPTOR,
                {0xFF, 0xFF, 0xFF, 0xF1, 0xDF, 0x3C, 0xB9, 0xE8}, // ucReadIO
                {0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00}, // ucReadIOShadow
                {0xB6, 0x6D, 0x1B, 0xE0, 0xDF, 0x1C, 0xB8, 0xE8}, // ucWriteIO
                {0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00}, // ucWriteIOShadow
                {0x43, 0xC6, 0x33, 0xDF, 0xF7, 0x3F, 0xF7, 0x3F, 0x00, 0x00,
                 0x4D, 0x1F, 0x37, 0x37, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0x07}, // ucReadExtIO
                {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // ucReadIOExtShadow
                {0x43, 0xC6, 0x33, 0xD8, 0xF7, 0x3F, 0xF7, 0x3F, 0x00, 0x00,
                 0x4D, 0x0F, 0x36, 0x36, 0x00, 0xC9, 0x3C, 0xF0, 0xFF, 0x04}, // ucWriteExtIO
                {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // ucWriteIOExtShadow
                0x31,                                                         // ucIDRAddress
                0x57,                                                         // ucSPMCRAddress
                0x3B,                                                         // ucRAMPZAddress
                fill_b2(256),                                                 // uiFlashPageSize
                8,                                                            // ucEepromPageSize
                fill_b4(0x3E00),                                              // ulBootAddress
                fill_b2(0xFA),                                                // uiUpperExtIOLoc
                fill_b4(32768),                                               // ulFlashSize
                {0x00},                                                       // ucEepromInst
                {0x00},                                                       // ucFlashInst
                0x3E,                                                         // ucSPHaddr
                0x3D,                                                         // ucSPLaddr
                fill_b2(32768 / 256),                                         // uiFlashpages
                0x00,                                                         // ucDWDRAddress
                0x00,                                                         // ucDWBasePC
                0x00,            // ucAllowFullPageBitstream
                fill_b2(0x00),   // uiStartSmallestBootLoaderSection
                1,               // EnablePageProgramming
                0x01,            // ucCacheType
                fill_b2(0x0100), // uiSramStartAddr
                0,               // ucResetType
                0,               // ucPCMaskExtended
                0,               // ucPCMaskHigh
                0,               // ucEindAddress
                fill_b2(0x1F),   // EECRAddress
            },
            {0}, // Xmega device descr.
        },
        {
            "at90can64",
            0x9681,
            256,
            256, // 65536 bytes flash
            8,
            256,    // 2048 bytes EEPROM
            37 * 4, // 37 interrupt vectors
            DEVFL_MKII_ONLY,
            at90can64_io_registers,
            false,
            0x07,
            0x8000, // fuses
            0x66,   // osccal
            3,      // OCD revision
            {
                0 // no mkI support
            },
            {
                CMND_SET_DEVICE_DESCRIPTOR,
                {0xFF, 0xFF, 0xFF, 0xF1, 0xDF, 0x3C, 0xB9, 0xE8}, // ucReadIO
                {0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00}, // ucReadIOShadow
                {0xB6, 0x6D, 0x1B, 0xE0, 0xDF, 0x1C, 0xB8, 0xE8}, // ucWriteIO
                {0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00}, // ucWriteIOShadow
                {0x43, 0xC6, 0x33, 0xDF, 0xF7, 0x3F, 0xF7, 0x3F, 0x00, 0x00,
                 0x4D, 0x1F, 0x37, 0x37, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0x07}, // ucReadExtIO
                {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // ucReadIOExtShadow
                {0x43, 0xC6, 0x33, 0xD8, 0xF7, 0x3F, 0xF7, 0x3F, 0x00, 0x00,
                 0x4D, 0x0F, 0x36, 0x36, 0x00, 0xC9, 0x3C, 0xF0, 0xFF, 0x04}, // ucWriteExtIO
                {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // ucWriteIOExtShadow
                0x31,                                                         // ucIDRAddress
                0x57,                                                         // ucSPMCRAddress
                0x3B,                                                         // ucRAMPZAddress
                fill_b2(256),                                                 // uiFlashPageSize
                8,                                                            // ucEepromPageSize
                fill_b4(0x7E00),                                              // ulBootAddress
                fill_b2(0xFA),                                                // uiUpperExtIOLoc
                fill_b4(65536),                                               // ulFlashSize
                {0x00},                                                       // ucEepromInst
                {0x00},                                                       // ucFlashInst
                0x3E,                                                         // ucSPHaddr
                0x3D,                                                         // ucSPLaddr
                fill_b2(65536 / 256),                                         // uiFlashpages
                0x00,                                                         // ucDWDRAddress
                0x00,                                                         // ucDWBasePC
                0x00,            // ucAllowFullPageBitstream
                fill_b2(0x00),   // uiStartSmallestBootLoaderSection
                1,               // EnablePageProgramming
                0x01,            // ucCacheType
                fill_b2(0x0100), // uiSramStartAddr
                0,               // ucResetType
                0,               // ucPCMaskExtended
                0,               // ucPCMaskHigh
                0,               // ucEindAddress
                fill_b2(0x1F),   // EECRAddress
            },
            {0}, // Xmega device descr.
        },
        {
            "at90pwm216",
            0x9483,
            64,
            256, // 16384 bytes flash
            4,
            128,    // 512 bytes EEPROM
            32 * 4, // 32 interrupt vectors
            DEVFL_MKII_ONLY,
            at90pwm216_io_registers,
            false,
            0x07,
            0x0000, // fuses
            0x66,   // osccal
            1,      // OCD revision
            {
                0 // no mkI support
            },
            {
                CMND_SET_DEVICE_DESCRIPTOR,
                {0xF8, 0x7F, 0x60, 0xFE, 0xFF, 0x33, 0xB9, 0xE0}, // ucReadIO
                {0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00}, // ucReadIOShadow
                {0xF8, 0x7F, 0x40, 0xEE, 0xFF, 0x33, 0xBC, 0xE0}, // ucWriteIO
                {0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00}, // ucWriteIOShadow
                {0x53, 0xC2, 0xC0, 0xDF, 0xF7, 0x0F, 0x00, 0x00, 0x3F, 0xE4,
                 0x00, 0x00, 0x37, 0x37, 0xFD, 0xFF, 0x00, 0x00, 0xFF, 0xFF}, // ucReadExtIO
                {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // ucReadIOExtShadow
                {0x11, 0xC2, 0xC0, 0xD8, 0xF7, 0x0F, 0x00, 0x00, 0x3F, 0xE4,
                 0x00, 0x00, 0x36, 0x33, 0x01, 0xFC, 0x05, 0xFC, 0x07, 0xFC}, // ucWriteExtIO
                {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // ucWriteIOExtShadow
                0x00,                                                         // ucIDRAddress
                0X00,                                                         // ucSPMCRAddress
                0,                                                            // ucRAMPZAddress
                fill_b2(64),                                                  // uiFlashPageSize
                4,                                                            // ucEepromPageSize
                fill_b4(0x1F00),                                              // ulBootAddress
                fill_b2(0xFF),                                                // uiUpperExtIOLoc
                fill_b4(16384),                                               // ulFlashSize
                {0xBD, 0xF2, 0xBD, 0xE1, 0xBB, 0xCF, 0xB4, 0x00, 0xBE, 0x01,
                 0xB6, 0x01, 0xBC, 0x00, 0xBB, 0xBF, 0x99, 0xF9, 0xBB, 0xAF}, // ucEepromInst
                {0xB6, 0x01, 0x11},                                           // ucFlashInst
                0x3E,                                                         // ucSPHaddr
                0x3D,                                                         // ucSPLaddr
                fill_b2(16384 / 64),                                          // uiFlashpages
                0x31,                                                         // ucDWDRAddress
                0x00,                                                         // ucDWBasePC
                0x00,            // ucAllowFullPageBitstream
                fill_b2(0x1F00), // uiStartSmallestBootLoaderSection
                1,               // EnablePageProgramming
                0,               // ucCacheType
                fill_b2(0x0100), // uiSramStartAddr
                0,               // ucResetType
                0,               // ucPCMaskExtended
                0,               // ucPCMaskHigh
                0,               // ucEindAddress
                fill_b2(0x1F),   // EECRAddress
            },
            {0}, // Xmega device descr.
        },
        {
            "at90pwm316",
            0x9483,
            64,
            256, // 16384 bytes flash
            4,
            128,    // 512 bytes EEPROM
            32 * 4, // 32 interrupt vectors
            DEVFL_MKII_ONLY,
            at90pwm316_io_registers,
            false,
            0x07,
            0x0000, // fuses
            0x66,   // osccal
            1,      // OCD revision
            {
                0 // no mkI support
            },
            {
                CMND_SET_DEVICE_DESCRIPTOR,
                {0xF8, 0x7F, 0x60, 0xFE, 0xFF, 0x33, 0xB9, 0xE0}, // ucReadIO
                {0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00}, // ucReadIOShadow
                {0xF8, 0x7F, 0x40, 0xEE, 0xFF, 0x33, 0xBC, 0xE0}, // ucWriteIO
                {0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00}, // ucWriteIOShadow
                {0x53, 0xC2, 0xC0, 0xDF, 0xF7, 0x0F, 0x00, 0x00, 0x3F, 0xE4,
                 0x00, 0x00, 0x37, 0x37, 0xFD, 0xFF, 0xFD, 0xFF, 0xFF, 0xFF}, // ucReadExtIO
                {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // ucReadIOExtShadow
                {0x11, 0xC2, 0xC0, 0xD8, 0xF7, 0x0F, 0x00, 0x00, 0x3F, 0xE4,
                 0x00, 0x00, 0x36, 0x33, 0x01, 0xFC, 0x05, 0xFC, 0x07, 0xFC}, // ucWriteExtIO
                {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // ucWriteIOExtShadow
                0x00,                                                         // ucIDRAddress
                0X00,                                                         // ucSPMCRAddress
                0,                                                            // ucRAMPZAddress
                fill_b2(64),                                                  // uiFlashPageSize
                4,                                                            // ucEepromPageSize
                fill_b4(0x1F00),                                              // ulBootAddress
                fill_b2(0xFF),                                                // uiUpperExtIOLoc
                fill_b4(16384),                                               // ulFlashSize
                {0xBD, 0xF2, 0xBD, 0xE1, 0xBB, 0xCF, 0xB4, 0x00, 0xBE, 0x01,
                 0xB6, 0x01, 0xBC, 0x00, 0xBB, 0xBF, 0x99, 0xF9, 0xBB, 0xAF}, // ucEepromInst
                {0xB6, 0x01, 0x11},                                           // ucFlashInst
                0x3E,                                                         // ucSPHaddr
                0x3D,                                                         // ucSPLaddr
                fill_b2(16384 / 64),                                          // uiFlashpages
                0x31,                                                         // ucDWDRAddress
                0x00,                                                         // ucDWBasePC
                0x00,            // ucAllowFullPageBitstream
                fill_b2(0x1F00), // uiStartSmallestBootLoaderSection
                1,               // EnablePageProgramming
                0,               // ucCacheType
                fill_b2(0x0100), // uiSramStartAddr
                0,               // ucResetType
                0,               // ucPCMaskExtended
                0,               // ucPCMaskHigh
                0,               // ucEindAddress
                fill_b2(0x1F),   // EECRAddress
            },
            {0}, // Xmega device descr.
        },
        {
            "at90usb1287",
            0x9782,
            256,
            512, // 131072 bytes flash
            8,
            512,    // 4096 bytes EEPROM
            38 * 4, // 38 interrupt vectors
            DEVFL_MKII_ONLY,
            at90usb1287_io_registers,
            false,
            0x07,
            0x8000, // fuses
            0x66,   // osccal
            3,      // OCD revision
            {
                0 // no mkI support
            },
            {
                CMND_SET_DEVICE_DESCRIPTOR,
                {0xFF, 0xFF, 0xE3, 0xF9, 0xFF, 0x3F, 0xB9, 0xF8}, // ucReadIO
                {0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00}, // ucReadIOShadow
                {0xB6, 0x6D, 0x03, 0xE0, 0xFF, 0x1F, 0xB8, 0xF8}, // ucWriteIO
                {0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00}, // ucWriteIOShadow
                {0x73, 0xCF, 0x33, 0xDF, 0xF7, 0x3F, 0xF7, 0xFF, 0xFF, 0x7F,
                 0x5F, 0x3F, 0x00, 0x37, 0x80, 0xE7, 0x7F, 0xFF, 0xFD, 0x03}, // ucReadExtIO
                {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // ucReadIOExtShadow
                {0x73, 0xCF, 0x33, 0xD8, 0xF7, 0x3F, 0xF7, 0xFF, 0xF3, 0x7F,
                 0x5F, 0x2F, 0x00, 0x36, 0x80, 0xE5, 0x0F, 0x7F, 0x31, 0x03}, // ucWriteExtIO
                {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // ucWriteIOExtShadow
                0x31,                                                         // ucIDRAddress
                0x57,                                                         // ucSPMCRAddress
                0x3B,                                                         // ucRAMPZAddress
                fill_b2(256),                                                 // uiFlashPageSize
                8,                                                            // ucEepromPageSize
                fill_b4(0xFE00),                                              // ulBootAddress
                fill_b2(0x00FF),                                              // uiUpperExtIOLoc
                fill_b4(131072),                                              // ulFlashSize
                {0x00},                                                       // ucEepromInst
                {0x00},                                                       // ucFlashInst
                0x3E,                                                         // ucSPHaddr
                0x3D,                                                         // ucSPLaddr
                fill_b2(131072 / 256),                                        // uiFlashpages
                0x00,                                                         // ucDWDRAddress
                0x00,                                                         // ucDWBasePC
                0x00,           // ucAllowFullPageBitstream
                fill_b2(0x00),  // uiStartSmallestBootLoaderSection
                1,              // EnablePageProgramming
                0,              // ucCacheType
                fill_b2(0x100), // uiSramStartAddr
                0,              // ucResetType
                0,              // ucPCMaskExtended
                0,              // ucPCMaskHigh
                0x3C,           // ucEindAddress
                fill_b2(0x1F),  // EECRAddress
            },
            {0}, // Xmega device descr.
        },
        {
            "at90usb162",
            0x9482,
            128,
            128, // 16384 bytes flash
            4,
            128,    // 512 bytes EEPROM
            38 * 4, // 38 interrupt vectors
            DEVFL_MKII_ONLY,
            at90usb162_io_registers,
            false,
            0x07,
            0x0000, // fuses
            0x66,   // osccal
            1,      // OCD revision
            {
                0 // no mkI support
            },
            {
                CMND_SET_DEVICE_DESCRIPTOR,
                {0xF8, 0x0F, 0x60, 0xF8, 0xFF, 0x3F, 0xB9, 0xF0}, // ucReadIO
                {0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00}, // ucReadIOShadow
                {0xB0, 0x0D, 0x00, 0xE0, 0xFF, 0x1F, 0xB8, 0xF0}, // ucWriteIO
                {0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00}, // ucWriteIOShadow
                {0x7F, 0xDF, 0x00, 0x00, 0xF7, 0x3F, 0x00, 0x00, 0x00, 0x00,
                 0x00, 0x00, 0x00, 0x3F, 0x07, 0x01, 0x7F, 0xFF, 0x15, 0x0C}, // ucReadExtIO
                {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // ucReadIOExtShadow
                {0x34, 0xDF, 0x00, 0xC8, 0xF7, 0x3F, 0x40, 0x00, 0x00, 0x00,
                 0x00, 0x00, 0x00, 0x7F, 0x03, 0x01, 0x0F, 0x7F, 0x11, 0x0C}, // ucWriteExtIO
                {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // ucWriteIOExtShadow
                0x00,                                                         // ucIDRAddress
                0x00,                                                         // ucSPMCRAddress
                0x3B,                                                         // ucRAMPZAddress
                fill_b2(128),                                                 // uiFlashPageSize
                4,                                                            // ucEepromPageSize
                fill_b4(0x1F00),                                              // ulBootAddress
                fill_b2(0xFB),                                                // uiUpperExtIOLoc
                fill_b4(16384),                                               // ulFlashSize
                {0xBD, 0xF2, 0xBD, 0xE1, 0xBB, 0xCF, 0xB4, 0x00, 0xBE, 0x01,
                 0xB6, 0x01, 0xBC, 0x00, 0xBB, 0xBF, 0x99, 0xF9, 0xBB, 0xAF}, // ucEepromInst
                {0xB6, 0x01, 0x11},                                           // ucFlashInst
                0x3E,                                                         // ucSPHaddr
                0x3D,                                                         // ucSPLaddr
                fill_b2(16384 / 128),                                         // uiFlashpages
                0x31,                                                         // ucDWDRAddress
                0x00,                                                         // ucDWBasePC
                0x00,            // ucAllowFullPageBitstream
                fill_b2(0x1F00), // uiStartSmallestBootLoaderSection
                1,               // EnablePageProgramming
                0,               // ucCacheType
                fill_b2(0x100),  // uiSramStartAddr
                0,               // ucResetType
                0,               // ucPCMaskExtended
                0,               // ucPCMaskHigh
                0x3C,            // ucEindAddress
                fill_b2(0x1F),   // EECRAddress
            },
            {0}, // Xmega device descr.
        },
        {
            "at90usb646",
            0x9682,
            256,
            256, // 65536 bytes flash
            8,
            256,    // 2048 bytes EEPROM
            38 * 4, // 38 interrupt vectors
            DEVFL_MKII_ONLY,
            at90usb646_io_registers,
            false,
            0x07,
            0x8000, // fuses
            0x66,   // osccal
            3,      // OCD revision
            {
                0 // no mkI support
            },
            {
                CMND_SET_DEVICE_DESCRIPTOR,
                {0xFF, 0xFF, 0xE3, 0xF9, 0xFF, 0x3F, 0xB9, 0xF8}, // ucReadIO
                {0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00}, // ucReadIOShadow
                {0xB6, 0x6D, 0x03, 0xE0, 0xFF, 0x1F, 0xB8, 0xF8}, // ucWriteIO
                {0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00}, // ucWriteIOShadow
                {0x73, 0xCF, 0x33, 0xDF, 0xF7, 0x3F, 0xF7, 0xFF, 0xFF, 0x7F,
                 0x5F, 0x3F, 0x00, 0x37, 0x80, 0xE7, 0x7F, 0xFF, 0xFD, 0x03}, // ucReadExtIO
                {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // ucReadIOExtShadow
                {0x73, 0xCF, 0x33, 0xD8, 0xF7, 0x3F, 0xF7, 0xFF, 0xF3, 0x7F,
                 0x5F, 0x2F, 0x00, 0x36, 0x80, 0xE5, 0x0F, 0x7F, 0x31, 0x03}, // ucWriteExtIO
                {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // ucWriteIOExtShadow
                0x31,                                                         // ucIDRAddress
                0x57,                                                         // ucSPMCRAddress
                0x3B,                                                         // ucRAMPZAddress
                fill_b2(256),                                                 // uiFlashPageSize
                8,                                                            // ucEepromPageSize
                fill_b4(0xFE00),                                              // ulBootAddress
                fill_b2(0x00FF),                                              // uiUpperExtIOLoc
                fill_b4(65536),                                               // ulFlashSize
                {0x00},                                                       // ucEepromInst
                {0x00},                                                       // ucFlashInst
                0x3E,                                                         // ucSPHaddr
                0x3D,                                                         // ucSPLaddr
                fill_b2(65536 / 256),                                         // uiFlashpages
                0x00,                                                         // ucDWDRAddress
                0x00,                                                         // ucDWBasePC
                0x00,           // ucAllowFullPageBitstream
                fill_b2(0x00),  // uiStartSmallestBootLoaderSection
                1,              // EnablePageProgramming
                0,              // ucCacheType
                fill_b2(0x100), // uiSramStartAddr
                0,              // ucResetType
                0,              // ucPCMaskExtended
                0,              // ucPCMaskHigh
                0x3C,           // ucEindAddress
                fill_b2(0x1F),  // EECRAddress
            },
            {0}, // Xmega device descr.
        },
        {
            "at90usb647",
            0x9682,
            256,
            256, // 65536 bytes flash
            8,
            256,    // 2048 bytes EEPROM
            38 * 4, // 38 interrupt vectors
            DEVFL_MKII_ONLY,
            at90usb647_io_registers,
            false,
            0x07,
            0x8000, // fuses
            0x66,   // osccal
            3,      // OCD revision
            {
                0 // no mkI support
            },
            {
                CMND_SET_DEVICE_DESCRIPTOR,
                {0xFF, 0xFF, 0xE3, 0xF9, 0xFF, 0x3F, 0xB9, 0xF8}, // ucReadIO
                {0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00}, // ucReadIOShadow
                {0xB6, 0x6D, 0x03, 0xE0, 0xFF, 0x1F, 0xB8, 0xF8}, // ucWriteIO
                {0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00}, // ucWriteIOShadow
                {0x73, 0xCF, 0x33, 0xDF, 0xF7, 0x3F, 0xF7, 0xFF, 0xFF, 0x7F,
                 0x5F, 0x3F, 0x00, 0x37, 0x80, 0xE7, 0x7F, 0xFF, 0xFD, 0x03}, // ucReadExtIO
                {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // ucReadIOExtShadow
                {0x73, 0xCF, 0x33, 0xD8, 0xF7, 0x3F, 0xF7, 0xFF, 0xF3, 0x7F,
                 0x5F, 0x2F, 0x00, 0x36, 0x80, 0xE5, 0x0F, 0x7F, 0x31, 0x03}, // ucWriteExtIO
                {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // ucWriteIOExtShadow
                0x31,                                                         // ucIDRAddress
                0x57,                                                         // ucSPMCRAddress
                0x3B,                                                         // ucRAMPZAddress
                fill_b2(256),                                                 // uiFlashPageSize
                8,                                                            // ucEepromPageSize
                fill_b4(0xFE00),                                              // ulBootAddress
                fill_b2(0x00FF),                                              // uiUpperExtIOLoc
                fill_b4(65536),                                               // ulFlashSize
                {0x00},                                                       // ucEepromInst
                {0x00},                                                       // ucFlashInst
                0x3E,                                                         // ucSPHaddr
                0x3D,                                                         // ucSPLaddr
                fill_b2(65536 / 256),                                         // uiFlashpages
                0x00,                                                         // ucDWDRAddress
                0x00,                                                         // ucDWBasePC
                0x00,           // ucAllowFullPageBitstream
                fill_b2(0x00),  // uiStartSmallestBootLoaderSection
                1,              // EnablePageProgramming
                0,              // ucCacheType
                fill_b2(0x100), // uiSramStartAddr
                0,              // ucResetType
                0,              // ucPCMaskExtended
                0,              // ucPCMaskHigh
                0x3C,           // ucEindAddress
                fill_b2(0x1F),  // EECRAddress
            },
            {0}, // Xmega device descr.
        },
        {
            "atmega1284p",
            0x9705,
            256,
            512, // 131072 bytes flash
            8,
            512,    // 4096 bytes EEPROM
            35 * 4, // 35 interrupt vectors
            DEVFL_MKII_ONLY,
            atmega1284p_io_registers,
            false,
            0x07,
            0x8000, // fuses
            0x66,   // osccal
            3,      // OCD revision
            {
                0 // no mkI support
            },
            {
                CMND_SET_DEVICE_DESCRIPTOR,
                {0xFF, 0x0F, 0xE0, 0xF9, 0xFF, 0x3D, 0xB9, 0xE8}, // ucReadIO
                {0X00, 0X00, 0X00, 0X00, 0X01, 0X00, 0X00, 0X00}, // ucReadIOShadow
                {0xFF, 0x0F, 0x00, 0xE0, 0xFF, 0x1D, 0xB8, 0xE8}, // ucWriteIO
                {0X00, 0X00, 0X00, 0X00, 0X01, 0X00, 0X00, 0X00}, // ucWriteIOShadow
                {0x73, 0xFD, 0x0B, 0xDF, 0xF7, 0x0F, 0xF7, 0x0F, 0x00, 0x00,
                 0x5F, 0x3F, 0x37, 0x37, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // ucReadExtIO
                {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // ucReadIOExtShadow
                {0x73, 0xFD, 0x0B, 0xD8, 0xF7, 0x0F, 0xF7, 0x0F, 0x00, 0x00,
                 0x5F, 0x2F, 0x36, 0x36, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // ucWriteExtIO
                {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // ucWriteIOExtShadow
                0x31,                                                         // ucIDRAddress
                0X57,                                                         // ucSPMCRAddress
                0x3B,                                                         // ucRAMPZAddress
                fill_b2(256),                                                 // uiFlashPageSize
                8,                                                            // ucEepromPageSize
                fill_b4(0xFE00),                                              // ulBootAddress
                fill_b2(0xCE),                                                // uiUpperExtIOLoc
                fill_b4(131072),                                              // ulFlashSize
                {0x00},                                                       // ucEepromInst
                {0x00},                                                       // ucFlashInst
                0x3E,                                                         // ucSPHaddr
                0x3D,                                                         // ucSPLaddr
                fill_b2(131072 / 256),                                        // uiFlashpages
                0x00,                                                         // ucDWDRAddress
                0x00,                                                         // ucDWBasePC
                0x00,           // ucAllowFullPageBitstream
                fill_b2(0x00),  // uiStartSmallestBootLoaderSection
                1,              // EnablePageProgramming
                0,              // ucCacheType
                fill_b2(0x100), // uiSramStartAddr
                0,              // ucResetType
                0,              // ucPCMaskExtended
                0,              // ucPCMaskHigh
                0,              // ucEindAddress
                fill_b2(0x1F),  // EECRAddress
            },
            {0}, // Xmega device descr.
        },
        {
            "atmega165",
            0x9407,
            128,
            128, // 16384 bytes flash
            4,
            128,    // 512 bytes EEPROM
            22 * 4, // 22 interrupt vectors
            DEVFL_MKII_ONLY,
            atmega165_io_registers,
            false,
            0x07,
            0x8000, // fuses
            0x66,   // osccal
            3,      // OCD revision
            {
                0 // no mkI support
            },
            {
                CMND_SET_DEVICE_DESCRIPTOR,
                {0xFF, 0xFF, 0xFF, 0xF0, 0xDF, 0x3C, 0xB9, 0xE0}, // ucReadIO
                {0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00}, // ucReadIOShadow
                {0xB6, 0x6D, 0x1B, 0xE0, 0xDF, 0x1C, 0xB8, 0xE0}, // ucWriteIO
                {0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00}, // ucWriteIOShadow
                {0x53, 0xDA, 0x01, 0xDF, 0xF7, 0x0F, 0x00, 0x00, 0x00, 0x00,
                 0x4D, 0x07, 0x37, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // ucReadExtIO
                {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // ucReadIOExtShadow
                {0x53, 0xDA, 0x01, 0xD8, 0xF7, 0x0F, 0x00, 0x00, 0x00, 0x00,
                 0x4D, 0x05, 0x36, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // ucWriteExtIO
                {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // ucWriteIOExtShadow
                0x31,                                                         // ucIDRAddress
                0X57,                                                         // ucSPMCRAddress
                0,                                                            // ucRAMPZAddress
                fill_b2(128),                                                 // uiFlashPageSize
                4,                                                            // ucEepromPageSize
                fill_b4(0x1F80),                                              // ulBootAddress
                fill_b2(0xFE),                                                // uiUpperExtIOLoc
                fill_b4(16384),                                               // ulFlashSize
                {0x00},                                                       // ucEepromInst
                {0x00},                                                       // ucFlashInst
                0x3E,                                                         // ucSPHaddr
                0x3D,                                                         // ucSPLaddr
                fill_b2(16384 / 128),                                         // uiFlashpages
                0x00,                                                         // ucDWDRAddress
                0x00,                                                         // ucDWBasePC
                0x00,           // ucAllowFullPageBitstream
                fill_b2(0x00),  // uiStartSmallestBootLoaderSection
                1,              // EnablePageProgramming
                0,              // ucCacheType
                fill_b2(0x100), // uiSramStartAddr
                0,              // ucResetType
                0,              // ucPCMaskExtended
                0,              // ucPCMaskHigh
                0,              // ucEindAddress
                fill_b2(0x1F),  // EECRAddress
            },
            {0}, // Xmega device descr.
        },
        {
            "atmega165p",
            0x9407,
            128,
            128, // 16384 bytes flash
            4,
            128,    // 512 bytes EEPROM
            22 * 4, // 22 interrupt vectors
            DEVFL_MKII_ONLY,
            atmega165p_io_registers,
            false,
            0x07,
            0x8000, // fuses
            0x66,   // osccal
            3,      // OCD revision
            {
                0 // no mkI support
            },
            {
                CMND_SET_DEVICE_DESCRIPTOR,
                {0xFF, 0xFF, 0xFF, 0xF0, 0xDF, 0x3C, 0xB9, 0xE0}, // ucReadIO
                {0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00}, // ucReadIOShadow
                {0xB6, 0x6D, 0x1B, 0xE0, 0xDF, 0x1C, 0xB8, 0xE0}, // ucWriteIO
                {0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00}, // ucWriteIOShadow
                {0x53, 0xDA, 0x01, 0xDF, 0xF7, 0x0F, 0x00, 0x00, 0x00, 0x00,
                 0x4D, 0x07, 0x37, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // ucReadExtIO
                {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // ucReadIOExtShadow
                {0x53, 0xDA, 0x01, 0xD8, 0xF7, 0x0F, 0x00, 0x00, 0x00, 0x00,
                 0x4D, 0x05, 0x36, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // ucWriteExtIO
                {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // ucWriteIOExtShadow
                0x31,                                                         // ucIDRAddress
                0X57,                                                         // ucSPMCRAddress
                0,                                                            // ucRAMPZAddress
                fill_b2(128),                                                 // uiFlashPageSize
                4,                                                            // ucEepromPageSize
                fill_b4(0x1F80),                                              // ulBootAddress
                fill_b2(0xFE),                                                // uiUpperExtIOLoc
                fill_b4(16384),                                               // ulFlashSize
                {0x00},                                                       // ucEepromInst
                {0x00},                                                       // ucFlashInst
                0x3E,                                                         // ucSPHaddr
                0x3D,                                                         // ucSPLaddr
                fill_b2(16384 / 128),                                         // uiFlashpages
                0x00,                                                         // ucDWDRAddress
                0x00,                                                         // ucDWBasePC
                0x00,           // ucAllowFullPageBitstream
                fill_b2(0x00),  // uiStartSmallestBootLoaderSection
                1,              // EnablePageProgramming
                0,              // ucCacheType
                fill_b2(0x100), // uiSramStartAddr
                0,              // ucResetType
                0,              // ucPCMaskExtended
                0,              // ucPCMaskHigh
                0,              // ucEindAddress
                fill_b2(0x1F),  // EECRAddress
            },
            {0}, // Xmega device descr.
        },
        {
            "atmega168p",
            0x940B,
            128,
            128, // 16384 bytes flash
            4,
            128,    // 512 bytes EEPROM
            26 * 4, // 26 interrupt vectors
            DEVFL_MKII_ONLY,
            atmega168p_io_registers,
            false,
            0x07,
            0x0000, // fuses
            0x66,   // osccal
            1,      // OCD revision
            {
                0 // no mkI support
            },
            {
                CMND_SET_DEVICE_DESCRIPTOR,
                {0xF8, 0x0F, 0xE0, 0xF8, 0xFF, 0x3D, 0xB9, 0xE0}, // ucReadIO
                {0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00}, // ucReadIOShadow
                {0xB0, 0x0D, 0x00, 0xE0, 0xFF, 0x1D, 0xB8, 0xE0}, // ucWriteIO
                {0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00}, // ucWriteIOShadow
                {0x53, 0xFB, 0x01, 0xDF, 0xF7, 0x0F, 0x00, 0x00, 0x00, 0x00,
                 0x5F, 0x3F, 0x37, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // ucReadExtIO
                {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // ucReadIOExtShadow
                {0x00, 0xFB, 0x01, 0xD8, 0xF7, 0x0F, 0x00, 0x00, 0x00, 0x00,
                 0x5F, 0x2F, 0x36, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // ucWriteExtIO
                {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // ucWriteIOExtShadow
                0x00,                                                         // ucIDRAddress
                0X00,                                                         // ucSPMCRAddress
                0,                                                            // ucRAMPZAddress
                fill_b2(128),                                                 // uiFlashPageSize
                4,                                                            // ucEepromPageSize
                fill_b4(0x1F80),                                              // ulBootAddress
                fill_b2(0xC6),                                                // uiUpperExtIOLoc
                fill_b4(16384),                                               // ulFlashSize
                {0xBD, 0xF2, 0xBD, 0xE1, 0xBB, 0xCF, 0xB4, 0x00, 0xBE, 0x01,
                 0xB6, 0x01, 0xBC, 0x00, 0xBB, 0xBF, 0x99, 0xF9, 0xBB, 0xAF}, // ucEepromInst
                {0xB6, 0x01, 0x11},                                           // ucFlashInst
                0x3E,                                                         // ucSPHaddr
                0x3D,                                                         // ucSPLaddr
                fill_b2(16384 / 128),                                         // uiFlashpages
                0x31,                                                         // ucDWDRAddress
                0x00,                                                         // ucDWBasePC
                0x00,            // ucAllowFullPageBitstream
                fill_b2(0x1F80), // uiStartSmallestBootLoaderSection
                1,               // EnablePageProgramming
                0,               // ucCacheType
                fill_b2(0x100),  // uiSramStartAddr
                0,               // ucResetType
                0,               // ucPCMaskExtended
                0,               // ucPCMaskHigh
                0,               // ucEindAddress
                fill_b2(0x1F),   // EECRAddress
            },
            {0}, // Xmega device descr.
        },
        {
            "atmega16hva",
            0x940C,
            128,
            128, // 16384 bytes flash
            4,
            64,     // 256 bytes EEPROM
            21 * 4, // 21 interrupt vectors
            DEVFL_MKII_ONLY,
            atmega16hva_io_registers,
            false,
            0x07,
            0x0000, // fuses
            0x66,   // osccal
            1,      // OCD revision
            {
                0 // no mkI support
            },
            {
                CMND_SET_DEVICE_DESCRIPTOR,
                {0x7F, 0x01, 0xE0, 0xF0, 0xFB, 0x3F, 0xB8, 0xE0}, // ucReadIO
                {0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00}, // ucReadIOShadow
                {0x37, 0x01, 0x00, 0xE0, 0xFB, 0x1F, 0xA8, 0xE0}, // ucWriteIO
                {0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00}, // ucWriteIOShadow
                {0x53, 0xC2, 0x00, 0x57, 0x33, 0x03, 0x00, 0x00, 0x00, 0x00,
                 0x00, 0x00, 0x00, 0x01, 0x03, 0x00, 0x7F, 0x03, 0xED, 0x7F}, // ucReadExtIO
                {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // ucReadIOExtShadow
                {0x50, 0xC2, 0x00, 0x50, 0x33, 0x03, 0x00, 0x00, 0x00, 0x00,
                 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x70, 0x00, 0xED, 0x3F}, // ucWriteExtIO
                {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // ucWriteIOExtShadow
                0x00,                                                         // ucIDRAddress
                0x57,                                                         // ucSPMCRAddress
                0,                                                            // ucRAMPZAddress
                fill_b2(128),                                                 // uiFlashPageSize
                4,                                                            // ucEepromPageSize
                fill_b4(0),                                                   // ulBootAddress
                fill_b2(0xFE),                                                // uiUpperExtIOLoc
                fill_b4(16384),                                               // ulFlashSize
                {0xBD, 0xF2, 0xBD, 0xE1, 0xBB, 0xCF, 0xB4, 0x00, 0xBE, 0x01,
                 0xB6, 0x01, 0xBC, 0x00, 0xBB, 0xBF, 0x99, 0xF9, 0xBB, 0xAF}, // ucEepromInst
                {0xB6, 0x01, 0x11},                                           // ucFlashInst
                0x3E,                                                         // ucSPHaddr
                0x3D,                                                         // ucSPLaddr
                fill_b2(16384 / 128),                                         // uiFlashpages
                0x31,                                                         // ucDWDRAddress
                0x00,                                                         // ucDWBasePC
                0x00,           // ucAllowFullPageBitstream
                fill_b2(0x00),  // uiStartSmallestBootLoaderSection
                1,              // EnablePageProgramming
                0,              // ucCacheType
                fill_b2(0x100), // uiSramStartAddr
                0,              // ucResetType
                0,              // ucPCMaskExtended
                0,              // ucPCMaskHigh
                0,              // ucEindAddress
                fill_b2(0x1F),  // EECRAddress
            },
            {0}, // Xmega device descr.
        },
        {
            "atmega3250p",
            0x950E,
            128,
            256, // 32768 bytes flash
            4,
            256,    // 1024 bytes EEPROM
            25 * 4, // 25 interrupt vectors
            DEVFL_MKII_ONLY,
            atmega3250p_io_registers,
            false,
            0x07,
            0x8000, // fuses
            0x66,   // osccal
            3,      // OCD revision
            {
                0 // no mkI support
            },
            {
                CMND_SET_DEVICE_DESCRIPTOR,
                {0xFF, 0xFF, 0xFF, 0xF0, 0xDF, 0x3C, 0xB9, 0xE0}, // ucReadIO
                {0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00}, // ucReadIOShadow
                {0xB6, 0x6D, 0x1B, 0xE0, 0xDF, 0x1C, 0xB8, 0xE0}, // ucWriteIO
                {0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00}, // ucWriteIOShadow
                {0x53, 0xFA, 0x09, 0xDF, 0xF7, 0x0F, 0x00, 0x00, 0x00, 0x00,
                 0x4D, 0x07, 0x37, 0x00, 0x00, 0x3F, 0x00, 0x00, 0x00, 0x00}, // ucReadExtIO
                {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // ucReadIOExtShadow
                {0x53, 0xFA, 0x09, 0xD8, 0xF7, 0x0F, 0x00, 0x00, 0x00, 0x00,
                 0x4D, 0x05, 0x36, 0x00, 0x00, 0x3F, 0x00, 0x00, 0x00, 0x00}, // ucWriteExtIO
                {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // ucWriteIOExtShadow
                0x31,                                                         // ucIDRAddress
                0x57,                                                         // ucSPMCRAddress
                0,                                                            // ucRAMPZAddress
                fill_b2(128),                                                 // uiFlashPageSize
                4,                                                            // ucEepromPageSize
                fill_b4(0x3F00),                                              // ulBootAddress
                fill_b2(0xDD),                                                // uiUpperExtIOLoc
                fill_b4(32768),                                               // ulFlashSize
                {0x00},                                                       // ucEepromInst
                {0x00},                                                       // ucFlashInst
                0x3E,                                                         // ucSPHaddr
                0x3D,                                                         // ucSPLaddr
                fill_b2(32768 / 128),                                         // uiFlashpages
                0x00,                                                         // ucDWDRAddress
                0x40,                                                         // ucDWBasePC
                0x00,           // ucAllowFullPageBitstream
                fill_b2(0x00),  // uiStartSmallestBootLoaderSection
                1,              // EnablePageProgramming
                0,              // ucCacheType
                fill_b2(0x100), // uiSramStartAddr
                0,              // ucResetType
                0,              // ucPCMaskExtended
                0x40,           // ucPCMaskHigh
                0,              // ucEindAddress
                fill_b2(0x1F),  // EECRAddress
            },
            {0}, // Xmega device descr.
        },
        {
            "atmega325p",
            0x950D,
            128,
            256, // 32768 bytes flash
            4,
            256,    // 1024 bytes EEPROM
            22 * 4, // 22 interrupt vectors
            DEVFL_MKII_ONLY,
            atmega325p_io_registers,
            false,
            0x07,
            0x8000, // fuses
            0x66,   // osccal
            3,      // OCD revision
            {
                0 // no mkI support
            },
            {
                CMND_SET_DEVICE_DESCRIPTOR,
                {0xFF, 0xFF, 0xFF, 0xF0, 0xDF, 0x3C, 0xB9, 0xE0}, // ucReadIO
                {0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00}, // ucReadIOShadow
                {0xB6, 0x6D, 0x1B, 0xE0, 0xDF, 0x1C, 0xB8, 0xE0}, // ucWriteIO
                {0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00}, // ucWriteIOShadow
                {0x53, 0xDA, 0x01, 0xDF, 0xF7, 0x0F, 0x00, 0x00, 0x00, 0x00,
                 0x4D, 0x07, 0x37, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // ucReadExtIO
                {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // ucReadIOExtShadow
                {0x53, 0xDA, 0x01, 0xD8, 0xF7, 0x0F, 0x00, 0x00, 0x00, 0x00,
                 0x4D, 0x05, 0x36, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // ucWriteExtIO
                {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // ucWriteIOExtShadow
                0x31,                                                         // ucIDRAddress
                0x57,                                                         // ucSPMCRAddress
                0,                                                            // ucRAMPZAddress
                fill_b2(128),                                                 // uiFlashPageSize
                4,                                                            // ucEepromPageSize
                fill_b4(0x3F00),                                              // ulBootAddress
                fill_b2(0xC6),                                                // uiUpperExtIOLoc
                fill_b4(32768),                                               // ulFlashSize
                {0x00},                                                       // ucEepromInst
                {0x00},                                                       // ucFlashInst
                0x3E,                                                         // ucSPHaddr
                0x3D,                                                         // ucSPLaddr
                fill_b2(32768 / 128),                                         // uiFlashpages
                0x00,                                                         // ucDWDRAddress
                0x40,                                                         // ucDWBasePC
                0x00,           // ucAllowFullPageBitstream
                fill_b2(0x00),  // uiStartSmallestBootLoaderSection
                1,              // EnablePageProgramming
                0,              // ucCacheType
                fill_b2(0x100), // uiSramStartAddr
                0,              // ucResetType
                0,              // ucPCMaskExtended
                0x40,           // ucPCMaskHigh
                0,              // ucEindAddress
                fill_b2(0x1F),  // EECRAddress
            },
            {0}, // Xmega device descr.
        },
        {
            "atmega328p",
            0x950F,
            128,
            256, // 32768 bytes flash
            4,
            256,    // 1024 bytes EEPROM
            26 * 4, // 26 interrupt vectors
            DEVFL_MKII_ONLY,
            atmega328p_io_registers,
            false,
            0x07,
            0x0000, // fuses
            0x66,   // osccal
            1,      // OCD revision
            {
                0 // no mkI support
            },
            {
                CMND_SET_DEVICE_DESCRIPTOR,
                {0xF8, 0x0F, 0xE0, 0xF8, 0xFF, 0x3D, 0xB9, 0xE0}, // ucReadIO
                {0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00}, // ucReadIOShadow
                {0xB0, 0x0D, 0x00, 0xE0, 0xFF, 0x1D, 0xB8, 0xE0}, // ucWriteIO
                {0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00}, // ucWriteIOShadow
                {0x53, 0xFB, 0x01, 0xDF, 0xF7, 0x0F, 0x00, 0x00, 0x00, 0x00,
                 0x5F, 0x3F, 0x37, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // ucReadExtIO
                {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // ucReadIOExtShadow
                {0x00, 0xFB, 0x01, 0xD8, 0xF7, 0x0F, 0x00, 0x00, 0x00, 0x00,
                 0x5F, 0x2F, 0x36, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // ucWriteExtIO
                {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // ucWriteIOExtShadow
                0x31,                                                         // ucIDRAddress
                0X57,                                                         // ucSPMCRAddress
                0,                                                            // ucRAMPZAddress
                fill_b2(128),                                                 // uiFlashPageSize
                4,                                                            // ucEepromPageSize
                fill_b4(0x3F00),                                              // ulBootAddress
                fill_b2(0xC6),                                                // uiUpperExtIOLoc
                fill_b4(32768),                                               // ulFlashSize
                {0xBD, 0xF2, 0xBD, 0xE1, 0xBB, 0xCF, 0xB4, 0x00, 0xBE, 0x01,
                 0xB6, 0x01, 0xBC, 0x00, 0xBB, 0xBF, 0x99, 0xF9, 0xBB, 0xAF}, // ucEepromInst
                {0xB6, 0x01, 0x11},                                           // ucFlashInst
                0x3E,                                                         // ucSPHaddr
                0x3D,                                                         // ucSPLaddr
                fill_b2(32768 / 128),                                         // uiFlashpages
                0x31,                                                         // ucDWDRAddress
                0x00,                                                         // ucDWBasePC
                0x00,            // ucAllowFullPageBitstream
                fill_b2(0x3F00), // uiStartSmallestBootLoaderSection
                1,               // EnablePageProgramming
                0,               // ucCacheType
                fill_b2(0x100),  // uiSramStartAddr
                0,               // ucResetType
                0,               // ucPCMaskExtended
                0,               // ucPCMaskHigh
                0,               // ucEindAddress
                fill_b2(0x1F),   // EECRAddress
            },
            {0}, // Xmega device descr.
        },
        {
            "atmega3290p",
            0x950C,
            128,
            256, // 32768 bytes flash
            4,
            256,    // 1024 bytes EEPROM
            25 * 4, // 25 interrupt vectors
            DEVFL_MKII_ONLY,
            atmega3290p_io_registers,
            false,
            0x07,
            0x8000, // fuses
            0x66,   // osccal
            3,      // OCD revision
            {
                0 // no mkI support
            },
            {
                CMND_SET_DEVICE_DESCRIPTOR,
                {0xFF, 0xFF, 0xFF, 0xF0, 0xDF, 0x3C, 0xB9, 0xE0}, // ucReadIO
                {0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00}, // ucReadIOShadow
                {0xB6, 0x6D, 0x1B, 0xE0, 0xDF, 0x1C, 0xB8, 0xE0}, // ucWriteIO
                {0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00}, // ucWriteIOShadow
                {0x53, 0xFA, 0x09, 0xDF, 0xF7, 0x0F, 0x00, 0x00, 0x00, 0x00,
                 0x4D, 0x07, 0x37, 0x00, 0x00, 0x3F, 0xF0, 0xF0, 0xFF, 0xFF}, // ucReadExtIO
                {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // ucReadIOExtShadow
                {0x53, 0xFA, 0x09, 0xD8, 0xF7, 0x0F, 0x00, 0x00, 0x00, 0x00,
                 0x4D, 0x05, 0x36, 0x00, 0x00, 0x3F, 0xE0, 0xF0, 0xFF, 0xFF}, // ucWriteExtIO
                {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // ucWriteIOExtShadow
                0x31,                                                         // ucIDRAddress
                0X57,                                                         // ucSPMCRAddress
                0,                                                            // ucRAMPZAddress
                fill_b2(128),                                                 // uiFlashPageSize
                4,                                                            // ucEepromPageSize
                fill_b4(0x3F00),                                              // ulBootAddress
                fill_b2(0xFF),                                                // uiUpperExtIOLoc
                fill_b4(32768),                                               // ulFlashSize
                {0x00},                                                       // ucEepromInst
                {0x00},                                                       // ucFlashInst
                0x3E,                                                         // ucSPHaddr
                0x3D,                                                         // ucSPLaddr
                fill_b2(32768 / 128),                                         // uiFlashpages
                0x00,                                                         // ucDWDRAddress
                0x40,                                                         // ucDWBasePC
                0x00,           // ucAllowFullPageBitstream
                fill_b2(0x00),  // uiStartSmallestBootLoaderSection
                1,              // EnablePageProgramming
                0,              // ucCacheType
                fill_b2(0x100), // uiSramStartAddr
                0,              // ucResetType
                0,              // ucPCMaskExtended
                0x40,           // ucPCMaskHigh
                0,              // ucEindAddress
                fill_b2(0x1F),  // EECRAddress
            },
            {0}, // Xmega device descr.
        },
        {
            "atmega329p",
            0x9503,
            128,
            256, // 32768 bytes flash
            4,
            256,    // 1024 bytes EEPROM
            23 * 4, // 23 interrupt vectors
            DEVFL_MKII_ONLY,
            atmega329p_io_registers,
            false,
            0x07,
            0x8000, // fuses
            0x66,   // osccal
            3,      // OCD revision
            {
                0 // no mkI support
            },
            {
                CMND_SET_DEVICE_DESCRIPTOR,
                {0xFF, 0xFF, 0xFF, 0xF0, 0xDF, 0x3C, 0xB9, 0xE0}, // ucReadIO
                {0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00}, // ucReadIOShadow
                {0xB6, 0x6D, 0x1B, 0xE0, 0xDF, 0x1C, 0xB8, 0xE0}, // ucWriteIO
                {0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00}, // ucWriteIOShadow
                {0x53, 0xDA, 0x01, 0xDF, 0xF7, 0x0F, 0x00, 0x00, 0x00, 0x00,
                 0x4D, 0x07, 0x37, 0x00, 0x00, 0x00, 0xF0, 0xF0, 0xDE, 0x7B}, // ucReadExtIO
                {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // ucReadIOExtShadow
                {0x53, 0xDA, 0x01, 0xD8, 0xF7, 0x0F, 0x00, 0x00, 0x00, 0x00,
                 0x4D, 0x05, 0x36, 0x00, 0x00, 0x00, 0xE0, 0xF0, 0xDE, 0x7B}, // ucWriteExtIO
                {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // ucWriteIOExtShadow
                0x31,                                                         // ucIDRAddress
                0X57,                                                         // ucSPMCRAddress
                0,                                                            // ucRAMPZAddress
                fill_b2(128),                                                 // uiFlashPageSize
                4,                                                            // ucEepromPageSize
                fill_b4(0x3F00),                                              // ulBootAddress
                fill_b2(0xFE),                                                // uiUpperExtIOLoc
                fill_b4(32768),                                               // ulFlashSize
                {0x00},                                                       // ucEepromInst
                {0x00},                                                       // ucFlashInst
                0x3E,                                                         // ucSPHaddr
                0x3D,                                                         // ucSPLaddr
                fill_b2(32768 / 128),                                         // uiFlashpages
                0x00,                                                         // ucDWDRAddress
                0x40,                                                         // ucDWBasePC
                0x00,           // ucAllowFullPageBitstream
                fill_b2(0x00),  // uiStartSmallestBootLoaderSection
                1,              // EnablePageProgramming
                0,              // ucCacheType
                fill_b2(0x100), // uiSramStartAddr
                0,              // ucResetType
                0,              // ucPCMaskExtended
                0x40,           // ucPCMaskHigh
                0,              // ucEindAddress
                fill_b2(0x1F),  // EECRAddress
            },
            {0}, // Xmega device descr.
        },
        {
            "atmega32hvb",
            0x9510,
            128,
            256, // 32768 bytes flash
            4,
            256,    // 1024 bytes EEPROM
            29 * 4, // 29 interrupt vectors
            DEVFL_MKII_ONLY,
            atmega32hvb_io_registers,
            false,
            0x07,
            0x0000, // fuses
            0x66,   // osccal
            1,      // OCD revision
            {
                0 // no mkI support
            },
            {
                CMND_SET_DEVICE_DESCRIPTOR,
                {0x7F, 0x01, 0xE0, 0xF8, 0xFF, 0x3F, 0xB8, 0xE0}, // ucReadIO
                {0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00}, // ucReadIOShadow
                {0x37, 0x01, 0x00, 0xE0, 0xFF, 0x1F, 0xA8, 0xE0}, // ucWriteIO
                {0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00}, // ucWriteIOShadow
                {0x53, 0xDB, 0x00, 0x57, 0x33, 0x03, 0x00, 0x00, 0x00, 0x00,
                 0x00, 0x7F, 0x00, 0x01, 0x17, 0x00, 0xFF, 0x07, 0xEF, 0x7F}, // ucReadExtIO
                {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // ucReadIOExtShadow
                {0x50, 0xDB, 0x00, 0x50, 0x33, 0x03, 0x00, 0x00, 0x00, 0x00,
                 0x00, 0x7F, 0x00, 0x00, 0x17, 0x00, 0xCF, 0x07, 0xEF, 0x3F}, // ucWriteExtIO
                {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // ucWriteIOExtShadow
                0x00,                                                         // ucIDRAddress
                0x57,                                                         // ucSPMCRAddress
                0,                                                            // ucRAMPZAddress
                fill_b2(128),                                                 // uiFlashPageSize
                4,                                                            // ucEepromPageSize
                fill_b4(0x3F00),                                              // ulBootAddress
                fill_b2(0xFE),                                                // uiUpperExtIOLoc
                fill_b4(32768),                                               // ulFlashSize
                {0xBD, 0xF2, 0xBD, 0xE1, 0xBB, 0xCF, 0xB4, 0x00, 0xBE, 0x01,
                 0xB6, 0x01, 0xBC, 0x00, 0xBB, 0xBF, 0x99, 0xF9, 0xBB, 0xAF}, // ucEepromInst
                {0xB6, 0x01, 0x11},                                           // ucFlashInst
                0x3E,                                                         // ucSPHaddr
                0x3D,                                                         // ucSPLaddr
                fill_b2(32768 / 128),                                         // uiFlashpages
                0x31,                                                         // ucDWDRAddress
                0x00,                                                         // ucDWBasePC
                0x00,            // ucAllowFullPageBitstream
                fill_b2(0x3F00), // uiStartSmallestBootLoaderSection
                1,               // EnablePageProgramming
                0,               // ucCacheType
                fill_b2(0x100),  // uiSramStartAddr
                0,               // ucResetType
                0,               // ucPCMaskExtended
                0,               // ucPCMaskHigh
                0,               // ucEindAddress
                fill_b2(0x1F),   // EECRAddress
            },
            {0}, // Xmega device descr.
        },
        {
            "atmega32u4",
            0x9587,
            128,
            256, // 32768 bytes flash
            4,
            256,    // 1024 bytes EEPROM
            43 * 4, // 43 interrupt vectors
            DEVFL_MKII_ONLY,
            atmega32u4_io_registers,
            false,
            0x07,
            0x8000, // fuses
            0x66,   // osccal
            3,      // OCD revision
            {
                0 // no mkI support
            },
            {
                CMND_SET_DEVICE_DESCRIPTOR,
                {0xF8, 0xFF, 0xE3, 0xFB, 0xFF, 0x3F, 0xBD, 0xF8}, // ucReadIO
                {0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00}, // ucReadIOShadow
                {0xB0, 0x6D, 0x03, 0xE0, 0xFF, 0x1F, 0xBC, 0xF8}, // ucWriteIO
                {0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00}, // ucWriteIOShadow
                {0xF3, 0xCF, 0x07, 0xDF, 0xF7, 0x3F, 0xF7, 0x3F, 0x00, 0x00, 0x1F, 0xFF, 0xFF, 0xB7,
                 0x97, 0x07, 0x7F, 0xFF, 0x1D}, // ucReadExtIO
                {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // ucReadIOExtShadow
                {0xF3, 0xCF, 0x07, 0xD8, 0xF7, 0x3F, 0xF7, 0x3F, 0x00, 0x00, 0x1F, 0xEF, 0x7F, 0xB6,
                 0x97, 0x05, 0x0F, 0x7F, 0x11}, // ucWriteExtIO
                {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // ucWriteIOExtShadow
                0x31,                                                         // ucIDRAddress
                0x57,                                                         // ucSPMCRAddress
                0x3B,                                                         // ucRAMPZAddress
                fill_b2(128),                                                 // uiFlashPageSize
                4,                                                            // ucEepromPageSize
                fill_b4(0x3F00),                                              // ulBootAddress
                fill_b2(0x00FF),                                              // uiUpperExtIOLoc
                fill_b4(32768),                                               // ulFlashSize
                {0x00},                                                       // ucEepromInst
                {0x00},                                                       // ucFlashInst
                0x3E,                                                         // ucSPHaddr
                0x3D,                                                         // ucSPLaddr
                fill_b2(32768 / 128),                                         // uiFlashpages
                0x00,                                                         // ucDWDRAddress
                0x00,                                                         // ucDWBasePC
                0x00,           // ucAllowFullPageBitstream
                fill_b2(0x00),  // uiStartSmallestBootLoaderSection
                1,              // EnablePageProgramming
                0,              // ucCacheType
                fill_b2(0x100), // uiSramStartAddr
                0,              // ucResetType
                0,              // ucPCMaskExtended
                0,              // ucPCMaskHigh
                0x3C,           // ucEindAddress
                fill_b2(0x1F),  // EECRAddress
            },
            {0}, // Xmega device descr.
        },
        {
            "atmega406",
            0x9507,
            128,
            320, // 40960 bytes flash
            4,
            128,    // 512 bytes EEPROM
            23 * 4, // 23 interrupt vectors
            DEVFL_MKII_ONLY,
            atmega406_io_registers,
            false,
            0x07,
            0x0200, // fuses
            0,      // osccal
            0,      // OCD revision
            {
                0 // no mkI support
            },
            {
                CMND_SET_DEVICE_DESCRIPTOR,
                {0x3F, 0x0F, 0x60, 0xF8, 0xFF, 0x0D, 0xB8, 0xE0}, // ucReadIO
                {0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00}, // ucReadIOShadow
                {0x37, 0x0F, 0x00, 0xE0, 0xFF, 0x0D, 0xB8, 0xE0}, // ucWriteIO
                {0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00}, // ucWriteIOShadow
                {0x55, 0xDB, 0x00, 0x57, 0x32, 0x03, 0x00, 0x00, 0x00, 0x00,
                 0x00, 0x7F, 0x01, 0x00, 0x03, 0x00, 0xFF, 0x03, 0xFF, 0x01}, // ucReadExtIO
                {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // ucReadIOExtShadow
                {0x50, 0xDB, 0x00, 0x50, 0x32, 0x03, 0x00, 0x00, 0x00, 0x00,
                 0x00, 0x6D, 0x01, 0x00, 0x03, 0x00, 0xD0, 0x00, 0xFB, 0x00}, // ucWriteExtIO
                {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // ucWriteIOExtShadow
                0x31,                                                         // ucIDRAddress
                0X57,                                                         // ucSPMCRAddress
                0,                                                            // ucRAMPZAddress
                fill_b2(128),                                                 // uiFlashPageSize
                4,                                                            // ucEepromPageSize
                fill_b4(0x4F00),                                              // ulBootAddress
                fill_b2(0xF8),                                                // uiUpperExtIOLoc
                fill_b4(40960),                                               // ulFlashSize
                {0x00},                                                       // ucEepromInst
                {0x00},                                                       // ucFlashInst
                0x3E,                                                         // ucSPHaddr
                0x3D,                                                         // ucSPLaddr
                fill_b2(40960 / 128),                                         // uiFlashpages
                0x00,                                                         // ucDWDRAddress
                0x00,                                                         // ucDWBasePC
                0x00,           // ucAllowFullPageBitstream
                fill_b2(0x00),  // uiStartSmallestBootLoaderSection
                1,              // EnablePageProgramming
                0x00,           // ucCacheType
                fill_b2(0x100), // uiSramStartAddr
                0,              // ucResetType
                0,              // ucPCMaskExtended
                0,              // ucPCMaskHigh
                0,              // ucEindAddress
                fill_b2(0x1F),  // EECRAddress
            },
            {0}, // Xmega device descr.
        },
        {
            "atmega48p",
            0x920A,
            64,
            64, // 4096 bytes flash
            4,
            64,     // 256 bytes EEPROM
            26 * 2, // 26 interrupt vectors
            DEVFL_MKII_ONLY,
            atmega48p_io_registers,
            false,
            0x07,
            0x0000, // fuses
            0x66,   // osccal
            1,      // OCD revision
            {
                0 // no mkI support
            },
            {
                CMND_SET_DEVICE_DESCRIPTOR,
                {0xF8, 0x0F, 0xE0, 0xF8, 0xFB, 0x3D, 0xB9, 0xE0}, // ucReadIO
                {0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00}, // ucReadIOShadow
                {0xB0, 0x0D, 0x00, 0xE0, 0xFB, 0x1D, 0xB8, 0xE0}, // ucWriteIO
                {0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00}, // ucWriteIOShadow
                {0x53, 0xFB, 0x01, 0xDF, 0xF3, 0x0F, 0x00, 0x00, 0x00, 0x00,
                 0x5F, 0x3F, 0x37, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // ucReadExtIO
                {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // ucReadIOExtShadow
                {0x00, 0xFB, 0x01, 0xD8, 0xF3, 0x0F, 0x00, 0x00, 0x00, 0x00,
                 0x5F, 0x2F, 0x36, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // ucWriteExtIO
                {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // ucWriteIOExtShadow
                0x31,                                                         // ucIDRAddress
                0X57,                                                         // ucSPMCRAddress
                0,                                                            // ucRAMPZAddress
                fill_b2(64),                                                  // uiFlashPageSize
                4,                                                            // ucEepromPageSize
                fill_b4(0x0000),                                              // ulBootAddress
                fill_b2(0xC6),                                                // uiUpperExtIOLoc
                fill_b4(4096),                                                // ulFlashSize
                {0xBD, 0xF2, 0xBD, 0xE1, 0xBB, 0xCF, 0xB4, 0x00, 0xBE, 0x01,
                 0xB6, 0x01, 0xBC, 0x00, 0xBB, 0xBF, 0x99, 0xF9, 0xBB, 0xAF}, // ucEepromInst
                {0xB6, 0x01, 0x11},                                           // ucFlashInst
                0x3E,                                                         // ucSPHaddr
                0x3D,                                                         // ucSPLaddr
                fill_b2(4096 / 64),                                           // uiFlashpages
                0x31,                                                         // ucDWDRAddress
                0x00,                                                         // ucDWBasePC
                0x00,           // ucAllowFullPageBitstream
                fill_b2(0x00),  // uiStartSmallestBootLoaderSection
                1,              // EnablePageProgramming
                0,              // ucCacheType
                fill_b2(0x100), // uiSramStartAddr
                0,              // ucResetType
                0,              // ucPCMaskExtended
                0,              // ucPCMaskHigh
                0,              // ucEindAddress
                fill_b2(0x1F),  // EECRAddress
            },
            {0}, // Xmega device descr.
        },
        {
            "atmega644p",
            0x960A,
            256,
            256, // 65536 bytes flash
            8,
            256,    // 2048 bytes EEPROM
            31 * 4, // 31 interrupt vectors
            DEVFL_MKII_ONLY,
            atmega644p_io_registers,
            false,
            0x07,
            0x8000, // fuses
            0x66,   // osccal
            3,      // OCD revision
            {
                0 // no mkI support
            },
            {
                CMND_SET_DEVICE_DESCRIPTOR,
                {0xFF, 0x0F, 0xE0, 0xF8, 0xFF, 0x3D, 0xB9, 0xE8}, // ucReadIO
                {0X00, 0X00, 0X00, 0X00, 0X01, 0X00, 0X00, 0X00}, // ucReadIOShadow
                {0xB6, 0x0D, 0x00, 0xE0, 0xFF, 0x1D, 0xB8, 0xE8}, // ucWriteIO
                {0X00, 0X00, 0X00, 0X00, 0X01, 0X00, 0X00, 0X00}, // ucWriteIOShadow
                {0x53, 0xFB, 0x09, 0xDF, 0xF7, 0x0F, 0x00, 0x00, 0x00, 0x00,
                 0x5F, 0x3F, 0x37, 0x37, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // ucReadExtIO
                {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // ucReadIOExtShadow
                {0x53, 0xFB, 0x09, 0xD8, 0xF7, 0x0F, 0x00, 0x00, 0x00, 0x00,
                 0x5F, 0x2F, 0x36, 0x36, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // ucWriteExtIO
                {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // ucWriteIOExtShadow
                0x31,                                                         // ucIDRAddress
                0X57,                                                         // ucSPMCRAddress
                0x3B,                                                         // ucRAMPZAddress
                fill_b2(256),                                                 // uiFlashPageSize
                8,                                                            // ucEepromPageSize
                fill_b4(0x7e00),                                              // ulBootAddress
                fill_b2(0xCE),                                                // uiUpperExtIOLoc
                fill_b4(65536),                                               // ulFlashSize
                {0x00},                                                       // ucEepromInst
                {0x00},                                                       // ucFlashInst
                0x3E,                                                         // ucSPHaddr
                0x3D,                                                         // ucSPLaddr
                fill_b2(65536 / 256),                                         // uiFlashpages
                0x00,                                                         // ucDWDRAddress
                0x00,                                                         // ucDWBasePC
                0x00,           // ucAllowFullPageBitstream
                fill_b2(0x00),  // uiStartSmallestBootLoaderSection
                1,              // EnablePageProgramming
                0,              // ucCacheType
                fill_b2(0x100), // uiSramStartAddr
                0,              // ucResetType
                0,              // ucPCMaskExtended
                0,              // ucPCMaskHigh
                0,              // ucEindAddress
                fill_b2(0x1F),  // EECRAddress
            },
            {0}, // Xmega device descr.
        },
        {
            "atmega88p",
            0x930F,
            64,
            128, // 8192 bytes flash
            4,
            128,    // 512 bytes EEPROM
            26 * 2, // 26 interrupt vectors
            DEVFL_MKII_ONLY,
            atmega88p_io_registers,
            false,
            0x07,
            0x0000, // fuses
            0x66,   // osccal
            1,      // OCD revision
            {
                0 // no mkI support
            },
            {
                CMND_SET_DEVICE_DESCRIPTOR,
                {0xF8, 0x0F, 0xE0, 0xF8, 0xFF, 0x3D, 0xB9, 0xE0}, // ucReadIO
                {0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00}, // ucReadIOShadow
                {0xB0, 0x0D, 0x00, 0xE0, 0xFF, 0x1D, 0xB8, 0xE0}, // ucWriteIO
                {0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00}, // ucWriteIOShadow
                {0x53, 0xFB, 0x01, 0xDF, 0xF7, 0x0F, 0x00, 0x00, 0x00, 0x00,
                 0x5F, 0x3F, 0x37, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // ucReadExtIO
                {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // ucReadIOExtShadow
                {0x00, 0xFB, 0x01, 0xD8, 0xF7, 0x0F, 0x00, 0x00, 0x00, 0x00,
                 0x5F, 0x2F, 0x36, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // ucWriteExtIO
                {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // ucWriteIOExtShadow
                0x31,                                                         // ucIDRAddress
                0X57,                                                         // ucSPMCRAddress
                0,                                                            // ucRAMPZAddress
                fill_b2(64),                                                  // uiFlashPageSize
                4,                                                            // ucEepromPageSize
                fill_b4(0x0F80),                                              // ulBootAddress
                fill_b2(0xC6),                                                // uiUpperExtIOLoc
                fill_b4(8192),                                                // ulFlashSize
                {0xBD, 0xF2, 0xBD, 0xE1, 0xBB, 0xCF, 0xB4, 0x00, 0xBE, 0x01,
                 0xB6, 0x01, 0xBC, 0x00, 0xBB, 0xBF, 0x99, 0xF9, 0xBB, 0xAF}, // ucEepromInst
                {0xB6, 0x01, 0x11},                                           // ucFlashInst
                0x3E,                                                         // ucSPHaddr
                0x3D,                                                         // ucSPLaddr
                fill_b2(8192 / 64),                                           // uiFlashpages
                0x31,                                                         // ucDWDRAddress
                0x00,                                                         // ucDWBasePC
                0x00,           // ucAllowFullPageBitstream
                fill_b2(0xF80), // uiStartSmallestBootLoaderSection
                1,              // EnablePageProgramming
                0,              // ucCacheType
                fill_b2(0x100), // uiSramStartAddr
                0,              // ucResetType
                0,              // ucPCMaskExtended
                0,              // ucPCMaskHigh
                0,              // ucEindAddress
                fill_b2(0x1F),  // EECRAddress
            },
            {0}, // Xmega device descr.
        },
        {
            "attiny167",
            0x9487,
            128,
            128, // 16384 bytes flash
            4,
            128,    // 512 bytes EEPROM
            20 * 4, // 20 interrupt vectors
            DEVFL_MKII_ONLY,
            attiny167_io_registers,
            false,
            0x07,
            0x0000, // fuses
            0x66,   // osccal
            1,      // OCD revision
            {
                0 // no mkI support
            },
            {
                CMND_SET_DEVICE_DESCRIPTOR,
                {0x3F, 0x00, 0x64, 0xF8, 0xEF, 0x3D, 0xB9, 0xE0}, // ucReadIO
                {0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00}, // ucReadIOShadow
                {0x36, 0x00, 0x04, 0xE0, 0xEF, 0x1D, 0xB8, 0xE0}, // ucWriteIO
                {0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00}, // ucWriteIOShadow
                {0x5F, 0xDB, 0x80, 0xDF, 0xFF, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x40, 0x1F, 0x00, 0xFF,
                 0x07, 0x00}, // ucReadExtIO
                {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // ucReadIOExtShadow
                {0x1C, 0xDB, 0x80, 0xD8, 0xFF, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x40, 0x15, 0x00, 0xF7,
                 0x07, 0x00}, // ucWriteExtIO
                {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // ucWriteIOExtShadow
                0x00,                                                         // ucIDRAddress
                0x57,                                                         // ucSPMCRAddress
                0,                                                            // ucRAMPZAddress
                fill_b2(128),                                                 // uiFlashPageSize
                4,                                                            // ucEepromPageSize
                fill_b4(0),                                                   // ulBootAddress
                fill_b2(0x00D2),                                              // uiUpperExtIOLoc
                fill_b4(16384),                                               // ulFlashSize
                {0xBD, 0xF2, 0xBD, 0xE1, 0xBB, 0xCF, 0xB4, 0x00, 0xBE, 0x01,
                 0xB6, 0x01, 0xBC, 0x00, 0xBB, 0xBF, 0x99, 0xF9, 0xBB, 0xAF}, // ucEepromInst
                {0xB6, 0x01, 0x11},                                           // ucFlashInst
                0x3E,                                                         // ucSPHaddr
                0x3D,                                                         // ucSPLaddr
                fill_b2(16384 / 128),                                         // uiFlashpages
                0x31,                                                         // ucDWDRAddress
                0x00,                                                         // ucDWBasePC
                0x00,            // ucAllowFullPageBitstream
                fill_b2(0x00),   // uiStartSmallestBootLoaderSection
                1,               // EnablePageProgramming
                0,               // ucCacheType
                fill_b2(0x0100), // uiSramStartAddr
                0,               // ucResetType
                0,               // ucPCMaskExtended
                0,               // ucPCMaskHigh
                0,               // ucEindAddress
                fill_b2(0x1F),   // EECRAddress
            },
            {0}, // Xmega device descr.
        },
        {
            "attiny43u",
            0x920C,
            64,
            64, // 4096 bytes flash
            4,
            16,     // 64 bytes EEPROM
            16 * 2, // 16 interrupt vectors
            DEVFL_MKII_ONLY,
            attiny43u_io_registers,
            false,
            0x07,
            0x0000, // fuses
            0x51,   // osccal
            1,      // OCD revision
            {
                0 // no mkI support
            },
            {
                CMND_SET_DEVICE_DESCRIPTOR,
                {0xFB, 0xF9, 0xFD, 0x7F, 0x4B, 0xF8, 0xFF, 0xFF}, // ucReadIO
                {0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00}, // ucReadIOShadow
                {0x8B, 0xB0, 0xBD, 0x7D, 0x09, 0xF8, 0x7D, 0xFA}, // ucWriteIO
                {0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00}, // ucWriteIOShadow
                {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // ucReadExtIO
                {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // ucReadIOExtShadow
                {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // ucWriteExtIO
                {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // ucWriteIOExtShadow
                0x00,                                                         // ucIDRAddress
                0x57,                                                         // ucSPMCRAddress
                0,                                                            // ucRAMPZAddress
                fill_b2(64),                                                  // uiFlashPageSize
                4,                                                            // ucEepromPageSize
                fill_b4(0),                                                   // ulBootAddress
                fill_b2(0x0000),                                              // uiUpperExtIOLoc
                fill_b4(4096),                                                // ulFlashSize
                {0xBB, 0xFF, 0xBB, 0xEE, 0xBB, 0xCC, 0xB2, 0x0D, 0xBC, 0x07,
                 0xB4, 0x07, 0xBA, 0x0D, 0xBB, 0xBC, 0x99, 0xE1, 0xBB, 0xAC}, // ucEepromInst
                {0xB4, 0x07, 0x17},                                           // ucFlashInst
                0x3E,                                                         // ucSPHaddr
                0x3D,                                                         // ucSPLaddr
                fill_b2(4096 / 64),                                           // uiFlashpages
                0x20,                                                         // ucDWDRAddress
                0x00,                                                         // ucDWBasePC
                0x00,          // ucAllowFullPageBitstream
                fill_b2(0x00), // uiStartSmallestBootLoaderSection
                1,             // EnablePageProgramming
                0,             // ucCacheType
                fill_b2(0x60), // uiSramStartAddr
                0,             // ucResetType
                0,             // ucPCMaskExtended
                0,             // ucPCMaskHigh
                0,             // ucEindAddress
                fill_b2(0x1C), // EECRAddress
            },
            {0}, // Xmega device descr.
        },
        {
            "attiny48",
            0x9209,
            64,
            64, // 4096 bytes flash
            4,
            16,     // 64 bytes EEPROM
            20 * 2, // 20 interrupt vectors
            DEVFL_MKII_ONLY,
            attiny48_io_registers,
            false,
            0x07,
            0x0000, // fuses
            0x66,   // osccal
            1,      // OCD revision
            {
                0 // no mkI support
            },
            {
                CMND_SET_DEVICE_DESCRIPTOR,
                {0xF8, 0x7F, 0x64, 0xF8, 0xEB, 0x3D, 0xB9, 0xA0}, // ucReadIO
                {0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00}, // ucReadIOShadow
                {0xB0, 0x0D, 0x00, 0xE0, 0xFB, 0x1D, 0xB8, 0xA0}, // ucWriteIO
                {0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00}, // ucWriteIOShadow
                {0x53, 0xFF, 0x00, 0xDF, 0xF7, 0x0F, 0x00, 0x00, 0x00, 0x00,
                 0x00, 0x7F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // ucReadExtIO
                {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // ucReadIOExtShadow
                {0x00, 0xFF, 0x00, 0xDC, 0xF7, 0x0F, 0x00, 0x00, 0x00, 0x00,
                 0x00, 0x7F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // ucWriteExtIO
                {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // ucWriteIOExtShadow
                0x00,                                                         // ucIDRAddress
                0X00,                                                         // ucSPMCRAddress
                0,                                                            // ucRAMPZAddress
                fill_b2(64),                                                  // uiFlashPageSize
                4,                                                            // ucEepromPageSize
                fill_b4(0x0000),                                              // ulBootAddress
                fill_b2(0xBD),                                                // uiUpperExtIOLoc
                fill_b4(4096),                                                // ulFlashSize
                {0xBD, 0xF2, 0xBD, 0xE1, 0xBB, 0xCF, 0xB4, 0x00, 0xBE, 0x01,
                 0xB6, 0x01, 0xBC, 0x00, 0xBB, 0xBF, 0x99, 0xF9, 0xBB, 0xAF}, // ucEepromInst
                {0xB6, 0x01, 0x11},                                           // ucFlashInst
                0x3E,                                                         // ucSPHaddr
                0x3D,                                                         // ucSPLaddr
                fill_b2(4096 / 64),                                           // uiFlashpages
                0x31,                                                         // ucDWDRAddress
                0x00,                                                         // ucDWBasePC
                0x00,           // ucAllowFullPageBitstream
                fill_b2(0x00),  // uiStartSmallestBootLoaderSection
                1,              // EnablePageProgramming
                0,              // ucCacheType
                fill_b2(0x100), // uiSramStartAddr
                0,              // ucResetType
                0,              // ucPCMaskExtended
                0,              // ucPCMaskHigh
                0,              // ucEindAddress
                fill_b2(0x1F),  // EECRAddress
            },
            {0}, // Xmega device descr.
        },
        {
            "attiny88",
            0x9311,
            64,
            128, // 8192 bytes flash
            4,
            16,     // 64 bytes EEPROM
            20 * 2, // 20 interrupt vectors
            DEVFL_MKII_ONLY,
            attiny88_io_registers,
            false,
            0x07,
            0x0000, // fuses
            0x66,   // osccal
            1,      // OCD revision
            {
                0 // no mkI support
            },
            {
                CMND_SET_DEVICE_DESCRIPTOR,
                {0xF8, 0x7F, 0x64, 0xF8, 0xEB, 0x3D, 0xB9, 0xA0}, // ucReadIO
                {0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00}, // ucReadIOShadow
                {0xB0, 0x0D, 0x00, 0xE0, 0xFB, 0x1D, 0xB8, 0xA0}, // ucWriteIO
                {0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00}, // ucWriteIOShadow
                {0x53, 0xFF, 0x00, 0xDF, 0xF7, 0x0F, 0x00, 0x00, 0x00, 0x00,
                 0x00, 0x7F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // ucReadExtIO
                {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // ucReadIOExtShadow
                {0x00, 0xFF, 0x00, 0xDC, 0xF7, 0x0F, 0x00, 0x00, 0x00, 0x00,
                 0x00, 0x7F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // ucWriteExtIO
                {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // ucWriteIOExtShadow
                0x00,                                                         // ucIDRAddress
                0X00,                                                         // ucSPMCRAddress
                0,                                                            // ucRAMPZAddress
                fill_b2(64),                                                  // uiFlashPageSize
                4,                                                            // ucEepromPageSize
                fill_b4(0x0000),                                              // ulBootAddress
                fill_b2(0xBD),                                                // uiUpperExtIOLoc
                fill_b4(8192),                                                // ulFlashSize
                {0xBD, 0xF2, 0xBD, 0xE1, 0xBB, 0xCF, 0xB4, 0x00, 0xBE, 0x01,
                 0xB6, 0x01, 0xBC, 0x00, 0xBB, 0xBF, 0x99, 0xF9, 0xBB, 0xAF}, // ucEepromInst
                {0xB6, 0x01, 0x11},                                           // ucFlashInst
                0x3E,                                                         // ucSPHaddr
                0x3D,                                                         // ucSPLaddr
                fill_b2(8192 / 64),                                           // uiFlashpages
                0x31,                                                         // ucDWDRAddress
                0x00,                                                         // ucDWBasePC
                0x00,           // ucAllowFullPageBitstream
                fill_b2(0x00),  // uiStartSmallestBootLoaderSection
                1,              // EnablePageProgramming
                0,              // ucCacheType
                fill_b2(0x100), // uiSramStartAddr
                0,              // ucResetType
                0,              // ucPCMaskExtended
                0,              // ucPCMaskHigh
                0,              // ucEindAddress
                fill_b2(0x1F),  // EECRAddress
            },
            {0}, // Xmega device descr.
        },
        // DEV_ATXMEGA128A1 revision D
        {
            "atxmega128a1revd",
            0x9741,
            512,
            272, // 139264 bytes flash
            32,
            64,      // 2048 bytes EEPROM
            125 * 4, // 125 interrupt vectors
            DEVFL_MKII_ONLY,
            nullptr, // registers not yet defined
            true,
            0x37,
            0x0000, // fuses
            0,      // osccal
            0,      // OCD revision
            {
                0 // no mkI support
            },
            {
                CMND_SET_DEVICE_DESCRIPTOR,
                {0xFF, 0xFF, 0xFF, 0xF9, 0xFF, 0x3D, 0xB9, 0xF8}, // ucReadIO
                {0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00}, // ucReadIOShadow
                {0xFF, 0xFF, 0x1F, 0xE0, 0xFF, 0x1D, 0xA9, 0xF8}, // ucWriteIO
                {0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00}, // ucWriteIOShadow
                {0x73, 0xFF, 0x3F, 0xFF, 0xF7, 0x3F, 0xF7, 0x3F, 0xF7, 0x3F,
                 0x5F, 0x3F, 0x37, 0x37, 0x36, 0x00, 0x00, 0x00, 0x00, 0x00,
                 0xFF, 0x0F, 0x00, 0x00, 0xF7, 0x3F, 0x36, 0x00}, // ucReadExtIO
                {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // ucReadIOExtShadow
                {0x73, 0xFF, 0x3F, 0xF8, 0xF7, 0x3F, 0xF7, 0x3F, 0xF7, 0x3F,
                 0x5F, 0x2F, 0x36, 0x36, 0x36, 0x00, 0x00, 0x00, 0x00, 0x00,
                 0xFF, 0x0F, 0x00, 0x00, 0xF7, 0x3F, 0x36, 0x00}, // ucWriteExtIO
                {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // ucWriteIOExtShadow
                0x31,                                                         // ucIDRAddress
                0x57,                                                         // ucSPMCRAddress
                0,                                                            // ucRAMPZAddress
                fill_b2(512),                                                 // uiFlashPageSize
                32,                                                           // ucEepromPageSize
                fill_b4(0x20000),                                             // ulBootAddress
                fill_b2(0x136),                                               // uiUpperExtIOLoc
                fill_b4(139264),                                              // ulFlashSize
                {0x00},                                                       // ucEepromInst
                {0x00},                                                       // ucFlashInst
                0x3E,                                                         // ucSPHaddr
                0x3D,                                                         // ucSPLaddr
                fill_b2(139264 / 512),                                        // uiFlashpages
                0x00,                                                         // ucDWDRAddress
                0x00,                                                         // ucDWBasePC
                0x00,          // ucAllowFullPageBitstream
                fill_b2(0x00), // uiStartSmallestBootLoaderSection
                1,             // EnablePageProgramming
                0x02,          // ucCacheType
                fill_b2(8192), // uiSramStartAddr
                0,             // ucResetType
                0,             // ucPCMaskExtended
                0,             // ucPCMaskHigh
                0,             // ucEindAddress
                fill_b2(0),    // EECRAddress
            },
            {
                CMND_SET_XMEGA_PARAMS, // cmd
                fill_b2(2),            // whatever
                47,                    // length of following data
                fill_b4(0x800000),     // NVM offset for application flash
                fill_b4(0x820000),     // NVM offset for boot flash
                fill_b4(0x8c0000),     // NVM offset for EEPROM
                fill_b4(0x8f0020),     // NVM offset for fuses
                fill_b4(0x8f0027),     // NVM offset for lock bits
                fill_b4(0x8e0400),     // NVM offset for user signature row
                fill_b4(0x8e0200),     // NVM offset for production sig. row
                fill_b4(0x1000000),    // NVM offset for data memory
                fill_b4(131072),       // size of application flash
                fill_b2(8192),         // size of boot flash
                fill_b2(512),          // flash page size
                fill_b2(2048),         // size of EEPROM
                32,                    // EEPROM page size
                fill_b2(0x1c0),        // IO space base address of NVM controller
                fill_b2(0x90),         // IO space address of MCU control
            },
        },
        // DEV_ATXMEGA128A1 revision G (and newer)
        {
            "atxmega128a1",
            0x974c,
            512,
            272, // 139264 bytes flash
            32,
            64,      // 2048 bytes EEPROM
            125 * 4, // 125 interrupt vectors
            DEVFL_MKII_ONLY,
            nullptr, // registers not yet defined
            true,
            0x37,
            0x0000, // fuses
            0,      // osccal
            0,      // OCD revision
            {
                0 // no mkI support
            },
            {
                CMND_SET_DEVICE_DESCRIPTOR,
                {0xFF, 0xFF, 0xFF, 0xF9, 0xFF, 0x3D, 0xB9, 0xF8}, // ucReadIO
                {0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00}, // ucReadIOShadow
                {0xFF, 0xFF, 0x1F, 0xE0, 0xFF, 0x1D, 0xA9, 0xF8}, // ucWriteIO
                {0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00}, // ucWriteIOShadow
                {0x73, 0xFF, 0x3F, 0xFF, 0xF7, 0x3F, 0xF7, 0x3F, 0xF7, 0x3F,
                 0x5F, 0x3F, 0x37, 0x37, 0x36, 0x00, 0x00, 0x00, 0x00, 0x00,
                 0xFF, 0x0F, 0x00, 0x00, 0xF7, 0x3F, 0x36, 0x00}, // ucReadExtIO
                {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // ucReadIOExtShadow
                {0x73, 0xFF, 0x3F, 0xF8, 0xF7, 0x3F, 0xF7, 0x3F, 0xF7, 0x3F,
                 0x5F, 0x2F, 0x36, 0x36, 0x36, 0x00, 0x00, 0x00, 0x00, 0x00,
                 0xFF, 0x0F, 0x00, 0x00, 0xF7, 0x3F, 0x36, 0x00}, // ucWriteExtIO
                {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // ucWriteIOExtShadow
                0x31,                                                         // ucIDRAddress
                0x57,                                                         // ucSPMCRAddress
                0,                                                            // ucRAMPZAddress
                fill_b2(512),                                                 // uiFlashPageSize
                32,                                                           // ucEepromPageSize
                fill_b4(0x20000),                                             // ulBootAddress
                fill_b2(0x136),                                               // uiUpperExtIOLoc
                fill_b4(139264),                                              // ulFlashSize
                {0x00},                                                       // ucEepromInst
                {0x00},                                                       // ucFlashInst
                0x3E,                                                         // ucSPHaddr
                0x3D,                                                         // ucSPLaddr
                fill_b2(139264 / 512),                                        // uiFlashpages
                0x00,                                                         // ucDWDRAddress
                0x00,                                                         // ucDWBasePC
                0x00,          // ucAllowFullPageBitstream
                fill_b2(0x00), // uiStartSmallestBootLoaderSection
                1,             // EnablePageProgramming
                0x02,          // ucCacheType
                fill_b2(8192), // uiSramStartAddr
                0,             // ucResetType
                0,             // ucPCMaskExtended
                0,             // ucPCMaskHigh
                0,             // ucEindAddress
                fill_b2(0),    // EECRAddress
            },
            {
                CMND_SET_XMEGA_PARAMS, // cmd
                fill_b2(2),            // whatever
                47,                    // length of following data
                fill_b4(0x800000),     // NVM offset for application flash
                fill_b4(0x820000),     // NVM offset for boot flash
                fill_b4(0x8c0000),     // NVM offset for EEPROM
                fill_b4(0x8f0020),     // NVM offset for fuses
                fill_b4(0x8f0027),     // NVM offset for lock bits
                fill_b4(0x8e0400),     // NVM offset for user signature row
                fill_b4(0x8e0200),     // NVM offset for production sig. row
                fill_b4(0x1000000),    // NVM offset for data memory
                fill_b4(131072),       // size of application flash
                fill_b2(8192),         // size of boot flash
                fill_b2(512),          // flash page size
                fill_b2(2048),         // size of EEPROM
                32,                    // EEPROM page size
                fill_b2(0x1c0),        // IO space base address of NVM controller
                fill_b2(0x90),         // IO space address of MCU control
            },
        },
        {
            "atxmega192a3",
            0x9744,
            512,
            400, // 204800 bytes flash
            32,
            128,     // 4096 bytes EEPROM
            122 * 4, // 122 interrupt vectors
            DEVFL_MKII_ONLY,
            nullptr, // registers not yet defined
            true,
            0x37,
            0x0000, // fuses
            0,      // osccal
            0,      // OCD revision
            {
                0 // no mkI support
            },
            {
                CMND_SET_DEVICE_DESCRIPTOR,
                {0xFF, 0xFF, 0xFF, 0xF9, 0xFF, 0x3D, 0xB9, 0xF8}, // ucReadIO
                {0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00}, // ucReadIOShadow
                {0xFF, 0xFF, 0x1F, 0xE0, 0xFF, 0x1D, 0xA9, 0xF8}, // ucWriteIO
                {0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00}, // ucWriteIOShadow
                {0x73, 0xFF, 0x3F, 0xFF, 0xF7, 0x3F, 0xF7, 0x3F, 0xF7, 0x3F,
                 0x5F, 0x3F, 0x37, 0x37, 0x36, 0x00, 0x00, 0x00, 0x00, 0x00,
                 0xFF, 0x0F, 0x00, 0x00, 0xF7, 0x3F, 0x36, 0x00}, // ucReadExtIO
                {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // ucReadIOExtShadow
                {0x73, 0xFF, 0x3F, 0xF8, 0xF7, 0x3F, 0xF7, 0x3F, 0xF7, 0x3F,
                 0x5F, 0x2F, 0x36, 0x36, 0x36, 0x00, 0x00, 0x00, 0x00, 0x00,
                 0xFF, 0x0F, 0x00, 0x00, 0xF7, 0x3F, 0x36, 0x00}, // ucWriteExtIO
                {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // ucWriteIOExtShadow
                0x31,                                                         // ucIDRAddress
                0x57,                                                         // ucSPMCRAddress
                0,                                                            // ucRAMPZAddress
                fill_b2(512),                                                 // uiFlashPageSize
                32,                                                           // ucEepromPageSize
                fill_b4(0x40000),                                             // ulBootAddress
                fill_b2(0x136),                                               // uiUpperExtIOLoc
                fill_b4(270336),                                              // ulFlashSize
                {0x00},                                                       // ucEepromInst
                {0x00},                                                       // ucFlashInst
                0x3E,                                                         // ucSPHaddr
                0x3D,                                                         // ucSPLaddr
                fill_b2(204800 / 512),                                        // uiFlashpages
                0x00,                                                         // ucDWDRAddress
                0x00,                                                         // ucDWBasePC
                0x00,          // ucAllowFullPageBitstream
                fill_b2(0x00), // uiStartSmallestBootLoaderSection
                1,             // EnablePageProgramming
                0x02,          // ucCacheType
                fill_b2(8192), // uiSramStartAddr
                0,             // ucResetType
                0,             // ucPCMaskExtended
                0,             // ucPCMaskHigh
                0,             // ucEindAddress
                fill_b2(0),    // EECRAddress
            },
            {
                CMND_SET_XMEGA_PARAMS, // cmd
                fill_b2(2),            // whatever
                47,                    // length of following data
                fill_b4(0x800000),     // NVM offset for application flash
                fill_b4(0x840000),     // NVM offset for boot flash
                fill_b4(0x8c0000),     // NVM offset for EEPROM
                fill_b4(0x8f0020),     // NVM offset for fuses
                fill_b4(0x8f0027),     // NVM offset for lock bits
                fill_b4(0x8e0400),     // NVM offset for user signature row
                fill_b4(0x8e0200),     // NVM offset for production sig. row
                fill_b4(0x1000000),    // NVM offset for data memory
                fill_b4(196608),       // size of application flash
                fill_b2(8192),         // size of boot flash
                fill_b2(512),          // flash page size
                fill_b2(4096),         // size of EEPROM
                32,                    // EEPROM page size
                fill_b2(0x1c0),        // IO space base address of NVM controller
                fill_b2(0x90),         // IO space address of MCU control
            },
        },
        {
            "atxmega256a3",
            0x9842,
            512,
            528, // 270336 bytes flash
            32,
            128,     // 4096 bytes EEPROM
            122 * 4, // 122 interrupt vectors
            DEVFL_MKII_ONLY,
            nullptr, // registers not yet defined
            true,
            0x37,
            0x0000, // fuses
            0,      // osccal
            0,      // OCD revision
            {
                0 // no mkI support
            },
            {
                CMND_SET_DEVICE_DESCRIPTOR,
                {0xFF, 0xFF, 0xFF, 0xF9, 0xFF, 0x3D, 0xB9, 0xF8}, // ucReadIO
                {0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00}, // ucReadIOShadow
                {0xFF, 0xFF, 0x1F, 0xE0, 0xFF, 0x1D, 0xA9, 0xF8}, // ucWriteIO
                {0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00}, // ucWriteIOShadow
                {0x73, 0xFF, 0x3F, 0xFF, 0xF7, 0x3F, 0xF7, 0x3F, 0xF7, 0x3F,
                 0x5F, 0x3F, 0x37, 0x37, 0x36, 0x00, 0x00, 0x00, 0x00, 0x00,
                 0xFF, 0x0F, 0x00, 0x00, 0xF7, 0x3F, 0x36, 0x00}, // ucReadExtIO
                {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // ucReadIOExtShadow
                {0x73, 0xFF, 0x3F, 0xF8, 0xF7, 0x3F, 0xF7, 0x3F, 0xF7, 0x3F,
                 0x5F, 0x2F, 0x36, 0x36, 0x36, 0x00, 0x00, 0x00, 0x00, 0x00,
                 0xFF, 0x0F, 0x00, 0x00, 0xF7, 0x3F, 0x36, 0x00}, // ucWriteExtIO
                {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // ucWriteIOExtShadow
                0x31,                                                         // ucIDRAddress
                0x57,                                                         // ucSPMCRAddress
                0,                                                            // ucRAMPZAddress
                fill_b2(512),                                                 // uiFlashPageSize
                32,                                                           // ucEepromPageSize
                fill_b4(0x40000),                                             // ulBootAddress
                fill_b2(0x136),                                               // uiUpperExtIOLoc
                fill_b4(270336),                                              // ulFlashSize
                {0x00},                                                       // ucEepromInst
                {0x00},                                                       // ucFlashInst
                0x3E,                                                         // ucSPHaddr
                0x3D,                                                         // ucSPLaddr
                fill_b2(270336 / 512),                                        // uiFlashpages
                0x00,                                                         // ucDWDRAddress
                0x00,                                                         // ucDWBasePC
                0x00,          // ucAllowFullPageBitstream
                fill_b2(0x00), // uiStartSmallestBootLoaderSection
                1,             // EnablePageProgramming
                0x02,          // ucCacheType
                fill_b2(8192), // uiSramStartAddr
                0,             // ucResetType
                0,             // ucPCMaskExtended
                0,             // ucPCMaskHigh
                0,             // ucEindAddress
                fill_b2(0),    // EECRAddress
            },
            {
                CMND_SET_XMEGA_PARAMS, // cmd
                fill_b2(2),            // whatever
                47,                    // length of following data
                fill_b4(0x800000),     // NVM offset for application flash
                fill_b4(0x840000),     // NVM offset for boot flash
                fill_b4(0x8c0000),     // NVM offset for EEPROM
                fill_b4(0x8f0020),     // NVM offset for fuses
                fill_b4(0x8f0027),     // NVM offset for lock bits
                fill_b4(0x8e0400),     // NVM offset for user signature row
                fill_b4(0x8e0200),     // NVM offset for production sig. row
                fill_b4(0x1000000),    // NVM offset for data memory
                fill_b4(262144),       // size of application flash
                fill_b2(8192),         // size of boot flash
                fill_b2(512),          // flash page size
                fill_b2(4096),         // size of EEPROM
                32,                    // EEPROM page size
                fill_b2(0x1c0),        // IO space base address of NVM controller
                fill_b2(0x90),         // IO space address of MCU control
            },
        },
        {
            "atxmega32a4",
            0x9541,
            256,
            144, // 36864 bytes flash
            32,
            32,     // 1024 bytes EEPROM
            94 * 4, // 94 interrupt vectors?
            DEVFL_MKII_ONLY,
            nullptr, // registers not yet defined
            true,
            0x37,
            0x0000, // fuses
            0,      // osccal
            0,      // OCD revision
            {
                0 // no mkI support
            },
            {
                CMND_SET_DEVICE_DESCRIPTOR,
                {0xFF, 0xFF, 0xFF, 0xF9, 0xFF, 0x3D, 0xB9, 0xF8}, // ucReadIO
                {0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00}, // ucReadIOShadow
                {0xFF, 0xFF, 0x1F, 0xE0, 0xFF, 0x1D, 0xA9, 0xF8}, // ucWriteIO
                {0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00}, // ucWriteIOShadow
                {0x73, 0xFF, 0x3F, 0xFF, 0xF7, 0x3F, 0xF7, 0x3F, 0xF7, 0x3F,
                 0x5F, 0x3F, 0x37, 0x37, 0x36, 0x00, 0x00, 0x00, 0x00, 0x00,
                 0xFF, 0x0F, 0x00, 0x00, 0xF7, 0x3F, 0x36, 0x00}, // ucReadExtIO
                {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // ucReadIOExtShadow
                {0x73, 0xFF, 0x3F, 0xF8, 0xF7, 0x3F, 0xF7, 0x3F, 0xF7, 0x3F,
                 0x5F, 0x2F, 0x36, 0x36, 0x36, 0x00, 0x00, 0x00, 0x00, 0x00,
                 0xFF, 0x0F, 0x00, 0x00, 0xF7, 0x3F, 0x36, 0x00}, // ucWriteExtIO
                {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // ucWriteIOExtShadow
                0x31,                                                         // ucIDRAddress
                0x57,                                                         // ucSPMCRAddress
                0,                                                            // ucRAMPZAddress
                fill_b2(256),                                                 // uiFlashPageSize
                32,                                                           // ucEepromPageSize
                fill_b4(0x8000),                                              // ulBootAddress
                fill_b2(0x136),                                               // uiUpperExtIOLoc
                fill_b4(256 * 144),                                           // ulFlashSize
                {0x00},                                                       // ucEepromInst
                {0x00},                                                       // ucFlashInst
                0x3E,                                                         // ucSPHaddr
                0x3D,                                                         // ucSPLaddr
                fill_b2(144),                                                 // uiFlashpages
                0x00,                                                         // ucDWDRAddress
                0x00,                                                         // ucDWBasePC
                0x00,          // ucAllowFullPageBitstream
                fill_b2(0x00), // uiStartSmallestBootLoaderSection
                1,             // EnablePageProgramming
                0x02,          // ucCacheType
                fill_b2(8192), // uiSramStartAddr
                0,             // ucResetType
                0,             // ucPCMaskExtended
                0,             // ucPCMaskHigh
                0,             // ucEindAddress
                fill_b2(0),    // EECRAddress
            },
            {
                CMND_SET_XMEGA_PARAMS, // cmd
                fill_b2(2),            // whatever
                47,                    // length of following data
                fill_b4(0x800000),     // NVM offset for application flash
                fill_b4(0x808000),     // NVM offset for boot flash
                fill_b4(0x8c0000),     // NVM offset for EEPROM
                fill_b4(0x8f0020),     // NVM offset for fuses
                fill_b4(0x8f0027),     // NVM offset for lock bits
                fill_b4(0x8e0400),     // NVM offset for user signature row
                fill_b4(0x8e0200),     // NVM offset for production sig. row
                fill_b4(0x1000000),    // NVM offset for data memory
                fill_b4(32768),        // size of application flash
                fill_b2(4096),         // size of boot flash
                fill_b2(256),          // flash page size
                fill_b2(1024),         // size of EEPROM
                32,                    // EEPROM page size
                fill_b2(0x1c0),        // IO space base address of NVM controller
                fill_b2(0x90),         // IO space address of MCU control
            },
        },
        {
            "atxmega128a3",
            0x9742,
            512,
            272, // 139264 bytes flash
            32,
            64,      // 2048 bytes EEPROM
            122 * 4, // 122 interrupt vectors
            DEVFL_MKII_ONLY,
            nullptr, // registers not yet defined
            true,
            0x37,
            0x0000, // fuses
            0,      // osccal
            0,      // OCD revision
            {
                0 // no mkI support
            },
            {
                CMND_SET_DEVICE_DESCRIPTOR,
                {0xFF, 0xFF, 0xFF, 0xF9, 0xFF, 0x3D, 0xB9, 0xF8}, // ucReadIO
                {0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00}, // ucReadIOShadow
                {0xFF, 0xFF, 0x1F, 0xE0, 0xFF, 0x1D, 0xA9, 0xF8}, // ucWriteIO
                {0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00}, // ucWriteIOShadow
                {0x73, 0xFF, 0x3F, 0xFF, 0xF7, 0x3F, 0xF7, 0x3F, 0xF7, 0x3F,
                 0x5F, 0x3F, 0x37, 0x37, 0x36, 0x00, 0x00, 0x00, 0x00, 0x00,
                 0xFF, 0x0F, 0x00, 0x00, 0xF7, 0x3F, 0x36, 0x00}, // ucReadExtIO
                {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // ucReadIOExtShadow
                {0x73, 0xFF, 0x3F, 0xF8, 0xF7, 0x3F, 0xF7, 0x3F, 0xF7, 0x3F,
                 0x5F, 0x2F, 0x36, 0x36, 0x36, 0x00, 0x00, 0x00, 0x00, 0x00,
                 0xFF, 0x0F, 0x00, 0x00, 0xF7, 0x3F, 0x36, 0x00}, // ucWriteExtIO
                {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // ucWriteIOExtShadow
                0x31,                                                         // ucIDRAddress
                0x57,                                                         // ucSPMCRAddress
                0,                                                            // ucRAMPZAddress
                fill_b2(512),                                                 // uiFlashPageSize
                32,                                                           // ucEepromPageSize
                fill_b4(0x40000),                                             // ulBootAddress
                fill_b2(0x136),                                               // uiUpperExtIOLoc
                fill_b4(139264),                                              // ulFlashSize
                {0x00},                                                       // ucEepromInst
                {0x00},                                                       // ucFlashInst
                0x3E,                                                         // ucSPHaddr
                0x3D,                                                         // ucSPLaddr
                fill_b2(139264 / 512),                                        // uiFlashpages
                0x00,                                                         // ucDWDRAddress
                0x00,                                                         // ucDWBasePC
                0x00,          // ucAllowFullPageBitstream
                fill_b2(0x00), // uiStartSmallestBootLoaderSection
                1,             // EnablePageProgramming
                0x02,          // ucCacheType
                fill_b2(8192), // uiSramStartAddr
                0,             // ucResetType
                0,             // ucPCMaskExtended
                0,             // ucPCMaskHigh
                0,             // ucEindAddress
                fill_b2(0),    // EECRAddress
            },
            {
                CMND_SET_XMEGA_PARAMS, // cmd
                fill_b2(2),            // whatever
                47,                    // length of following data
                fill_b4(0x800000),     // NVM offset for application flash
                fill_b4(0x840000),     // NVM offset for boot flash
                fill_b4(0x8c0000),     // NVM offset for EEPROM
                fill_b4(0x8f0020),     // NVM offset for fuses
                fill_b4(0x8f0027),     // NVM offset for lock bits
                fill_b4(0x8e0400),     // NVM offset for user signature row
                fill_b4(0x8e0200),     // NVM offset for production sig. row
                fill_b4(0x1000000),    // NVM offset for data memory
                fill_b4(131072),       // size of application flash
                fill_b2(8192),         // size of boot flash
                fill_b2(512),          // flash page size
                fill_b2(2048),         // size of EEPROM
                32,                    // EEPROM page size
                fill_b2(0x1c0),        // IO space base address of NVM controller
                fill_b2(0x90),         // IO space address of MCU control
            },
        },
        {
            "atxmega16d4",
            0x9442,
            256,
            80, // 20480 bytes flash
            32,
            32,     // 1024 bytes EEPROM
            91 * 4, // 91 interrupt vectors
            DEVFL_MKII_ONLY,
            nullptr, // registers not yet defined
            true,
            0x37,
            0x0000, // fuses
            0,      // osccal
            0,      // OCD revision
            {
                0 // no mkI support
            },
            {
                CMND_SET_DEVICE_DESCRIPTOR,
                {0xFF, 0xFF, 0xFF, 0xF9, 0xFF, 0x3D, 0xB9, 0xF8}, // ucReadIO
                {0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00}, // ucReadIOShadow
                {0xFF, 0xFF, 0x1F, 0xE0, 0xFF, 0x1D, 0xA9, 0xF8}, // ucWriteIO
                {0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00}, // ucWriteIOShadow
                {0x73, 0xFF, 0x3F, 0xFF, 0xF7, 0x3F, 0xF7, 0x3F, 0xF7, 0x3F,
                 0x5F, 0x3F, 0x37, 0x37, 0x36, 0x00, 0x00, 0x00, 0x00, 0x00,
                 0xFF, 0x0F, 0x00, 0x00, 0xF7, 0x3F, 0x36, 0x00}, // ucReadExtIO
                {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // ucReadIOExtShadow
                {0x73, 0xFF, 0x3F, 0xF8, 0xF7, 0x3F, 0xF7, 0x3F, 0xF7, 0x3F,
                 0x5F, 0x2F, 0x36, 0x36, 0x36, 0x00, 0x00, 0x00, 0x00, 0x00,
                 0xFF, 0x0F, 0x00, 0x00, 0xF7, 0x3F, 0x36, 0x00}, // ucWriteExtIO
                {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // ucWriteIOExtShadow
                0x31,                                                         // ucIDRAddress
                0x57,                                                         // ucSPMCRAddress
                0,                                                            // ucRAMPZAddress
                fill_b2(256),                                                 // uiFlashPageSize
                32,                                                           // ucEepromPageSize
                fill_b4(0x4000),                                              // ulBootAddress
                fill_b2(0x136),                                               // uiUpperExtIOLoc
                fill_b4(20480),                                               // ulFlashSize
                {0x00},                                                       // ucEepromInst
                {0x00},                                                       // ucFlashInst
                0x3E,                                                         // ucSPHaddr
                0x3D,                                                         // ucSPLaddr
                fill_b2(20480 / 256),                                         // uiFlashpages
                0x00,                                                         // ucDWDRAddress
                0x00,                                                         // ucDWBasePC
                0x00,          // ucAllowFullPageBitstream
                fill_b2(0x00), // uiStartSmallestBootLoaderSection
                1,             // EnablePageProgramming
                0x02,          // ucCacheType
                fill_b2(8192), // uiSramStartAddr
                0,             // ucResetType
                0,             // ucPCMaskExtended
                0,             // ucPCMaskHigh
                0,             // ucEindAddress
                fill_b2(0),    // EECRAddress
            },
            {
                CMND_SET_XMEGA_PARAMS, // cmd
                fill_b2(2),            // whatever
                47,                    // length of following data
                fill_b4(0x800000),     // NVM offset for application flash
                fill_b4(0x804000),     // NVM offset for boot flash
                fill_b4(0x8c0000),     // NVM offset for EEPROM
                fill_b4(0x8f0020),     // NVM offset for fuses
                fill_b4(0x8f0027),     // NVM offset for lock bits
                fill_b4(0x8e0400),     // NVM offset for user signature row
                fill_b4(0x8e0200),     // NVM offset for production sig. row
                fill_b4(0x1000000),    // NVM offset for data memory
                fill_b4(16384),        // size of application flash
                fill_b2(4096),         // size of boot flash
                fill_b2(256),          // flash page size
                fill_b2(1024),         // size of EEPROM
                32,                    // EEPROM page size
                fill_b2(0x1c0),        // IO space base address of NVM controller
                fill_b2(0x90),         // IO space address of MCU control
            },
        },
        {
            "atmega128rfa1",
            0xA701,
            256,
            512, // 131072 bytes flash
            8,
            512,    // 4096 bytes EEPROM
            72 * 4, // 72 interrupt vectors
            DEVFL_MKII_ONLY,
            atmega128rfa1_io_registers,
            false,
            0x07,
            0x8000, // fuses
            0x66,   // osccal
            3,      // OCD revision
            {
                0 // no mkI support
            },
            {
                CMND_SET_DEVICE_DESCRIPTOR,
                {0xFF, 0xFF, 0xFF, 0xF9, 0xFF, 0x3D, 0xB9, 0xF8}, // ucReadIO
                {0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00}, // ucReadIOShadow
                {0xFF, 0xFF, 0x1F, 0xE0, 0xFF, 0x1D, 0xA9, 0xF8}, // ucWriteIO
                {0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00}, // ucWriteIOShadow
                {0xFB, 0xFF, 0xBF, 0xFF, 0xF7, 0x3F, 0xF7, 0x3F, 0xF7, 0x3F, 0x5F, 0x3F, 0x77, 0x77,
                 0x03, 0xF0, 0xFF, 0xFF, 0xFF, 0x01, 0x00, 0x00, 0x00, 0x00, 0xF7, 0xBF, 0xFF, 0xFA,
                 0xFE, 0xFF, 0xA7, 0xFF, 0xFF, 0xFF, 0xEF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
                 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF}, // ucReadExtIO
                {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // ucReadIOExtShadow
                {0xFB, 0xFF, 0xBF, 0xFF, 0xB7, 0x3F, 0xB7, 0x3F, 0xB7, 0x3F, 0x5F, 0x3F, 0x77, 0x77,
                 0x03, 0xB0, 0xFF, 0xE1, 0xFF, 0x01, 0x00, 0x00, 0x00, 0x00, 0xB7, 0xBF, 0xFF, 0xDA,
                 0x3C, 0xFF, 0xA7, 0x0F, 0xFF, 0xFF, 0xE8, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
                 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF}, // ucWriteExtIO
                {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // ucWriteIOExtShadow
                0x31,                                                         // ucIDRAddress
                0x57,                                                         // ucSPMCRAddress
                0x3B,                                                         // ucRAMPZAddress
                fill_b2(256),                                                 // uiFlashPageSize
                8,                                                            // ucEepromPageSize
                fill_b4(0xFE00),                                              // ulBootAddress
                fill_b2(0x01FF),                                              // uiUpperExtIOLoc
                fill_b4(131072),                                              // ulFlashSize
                {0x00},                                                       // ucEepromInst
                {0x00},                                                       // ucFlashInst
                0x3E,                                                         // ucSPHaddr
                0x3D,                                                         // ucSPLaddr
                fill_b2(131072 / 256),                                        // uiFlashpages
                0x00,                                                         // ucDWDRAddress
                0x00,                                                         // ucDWBasePC
                0x00,           // ucAllowFullPageBitstream
                fill_b2(0x00),  // uiStartSmallestBootLoaderSection
                1,              // EnablePageProgramming
                0,              // ucCacheType
                fill_b2(0x200), // uiSramStartAddr
                0,              // ucResetType
                0,              // ucPCMaskExtended
                0,              // ucPCMaskHigh
                0x3C,           // ucEindAddress
                fill_b2(0x1F),  // EECRAddress
            },
            {0}, // Xmega device descr.
        },
        {
            "atmega64rfr2",
            0xA602,
            256,
            256, // 65536 bytes flash
            8,
            256,    // 2048 bytes EEPROM
            77 * 4, // 77 interrupt vectors
            DEVFL_MKII_ONLY,
            atmega256rfr2_io_registers,
            false,
            0x07,
            0x8000, // fuses
            0x66,   // osccal
            3,      // OCD revision
            {
                0 // no mkI support
            },
            {
                CMND_SET_DEVICE_DESCRIPTOR,
                {0xFF, 0xFF, 0xFF, 0xF9, 0xFF, 0x3D, 0xB9, 0xF8}, // ucReadIO
                {0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00}, // ucReadIOShadow
                {0xFF, 0xFF, 0x1F, 0xE0, 0xFF, 0x1D, 0xA9, 0xF8}, // ucWriteIO
                {0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00}, // ucWriteIOShadow
                {0xFB, 0xFF, 0xBF, 0xFF, 0xF7, 0x3F, 0xF7, 0x3F, 0xF7, 0x3F, 0x5F, 0x3F, 0x77, 0x77,
                 0x03, 0xF0, 0xFF, 0xFF, 0xFF, 0x01, 0x00, 0x00, 0x00, 0x00, 0xF7, 0xBF, 0xFF, 0xFA,
                 0xFE, 0xFF, 0xA7, 0xFF, 0xFF, 0xFF, 0xEF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
                 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF}, // ucReadExtIO
                {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // ucReadIOExtShadow
                {0xFB, 0xFF, 0xBF, 0xFF, 0xB7, 0x3F, 0xB7, 0x3F, 0xB7, 0x3F, 0x5F, 0x3F, 0x77, 0x77,
                 0x03, 0xB0, 0xFF, 0xE1, 0xFF, 0x01, 0x00, 0x00, 0x00, 0x00, 0xB7, 0xBF, 0xFF, 0xDA,
                 0x3C, 0xFF, 0xA7, 0x0F, 0xFF, 0xFF, 0xE8, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
                 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF}, // ucWriteExtIO
                {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // ucWriteIOExtShadow
                0x31,                                                         // ucIDRAddress
                0x57,                                                         // ucSPMCRAddress
                0x3B,                                                         // ucRAMPZAddress
                fill_b2(256),                                                 // uiFlashPageSize
                8,                                                            // ucEepromPageSize
                fill_b4(0x7E00),                                              // ulBootAddress
                fill_b2(0x01FF),                                              // uiUpperExtIOLoc
                fill_b4(65536),                                               // ulFlashSize
                {0x00},                                                       // ucEepromInst
                {0x00},                                                       // ucFlashInst
                0x3E,                                                         // ucSPHaddr
                0x3D,                                                         // ucSPLaddr
                fill_b2(65536 / 256),                                         // uiFlashpages
                0x00,                                                         // ucDWDRAddress
                0x00,                                                         // ucDWBasePC
                0x00,           // ucAllowFullPageBitstream
                fill_b2(0x00),  // uiStartSmallestBootLoaderSection
                1,              // EnablePageProgramming
                0,              // ucCacheType
                fill_b2(0x200), // uiSramStartAddr
                0,              // ucResetType
                0,              // ucPCMaskExtended
                0,              // ucPCMaskHigh
                0x3C,           // ucEindAddress
                fill_b2(0x1F),  // EECRAddress
            },
            {0}, // Xmega device descr.
        },
        {
            "atmega644rfr2",
            0xA603,
            256,
            256, // 65536 bytes flash
            8,
            256,    // 2048 bytes EEPROM
            77 * 4, // 77 interrupt vectors
            DEVFL_MKII_ONLY,
            atmega256rfr2_io_registers,
            false,
            0x07,
            0x8000, // fuses
            0x66,   // osccal
            3,      // OCD revision
            {
                0 // no mkI support
            },
            {
                CMND_SET_DEVICE_DESCRIPTOR,
                {0xFF, 0xFF, 0xFF, 0xF9, 0xFF, 0x3D, 0xB9, 0xF8}, // ucReadIO
                {0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00}, // ucReadIOShadow
                {0xFF, 0xFF, 0x1F, 0xE0, 0xFF, 0x1D, 0xA9, 0xF8}, // ucWriteIO
                {0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00}, // ucWriteIOShadow
                {0xFB, 0xFF, 0xBF, 0xFF, 0xF7, 0x3F, 0xF7, 0x3F, 0xF7, 0x3F, 0x5F, 0x3F, 0x77, 0x77,
                 0x03, 0xF0, 0xFF, 0xFF, 0xFF, 0x01, 0x00, 0x00, 0x00, 0x00, 0xF7, 0xBF, 0xFF, 0xFA,
                 0xFE, 0xFF, 0xA7, 0xFF, 0xFF, 0xFF, 0xEF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
                 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF}, // ucReadExtIO
                {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // ucReadIOExtShadow
                {0xFB, 0xFF, 0xBF, 0xFF, 0xB7, 0x3F, 0xB7, 0x3F, 0xB7, 0x3F, 0x5F, 0x3F, 0x77, 0x77,
                 0x03, 0xB0, 0xFF, 0xE1, 0xFF, 0x01, 0x00, 0x00, 0x00, 0x00, 0xB7, 0xBF, 0xFF, 0xDA,
                 0x3C, 0xFF, 0xA7, 0x0F, 0xFF, 0xFF, 0xE8, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
                 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF}, // ucWriteExtIO
                {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // ucWriteIOExtShadow
                0x31,                                                         // ucIDRAddress
                0x57,                                                         // ucSPMCRAddress
                0x3B,                                                         // ucRAMPZAddress
                fill_b2(256),                                                 // uiFlashPageSize
                8,                                                            // ucEepromPageSize
                fill_b4(0x7E00),                                              // ulBootAddress
                fill_b2(0x01FF),                                              // uiUpperExtIOLoc
                fill_b4(65536),                                               // ulFlashSize
                {0x00},                                                       // ucEepromInst
                {0x00},                                                       // ucFlashInst
                0x3E,                                                         // ucSPHaddr
                0x3D,                                                         // ucSPLaddr
                fill_b2(65536 / 256),                                         // uiFlashpages
                0x00,                                                         // ucDWDRAddress
                0x00,                                                         // ucDWBasePC
                0x00,           // ucAllowFullPageBitstream
                fill_b2(0x00),  // uiStartSmallestBootLoaderSection
                1,              // EnablePageProgramming
                0,              // ucCacheType
                fill_b2(0x200), // uiSramStartAddr
                0,              // ucResetType
                0,              // ucPCMaskExtended
                0,              // ucPCMaskHigh
                0x3C,           // ucEindAddress
                fill_b2(0x1F),  // EECRAddress
            },
            {0}, // Xmega device descr.
        },
        {
            "atmega128rfr2",
            0xA702,
            256,
            512, // 131072 bytes flash
            8,
            512,    // 4096 bytes EEPROM
            77 * 4, // 77 interrupt vectors
            DEVFL_MKII_ONLY,
            atmega256rfr2_io_registers,
            false,
            0x07,
            0x8000, // fuses
            0x66,   // osccal
            3,      // OCD revision
            {
                0 // no mkI support
            },
            {
                CMND_SET_DEVICE_DESCRIPTOR,
                {0xFF, 0xFF, 0xFF, 0xF9, 0xFF, 0x3D, 0xB9, 0xF8}, // ucReadIO
                {0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00}, // ucReadIOShadow
                {0xFF, 0xFF, 0x1F, 0xE0, 0xFF, 0x1D, 0xA9, 0xF8}, // ucWriteIO
                {0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00}, // ucWriteIOShadow
                {0xFB, 0xFF, 0xBF, 0xFF, 0xF7, 0x3F, 0xF7, 0x3F, 0xF7, 0x3F, 0x5F, 0x3F, 0x77, 0x77,
                 0x03, 0xF0, 0xFF, 0xFF, 0xFF, 0x01, 0x00, 0x00, 0x00, 0x00, 0xF7, 0xBF, 0xFF, 0xFA,
                 0xFE, 0xFF, 0xA7, 0xFF, 0xFF, 0xFF, 0xEF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
                 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF}, // ucReadExtIO
                {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // ucReadIOExtShadow
                {0xFB, 0xFF, 0xBF, 0xFF, 0xB7, 0x3F, 0xB7, 0x3F, 0xB7, 0x3F, 0x5F, 0x3F, 0x77, 0x77,
                 0x03, 0xB0, 0xFF, 0xE1, 0xFF, 0x01, 0x00, 0x00, 0x00, 0x00, 0xB7, 0xBF, 0xFF, 0xDA,
                 0x3C, 0xFF, 0xA7, 0x0F, 0xFF, 0xFF, 0xE8, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
                 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF}, // ucWriteExtIO
                {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // ucWriteIOExtShadow
                0x31,                                                         // ucIDRAddress
                0x57,                                                         // ucSPMCRAddress
                0x3B,                                                         // ucRAMPZAddress
                fill_b2(256),                                                 // uiFlashPageSize
                8,                                                            // ucEepromPageSize
                fill_b4(0xFE00),                                              // ulBootAddress
                fill_b2(0x01FF),                                              // uiUpperExtIOLoc
                fill_b4(131072),                                              // ulFlashSize
                {0x00},                                                       // ucEepromInst
                {0x00},                                                       // ucFlashInst
                0x3E,                                                         // ucSPHaddr
                0x3D,                                                         // ucSPLaddr
                fill_b2(131072 / 256),                                        // uiFlashpages
                0x00,                                                         // ucDWDRAddress
                0x00,                                                         // ucDWBasePC
                0x00,           // ucAllowFullPageBitstream
                fill_b2(0x00),  // uiStartSmallestBootLoaderSection
                1,              // EnablePageProgramming
                0,              // ucCacheType
                fill_b2(0x200), // uiSramStartAddr
                0,              // ucResetType
                0,              // ucPCMaskExtended
                0,              // ucPCMaskHigh
                0x3C,           // ucEindAddress
                fill_b2(0x1F),  // EECRAddress
            },
            {0}, // Xmega device descr.
        },
        {
            "atmega1284rfr2",
            0xA703,
            256,
            512, // 131072 bytes flash
            8,
            512,    // 4096 bytes EEPROM
            77 * 4, // 77 interrupt vectors
            DEVFL_MKII_ONLY,
            atmega256rfr2_io_registers,
            false,
            0x07,
            0x8000, // fuses
            0x66,   // osccal
            3,      // OCD revision
            {
                0 // no mkI support
            },
            {
                CMND_SET_DEVICE_DESCRIPTOR,
                {0xFF, 0xFF, 0xFF, 0xF9, 0xFF, 0x3D, 0xB9, 0xF8}, // ucReadIO
                {0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00}, // ucReadIOShadow
                {0xFF, 0xFF, 0x1F, 0xE0, 0xFF, 0x1D, 0xA9, 0xF8}, // ucWriteIO
                {0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00}, // ucWriteIOShadow
                {0xFB, 0xFF, 0xBF, 0xFF, 0xF7, 0x3F, 0xF7, 0x3F, 0xF7, 0x3F, 0x5F, 0x3F, 0x77, 0x77,
                 0x03, 0xF0, 0xFF, 0xFF, 0xFF, 0x01, 0x00, 0x00, 0x00, 0x00, 0xF7, 0xBF, 0xFF, 0xFA,
                 0xFE, 0xFF, 0xA7, 0xFF, 0xFF, 0xFF, 0xEF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
                 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF}, // ucReadExtIO
                {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // ucReadIOExtShadow
                {0xFB, 0xFF, 0xBF, 0xFF, 0xB7, 0x3F, 0xB7, 0x3F, 0xB7, 0x3F, 0x5F, 0x3F, 0x77, 0x77,
                 0x03, 0xB0, 0xFF, 0xE1, 0xFF, 0x01, 0x00, 0x00, 0x00, 0x00, 0xB7, 0xBF, 0xFF, 0xDA,
                 0x3C, 0xFF, 0xA7, 0x0F, 0xFF, 0xFF, 0xE8, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
                 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF}, // ucWriteExtIO
                {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // ucWriteIOExtShadow
                0x31,                                                         // ucIDRAddress
                0x57,                                                         // ucSPMCRAddress
                0x3B,                                                         // ucRAMPZAddress
                fill_b2(256),                                                 // uiFlashPageSize
                8,                                                            // ucEepromPageSize
                fill_b4(0xFE00),                                              // ulBootAddress
                fill_b2(0x01FF),                                              // uiUpperExtIOLoc
                fill_b4(131072),                                              // ulFlashSize
                {0x00},                                                       // ucEepromInst
                {0x00},                                                       // ucFlashInst
                0x3E,                                                         // ucSPHaddr
                0x3D,                                                         // ucSPLaddr
                fill_b2(131072 / 256),                                        // uiFlashpages
                0x00,                                                         // ucDWDRAddress
                0x00,                                                         // ucDWBasePC
                0x00,           // ucAllowFullPageBitstream
                fill_b2(0x00),  // uiStartSmallestBootLoaderSection
                1,              // EnablePageProgramming
                0,              // ucCacheType
                fill_b2(0x200), // uiSramStartAddr
                0,              // ucResetType
                0,              // ucPCMaskExtended
                0,              // ucPCMaskHigh
                0x3C,           // ucEindAddress
                fill_b2(0x1F),  // EECRAddress
            },
            {0}, // Xmega device descr.
        },
        {
            "atmega256rfr2",
            0xA802,
            256,
            1024, // 262144 bytes flash
            8,
            1024,   // 8192 bytes EEPROM
            77 * 4, // 77 interrupt vectors
            DEVFL_MKII_ONLY,
            atmega256rfr2_io_registers,
            false,
            0x07,
            0x8000, // fuses
            0x66,   // osccal
            4,      // OCD revision
            {
                0 // no mkI support
            },
            {
                CMND_SET_DEVICE_DESCRIPTOR,
                {0xFF, 0xFF, 0xFF, 0xF9, 0xFF, 0x3D, 0xB9, 0xF8}, // ucReadIO
                {0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00}, // ucReadIOShadow
                {0xFF, 0xFF, 0x1F, 0xE0, 0xFF, 0x1D, 0xA9, 0xF8}, // ucWriteIO
                {0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00}, // ucWriteIOShadow
                {0xFB, 0xFF, 0xBF, 0xFF, 0xF7, 0x3F, 0xF7, 0x3F, 0xF7, 0x3F, 0x5F, 0x3F, 0x77, 0x77,
                 0x03, 0xF0, 0xFF, 0xFF, 0xFF, 0x01, 0x00, 0x00, 0x00, 0x00, 0xF7, 0xBF, 0xFF, 0xFA,
                 0xFE, 0xFF, 0xA7, 0xFF, 0xFF, 0xFF, 0xEF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
                 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF}, // ucReadExtIO
                {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // ucReadIOExtShadow
                {0xFB, 0xFF, 0xBF, 0xFF, 0xB7, 0x3F, 0xB7, 0x3F, 0xB7, 0x3F, 0x5F, 0x3F, 0x77, 0x77,
                 0x03, 0xB0, 0xFF, 0xE1, 0xFF, 0x01, 0x00, 0x00, 0x00, 0x00, 0xB7, 0xBF, 0xFF, 0xDA,
                 0x3C, 0xFF, 0xA7, 0x0F, 0xFF, 0xFF, 0xE8, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
                 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF}, // ucWriteExtIO
                {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // ucWriteIOExtShadow
                0x31,                                                         // ucIDRAddress
                0x57,                                                         // ucSPMCRAddress
                0x3B,                                                         // ucRAMPZAddress
                fill_b2(256),                                                 // uiFlashPageSize
                8,                                                            // ucEepromPageSize
                fill_b4(0x1FE00),                                             // ulBootAddress
                fill_b2(0x01FF),                                              // uiUpperExtIOLoc
                fill_b4(262144),                                              // ulFlashSize
                {0x00},                                                       // ucEepromInst
                {0x00},                                                       // ucFlashInst
                0x3E,                                                         // ucSPHaddr
                0x3D,                                                         // ucSPLaddr
                fill_b2(262144 / 256),                                        // uiFlashpages
                0x00,                                                         // ucDWDRAddress
                0x00,                                                         // ucDWBasePC
                0x00,           // ucAllowFullPageBitstream
                fill_b2(0x00),  // uiStartSmallestBootLoaderSection
                1,              // EnablePageProgramming
                0,              // ucCacheType
                fill_b2(0x200), // uiSramStartAddr
                0,              // ucResetType
                0,              // ucPCMaskExtended
                0,              // ucPCMaskHigh
                0x3C,           // ucEindAddress
                fill_b2(0x1F),  // EECRAddress
            },
            {0}, // Xmega device descr.
        },
        {
            "atmega2564rfr2",
            0xA803,
            256,
            1024, // 262144 bytes flash
            8,
            1024,   // 8192 bytes EEPROM
            77 * 4, // 77 interrupt vectors
            DEVFL_MKII_ONLY,
            atmega256rfr2_io_registers,
            false,
            0x07,
            0x8000, // fuses
            0x66,   // osccal
            4,      // OCD revision
            {
                0 // no mkI support
            },
            {
                CMND_SET_DEVICE_DESCRIPTOR,
                {0xFF, 0xFF, 0xFF, 0xF9, 0xFF, 0x3D, 0xB9, 0xF8}, // ucReadIO
                {0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00}, // ucReadIOShadow
                {0xFF, 0xFF, 0x1F, 0xE0, 0xFF, 0x1D, 0xA9, 0xF8}, // ucWriteIO
                {0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00}, // ucWriteIOShadow
                {0xFB, 0xFF, 0xBF, 0xFF, 0xF7, 0x3F, 0xF7, 0x3F, 0xF7, 0x3F, 0x5F, 0x3F, 0x77, 0x77,
                 0x03, 0xF0, 0xFF, 0xFF, 0xFF, 0x01, 0x00, 0x00, 0x00, 0x00, 0xF7, 0xBF, 0xFF, 0xFA,
                 0xFE, 0xFF, 0xA7, 0xFF, 0xFF, 0xFF, 0xEF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
                 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF}, // ucReadExtIO
                {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // ucReadIOExtShadow
                {0xFB, 0xFF, 0xBF, 0xFF, 0xB7, 0x3F, 0xB7, 0x3F, 0xB7, 0x3F, 0x5F, 0x3F, 0x77, 0x77,
                 0x03, 0xB0, 0xFF, 0xE1, 0xFF, 0x01, 0x00, 0x00, 0x00, 0x00, 0xB7, 0xBF, 0xFF, 0xDA,
                 0x3C, 0xFF, 0xA7, 0x0F, 0xFF, 0xFF, 0xE8, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
                 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF}, // ucWriteExtIO
                {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // ucWriteIOExtShadow
                0x31,                                                         // ucIDRAddress
                0x57,                                                         // ucSPMCRAddress
                0x3B,                                                         // ucRAMPZAddress
                fill_b2(256),                                                 // uiFlashPageSize
                8,                                                            // ucEepromPageSize
                fill_b4(0x1FE00),                                             // ulBootAddress
                fill_b2(0x01FF),                                              // uiUpperExtIOLoc
                fill_b4(262144),                                              // ulFlashSize
                {0x00},                                                       // ucEepromInst
                {0x00},                                                       // ucFlashInst
                0x3E,                                                         // ucSPHaddr
                0x3D,                                                         // ucSPLaddr
                fill_b2(262144 / 256),                                        // uiFlashpages
                0x00,                                                         // ucDWDRAddress
                0x00,                                                         // ucDWBasePC
                0x00,           // ucAllowFullPageBitstream
                fill_b2(0x00),  // uiStartSmallestBootLoaderSection
                1,              // EnablePageProgramming
                0,              // ucCacheType
                fill_b2(0x200), // uiSramStartAddr
                0,              // ucResetType
                0,              // ucPCMaskExtended
                0,              // ucPCMaskHigh
                0x3C,           // ucEindAddress
                fill_b2(0x1F),  // EECRAddress
            },
            {0}, // Xmega device descr.
        },
        {
            "atxmega128b1",
            0x974d,
            256,
            544, // 139264 bytes flash (page size. # pages)
            32,
            64,     // 2048 bytes EEPROM
            81 * 4, // 81 interrupt vectors
            DEVFL_MKII_ONLY,
            nullptr, // registers not yet defined
            true,
            0x37,
            0x0000, // fuses
            0,      // osccal
            0,      // OCD revision
            {
                0 // no mkI support
            },
            {
                CMND_SET_DEVICE_DESCRIPTOR,
                {0xFF, 0xFF, 0xFF, 0xF9, 0xFF, 0x3D, 0xB9, 0xF8}, // ucReadIO
                {0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00}, // ucReadIOShadow
                {0xFF, 0xFF, 0x1F, 0xE0, 0xFF, 0x1D, 0xA9, 0xF8}, // ucWriteIO
                {0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00}, // ucWriteIOShadow
                {0x73, 0xFF, 0x3F, 0xFF, 0xF7, 0x3F, 0xF7, 0x3F, 0xF7, 0x3F,
                 0x5F, 0x3F, 0x37, 0x37, 0x36, 0x00, 0x00, 0x00, 0x00, 0x00,
                 0xFF, 0x0F, 0x00, 0x00, 0xF7, 0x3F, 0x36, 0x00}, // ucReadExtIO
                {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // ucReadIOExtShadow
                {0x73, 0xFF, 0x3F, 0xF8, 0xF7, 0x3F, 0xF7, 0x3F, 0xF7, 0x3F,
                 0x5F, 0x2F, 0x36, 0x36, 0x36, 0x00, 0x00, 0x00, 0x00, 0x00,
                 0xFF, 0x0F, 0x00, 0x00, 0xF7, 0x3F, 0x36, 0x00}, // ucWriteExtIO
                {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // ucWriteIOExtShadow
                0x31,                                                         // ucIDRAddress
                0x57,                                                         // ucSPMCRAddress
                0,                                                            // ucRAMPZAddress
                fill_b2(256),                                                 // uiFlashPageSize
                32,                                                           // ucEepromPageSize
                fill_b4(0x20000),                                             // ulBootAddress
                fill_b2(0x136),                                               // uiUpperExtIOLoc
                fill_b4(139264),                                              // ulFlashSize
                {0x00},                                                       // ucEepromInst
                {0x00},                                                       // ucFlashInst
                0x3E,                                                         // ucSPHaddr
                0x3D,                                                         // ucSPLaddr
                fill_b2(139264 / 256),                                        // uiFlashpages
                0x00,                                                         // ucDWDRAddress
                0x00,                                                         // ucDWBasePC
                0x00,          // ucAllowFullPageBitstream
                fill_b2(0x00), // uiStartSmallestBootLoaderSection
                1,             // EnablePageProgramming
                0x02,          // ucCacheType
                fill_b2(8192), // uiSramStartAddr
                0,             // ucResetType
                0,             // ucPCMaskExtended
                0,             // ucPCMaskHigh
                0,             // ucEindAddress
                fill_b2(0),    // EECRAddress
            },
            {
                CMND_SET_XMEGA_PARAMS, // cmd
                fill_b2(2),            // whatever
                47,                    // length of following data
                fill_b4(0x800000),     // NVM offset for application flash
                fill_b4(0x820000),     // NVM offset for boot flash
                fill_b4(0x8c0000),     // NVM offset for EEPROM
                fill_b4(0x8f0020),     // NVM offset for fuses
                fill_b4(0x8f0027),     // NVM offset for lock bits
                fill_b4(0x8e0400),     // NVM offset for user signature row
                fill_b4(0x8e0200),     // NVM offset for production sig. row
                fill_b4(0x1000000),    // NVM offset for data memory
                fill_b4(131072),       // size of application flash
                fill_b2(8192),         // size of boot flash
                fill_b2(256),          // flash page size
                fill_b2(2048),         // size of EEPROM
                32,                    // EEPROM page size
                fill_b2(0x1c0),        // IO space base address of NVM controller
                fill_b2(0x90),         // IO space address of MCU control
            },
        },
        {
            "atxmega128b3",
            0x974b,
            256,
            544, // 139264 bytes flash (page size. # pages)
            32,
            64,     // 2048 bytes EEPROM
            54 * 4, // 54 interrupt vectors
            DEVFL_MKII_ONLY,
            nullptr, // registers not yet defined
            true,
            0x37,
            0x0000, // fuses
            0,      // osccal
            0,      // OCD revision
            {
                0 // no mkI support
            },
            {
                CMND_SET_DEVICE_DESCRIPTOR,
                {0xFF, 0xFF, 0xFF, 0xF9, 0xFF, 0x3D, 0xB9, 0xF8}, // ucReadIO
                {0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00}, // ucReadIOShadow
                {0xFF, 0xFF, 0x1F, 0xE0, 0xFF, 0x1D, 0xA9, 0xF8}, // ucWriteIO
                {0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00}, // ucWriteIOShadow
                {0x73, 0xFF, 0x3F, 0xFF, 0xF7, 0x3F, 0xF7, 0x3F, 0xF7, 0x3F,
                 0x5F, 0x3F, 0x37, 0x37, 0x36, 0x00, 0x00, 0x00, 0x00, 0x00,
                 0xFF, 0x0F, 0x00, 0x00, 0xF7, 0x3F, 0x36, 0x00}, // ucReadExtIO
                {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // ucReadIOExtShadow
                {0x73, 0xFF, 0x3F, 0xF8, 0xF7, 0x3F, 0xF7, 0x3F, 0xF7, 0x3F,
                 0x5F, 0x2F, 0x36, 0x36, 0x36, 0x00, 0x00, 0x00, 0x00, 0x00,
                 0xFF, 0x0F, 0x00, 0x00, 0xF7, 0x3F, 0x36, 0x00}, // ucWriteExtIO
                {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // ucWriteIOExtShadow
                0x31,                                                         // ucIDRAddress
                0x57,                                                         // ucSPMCRAddress
                0,                                                            // ucRAMPZAddress
                fill_b2(256),                                                 // uiFlashPageSize
                32,                                                           // ucEepromPageSize
                fill_b4(0x20000),                                             // ulBootAddress
                fill_b2(0x136),                                               // uiUpperExtIOLoc
                fill_b4(139264),                                              // ulFlashSize
                {0x00},                                                       // ucEepromInst
                {0x00},                                                       // ucFlashInst
                0x3E,                                                         // ucSPHaddr
                0x3D,                                                         // ucSPLaddr
                fill_b2(139264 / 256),                                        // uiFlashpages
                0x00,                                                         // ucDWDRAddress
                0x00,                                                         // ucDWBasePC
                0x00,          // ucAllowFullPageBitstream
                fill_b2(0x00), // uiStartSmallestBootLoaderSection
                1,             // EnablePageProgramming
                0x02,          // ucCacheType
                fill_b2(8192), // uiSramStartAddr
                0,             // ucResetType
                0,             // ucPCMaskExtended
                0,             // ucPCMaskHigh
                0,             // ucEindAddress
                fill_b2(0),    // EECRAddress
            },
            {
                CMND_SET_XMEGA_PARAMS, // cmd
                fill_b2(2),            // whatever
                47,                    // length of following data
                fill_b4(0x800000),     // NVM offset for application flash
                fill_b4(0x820000),     // NVM offset for boot flash
                fill_b4(0x8c0000),     // NVM offset for EEPROM
                fill_b4(0x8f0020),     // NVM offset for fuses
                fill_b4(0x8f0027),     // NVM offset for lock bits
                fill_b4(0x8e0400),     // NVM offset for user signature row
                fill_b4(0x8e0200),     // NVM offset for production sig. row
                fill_b4(0x1000000),    // NVM offset for data memory
                fill_b4(131072),       // size of application flash
                fill_b2(8192),         // size of boot flash
                fill_b2(256),          // flash page size
                fill_b2(2048),         // size of EEPROM
                32,                    // EEPROM page size
                fill_b2(0x1c0),        // IO space base address of NVM controller
                fill_b2(0x90),         // IO space address of MCU control
            },
        },
        {
            "atxmega64b1",
            0x9652,
            256,
            272, // 69,632 bytes flash (page size. # pages)
            32,
            64,     // 2048 bytes EEPROM
            81 * 4, // 81 interrupt vectors
            DEVFL_MKII_ONLY,
            nullptr, // registers not yet defined
            true,
            0x37,
            0x0000, // fuses
            0,      // osccal
            0,      // OCD revision
            {
                0 // no mkI support
            },
            {
                CMND_SET_DEVICE_DESCRIPTOR,
                {0xFF, 0xFF, 0xFF, 0xF9, 0xFF, 0x3D, 0xB9, 0xF8}, // ucReadIO
                {0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00}, // ucReadIOShadow
                {0xFF, 0xFF, 0x1F, 0xE0, 0xFF, 0x1D, 0xA9, 0xF8}, // ucWriteIO
                {0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00}, // ucWriteIOShadow
                {0x73, 0xFF, 0x3F, 0xFF, 0xF7, 0x3F, 0xF7, 0x3F, 0xF7, 0x3F,
                 0x5F, 0x3F, 0x37, 0x37, 0x36, 0x00, 0x00, 0x00, 0x00, 0x00,
                 0xFF, 0x0F, 0x00, 0x00, 0xF7, 0x3F, 0x36, 0x00}, // ucReadExtIO
                {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // ucReadIOExtShadow
                {0x73, 0xFF, 0x3F, 0xF8, 0xF7, 0x3F, 0xF7, 0x3F, 0xF7, 0x3F,
                 0x5F, 0x2F, 0x36, 0x36, 0x36, 0x00, 0x00, 0x00, 0x00, 0x00,
                 0xFF, 0x0F, 0x00, 0x00, 0xF7, 0x3F, 0x36, 0x00}, // ucWriteExtIO
                {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // ucWriteIOExtShadow
                0x31,                                                         // ucIDRAddress
                0x57,                                                         // ucSPMCRAddress
                0,                                                            // ucRAMPZAddress
                fill_b2(256),                                                 // uiFlashPageSize
                32,                                                           // ucEepromPageSize
                fill_b4(0x10000),                                             // ulBootAddress
                fill_b2(0x136),                                               // uiUpperExtIOLoc
                fill_b4(69632),                                               // ulFlashSize
                {0x00},                                                       // ucEepromInst
                {0x00},                                                       // ucFlashInst
                0x3E,                                                         // ucSPHaddr
                0x3D,                                                         // ucSPLaddr
                fill_b2(69632 / 256),                                         // uiFlashpages
                0x00,                                                         // ucDWDRAddress
                0x00,                                                         // ucDWBasePC
                0x00,          // ucAllowFullPageBitstream
                fill_b2(0x00), // uiStartSmallestBootLoaderSection
                1,             // EnablePageProgramming
                0x02,          // ucCacheType
                fill_b2(8192), // uiSramStartAddr
                0,             // ucResetType
                0,             // ucPCMaskExtended
                0,             // ucPCMaskHigh
                0,             // ucEindAddress
                fill_b2(0),    // EECRAddress
            },
            {
                CMND_SET_XMEGA_PARAMS, // cmd
                fill_b2(2),            // whatever
                47,                    // length of following data
                fill_b4(0x800000),     // NVM offset for application flash
                fill_b4(0x810000),     // NVM offset for boot flash
                fill_b4(0x8c0000),     // NVM offset for EEPROM
                fill_b4(0x8f0020),     // NVM offset for fuses
                fill_b4(0x8f0027),     // NVM offset for lock bits
                fill_b4(0x8e0400),     // NVM offset for user signature row
                fill_b4(0x8e0200),     // NVM offset for production sig. row
                fill_b4(0x1000000),    // NVM offset for data memory
                fill_b4(65536),        // size of application flash
                fill_b2(4096),         // size of boot flash
                fill_b2(256),          // flash page size
                fill_b2(2048),         // size of EEPROM
                32,                    // EEPROM page size
                fill_b2(0x1c0),        // IO space base address of NVM controller
                fill_b2(0x90),         // IO space address of MCU control
            },
        },
        {
            "atxmega64b3",
            0x9651,
            256,
            272, // 69,632 bytes flash (page size. # pages)
            32,
            64,     // 2048 bytes EEPROM
            54 * 4, // 54 interrupt vectors
            DEVFL_MKII_ONLY,
            nullptr, // registers not yet defined
            true,
            0x37,
            0x0000, // fuses
            0,      // osccal
            0,      // OCD revision
            {
                0 // no mkI support
            },
            {
                CMND_SET_DEVICE_DESCRIPTOR,
                {0xFF, 0xFF, 0xFF, 0xF9, 0xFF, 0x3D, 0xB9, 0xF8}, // ucReadIO
                {0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00}, // ucReadIOShadow
                {0xFF, 0xFF, 0x1F, 0xE0, 0xFF, 0x1D, 0xA9, 0xF8}, // ucWriteIO
                {0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00}, // ucWriteIOShadow
                {0x73, 0xFF, 0x3F, 0xFF, 0xF7, 0x3F, 0xF7, 0x3F, 0xF7, 0x3F,
                 0x5F, 0x3F, 0x37, 0x37, 0x36, 0x00, 0x00, 0x00, 0x00, 0x00,
                 0xFF, 0x0F, 0x00, 0x00, 0xF7, 0x3F, 0x36, 0x00}, // ucReadExtIO
                {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // ucReadIOExtShadow
                {0x73, 0xFF, 0x3F, 0xF8, 0xF7, 0x3F, 0xF7, 0x3F, 0xF7, 0x3F,
                 0x5F, 0x2F, 0x36, 0x36, 0x36, 0x00, 0x00, 0x00, 0x00, 0x00,
                 0xFF, 0x0F, 0x00, 0x00, 0xF7, 0x3F, 0x36, 0x00}, // ucWriteExtIO
                {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // ucWriteIOExtShadow
                0x31,                                                         // ucIDRAddress
                0x57,                                                         // ucSPMCRAddress
                0,                                                            // ucRAMPZAddress
                fill_b2(256),                                                 // uiFlashPageSize
                32,                                                           // ucEepromPageSize
                fill_b4(0x10000),                                             // ulBootAddress
                fill_b2(0x136),                                               // uiUpperExtIOLoc
                fill_b4(69632),                                               // ulFlashSize
                {0x00},                                                       // ucEepromInst
                {0x00},                                                       // ucFlashInst
                0x3E,                                                         // ucSPHaddr
                0x3D,                                                         // ucSPLaddr
                fill_b2(69632 / 256),                                         // uiFlashpages
                0x00,                                                         // ucDWDRAddress
                0x00,                                                         // ucDWBasePC
                0x00,          // ucAllowFullPageBitstream
                fill_b2(0x00), // uiStartSmallestBootLoaderSection
                1,             // EnablePageProgramming
                0x02,          // ucCacheType
                fill_b2(8192), // uiSramStartAddr
                0,             // ucResetType
                0,             // ucPCMaskExtended
                0,             // ucPCMaskHigh
                0,             // ucEindAddress
                fill_b2(0),    // EECRAddress
            },
            {
                CMND_SET_XMEGA_PARAMS, // cmd
                fill_b2(2),            // whatever
                47,                    // length of following data
                fill_b4(0x800000),     // NVM offset for application flash
                fill_b4(0x810000),     // NVM offset for boot flash
                fill_b4(0x8c0000),     // NVM offset for EEPROM
                fill_b4(0x8f0020),     // NVM offset for fuses
                fill_b4(0x8f0027),     // NVM offset for lock bits
                fill_b4(0x8e0400),     // NVM offset for user signature row
                fill_b4(0x8e0200),     // NVM offset for production sig. row
                fill_b4(0x1000000),    // NVM offset for data memory
                fill_b4(65536),        // size of application flash
                fill_b2(4096),         // size of boot flash
                fill_b2(256),          // flash page size
                fill_b2(2048),         // size of EEPROM
                32,                    // EEPROM page size
                fill_b2(0x1c0),        // IO space base address of NVM controller
                fill_b2(0x90),         // IO space address of MCU control
            },
        },
        {
            "atxmega64a3",
            0x9642,
            256,
            272, // 69,632 bytes flash (page size. # pages)
            32,
            64,      // 2048 bytes EEPROM
            122 * 4, // 122 interrupt vectors
            DEVFL_MKII_ONLY,
            nullptr, // registers not yet defined
            true,
            0x37,
            0x0000, // fuses
            0,      // osccal
            0,      // OCD revision
            {
                0 // no mkI support
            },
            {
                CMND_SET_DEVICE_DESCRIPTOR,
                {0xFF, 0xFF, 0xFF, 0xF9, 0xFF, 0x3D, 0xB9, 0xF8}, // ucReadIO
                {0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00}, // ucReadIOShadow
                {0xFF, 0xFF, 0x1F, 0xE0, 0xFF, 0x1D, 0xA9, 0xF8}, // ucWriteIO
                {0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00}, // ucWriteIOShadow
                {0x73, 0xFF, 0x3F, 0xFF, 0xF7, 0x3F, 0xF7, 0x3F, 0xF7, 0x3F,
                 0x5F, 0x3F, 0x37, 0x37, 0x36, 0x00, 0x00, 0x00, 0x00, 0x00,
                 0xFF, 0x0F, 0x00, 0x00, 0xF7, 0x3F, 0x36, 0x00}, // ucReadExtIO
                {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // ucReadIOExtShadow
                {0x73, 0xFF, 0x3F, 0xF8, 0xF7, 0x3F, 0xF7, 0x3F, 0xF7, 0x3F,
                 0x5F, 0x2F, 0x36, 0x36, 0x36, 0x00, 0x00, 0x00, 0x00, 0x00,
                 0xFF, 0x0F, 0x00, 0x00, 0xF7, 0x3F, 0x36, 0x00}, // ucWriteExtIO
                {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // ucWriteIOExtShadow
                0x31,                                                         // ucIDRAddress
                0x57,                                                         // ucSPMCRAddress
                0,                                                            // ucRAMPZAddress
                fill_b2(256),                                                 // uiFlashPageSize
                32,                                                           // ucEepromPageSize
                fill_b4(0x20000),                                             // ulBootAddress
                fill_b2(0x136),                                               // uiUpperExtIOLoc
                fill_b4(69632),                                               // ulFlashSize
                {0x00},                                                       // ucEepromInst
                {0x00},                                                       // ucFlashInst
                0x3E,                                                         // ucSPHaddr
                0x3D,                                                         // ucSPLaddr
                fill_b2(69632 / 256),                                         // uiFlashpages
                0x00,                                                         // ucDWDRAddress
                0x00,                                                         // ucDWBasePC
                0x00,          // ucAllowFullPageBitstream
                fill_b2(0x00), // uiStartSmallestBootLoaderSection
                1,             // EnablePageProgramming
                0x02,          // ucCacheType
                fill_b2(8192), // uiSramStartAddr
                0,             // ucResetType
                0,             // ucPCMaskExtended
                0,             // ucPCMaskHigh
                0,             // ucEindAddress
                fill_b2(0),    // EECRAddress
            },
            {
                CMND_SET_XMEGA_PARAMS, // cmd
                fill_b2(2),            // whatever
                47,                    // length of following data
                fill_b4(0x800000),     // NVM offset for application flash
                fill_b4(0x840000),     // NVM offset for boot flash
                fill_b4(0x8c0000),     // NVM offset for EEPROM
                fill_b4(0x8f0020),     // NVM offset for fuses
                fill_b4(0x8f0027),     // NVM offset for lock bits
                fill_b4(0x8e0400),     // NVM offset for user signature row
                fill_b4(0x8e0200),     // NVM offset for production sig. row
                fill_b4(0x1000000),    // NVM offset for data memory
                fill_b4(69632),        // size of application flash
                fill_b2(4096),         // size of boot flash
                fill_b2(256),          // flash page size
                fill_b2(2048),         // size of EEPROM
                32,                    // EEPROM page size
                fill_b2(0x1c0),        // IO space base address of NVM controller
                fill_b2(0x90),         // IO space address of MCU control
            },
        },
        {
            "atxmega32e5",
            0x954c,
            128,
            288, // 36864 bytes flash
            32,
            32,     // 1024 bytes EEPROM
            40 * 4, // 40 interrupt vectors
            DEVFL_MKII_ONLY,
            nullptr, // registers not yet defined
            true,
            0x37,
            0x0000, // fuses
            0,      // osccal
            0,      // OCD revision
            {
                0 // no mkI support
            },
            {
                CMND_SET_DEVICE_DESCRIPTOR,
                {0xFF, 0xFF, 0xFF, 0xF9, 0xFF, 0x3D, 0xB9, 0xF8}, // ucReadIO
                {0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00}, // ucReadIOShadow
                {0xFF, 0xFF, 0x1F, 0xE0, 0xFF, 0x1D, 0xA9, 0xF8}, // ucWriteIO
                {0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00}, // ucWriteIOShadow
                {0x73, 0xFF, 0x3F, 0xFF, 0xF7, 0x3F, 0xF7, 0x3F, 0xF7, 0x3F,
                 0x5F, 0x3F, 0x37, 0x37, 0x36, 0x00, 0x00, 0x00, 0x00, 0x00,
                 0xFF, 0x0F, 0x00, 0x00, 0xF7, 0x3F, 0x36, 0x00}, // ucReadExtIO
                {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // ucReadIOExtShadow
                {0x73, 0xFF, 0x3F, 0xF8, 0xF7, 0x3F, 0xF7, 0x3F, 0xF7, 0x3F,
                 0x5F, 0x2F, 0x36, 0x36, 0x36, 0x00, 0x00, 0x00, 0x00, 0x00,
                 0xFF, 0x0F, 0x00, 0x00, 0xF7, 0x3F, 0x36, 0x00}, // ucWriteExtIO
                {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // ucWriteIOExtShadow
                0x31,                                                         // ucIDRAddress
                0x57,                                                         // ucSPMCRAddress
                0,                                                            // ucRAMPZAddress
                fill_b2(128),                                                 // uiFlashPageSize
                32,                                                           // ucEepromPageSize
                fill_b4(0x8000),                                              // ulBootAddress
                fill_b2(0x136),                                               // uiUpperExtIOLoc
                fill_b4(128 * 288),                                           // ulFlashSize
                {0x00},                                                       // ucEepromInst
                {0x00},                                                       // ucFlashInst
                0x3E,                                                         // ucSPHaddr
                0x3D,                                                         // ucSPLaddr
                fill_b2(288),                                                 // uiFlashpages
                0x00,                                                         // ucDWDRAddress
                0x00,                                                         // ucDWBasePC
                0x00,          // ucAllowFullPageBitstream
                fill_b2(0x00), // uiStartSmallestBootLoaderSection
                1,             // EnablePageProgramming
                0x02,          // ucCacheType
                fill_b2(8192), // uiSramStartAddr
                0,             // ucResetType
                0,             // ucPCMaskExtended
                0,             // ucPCMaskHigh
                0,             // ucEindAddress
                fill_b2(0),    // EECRAddress
            },
            {
                CMND_SET_XMEGA_PARAMS, // cmd
                fill_b2(2),            // whatever
                47,                    // length of following data
                fill_b4(0x800000),     // NVM offset for application flash
                fill_b4(0x808000),     // NVM offset for boot flash
                fill_b4(0x8c0000),     // NVM offset for EEPROM
                fill_b4(0x8f0020),     // NVM offset for fuses
                fill_b4(0x8f0027),     // NVM offset for lock bits
                fill_b4(0x8e0400),     // NVM offset for user signature row
                fill_b4(0x8e0200),     // NVM offset for production sig. row
                fill_b4(0x1000000),    // NVM offset for data memory
                fill_b4(32768),        // size of application flash
                fill_b2(4096),         // size of boot flash
                fill_b2(128),          // flash page size
                fill_b2(1024),         // size of EEPROM
                32,                    // EEPROM page size
                fill_b2(0x1c0),        // IO space base address of NVM controller
                fill_b2(0x90),         // IO space address of MCU control
            },
        },
        {
            "atxmega8e5",
            0x9341,
            128,
            80, // 10240 bytes flash
            32,
            16,     // ? bytes EEPROM
            40 * 4, // 40 interrupt vectors
            DEVFL_MKII_ONLY,
            nullptr, // registers not yet defined
            true,
            0x37,
            0x0000, // fuses
            0,      // osccal
            0,      // OCD revision
            {
                0 // no mkI support
            },
            {
                CMND_SET_DEVICE_DESCRIPTOR,
                {0xFF, 0xFF, 0xFF, 0xF9, 0xFF, 0x3D, 0xB9, 0xF8}, // ucReadIO
                {0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00}, // ucReadIOShadow
                {0xFF, 0xFF, 0x1F, 0xE0, 0xFF, 0x1D, 0xA9, 0xF8}, // ucWriteIO
                {0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00}, // ucWriteIOShadow
                {0x73, 0xFF, 0x3F, 0xFF, 0xF7, 0x3F, 0xF7, 0x3F, 0xF7, 0x3F,
                 0x5F, 0x3F, 0x37, 0x37, 0x36, 0x00, 0x00, 0x00, 0x00, 0x00,
                 0xFF, 0x0F, 0x00, 0x00, 0xF7, 0x3F, 0x36, 0x00}, // ucReadExtIO
                {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // ucReadIOExtShadow
                {0x73, 0xFF, 0x3F, 0xF8, 0xF7, 0x3F, 0xF7, 0x3F, 0xF7, 0x3F,
                 0x5F, 0x2F, 0x36, 0x36, 0x36, 0x00, 0x00, 0x00, 0x00, 0x00,
                 0xFF, 0x0F, 0x00, 0x00, 0xF7, 0x3F, 0x36, 0x00}, // ucWriteExtIO
                {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // ucWriteIOExtShadow
                0x31,                                                         // ucIDRAddress
                0x57,                                                         // ucSPMCRAddress
                0,                                                            // ucRAMPZAddress
                fill_b2(128),                                                 // uiFlashPageSize
                32,                                                           // ucEepromPageSize
                fill_b4(0x2000),                                              // ulBootAddress
                fill_b2(0x136),                                               // uiUpperExtIOLoc
                fill_b4(128 * 80),                                            // ulFlashSize
                {0x00},                                                       // ucEepromInst
                {0x00},                                                       // ucFlashInst
                0x3E,                                                         // ucSPHaddr
                0x3D,                                                         // ucSPLaddr
                fill_b2(80),                                                  // uiFlashpages
                0x00,                                                         // ucDWDRAddress
                0x00,                                                         // ucDWBasePC
                0x00,          // ucAllowFullPageBitstream
                fill_b2(0x00), // uiStartSmallestBootLoaderSection
                1,             // EnablePageProgramming
                0x02,          // ucCacheType
                fill_b2(8192), // uiSramStartAddr
                0,             // ucResetType
                0,             // ucPCMaskExtended
                0,             // ucPCMaskHigh
                0,             // ucEindAddress
                fill_b2(0),    // EECRAddress
            },
            {
                CMND_SET_XMEGA_PARAMS, // cmd
                fill_b2(2),            // whatever
                47,                    // length of following data
                fill_b4(0x800000),     // NVM offset for application flash
                fill_b4(0x808000),     // NVM offset for boot flash
                fill_b4(0x8c0000),     // NVM offset for EEPROM
                fill_b4(0x8f0020),     // NVM offset for fuses
                fill_b4(0x8f0027),     // NVM offset for lock bits
                fill_b4(0x8e0400),     // NVM offset for user signature row
                fill_b4(0x8e0200),     // NVM offset for production sig. row
                fill_b4(0x1000000),    // NVM offset for data memory
                fill_b4(8192),         // size of application flash
                fill_b2(2048),         // size of boot flash
                fill_b2(128),          // flash page size
                fill_b2(512),          // size of EEPROM
                32,                    // EEPROM page size
                fill_b2(0x1c0),        // IO space base address of NVM controller
                fill_b2(0x90),         // IO space address of MCU control
            },
        },
};
}

const jtag_device_def_type &FindDeviceDefinition(const unsigned int id, const char *name) {
    const jtag_device_def_type *found_id = nullptr;
    if (id) {
        statusOut("Reported device ID: 0x%0X\n", id);
        found_id = std::find_if(std::begin(deviceDefinitions), std::end(deviceDefinitions),
                                [&](const auto &dev) { return dev.device_id == id; });
        if( found_id == std::end(deviceDefinitions) )
            found_id = nullptr;
    }

    const jtag_device_def_type *found_name = nullptr;
    if (name) {
        debugOut("Looking for device: %s\n", name);
        found_name = std::find_if(std::begin(deviceDefinitions), std::end(deviceDefinitions),
                                  [&](const auto &dev) { return strcasecmp(dev.name, name) == 0; });
        if( found_name == std::end(deviceDefinitions) )
            found_name = nullptr;
    }

    if( !found_id && !found_name ) {
        fprintf(stderr, "Device not found in internal database: id=0x%0X or name='%s'\n", id, name?name:"");
        throw jtag_exception();
    } else if( found_id && found_name ) {
        if( found_name->device_id != found_id->device_id ) {
            statusOut("Detected device ID: 0x%0X %s -- FORCED with %s\n", found_id->device_id,
                      found_id->name, name);
            return *found_name;
        } else {
            return *found_id;
        }
    } else if( found_id ) {
        return *found_id;
    } else if( found_name ) {
        return *found_name;
    } else {
        // All cases were covered, silence the compiler
        throw jtag_exception();
    }
}

void DumpAllDeviceDefinitions() {
    fprintf(stderr, "%-17s  %10s  %8s  %8s\n", "Device Name", "Device ID", "Flash", "EEPROM");
    fprintf(stderr, "%-17s  %10s  %8s  %8s\n", "---------------", "---------", "-------",
            "-------");
    for( const auto& dev : deviceDefinitions ) {
        const unsigned eesize = dev.eeprom_page_size * dev.eeprom_page_count;

        if (eesize != 0 && eesize < 1024)
            fprintf(stderr, "%-17s      0x%04X  %4d KiB  %4.1f KiB\n", dev.name, dev.device_id,
                    dev.flash_page_size * dev.flash_page_count / 1024, eesize / 1024.0);
        else
            fprintf(stderr, "%-17s      0x%04X  %4d KiB  %4d KiB\n", dev.name, dev.device_id,
                    dev.flash_page_size * dev.flash_page_count / 1024, eesize / 1024);
    }
}
