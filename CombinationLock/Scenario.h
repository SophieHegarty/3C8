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
     * Have all the assertions in the scenario been successful sofar?
     */
    bool isSuccessfull() const;

    void sectionHeader(const char *) const;
    void interimReport() const;

    size_t check_count = 0;
    size_t successful_checks = 0;

    static const unsigned long DEFAULT_TIMEOUT = 5000;

    const char *name;
};

#define __CHECK_SKELETON_NT(scenario, checker, name, timeout) ({   \
            bool _result = false;                                  \
            const unsigned long _beginTime = micros();             \
            const unsigned long _endTime = _beginTime + timeout;   \
                                                                   \
            checker;                                               \
            (scenario).check_count++;                              \
                                                                   \
            Serial.print(F("Test "));                              \
            Serial.print((scenario).check_count);                  \
            Serial.print(F(": "));                                 \
            if (_result) {                                         \
                (scenario).successful_checks++;                    \
                Serial.println(F("success"));                      \
            } else {                                               \
                Serial.print((name));                              \
                Serial.print(F(" "));                              \
                Serial.print(F("failed after "));                  \
                Serial.print((timeout));                           \
                Serial.println(F(" us"));                          \
            }                                                      \
                                                                   \
            _result;                                               \
        })

/**
 * Make assertion for condetion. Retry on failure until success or timeout
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
            __CHECK_SKELETON_NT(scenario, {                       \
                while (!_result && micros() < _endTime) {         \
                    _result = (condition);                        \
                }                                                 \
            }, name, timeout);                                    \
        })
#define CHECK_CONDITION(scenario, condition) CHECK_CONDITION_NT(scenario, condition, F(#condition), Scenario::DEFAULT_TIMEOUT)
#define CHECK_CONDITION_N(scenario, condition, n) CHECK_CONDITION_NT(scenario, condition, (n), Scenario::DEFAULT_TIMEOUT)
#define CHECK_CONDITION_T(scenario, condition, t) CHECK_CONDITION_NT(scenario, condition, F(#condition), (t))

/**
 * Ensure that condition remains true for the entire duration of the timeout
 * Syntax same as for CHECK_CONDITION
 */
#define ENSURE_CONDITION_NT(scenario, condition, name, timeout) ({ \
            __CHECK_SKELETON_NT(scenario, ({                       \
                    _result = true;                                \
                    while (_result && micros() < _endTime) {       \
                        _result = _result && (condition);          \
                    }                                              \
                }), name, timeout);                                \
            })
#define ENSURE_CONDITION(scenario, condition) ENSURE_CONDITION_NT(scenario, condition, F(#condition), Scenario::DEFAULT_TIMEOUT)
#define ENSURE_CONDITION_N(scenario, condition, n) ENSURE_CONDITION_NT(scenario, condition, (n), Scenario::DEFAULT_TIMEOUT)
#define ENSURE_CONDITION_T(scenario, condition, t) ENSURE_CONDITION_NT(scenario, condition, F(#condition), (t))

#endif /* end of include guard: SCENARIO_H_Y3YWEDH5 */
