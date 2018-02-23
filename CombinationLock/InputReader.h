#pragma once

#include <Arduino.h>

class InputReader {
public:
    InputReader(byte a3, byte a2, byte a1, byte a0, byte valid_pin, byte clear_pin, byte enter_pin);
    virtual ~InputReader() = default;

    byte readNumber() const;
    bool isNumberValid() const;
    bool isClearEnabled() const;
    bool isEnterEnabled() const;

private:
    byte address_pins[4];
    byte valid_pin;
    byte clear_pin;
    byte enter_pin;
};
