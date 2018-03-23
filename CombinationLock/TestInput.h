#ifndef TESTINPUT_H_8NPHHZL1
#define TESTINPUT_H_8NPHHZL1

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
        InputReader reader(19, 18, 17, 16, 15, 14, 13);

        for (byte i = 0; i < 12; i++) {
            keypad.addKey(i);
            CHECK_CONDITION(s, reader.readNumber() == i);
            keypad.removeKey(i);
        }
    }
}

#endif /* end of include guard: TESTINPUT_H_8NPHHZL1 */
