#include "tm1637.h"

TM1637::TM1637(uint8_t pinCLK, uint8_t pinDIO) {
    this->pinCLK = pinCLK;
    this->pinDIO = pinDIO;

    pinMode(pinCLK, OUTPUT);
    pinMode(pinDIO, OUTPUT);
}

TM1637::~TM1637() {}

void TM1637::setBright(uint8_t bright) {
    if(bright < 0) bright = 0;
    if(bright > 8) bright = 8;

    this->_sendCommand(this->DISPLAY_BRIGHT[bright]);
}

void TM1637::begin() {
    this->_sendCommand(this->DISPLAY_CONFIGD);
    this->clearDisplay();
}

void TM1637::printSymbol(uint8_t position, uint8_t symbol) {
    if (position < 0) position = 0;
    if (position > 3) position = 3;
    
    this->_sendSymbol(position, symbol);
}

void TM1637::clearDisplay() {    
    this->_sendSymbol(0, 0);
    this->_sendSymbol(1, 0);
    this->_sendSymbol(2, 0);
    this->_sendSymbol(3, 0);
    this->_sendSymbol(4, 0);
    this->_sendSymbol(5, 0);
}

void TM1637::_CLK(uint8_t state) { digitalWrite(this->pinCLK, state); }
void TM1637::_DIO(uint8_t state) { digitalWrite(this->pinDIO, state); }

void TM1637::_start() {
    this->_CLK(1);
    this->_DIO(1);
    this->_DIO(0);
}

void TM1637::_stop() {
    this->_CLK(0);
    this->_CLK(1);
    this->_DIO(1);
}

void TM1637::_asc() {
    this->_CLK(0);

    pinMode(this->pinDIO, INPUT);
    this->_CLK(1);

    uint16_t limitAsk = 0;
    while (digitalRead(this->pinDIO)){
        limitAsk++;
        // that there would not be an eternal cycle
        if (limitAsk > 10000) break; 
    }

    pinMode(this->pinDIO, OUTPUT);
}

void TM1637::_sendByte(uint8_t data) {
    for (uint8_t i = 0; i < 8; i++) {
        this->_CLK(0);
        this->_DIO((data >> i) & 0x1);       
        this->_CLK(1);
        delayMicroseconds(5);
    }
}

void TM1637::_sendCommand(uint8_t command) {
    this->_start();
    this->_sendByte(command);
    this->_asc();
    this->_stop();
}

void TM1637::_sendSymbol(uint8_t address, uint8_t symbol) {
    if (address < 0) address = 0;
    if (address > 5) address = 5;
    
    address += 0xC0;

    this->_start();

    this->_sendByte(address);
    this->_asc();

    this->_sendByte(symbol);
    this->_asc();

    this->_stop();
}
