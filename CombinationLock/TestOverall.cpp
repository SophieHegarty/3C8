#include "TestScenarios.h"

#include "Scenario.h"

#include "Keypad.h"
#include "OutputReader.h"

#include <Arduino.h>
#include "stl.h"

void pulseKey(Keypad &keypad, byte key) {
    keypad.addKey(key);
    delay(10);
    keypad.removeKey(key);
    delay(10);
}

void inputNumber(Keypad &keypad, unsigned short n, byte digit_count = 4) {
    byte digits[4];

    // Extract digits from number, going backwards
    for (int i = 3; i >= 0; i--) {
        // Remainder in division by 10 is the last digit
        digits[i] = n % 10;
        n /= 10;
    }

    for (byte i = 0; i < digit_count; i++) {
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
        OutputReader output(1, 1, 1, 1, 1, 1, 1, 1); // TODO use actual pins
        char buffer[48];

        static const unsigned short correct_code = 9386;
        Serial.print("Correct code: ");
        Serial.println(correct_code);

        s.sectionHeader("3 incorrect inputs");
        inputNumber(keypad, 1111);
        pulseKey(keypad, Keypad::ENTER_KEY);
        ENSURE_CONDITION_T(s, !output.readStandby(), 1000);
        ENSURE_CONDITION_T(s, !output.readSuccess(), 1000);
        for (byte i = 0; i < 15; i++) { // Expect at least 15 seconds
            CHECK_CONDITION_T(s, output.readFailure(), 1000);
            ENSURE_CONDITION_T(s, output.readInputDisable(), 1000);
        }
        // Wait for the end of the lockout period
        CHECK_CONDITION_T(s, output.readInputDisable(), 20000);

        for (byte i = 0; i < 3; i++) {
            sprintf(buffer, "%d incorrect inputs, then a correct one", i);
            s.sectionHeader(buffer);
            // Incorrect inputs
            for (byte j = 0; j < i; j++) {
                inputNumber(keypad, 1111);
                pulseKey(keypad, Keypad::ENTER_KEY);
                CHECK_CONDITION(s, !output.readStandby());
                CHECK_CONDITION(s, !output.readSuccess());
                CHECK_CONDITION_T(s, output.readFailure(), 1000);
                CHECK_CONDITION(s, output.readInputDisable());

                // Wait for the end of the indicator period
                CHECK_CONDITION_T(s, !output.readInputDisable(), 10000);
            }
            // Correct inputs
            inputNumber(keypad, correct_code);
            pulseKey(keypad, Keypad::ENTER_KEY);
            CHECK_CONDITION(s, !output.readStandby());
            CHECK_CONDITION_T(s, output.readSuccess(), 1000);
            CHECK_CONDITION(s, !output.readFailure());
            CHECK_CONDITION(s, output.readInputDisable());

            // Wait for the end of the indicator period
            CHECK_CONDITION_T(s, !output.readInputDisable(), 10000);
        }
    }
}
