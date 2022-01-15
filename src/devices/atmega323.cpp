#include "../jtag.h"

namespace {

constexpr gdb_io_reg_def_type atmega323_io_registers[] = {{"TWBR", 0x20, 0x00},
                                                      {"TWSR", 0x21, 0x00},
                                                      {"TWAR", 0x22, 0x00},
                                                      {"TWDR", 0x23, 0x00},
                                                      {"ADCL", 0x24, IO_REG_RSE},
                                                      {"ADCH", 0x25, IO_REG_RSE},
                                                      {"ADCSR", 0x26, 0x00},
                                                      {"ADMUX", 0x27, 0x00},
                                                      {"ACSR", 0x28, 0x00},
                                                      {"UBRR", 0x29, 0x00},
                                                      {"UCSRB", 0x2a, 0x00},
                                                      {"UCSRA", 0x2b, 0x00},
                                                      {"UDR", 0x2c, IO_REG_RSE},
                                                      {"SPCR", 0x2d, 0x00},
                                                      {"SPSR", 0x2e, 0x00},
                                                      {"SPDR", 0x2f, 0x00},
                                                      {"PIND", 0x30, 0x00},
                                                      {"DDRD", 0x31, 0x00},
                                                      {"PORTD", 0x32, 0x00},
                                                      {"PINC", 0x33, 0x00},
                                                      {"DDRC", 0x34, 0x00},
                                                      {"PORTC", 0x35, 0x00},
                                                      {"PINB", 0x36, 0x00},
                                                      {"DDRB", 0x37, 0x00},
                                                      {"PORTB", 0x38, 0x00},
                                                      {"PINA", 0x39, 0x00},
                                                      {"DDRA", 0x3a, 0x00},
                                                      {"PORTA", 0x3b, 0x00},
                                                      {"EECR", 0x3c, 0x00},
                                                      {"EEDR", 0x3d, 0x00},
                                                      {"EEARL", 0x3e, 0x00},
                                                      {"EEARH", 0x3f, 0x00},
                                                      {"UBRRH", 0x40, 0x00},
                                                      {"WDTCR", 0x41, 0x00},
                                                      {"ASSR", 0x42, 0x00},
                                                      {"OCR2", 0x43, 0x00},
                                                      {"TCNT2", 0x44, 0x00},
                                                      {"TCCR2", 0x45, 0x00},
                                                      {"ICR1L", 0x46, 0x00},
                                                      {"ICR1H", 0x47, 0x00},
                                                      {"OCR1BL", 0x48, 0x00},
                                                      {"OCR1BH", 0x49, 0x00},
                                                      {"OCR1AL", 0x4a, 0x00},
                                                      {"OCR1AH", 0x4b, 0x00},
                                                      {"TCNT1L", 0x4c, 0x00},
                                                      {"TCNT1H", 0x4d, 0x00},
                                                      {"TCCR1B", 0x4e, 0x00},
                                                      {"TCCR1A", 0x4f, 0x00},
                                                      {"SFIOR", 0x50, 0x00},
                                                      {"OSCCAL", 0x51, 0x00},
                                                      {"TCNT0", 0x52, 0x00},
                                                      {"TCCR0", 0x53, 0x00},
                                                      {"MCUSR", 0x54, 0x00},
                                                      {"MCUCR", 0x55, 0x00},
                                                      {"TWCR", 0x56, 0x00},
                                                      {"SPMCR", 0x57, 0x00},
                                                      {"TIFR", 0x58, 0x00},
                                                      {"TIMSK", 0x59, 0x00},
                                                      {"GIFR", 0x5a, 0x00},
                                                      {"GIMSK", 0x5b, 0x00},
                                                      {"OCR0", 0x5c, 0x00},
                                                      {"SPL", 0x5d, 0x00},
                                                      {"SPH", 0x5e, 0x00},
                                                      {"SREG", 0x5f, 0x00},
                                                      {nullptr, 0, 0}};

[[maybe_unused]] const jtag_device_def_type atmega323 {
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
        fill_b2(0),                                       // uiStartSmallestBootLoaderSection
        1,                                                // EnablePageProgramming
        0,                                                // ucCacheType
        fill_b2(0x60),                                    // uiSramStartAddr
        0,                                                // ucResetType
        0,                                                // ucPCMaskExtended
        0,                                                // ucPCMaskHigh
        0,                                                // ucEindAddress
        fill_b2(0x1c),                                    // EECRAddress
    },
    {0} // Xmega device descr.
};

} // namespace
