#include "TestScenarios.h"

#include "Scenario.h"

#include "Keypad.h"
#include "OutputReader.h"

#include <Arduino.h>
#include "stl.h"

void pulseKey(Keypad &keypad, byte key) {
    keypad.addKey(key);
    delay(100);
    keypad.removeKey(key);
    delay(100);
}

void inputNumber(Keypad &keypad, unsigned short n) {
    byte digits[4];

    // Extract digits from number, going backwards
    for (int i = 3; i >= 0; i--) {
        // Remainder in division by 10 is the last digit
        digits[i] = n % 10;
        n /= 10;
    }

    for (byte i = 0; i < 4; i++) {
        pulseKey(keypad, digits[i]);
    }
}

/**
 * Integration test
 */
namespace scenarios {
    void testOverall() {
        Scenario s("Overall");
        Keypad keypad(2, 3, 4, 5, 6, 7, BYTE_MAX); // No reset
        OutputReader output(13, 14, 15, 16, 17, 18, 19, 8);
        char buffer[48];

        static const unsigned short correct_code = 9386;
        Serial.print("Correct code: ");
        Serial.println(correct_code);

        s.sectionHeader("3 incorrect inputs");
        keypad.clear();
        for (byte i = 0; i < 3; i++) {
            // Wait for the system to be ready
            CHECK_CONDITION_T(s, output.readStandby(), 5000);
            inputNumber(keypad, 1111);
            pulseKey(keypad, Keypad::ENTER_KEY);
        }
        CHECK_CONDITION_T(s, !output.readStandby(), 1000);
        CHECK_CONDITION_T(s, !output.readSuccess(), 1000);
        for (byte i = 0; i < 10; i++) { // Expect at least 10 seconds
            CHECK_CONDITION_T(s, output.readFailure(), 1000);
            ENSURE_CONDITION_T(s, output.readInputDisable(), 1000);
        }
        // Wait for the end of the lockout period
        Serial.println("Waiting for the end of the lockout period...");
        CHECK_CONDITION_T(s, !output.readInputDisable(), 20000);
        // The error signal might take a little more to turn off
        delay(1000);
        s.interimReport();

        keypad.clear();
        for (byte i = 0; i < 3; i++) {
            sprintf(buffer, "%d incorrect inputs, then a correct one", i);
            s.sectionHeader(buffer);
            // Incorrect inputs
            for (byte j = 0; j < i; j++) {
                inputNumber(keypad, 1111);
                pulseKey(keypad, Keypad::ENTER_KEY);
                CHECK_CONDITION(s, !output.readStandby());
                CHECK_CONDITION(s, !output.readSuccess());
                CHECK_CONDITION(s, output.readInputDisable());
                CHECK_CONDITION_T(s, output.readFailure(), 1000);

                Serial.println("Waiting for the incorrect signal to expire...");
                CHECK_CONDITION_T(s, !output.readInputDisable(), 10000);
            }
            // The error signal might take a little more to turn off
            delay(1000);
            // Correct inputs
            inputNumber(keypad, correct_code);
            pulseKey(keypad, Keypad::ENTER_KEY);
            CHECK_CONDITION(s, !output.readStandby());
            CHECK_CONDITION(s, output.readSuccess());
            CHECK_CONDITION(s, output.readInputDisable());
            ENSURE_CONDITION_T(s, !output.readFailure(), 500);

            Serial.println("Waiting for the correct signal to expire...");
            CHECK_CONDITION_T(s, !output.readInputDisable(), 10000);
            s.interimReport();
        }
    }
}
