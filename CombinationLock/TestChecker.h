#ifndef TESTCHECKER_H_AGIZLRKF
#define TESTCHECKER_H_AGIZLRKF

#include "Scenario.h"

#include "InputWriter.h"
#include "ValidatorReader.h"

#include <Arduino.h>
#include "stl.h"

bool checkNumber(Scenario &s,
                 InputWriter input,
                 ValidatorReader reader,
                 unsigned short n,
                 unsigned short correct) {
    byte digits[4];
    byte correct_digits[4];
    bool stillCorrect = true;
    bool result = true;

    // Extract digits from numbers, going backwards
    for (int i = 3; i >= 0; i--) {
        // Remainder in division by 10 is the last digit
        digits[i] = n % 10;
        n /= 10;

        correct_digits[i] = correct % 10;
        correct /= 10;
    }

    input.pulseClear();
    result = result && CHECK_CONDITION(s, reader.readPosition() == 0);
    result = result && CHECK_CONDITION(s, reader.stillCorrect());
    for (byte i = 0; i < 4; i++) {
        // Should this digit be asserted correct?
        stillCorrect = stillCorrect && (digits[i] == correct_digits[i]);

        Serial.print("NUMBER IN: ");
        Serial.println(digits[i]);
        input.writeNumber(digits[i]);
        input.pulseValid();

        bool position_ok = CHECK_CONDITION(s, reader.readPosition() == i + 1);
        result = result && position_ok;
        if (!position_ok) {
            Serial.print("Expected position");
            Serial.println(i + 1);
            Serial.print("Actual position");
            Serial.println(reader.readPosition());
        }

        // Explicitly separate the two stillCorrect readings to make use of the
        // automatic test naming
        if (stillCorrect) {
            result = result && CHECK_CONDITION(s, reader.stillCorrect());
        } else {
            result = result && CHECK_CONDITION(s, !reader.stillCorrect());
        }
    }
    return result;
}

/**
 * Scenario relating to the "Checker section" board
 */
namespace scenarios {
    void testCheckerSection() {
        Scenario s("CheckerSection");

        InputWriter input(5, 6, 7, 8, 4,3);
        ValidatorReader reader(18, 17, 16, 19);

        s.sectionHeader("Check correct answer");
        static const unsigned short correct_code = 9386;
        Serial.print("CODE: ");
        Serial.println(correct_code);
        checkNumber(s, input, reader, correct_code, correct_code);
        s.interimReport();

        s.sectionHeader("Check mistake");
        checkNumber(s, input, reader, 9382, correct_code);
        checkNumber(s, input, reader, 9322, correct_code);
        checkNumber(s, input, reader, 9222, correct_code);
        checkNumber(s, input, reader, 2222, correct_code);
        input.pulseClear();
        s.interimReport();

        s.sectionHeader("Check clear");
        input.pulseClear();
        for (byte i = 0; i <= 4; i++) { // Reset after i digits
            for (byte j = 0; j < i; j++) {
                input.writeNumber(1);
                input.pulseValid();
            }
            input.pulseClear();
            CHECK_CONDITION(s, reader.readPosition() == 0);
            CHECK_CONDITION(s, reader.stillCorrect());
        }
        s.interimReport();
    }
}

#endif /* end of include guard: TESTCHECKER_H_AGIZLRKF */
