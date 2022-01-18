#include <SPIMemory.h>

#include "keypad-six.h"

static SPIFlash flash(PIN_FLASH_CS);

static char printBuffer[128];

void setup() {
    Serial.begin(9600);
    while (!Serial);

    pinMode(PIN_SW8_DOWN, INPUT_PULLUP);
    pinMode(PIN_SW7_KEY1, INPUT_PULLUP);
    pinMode(PIN_SW6_KEY2, INPUT_PULLUP);
    pinMode(PIN_SW5_KEY3, INPUT_PULLUP);
    pinMode(PIN_SW4_KEY4, INPUT_PULLUP);
    pinMode(PIN_SW3_KEY5, INPUT_PULLUP);
    pinMode(PIN_SW2_KEY6, INPUT_PULLUP);
    pinMode(PIN_SW1_UP,   INPUT_PULLUP);

    Serial.println(__FILE__);

    flash.begin();

    while(1) {
        bool delay_required = false;
        if (digitalRead(PIN_SW2_KEY6) == LOW) {
            delay_required = true;
            Serial.println("Flash");
            uint8_t b1, b2, b3;
            uint32_t JEDEC = flash.getJEDECID();
            b1 = (JEDEC >> 16);
            b2 = (JEDEC >> 8);
            b3 = (JEDEC >> 0);
            memset(printBuffer, '\0', sizeof(printBuffer));
            snprintf(printBuffer, sizeof(printBuffer), " Manufacturer ID: %02xh\r\n Memory Type: %02xh\r\n Capacity: %02xh", b1, b2, b3);
            Serial.println(printBuffer);
            memset(printBuffer, '\0', sizeof(printBuffer));
            snprintf(printBuffer, sizeof(printBuffer), " JEDEC ID: %04lxh", JEDEC);
            Serial.println(printBuffer);
            uint32_t ManID = flash.getManID();
            memset(printBuffer, '\0', sizeof(printBuffer));
            snprintf(printBuffer, sizeof(printBuffer), " MAN ID: %04lxh", ManID);
            Serial.println(printBuffer);
        }
        
        if (delay_required) {
            delay(500);
        }
    }
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
