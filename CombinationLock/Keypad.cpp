#include "Keypad.h"

Keypad::Keypad(byte a2, byte a1, byte a0, byte data_pin, byte write_disable_0, byte write_disable_1, byte reset_pin)
        : latches{ Latch8(a2, a1, a0, data_pin, write_disable_0, reset_pin),
                   Latch8(a2, a1, a0, data_pin, write_disable_1, reset_pin) } {}

void Keypad::setKey(byte key) const {
    reset();
    addKey(key);
}

void Keypad::writeKey(byte key, byte value) const {
    byte address = KEYMAP[key];
    const Latch8 *latch;
    if (address < 8) {
        latch = &latches[0];
    } else {
        latch = &latches[1];
        address -= 8;
    }
    latch->writePin(address, value);
}

void Keypad::addKey(byte key) const {
    writeKey(key, HIGH);
}

void Keypad::removeKey(byte key) const {
    writeKey(key, LOW);
}

void Keypad::reset() const {
    latches[0].reset();
    // latches[1].reset(); // redundant, as the two latches use the same reset pin
}
