#pragma once

#include <Arduino.h>

class ValidatorWriter {
public:
    ValidatorWriter(byte p2, byte p1, byte p0, byte correct_pin);
    virtual ~ValidatorWriter() = default;

    void writePosition(byte position) const;
    void setCorrect(bool correct) const;

private:
    byte position_pins[3];
    byte correct_pin;
};
