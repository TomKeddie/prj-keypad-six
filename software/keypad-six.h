// @TomKeddie
// keypad pin definitions

#pragma once

#define MEGA_PIN_PB0 17
#define MEGA_PIN_PB1 -1
#define MEGA_PIN_PB3 -1
#define MEGA_PIN_PB4 8
#define MEGA_PIN_PB5 9
#define MEGA_PIN_PB6 10
#define MEGA_PIN_PB7 11

#define MEGA_PIN_PC6 5
#define MEGA_PIN_PC7 13

#define MEGA_PIN_PD0 3
#define MEGA_PIN_PD1 2
#define MEGA_PIN_PD2 0
#define MEGA_PIN_PD3 1
#define MEGA_PIN_PD4 4
#define MEGA_PIN_PD5 30
#define MEGA_PIN_PD6 12
#define MEGA_PIN_PD7 6

#define MEGA_PIN_PE6 7

#define MEGA_PIN_PF0 23
#define MEGA_PIN_PF1 22



// =====================================
// Buttons & Keys

#define PIN_SW2_KEY6 MEGA_PIN_PD1
#define PIN_SW3_KEY5 MEGA_PIN_PD2
#define PIN_SW4_KEY4 MEGA_PIN_PD3
#define PIN_SW5_KEY3 MEGA_PIN_PD5
// schematic error 5 & 6 are swapped
#define PIN_SW6_KEY2 MEGA_PIN_PD4
#define PIN_SW7_KEY1 MEGA_PIN_PD6

#define PIN_SW1_UP MEGA_PIN_PD0
#define PIN_SW8_DOWN MEGA_PIN_PD7

#define PIN_UP   MEGA_PIN_PD0
#define PIN_DOWN MEGA_PIN_PD7


// =====================================
// Displays

#define PIN_BACKLIGHT  MEGA_PIN_PC6
#define PIN_LCD_DC     MEGA_PIN_PB7
#define PIN_LCD_SCK    MEGA_PIN_PB1
#define PIN_LCD_MISO   MEGA_PIN_PB3
#define PIN_LCD_RESET_N  MEGA_PIN_PB4

#define PIN_LCD_CS2_N  MEGA_PIN_PB0
#define PIN_LCD_CS3_N  MEGA_PIN_PF0
#define PIN_LCD_CS4_N  MEGA_PIN_PF1
#define PIN_LCD_CS5_N  MEGA_PIN_PC7
#define PIN_LCD_CS6_N  MEGA_PIN_PB6
#define PIN_LCD_CS7_N  MEGA_PIN_PB5

#define ST7735_DC_PIN   PIN_LCD_DC
#define ST7735_SCK_PIN  PIN_LCD_SCK
#define ST7735_MISO_PIN PIN_LCD_MISO

// =====================================
// Misc

#define PIN_FLASH_CS_N MEGA_PIN_PE6
