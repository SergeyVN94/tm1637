# TM1637 library

Library for tm1637 driver  

# Example

main.ino  
```
#include "tm1637.h"

const uint8_t PIN_CLK = 9; // Any cipher pin
const uint8_t PIN_DIO = 10; // Any cipher pin

TM1637 tm1637(PIN_CLK, PIN_DIO);

void setup() {
    tm1637.begin();
    tm1637.setBright(7);
}

void loop() {
    tm1637.printSymbol(0, TM1637::SYMBOLS.symbol_A);
    tm1637.printSymbol(1, TM1637::SYMBOLS.symbol_F);
    tm1637.printSymbol(2, TM1637::SYMBOLS.numbers[7]);
    tm1637.printSymbol(3, TM1637::SYMBOLS.numbers[3]);
    delay(100);
}
```

# Using  

* `begin` - Loading settings into the module.  
  
* `setBright` - Setting the brightness of the glow, where 0 - the display is off, 8 - maximum brightness.  
  
* `printSymbol` - Displays a character on the display. The first parameter takes a position from 0 to 3. The second parameter takes an unsigned integer. 
You can use ready-made characters from an object of class TM1637 or create your own. 
Ready characters are called like this: TM1637::SYMBOLS.symbol_%symbol_name% (
for example: TM1637::SYMBOLS.symbol_A) or TM1637::SYMBOLS.numbers[number] (for example: TM1637::SYMBOLS.numbers[5]).  
Available symbols: 0-9, A,b,C,d,E,F.
  
* `clearDisplay` - Removes all characters from the display.  

### Custom symbol
```
uint8_t mySymbol = TM1637::SEGMENTS.B | TM1637::SEGMENTS.G | TM1637::SEGMENTS.E;
tm1637.printSymbol(0, mySymbol);
```