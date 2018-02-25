#pragma once

#include "stl.h"

class Test;
class Scenario {
public:
    Scenario(const std::string &name);
    virtual ~Scenario() = default;

    void addTest(bool (*f)(), std::string name = "", unsigned long timeout = DEFAULT_TIMEOUT);
#define ADD_CONDITION(f) addTest([&](){ return (f); }, #f)
#define ADD_CONDITION_N(f, n) addTest([&](){ return (f); }, (n))
#define ADD_CONDITION_T(f, t) addTest([&](){ return (f); }, #f, (t))
#define ADD_CONDITION_NT(f, n, t) addTest([&](){ return (f); }, (n), (t))

    bool run() const;

private:
    static const unsigned long DEFAULT_TIMEOUT = 1000;

    std::vector<Test> tests;
    const std::string &name;
};
