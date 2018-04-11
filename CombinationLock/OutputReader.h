#ifndef OUTPUTREADER_H_GJXYMSEL
#define OUTPUTREADER_H_GJXYMSEL

#include <Arduino.h>

/**
 * Class to read the outputs of the system
 */
class OutputReader {
public:
    OutputReader(byte hyphen0, byte hyphen1, byte hyphen, byte hyphen3,
                 byte standby_pin, byte success_pin, byte failure_pin,
                 byte input_disable_pin);

    /**
     * The four least significant bits in the return value correspond to the
     * status of the four hyphens.
     * hyphen0 corresponds to the least significant bit in the return value
     */
    byte readHyphenMask() const;
    /**
     * If the hyphens display a valid position, return that number, otherwise -1
     */
    byte readHyphenPosition() const;

    bool readSuccess() const;
    bool readStandby() const;
    bool readFailure() const;
    bool readInputDisable() const;

private:
    byte hyphen_pins[4];
    byte standby_pin;
    byte success_pin;
    byte failure_pin;
    byte input_disable_pin;
};

#endif /* end of include guard: OUTPUTREADER_H_GJXYMSEL */
