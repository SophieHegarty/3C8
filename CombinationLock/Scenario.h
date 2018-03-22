#ifndef SCENARIO_H_Y3YWEDH5
#define SCENARIO_H_Y3YWEDH5

#include "stl.h"

class Scenario {
public:
    Scenario(const char *name);
    virtual ~Scenario();

    bool check(bool (*f)(), const char *name = "", unsigned long timeout = DEFAULT_TIMEOUT);
#define CHECK_CONDITION(f) check([&](){ return (f); }, #f)
#define CHECK_CONDITION_N(f, n) check([&](){ return (f); }, (n))
#define CHECK_CONDITION_T(f, t) check([&](){ return (f); }, #f, (t))
#define CHECK_CONDITION_NT(f, n, t) check([&](){ return (f); }, (n), (t))

    bool isSuccessfull() const;

private:

    static const unsigned long DEFAULT_TIMEOUT = 1000;

    const char *name;

    size_t check_count = 0;
    size_t successful_checks = 0;
};

#endif /* end of include guard: SCENARIO_H_Y3YWEDH5 */
