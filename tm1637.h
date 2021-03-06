#ifndef TM1637_H
#define TM1637_H

#if ARDUINO >= 100
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

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