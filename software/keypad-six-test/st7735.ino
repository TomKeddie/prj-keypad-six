#include <SPI.h>
#include <avr/pgmspace.h>

#include "keypad-six.h"

#define ST7735_NOP     0x00
#define ST7735_SWRESET 0x01

#define ST7735_SLPOUT  0x11
#define ST7735_NORON   0x13

#define ST7735_DISPON  0x29
#define ST7735_CASET   0x2A
#define ST7735_RASET   0x2B
#define ST7735_RAMWR   0x2C

#define ST7735_COLMOD  0x3A
#define ST7735_MADCTL  0x36

#define ST7735_FRMCTR1 0xB1
#define ST7735_FRMCTR2 0xB2
#define ST7735_FRMCTR3 0xB3
#define ST7735_INVCTR  0xB4

#define ST7735_PWCTR1  0xC0
#define ST7735_PWCTR2  0xC1
#define ST7735_PWCTR3  0xC2
#define ST7735_PWCTR5  0xC4
#define ST7735_VMCTR1  0xC5
#define ST7735_VMOFCTR 0xC7

#define ST7735_GMCTRP1 0xE0
#define ST7735_GMCTRN1 0xE1

#define ST7735_MADCTL_MY  0x80
#define ST7735_MADCTL_MX  0x40
#define ST7735_MADCTL_MV  0x20
#define ST7735_MADCTL_ML  0x10
#define ST7735_MADCTL_RGB 0x00
#define ST7735_MADCTL_BGR 0x08
#define ST7735_MADCTL_MH  0x04

static const uint8_t lcd_x_origin = 24;
static const uint8_t lcd_x_size        = 80;
static const uint8_t lcd_y_size       = 160;

static inline void spi_write_command_reg(uint8_t c) {
    digitalWrite(ST7735_DC_PIN, 0);
    SPI.transfer(&c, sizeof(c));
}

static inline void spi_write_data(uint8_t c) {
    digitalWrite(ST7735_DC_PIN, 1);
    SPI.transfer(&c, sizeof(c));
}

static inline void spi_write_data(const uint8_t* data_p, uint8_t data_count) {
    digitalWrite(ST7735_DC_PIN, 1);
    SPI.transfer(data_p, data_count);
}

static void set_write_region(uint8_t x_begin, uint8_t y_begin, uint8_t x_end, uint8_t y_end) {
    // convert x co-ordinates to ram address using origin of display in ram
    x_begin += lcd_x_origin;
    x_end += lcd_x_origin;

    {
        spi_write_command_reg(ST7735_CASET);
        const uint8_t data[] = { 0x00, x_begin, 0x00, x_end };
        spi_write_data(data, sizeof(data));
    }
    {
        spi_write_command_reg(ST7735_RASET);
        const uint8_t data[] = { 0x00, y_begin, 0x00, y_end };
        spi_write_data(data, sizeof(data));
    }
    spi_write_command_reg(ST7735_RAMWR);
}

static void st7735_init(void) {
    spi_write_command_reg(ST7735_SWRESET);
    delay(150);
    spi_write_command_reg(ST7735_SLPOUT);
    delay(500);

    {
        spi_write_command_reg(ST7735_FRMCTR1);
        const uint8_t data[] = { 0x05, 0x3C, 0x3C };
        spi_write_data(data, sizeof(data));
    }
    {
        spi_write_command_reg(ST7735_FRMCTR2);
        const uint8_t data[] = { 0x05, 0x3C, 0x3C };
        spi_write_data(data, sizeof(data));
    }
    {
        spi_write_command_reg(ST7735_FRMCTR3);
        const uint8_t data[] = { 0x05, 0x3C, 0x3C, 0x05, 0x3C, 0x3C };
        spi_write_data(data, sizeof(data));
    }

    spi_write_command_reg(ST7735_INVCTR);
    spi_write_data(0x03);

    {
        spi_write_command_reg(ST7735_PWCTR1);
        const uint8_t data[] = { 0xE0, 0x00, 0x07 };
        spi_write_data(data, sizeof(data));
    }

    spi_write_command_reg(ST7735_PWCTR2);
    spi_write_data(0xC5);

    {
        spi_write_command_reg(ST7735_PWCTR3);
        const uint8_t data[] = { 0x0A, 0x00 };
        spi_write_data(data, sizeof(data));
    }
    {
        spi_write_command_reg(ST7735_PWCTR5);
        const uint8_t data[] = { 0x8D, 0xEE };
        spi_write_data(data, sizeof(data));
    }

    spi_write_command_reg(ST7735_VMCTR1);
    spi_write_data(0x03);

    spi_write_command_reg(ST7735_VMOFCTR);
    spi_write_data(0x10);

    spi_write_command_reg(ST7735_MADCTL);
    spi_write_data(0xC8);

    spi_write_command_reg(ST7735_COLMOD);
    spi_write_data(0x05);

    {
        spi_write_command_reg(ST7735_CASET);
        const uint8_t data[] = { 0x00, lcd_x_origin, 0x00, lcd_x_size - 1 + lcd_x_origin };
        spi_write_data(data, sizeof(data));
    }
    {
        spi_write_command_reg(ST7735_RASET);
        const uint8_t data[] = { 0x00, 0x00, 0x00, lcd_y_size - 1 };
        spi_write_data(data, sizeof(data));
    }
    {
        spi_write_command_reg(ST7735_GMCTRP1);
        const uint8_t data[] = { 0x27, 0x0E, 0x07, 0x04, 0x11, 0x0B, 0x06, 0x0C, 0x0E, 0x14, 0x1B, 0x3E, 0x06, 0x25, 0x07, 0x1F };
        spi_write_data(data, sizeof(data));
    }
    {
        spi_write_command_reg(ST7735_GMCTRN1);
        const uint8_t data[] = {0x27, 0x0E, 0x07, 0x04, 0x11, 0x0B, 0x06, 0x0C, 0x0E, 0x14, 0x1B, 0x3E, 0x30, 0x25, 0x07, 0x1F };
        spi_write_data(data, sizeof(data));
    }

    spi_write_command_reg(ST7735_NORON);
    delay(10);
    spi_write_command_reg(ST7735_DISPON);
    delay(100);

    spi_write_command_reg(ST7735_MADCTL);
    spi_write_data(ST7735_MADCTL_MX | ST7735_MADCTL_MY | ST7735_MADCTL_RGB);
}


