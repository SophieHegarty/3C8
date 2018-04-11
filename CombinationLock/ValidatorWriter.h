#ifndef VALIDATORWRITER_H_XOJNYPCC
#define VALIDATORWRITER_H_XOJNYPCC

#include <Arduino.h>

/**
 * Class to simulate the outputs of the "Comparator section" towards the "Output section"
 */
class ValidatorWriter {
public:
    ValidatorWriter(byte p2, byte p1, byte p0, byte correct_pin, byte enter_pin);

    void writePosition(byte position) const;
    void setCorrect(bool correct) const;
    void setEnter(bool enter) const;

private:
    static constexpr unsigned int U_PULSE_WIDTH = 1000;

    byte position_pins[3];
    byte correct_pin;
    byte enter_pin;
};

#endif /* end of include guard: VALIDATORWRITER_H_XOJNYPCC */
