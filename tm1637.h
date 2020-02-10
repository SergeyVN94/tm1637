#ifndef TM1637_H
#define TM1637_H

#include <Arduino.h>

#include "types.h"

class TM1637 {
   public:
    static Segments SEGMENTS;
    static Symbols SYMBOLS;

   public:
    TM1637(uint8_t pinCLK, uint8_t pinDIO);
    ~TM1637();
    void setBright(uint8_t bright);
    void begin();
    void printSymbol(uint8_t position, uint8_t symbol);
    void clearDisplay();

   private:
    uint8_t pinCLK;
    uint8_t pinDIO;

    // normal mode, fixed address, write data to display register
    const uint8_t DISPLAY_CONFIGD = 0x44;

    const struct {
        const uint8_t C0H;
        const uint8_t C1H;
        const uint8_t C2H;
        const uint8_t C3H;
        const uint8_t C4H;
        const uint8_t C5H;
    } ADDRESSES = {
        C0H : 0xC0,
        C1H : 0xC1,
        C2H : 0xC2,
        C3H : 0xC3,
        C4H : 0xC4,
        C5H : 0xC5,
    };

    const uint8_t DISPLAY_BRIGHT[9] = {
        0x80, 0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F,
    };

   private:
    void _CLK(uint8_t state);
    void _DIO(uint8_t state);
    void _start();
    void _stop();
    void _asc();
    void _sendByte(uint8_t data);
    void _sendCommand(uint8_t command);
    void _sendSymbol(uint8_t address, uint8_t symbol);
};

#endif