static void pin_init(void) {
    digitalWrite(PIN_BACKLIGHT, 0);
    digitalWrite(PIN_LCD_CS2_N, 1);
    digitalWrite(PIN_LCD_CS3_N, 1);
    digitalWrite(PIN_LCD_CS4_N, 1);
    digitalWrite(PIN_LCD_CS5_N, 1);
    digitalWrite(PIN_LCD_CS6_N, 1);
    digitalWrite(PIN_LCD_CS7_N, 1);

    pinMode(PIN_BACKLIGHT, OUTPUT);
    pinMode(PIN_LCD_CS2_N, OUTPUT);
    pinMode(PIN_LCD_CS3_N, OUTPUT);
    pinMode(PIN_LCD_CS4_N, OUTPUT);
    pinMode(PIN_LCD_CS5_N, OUTPUT);
    pinMode(PIN_LCD_CS6_N, OUTPUT);
    pinMode(PIN_LCD_CS7_N, OUTPUT);
    pinMode(ST7735_DC_PIN, OUTPUT);
    pinMode(PIN_LCD_RESET_N, OUTPUT);

    // reset all the LCDs
    digitalWrite(PIN_LCD_RESET_N, 0);
    delay(100);
    digitalWrite(PIN_LCD_RESET_N, 1);
}

static void st7735_black(void) {
    digitalWrite(PIN_LCD_CS7_N, 0);
    set_write_region(0, 0, lcd_x_size-1, lcd_y_size-1);
    digitalWrite(ST7735_DC_PIN, 1);
    for (uint8_t iy=0; iy < lcd_y_size; iy++) {
        for (uint8_t ix=0; ix < lcd_x_size; ix++) {
            uint8_t data[2] = { 0x00, 0x00 };            
            SPI.transfer(data, sizeof(data));
        }
    }
    digitalWrite(PIN_LCD_CS7_N, 1);
}

static void st7735_test(void) {
    digitalWrite(PIN_LCD_CS7_N, 0);
    set_write_region(0, 0, lcd_x_size-1, lcd_y_size-1);
    digitalWrite(ST7735_DC_PIN, 1);
    for (uint8_t iy=0; iy < lcd_y_size; iy++) {
        for (uint8_t ix=0; ix < lcd_x_size; ix++) {
            uint8_t data[2] = { (ix == (iy % lcd_x_size)) ? 0xff : 00, (ix == (iy % lcd_x_size)) ? 0xff : 00 };
            SPI.transfer(data, sizeof(data));
        }
    }
    digitalWrite(PIN_LCD_CS7_N, 1);
}

void lcd_init(void) {
    pin_init();

    digitalWrite(PIN_BACKLIGHT, 1);

    SPI.begin();
    SPI.beginTransaction(SPISettings(16000000, MSBFIRST, SPI_MODE0));
    digitalWrite(PIN_LCD_CS7_N, 0);

    st7735_init();
    st7735_black();
    st7735_test();
    

    digitalWrite(PIN_LCD_CS7_N, 1);
    SPI.endTransaction();
}
