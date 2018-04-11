#include "TestScenarios.h"

#include "Scenario.h"

#include "Keypad.h"
#include "InputReader.h"

#include <Arduino.h>
#include "stl.h"

/**
 * Scenario relating to the "Input section"
 */
namespace scenarios {
    void testInputSection() {
        Scenario s("InputSection");
        Keypad keypad(2, 3, 4, 5, 6, 7, BYTE_MAX); // No reset
        InputReader reader(16, 15, 14, 13, 19, 18, 17);
        const static byte input_disable = 8;
        pinMode(input_disable, OUTPUT);
        digitalWrite(input_disable, LOW);
        char buffer[100];

        s.sectionHeader("Individual kepresses");
        keypad.clear();
        for (byte i = 0; i < 10; i++) {
            keypad.addKey(i);
            delay(1);
            sprintf(buffer, "Key %d", i);
            if (!CHECK_CONDITION_N(s, reader.readNumber() == i, buffer)) {
                Serial.print("The actual output was ");
                Serial.println(reader.readNumber());
            }
            CHECK_CONDITION(s, reader.isNumberValid());
            keypad.removeKey(i);
        }
        keypad.addKey(Keypad::CLEAR_KEY);
        CHECK_CONDITION(s, reader.isClearEnabled());
        CHECK_CONDITION(s, !reader.isEnterEnabled());
        keypad.removeKey(Keypad::CLEAR_KEY);
        keypad.addKey(Keypad::ENTER_KEY);
        CHECK_CONDITION(s, !reader.isClearEnabled());
        CHECK_CONDITION(s, reader.isEnterEnabled());
        keypad.removeKey(Keypad::ENTER_KEY);
        s.interimReport();

        keypad.clear();
        s.sectionHeader("Double and triple digit presses");
        for (byte i = 0; i < 10; i++) {
            byte j = -1, k = -1;
            do { j = random(12); } while (i == j);
            do { k = random(12); } while (i == k || j == k);

            keypad.addKey(i);
            keypad.addKey(j);
            ENSURE_CONDITION(s, reader.readNumber() == i || !reader.isNumberValid());
            keypad.addKey(k);
            ENSURE_CONDITION(s, reader.readNumber() == i || !reader.isNumberValid());
            keypad.removeKey(k);
            keypad.removeKey(j);
            keypad.removeKey(i);
        }
        s.interimReport();

        keypad.clear();
        s.sectionHeader("Disable input");
        digitalWrite(input_disable, HIGH);
        for (byte i = 0; i < 10; i++) {
            keypad.addKey(i);
            ENSURE_CONDITION(s, !reader.isNumberValid());
            keypad.removeKey(i);
        }
        keypad.addKey(Keypad::ENTER_KEY);
        ENSURE_CONDITION(s, !reader.isEnterEnabled());
        keypad.removeKey(Keypad::ENTER_KEY);
        keypad.addKey(Keypad::CLEAR_KEY);
        ENSURE_CONDITION(s, !reader.isClearEnabled());
        keypad.removeKey(Keypad::CLEAR_KEY);
        digitalWrite(input_disable, LOW);
        s.interimReport();

        keypad.clear();
        s.sectionHeader("Enter, clear and digits should be mutually exclusive");
        keypad.addKey(Keypad::ENTER_KEY);
        for (byte i = 0; i < 10; i++) {
            keypad.addKey(i);
            ENSURE_CONDITION(s, !reader.isNumberValid());
            keypad.addKey(Keypad::CLEAR_KEY);
            ENSURE_CONDITION(s, !reader.isNumberValid());
            ENSURE_CONDITION(s, !reader.isClearEnabled());
            keypad.removeKey(Keypad::CLEAR_KEY);
            keypad.removeKey(i);
        }
        keypad.addKey(Keypad::CLEAR_KEY);
        ENSURE_CONDITION(s, !reader.isClearEnabled());
        keypad.removeKey(Keypad::CLEAR_KEY);
        keypad.removeKey(Keypad::ENTER_KEY);

        keypad.addKey(Keypad::CLEAR_KEY);
        for (byte i = 0; i < 10; i++) {
            keypad.addKey(i);
            ENSURE_CONDITION(s, !reader.isNumberValid());
            keypad.addKey(Keypad::ENTER_KEY);
            ENSURE_CONDITION(s, !reader.isNumberValid());
            ENSURE_CONDITION(s, !reader.isEnterEnabled());
            keypad.removeKey(Keypad::ENTER_KEY);
            keypad.removeKey(i);
        }
        keypad.addKey(Keypad::ENTER_KEY);
        ENSURE_CONDITION(s, !reader.isEnterEnabled());
        keypad.removeKey(Keypad::ENTER_KEY);
        keypad.removeKey(Keypad::CLEAR_KEY);

        for (byte i = 0; i < 10; i++) {
            keypad.addKey(i);
            keypad.addKey(Keypad::ENTER_KEY);
            ENSURE_CONDITION(s, !reader.isEnterEnabled());
            keypad.removeKey(Keypad::ENTER_KEY);
            keypad.addKey(Keypad::CLEAR_KEY);
            ENSURE_CONDITION(s, !reader.isClearEnabled());
            keypad.addKey(Keypad::ENTER_KEY);
            ENSURE_CONDITION(s, !reader.isEnterEnabled());
            ENSURE_CONDITION(s, !reader.isClearEnabled());
            keypad.removeKey(Keypad::ENTER_KEY);
            keypad.removeKey(Keypad::CLEAR_KEY);
            keypad.removeKey(i);
        }
        s.interimReport();
    }
}
