/* #include <SPI.h> */

#ifdef SPI_FLASH
#include <SPIMemory.h>
#endif

#include "keypad-six.h"

void lcd_init(void);


#ifdef SPI_FLASH
SPIFlash flash(PIN_FLASH_CS_N);
#endif

void setup() {
    lcd_init();

    Serial.begin(9600);
    while (!Serial);
    Serial.println(__FILE__);

    pinMode(PIN_SW8_DOWN, INPUT_PULLUP);
    pinMode(PIN_SW7_KEY1, INPUT_PULLUP);
    pinMode(PIN_SW6_KEY2, INPUT_PULLUP);
    pinMode(PIN_SW5_KEY3, INPUT_PULLUP);
    pinMode(PIN_SW4_KEY4, INPUT_PULLUP);
    pinMode(PIN_SW3_KEY5, INPUT_PULLUP);
    pinMode(PIN_SW2_KEY6, INPUT_PULLUP);
    pinMode(PIN_SW1_UP,   INPUT_PULLUP);

#ifdef SPI_FLASH
    flash.begin();
    uint32_t JEDEC = flash.getJEDECID();
    static char printBuffer[128];
    sprintf(printBuffer,
            "Flash\r\n"
            "  Manufacturer ID: 0x%02x\r\n"
            "  Memory Type:     0x%02x\r\n"
            "  Capacity:        0x%02x\r\n",
            (uint8_t) (0xff & (JEDEC >> 16)),
            (uint8_t) (0xff & (JEDEC >> 8)),
            (uint8_t) (0xff & (JEDEC >> 0)));
    Serial.print(printBuffer);
#endif
}

void loop() {
    bool delay_required = false;
    if (digitalRead(PIN_SW7_KEY1) == LOW) {
        Serial.println("1");
        delay_required = true;
    }
    if (digitalRead(PIN_SW6_KEY2) == LOW) {
        Serial.println("2");
        delay_required = true;
    }
    if (digitalRead(PIN_SW5_KEY3) == LOW) {
        Serial.println("3");
        delay_required = true;
    }
    if (digitalRead(PIN_SW4_KEY4) == LOW) {
        Serial.println("4");
        delay_required = true;
    }
    if (digitalRead(PIN_SW3_KEY5) == LOW) {
        Serial.println("5");
        delay_required = true;
    }
    if (digitalRead(PIN_SW2_KEY6) == LOW) {
        Serial.println("6");
        delay_required = true;
    }

    if (digitalRead(PIN_SW1_UP) == LOW) {
        Serial.println("U");
        delay_required = true;
    }
    if (digitalRead(PIN_SW8_DOWN) == LOW) {
        Serial.println("D");
        delay_required = true;
    }

    if (delay_required) {
        delay(200);
    }
}
