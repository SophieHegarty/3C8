#ifndef INPUTWRITER_H_QXLBVQKL
#define INPUTWRITER_H_QXLBVQKL

#include <Arduino.h>

/**
 * Class to simulate the outputs of the "Input stage" to the "Comparator stage"
 */
class InputWriter {
public:
    InputWriter(byte a3, byte a2, byte a1, byte a0,
            byte valid_pin,
            byte clear_pin);

    enum {
        VALID_KEY = 1,
        CLEAR_KEY = 2,
    };

    void writeNumber(byte number) const;

    // Pulse some of VALID_KEY, CLEAR_KEY
    void pulseSignal(byte signal_mask) const;

    void pulseValid() const;
    void pulseClear() const;

private:
    static constexpr unsigned int U_PULSE_WIDTH = 1000;

    byte address_pins[4];
    byte valid_pin;
    byte clear_pin;
};

#endif /* end of include guard: INPUTWRITER_H_QXLBVQKL */
