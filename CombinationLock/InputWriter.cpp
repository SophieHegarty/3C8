#include "InputWriter.h"

#include "stl.h"

InputWriter::InputWriter(byte a3, byte a2, byte a1, byte a0,
                         byte valid_pin,
                         byte clear_pin,
                         byte enter_pin)
        : address_pins{a0, a1, a2, a3},
          valid_pin(valid_pin),
          clear_pin(clear_pin),
          enter_pin(enter_pin) {
    for (byte pin : {a3, a2, a1, a0, valid_pin, clear_pin, enter_pin}) {
        pinMode(pin, OUTPUT);
        digitalWrite(pin, LOW);
    }
}

void InputWriter::writeNumber(byte number) const{
    for (byte i = 0; i < 4; i++) {
        digitalWrite(address_pins[i], (number & (1 << i)) ? HIGH : LOW);
    }
}

void InputWriter::pulseSignal(byte signal_mask) const{
    digitalWrite(valid_pin, (signal_mask & VALID_KEY) ? HIGH : LOW);
    digitalWrite(clear_pin, (signal_mask & CLEAR_KEY) ? HIGH : LOW);
    digitalWrite(enter_pin, (signal_mask & ENTER_KEY) ? HIGH : LOW);
    delayMicroseconds(U_PULSE_WIDTH);
    for (byte pin : {valid_pin, clear_pin, enter_pin}) {
        digitalWrite(pin, LOW);
    }
}

void InputWriter::pulseValid() const{
    pulseSignal(VALID_KEY);
}

void InputWriter::pulseClear() const{
    pulseSignal(CLEAR_KEY);
}

void InputWriter::pulseEnter() const{
    pulseSignal(ENTER_KEY);
}

