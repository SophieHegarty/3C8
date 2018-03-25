#ifndef SEVENSEGMENT_H_CW0DRSSO
#define SEVENSEGMENT_H_CW0DRSSO

#include <Arduino.h>

/**
 * Class to read the values displayed on a 7-segment display
 */
class SevenSegmentDisplay {
public:
    SevenSegmentDisplay(byte C, byte B, byte A, byte inhibit, byte read_pin);
    virtual ~SevenSegmentDisplay () = default;

    byte readSegments() const;
    bool isSegmentOn(byte segment) const;

    bool isHyphen() const;
    byte readSegmentNumber() const;

private:
    byte pins[3];
    byte inhibit_pin;
    byte read_pin;
};

#endif /* end of include guard: SEVENSEGMENT_H_CW0DRSSO */
