#ifndef SCENARIO_H_Y3YWEDH5
#define SCENARIO_H_Y3YWEDH5

#include <Arduino.h>

/**
 * Represents a coherent scenario and aids the assertions within the tests
 */
class Scenario {
public:
    Scenario(const char *name);
    virtual ~Scenario();

    /**
     * Make assertion for condetion.
     * For example, given Scenario s:
     *     CHECK_CONDITION(s, a == b);
     *     CHECK_CONDITION(s, c < d);
     *  By default, the name of the assertion is the text of the condition
     *  (i.e. "a == b" or "c < d" in the above examples), and the default timeout is used.
     *
     *  CHECK_CONDITION_N overrides the name, CHECK_CONDITION_T overrides
     *  the timeout, and CHECK_CONDITION_NT overrides both the name and the timeout.
     */
#define CHECK_CONDITION_NT(scenario, condition, name, timeout) ({ \
            bool result = false; \
            const unsigned long beginTime = micros(); \
            const unsigned long endTime = beginTime + timeout; \
            \
            while (!result && micros() < endTime) { \
                result = (condition); \
            } \
            \
            if (result) { \
                Serial.println("Success"); \
                (scenario).successful_checks++; \
            } else { \
                if ((name) != NULL && strcmp((name), "") != 0) { \
                    Serial.print((name)); \
                    Serial.print(" "); \
                    Serial.print("failed after "); \
                } else { \
                    Serial.print("Failed after "); \
                } \
                Serial.print((timeout)); \
                Serial.println(" us"); \
            } \
            (scenario).check_count++; \
            \
            result; \
        })
#define CHECK_CONDITION(scenario, condition) CHECK_CONDITION_NT(scenario, condition, #condition, Scenario::DEFAULT_TIMEOUT)
#define CHECK_CONDITION_N(scenario, condition, n) CHECK_CONDITION_NT(scenario, condition, (n), Scenario::DEFAULT_TIMEOUT)
#define CHECK_CONDITION_T(scenario, condition, t) CHECK_CONDITION_NT(scenario, condition, #condition, (t))

    /**
     * Have all the assertions in the scenario been successful sofar?
     */
    bool isSuccessfull() const;

    size_t check_count = 0;
    size_t successful_checks = 0;

    static const unsigned long DEFAULT_TIMEOUT = 1000;

    const char *name;
};

#endif /* end of include guard: SCENARIO_H_Y3YWEDH5 */
