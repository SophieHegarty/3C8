#ifndef VALIDATORREADER_H_16W2BKYB
#define VALIDATORREADER_H_16W2BKYB

#include <Arduino.h>

class ValidatorReader {
public:
    ValidatorReader(byte p2, byte p1, byte p0, byte correct_pin);
    virtual ~ValidatorReader() = default;

    byte readPosition() const;
    byte stillCorrect() const;

private:
    byte position_pins[3];
    byte correct_pin;
};

#endif /* end of include guard: VALIDATORREADER_H_16W2BKYB */
