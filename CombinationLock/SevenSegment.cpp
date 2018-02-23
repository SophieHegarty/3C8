#include "SevenSegment.h"

SevenSegmentDisplay::SevenSegmentDisplay(byte C, byte B, byte A, byte inhibit, byte read_pin)
        : pins{A, B, C}, inhibit_pin(inhibit), read_pin(read_pin) {

    for (byte i = 0; i < 3; i++) {
        pinMode(pins[i], OUTPUT);
        digitalWrite(pins[i], LOW);
    }
    pinMode(inhibit_pin, OUTPUT);
    digitalWrite(inhibit_pin, HIGH);
    pinMode(read_pin, INPUT);
}

byte SevenSegmentDisplay::readSegments() const {
    byte result = 0;

    // TODO: use display pinout
    for (byte segment = 0; segment < 8; segment++) {
        if (isSegmentOn(segment)) {
            result |= 1 << segment;
        }
    }

    return result;
}

bool SevenSegmentDisplay::isSegmentOn(byte segment) const {
    for (byte digit = 0; digit < 3; digit++) {
        digitalWrite(pins[digit], (segment & (1 << digit)) ? HIGH : LOW);
    }
    digitalWrite(inhibit_pin, LOW);
    delayMicroseconds(10);

    bool result = digitalRead(read_pin);

    digitalWrite(inhibit_pin, HIGH);
    delayMicroseconds(10);

    return result;
}

bool SevenSegmentDisplay::isHyphen() const {
    const static byte hypen_segment = 0; // TODO
    byte reading = readSegments();
    return reading == (1 << hypen_segment);
}

byte SevenSegmentDisplay::readSegmentNumber() const {
    switch (readSegments()) {
        case B00000000: return 0; // TODO
        default: return -1;
    }
}
