#ifndef SCENARIO_H_Y3YWEDH5
#define SCENARIO_H_Y3YWEDH5

#include "stl.h"

/**
 * Represents a coherent scenario and aids the assertions within the tests
 */
class Scenario {
public:
    Scenario(const char *name);
    virtual ~Scenario();

    /**
     * Assert f, repeatedly until it returns true or the timeout expires.
     * The success or failure of the assertion shows up as name in the logs
     * sent back through the serial connection.
     */
    bool check(bool (*f)(), const char *name = "", unsigned long timeout = DEFAULT_TIMEOUT);

    /**
     * Make assertion for condetion.
     * For example:
     *     CHECK_CONDITION(a == b);
     *     CHECK_CONDITION(c < d);
     *  By default, the name of the assertion is the text of the condition,
     *  and the default timeout is used.
     *
     *  CHECK_CONDITION_N overrides the name, CHECK_CONDITION_T overrides
     *  the timeout, and CHECK_CONDITION_NT overrides both the name and the timeout.
     */
#define CHECK_CONDITION(f) check([&](){ return (f); }, #f)
#define CHECK_CONDITION_N(f, n) check([&](){ return (f); }, (n))
#define CHECK_CONDITION_T(f, t) check([&](){ return (f); }, #f, (t))
#define CHECK_CONDITION_NT(f, n, t) check([&](){ return (f); }, (n), (t))

    /**
     * Have all the assertions in the scenario been successful sofar?
     */
    bool isSuccessfull() const;

private:
    static const unsigned long DEFAULT_TIMEOUT = 1000;

    const char *name;

    size_t check_count = 0;
    size_t successful_checks = 0;
};

#endif /* end of include guard: SCENARIO_H_Y3YWEDH5 */
