#ifndef VALIDATORWRITER_H_XOJNYPCC
#define VALIDATORWRITER_H_XOJNYPCC

#include <Arduino.h>

/**
 * Class to simulate the outputs of the "Comparator section" towards the "Output section"
 */
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

#endif /* end of include guard: VALIDATORWRITER_H_XOJNYPCC */
