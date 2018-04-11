#include "TestScenarios.h"

#include "Scenario.h"

#include "ValidatorWriter.h"
#include "OutputReader.h"

#include <Arduino.h>
#include "stl.h"

/**
 * Scenario relaing to the "Output section"
 */
namespace scenarios {
    void testOutputSection() {
        Scenario s("OutputSection");
        ValidatorWriter validator(6, 7, 8, 5, 4);
        OutputReader output(13, 14, 15, 16, 17, 18, 19, 3);
        char buffer[48];

        s.sectionHeader("3 incorrect inputs");
        validator.setCorrect(false);
        validator.writePosition(4);
        for (byte i = 0; i < 2; i++) {
            ENSURE_CONDITION(s, output.readStandby());
            ENSURE_CONDITION(s, !output.readSuccess());
            ENSURE_CONDITION(s, !output.readFailure());
            ENSURE_CONDITION(s, !output.readInputDisable());
            validator.setEnter(true);
            delay(1);
            validator.setEnter(false);
            CHECK_CONDITION(s, !output.readStandby());
            CHECK_CONDITION_T(s, output.readFailure(), 1000);
            ENSURE_CONDITION_T(s, !output.readSuccess(), 500);

            Serial.println("Waiting for incorrect message to expire...");
            CHECK_CONDITION_T(s, !output.readInputDisable(), 10000);
        }

        ENSURE_CONDITION(s, output.readStandby());
        ENSURE_CONDITION(s, !output.readSuccess());
        ENSURE_CONDITION(s, !output.readFailure());
        ENSURE_CONDITION(s, !output.readInputDisable());
        validator.setEnter(true);
        delay(1);
        validator.setEnter(false);
        CHECK_CONDITION(s, !output.readStandby());
        ENSURE_CONDITION_T(s, !output.readSuccess(), 500);
        CHECK_CONDITION_T(s, output.readFailure(), 1000);
        CHECK_CONDITION(s, output.readInputDisable());
        // Ensure that lockout lasts at least ~10 seconds
        for (byte i = 0; i < 10; i++) {
            ENSURE_CONDITION_T(s, output.readInputDisable(), 1000);
            CHECK_CONDITION_T(s, output.readFailure(), 1000);
        }

        Serial.println("Waiting for lockout to expire...");
        CHECK_CONDITION_T(s, !output.readInputDisable(), 30000);
        // The error signal might take a little more to turn off
        delay(1000);
        s.interimReport();

        for (byte i = 0; i < 3; i++) {
            sprintf(buffer, "Correct input after %d incorrect inputs", i);
            s.sectionHeader(buffer);
            for (int j = 0; j < i; j++) {
                validator.setCorrect(false);
                validator.writePosition(4);
                validator.setEnter(true);
                delay(1);
                validator.setEnter(false);

                Serial.println("Waiting for incorrect message to expire...");
                CHECK_CONDITION_T(s, !output.readInputDisable(), 10000);
            }
            // The error signal might take a little more to turn off
            delay(1000);
            validator.setCorrect(true);
            validator.writePosition(4);
            validator.setEnter(true);
            delay(1);
            validator.setEnter(false);
            CHECK_CONDITION(s, !output.readStandby());
            CHECK_CONDITION(s, output.readSuccess());
            ENSURE_CONDITION_T(s, !output.readFailure(), 1000);
            // Check again to ensure that the signal has a sufficient length
            CHECK_CONDITION(s, output.readSuccess());
            Serial.println("Waiting for correct message to expire...");
            CHECK_CONDITION_T(s, !output.readInputDisable(), 10000);
            s.interimReport();
        }
    }
}
