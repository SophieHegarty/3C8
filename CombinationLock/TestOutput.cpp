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
        ValidatorWriter validator(1, 1, 1, 1, 1); // TODO actual pins
        OutputReader output(1, 1, 1, 1, 1, 1, 1, 1); // TODO actual pins
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
            CHECK_CONDITION(s, !output.readStandby());
            CHECK_CONDITION_T(s, output.readFailure(), 1000);
            ENSURE_CONDITION_T(s, !output.readSuccess(), 500);
            validator.setEnter(false);

            Serial.println("Waiting 3 secods for incorrect message to expire");
            delay(3000);
        }

        ENSURE_CONDITION(s, output.readStandby());
        ENSURE_CONDITION(s, !output.readSuccess());
        ENSURE_CONDITION(s, !output.readFailure());
        ENSURE_CONDITION(s, !output.readInputDisable());
        validator.setEnter(true);
        CHECK_CONDITION(s, !output.readStandby());
        ENSURE_CONDITION_T(s, !output.readSuccess(), 500);
        CHECK_CONDITION_T(s, output.readFailure(), 1000);
        CHECK_CONDITION(s, output.readInputDisable());
        delay(1000);
        // Check again
        CHECK_CONDITION_T(s, output.readFailure(), 1000);
        CHECK_CONDITION(s, output.readInputDisable());
        validator.setEnter(false);

        s.interimReport();
        Serial.println("Waiting 30 seconds for correct message to expire");
        delay(30000);

        for (byte i = 0; i < 2; i++) {
            sprintf(buffer, "Correct input after %d incorrect inputs", i);
            s.sectionHeader(buffer);
            for (int j = 0; j < i; j++) {
                validator.setCorrect(false);
                validator.writePosition(4);
                validator.setEnter(true);
                delay(500);
                validator.setEnter(false);

                Serial.println("Waiting 3 secods for incorrect message to expire");
                delay(3000);
            }
            validator.setCorrect(true);
            validator.setEnter(true);
            CHECK_CONDITION(s, !output.readStandby());
            CHECK_CONDITION_T(s, output.readSuccess(), 1000);
            ENSURE_CONDITION_T(s, !output.readFailure(), 500);
            CHECK_CONDITION_T(s, output.readSuccess(), 1000); // Check again
            validator.setEnter(false);
            Serial.println("Waiting 30 seconds for correct message to expire");
            delay(30000);
            s.interimReport();
        }
    }
}
