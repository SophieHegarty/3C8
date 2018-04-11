#ifndef INPUTREADER_H_WASKF8T5
#define INPUTREADER_H_WASKF8T5

#include <Arduino.h>

/**
 * Class to read the outputs of the "Input stage"
 */
class InputReader {
public:
    InputReader(byte a3, byte a2, byte a1, byte a0,
            byte valid_pin,
            byte clear_pin,
            byte enter_pin);

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

#endif /* end of include guard: INPUTREADER_H_WASKF8T5 */
