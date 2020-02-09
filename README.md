## tm1637 library

# Install
git clone https://github.com/SergeyVN94/tm1637-modul-lib.git

# Using

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
    tm1637.printSymbol(0, tm1637.SYMBOLS.symbol_0);
    tm1637.printSymbol(0, tm1637.SYMBOLS.symbol_1);
    tm1637.printSymbol(0, tm1637.SYMBOLS.symbol_2);
    tm1637.printSymbol(0, tm1637.SYMBOLS.symbol_3);
}
```

# Class Methods TM1637  
begin - Loading settings into the module.  
  
setBright - Setting the brightness of the glow, where 0 - the display is off, 8 - maximum brightness.  
  
printSymbol - Displays a character on the display. The first parameter takes a position from 0 to 3. The second parameter takes an unsigned integer. 
You can use ready-made characters from an object of class TM1637 or create your own. 
Ready characters are called like this: tm1637.SYMBOLS.symbol_%symbol_name% (
for example: tm1637.SYMBOLS.symbol_A).  
Available symbols: 0-9, A,b,C,d,E,F.  
  
clearDisplay - Removes all characters from the display.