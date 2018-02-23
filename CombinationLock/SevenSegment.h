#pragma once

#include <Arduino.h>

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
