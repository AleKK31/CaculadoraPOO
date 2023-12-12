#pragma once

enum Digit { ZERO, ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT ,NINE};

enum Signal{ POSITIVE, NEGATIVE};

enum Operator{ SUM, SUBTRACTION, DIVISION, MULTIPLICATION, PERCENTAGE, SQUARE_ROOT, NO};

enum Control{ ON_CLEAR_ERROR, OFF, MEMORY_READ_CLEAR, MEMORY_SUM, MEMORY_SUBTRACTION, EQUAL, DECIMAL_SEPARATOR};

class Display{
public:
    virtual void addDigit(Digit, bool withDot = false) = 0;
    virtual void setSignal(Signal) = 0;
    virtual void clear() = 0;
};

class Cpu{
public:
    virtual void receiveDigit(Digit) = 0;
    virtual void receiveOperator(Operator) = 0;
    virtual void receiveControl(Control) = 0;
    virtual void setDisplay(Display &) = 0;
};

class Key;
class Keyboard{
public:
    virtual void receiveDigit(Digit) = 0;
    virtual void receiveOperator(Operator) = 0;
    virtual void receiveControl(Control) = 0;
    virtual void addKey(Key &key) = 0;
    virtual Key &findKey(char) = 0;
    virtual void setCpu(Cpu &) = 0;
};

class Key{
public:
    virtual void press() = 0;
    virtual void setKeyboard(Keyboard &) = 0;
    virtual char getSymbol() = 0;
};