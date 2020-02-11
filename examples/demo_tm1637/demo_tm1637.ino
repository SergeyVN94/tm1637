#include "tm1637.h"

const uint8_t PIN_CLK = 9;
const uint8_t PIN_DIO = 10;

TM1637 tm1637(PIN_CLK, PIN_DIO);

uint8_t chars[16];

void setup() {
    tm1637.begin();
    tm1637.setBright(7);

    for (uint8_t i = 0; i < 10; i++) {
        chars[i] = TM1637::SYMBOLS.numbers[i];
    }

    chars[10] = TM1637::SYMBOLS.symbol_A;
    chars[11] = TM1637::SYMBOLS.symbol_C;
    chars[12] = TM1637::SYMBOLS.symbol_E;
    chars[13] = TM1637::SYMBOLS.symbol_b;
    chars[14] = TM1637::SYMBOLS.symbol_d;
    chars[15] = TM1637::SYMBOLS.symbol_F;
}

void test1(uint8_t DELAY_DEMO) {
    for (uint8_t i = 0; i < 4; i++) {
        tm1637.printSymbol(i, TM1637::SEGMENTS.A);
        delay(DELAY_DEMO);
        tm1637.printSymbol(i, TM1637::SEGMENTS.B);
        delay(DELAY_DEMO);
        tm1637.printSymbol(i, TM1637::SEGMENTS.C);
        delay(DELAY_DEMO);
        tm1637.printSymbol(i, TM1637::SEGMENTS.D);
        delay(DELAY_DEMO);
        tm1637.printSymbol(i, TM1637::SEGMENTS.E);
        delay(DELAY_DEMO);
        tm1637.printSymbol(i, TM1637::SEGMENTS.F);
        delay(DELAY_DEMO);
        tm1637.printSymbol(i, TM1637::SEGMENTS.G);
        delay(DELAY_DEMO);
        tm1637.clearDisplay();
        delay(DELAY_DEMO);
    }
}

void test2(uint8_t DELAY_DEMO) {
    for (int8_t i = 3; i >= 0; i--) {
        tm1637.printSymbol(i, TM1637::SEGMENTS.A);
        delay(DELAY_DEMO);
        tm1637.printSymbol(i, TM1637::SEGMENTS.B);
        delay(DELAY_DEMO);
        tm1637.printSymbol(i, TM1637::SEGMENTS.C);
        delay(DELAY_DEMO);
        tm1637.printSymbol(i, TM1637::SEGMENTS.D);
        delay(DELAY_DEMO);
        tm1637.printSymbol(i, TM1637::SEGMENTS.E);
        delay(DELAY_DEMO);
        tm1637.printSymbol(i, TM1637::SEGMENTS.F);
        delay(DELAY_DEMO);
        tm1637.printSymbol(i, TM1637::SEGMENTS.G);
        delay(DELAY_DEMO);
        tm1637.clearDisplay();
        delay(DELAY_DEMO);
    }
}

void test3(uint8_t DELAY_DEMO) {
    for (uint8_t i = 0; i < 16; i++) {
        for (uint8_t j = 0; j < 4; j++) {
            tm1637.printSymbol(j, chars[i]);
            delay(DELAY_DEMO);
            tm1637.clearDisplay();
        }

        delay(DELAY_DEMO);
    }
}

boolean printNumber(int16_t number) {
    tm1637.clearDisplay();
    if (number < -999) number = -999;
    if (number > 9999) number = 9999;

    if (number < 0) {
        number = number * -1;
        uint8_t pos = 1;
        if (number < 10) tm1637.printSymbol(2, tm1637.SEGMENTS.G);
        if (number < 100 && number > 9)
            tm1637.printSymbol(1, tm1637.SEGMENTS.G);
        if (number > 100) tm1637.printSymbol(0, tm1637.SEGMENTS.G);
    }

    uint8_t digit = number % 10;
    tm1637.printSymbol(3, chars[digit]);

    if (number < 10) return true;
    digit = (number / 10) % 10;
    tm1637.printSymbol(2, chars[digit]);

    if (number < 100) return true;
    digit = (number / 100) % 10;
    tm1637.printSymbol(1, chars[digit]);

    if (number < 1000) return true;
    digit = (number / 1000);
    tm1637.printSymbol(0, chars[digit]);

    return true;
}

void test4(uint8_t DELAY_DEMO) {
    for (int16_t i = -999; i < 10000; i++) {
        printNumber(i);
        delay(DELAY_DEMO);
    }
}

void testCustomSymbol(uint8_t DELAY_DEMO) {
    uint8_t mySymbol = TM1637::SEGMENTS.B | TM1637::SEGMENTS.G | TM1637::SEGMENTS.E;
    tm1637.printSymbol(0, mySymbol);
    delay(DELAY_DEMO);

    mySymbol = TM1637::SEGMENTS.A | TM1637::SEGMENTS.B | TM1637::SEGMENTS.G | TM1637::SEGMENTS.F;
    tm1637.printSymbol(1, mySymbol);
    delay(DELAY_DEMO);

    mySymbol = TM1637::SEGMENTS.C | TM1637::SEGMENTS.D | TM1637::SEGMENTS.E;
    tm1637.printSymbol(2, mySymbol);
    delay(DELAY_DEMO);

    mySymbol = TM1637::SEGMENTS.F | TM1637::SEGMENTS.G | TM1637::SEGMENTS.C;
    tm1637.printSymbol(3, mySymbol);
    delay(DELAY_DEMO);
}

void loop() {
    test1(80);
    delay(80);

    test2(80);
    delay(80);

    test3(80);
    delay(80);

    testCustomSymbol(1000);
    delay(100);

    test4(20);
    delay(100);
}
