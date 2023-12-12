#pragma once

#include "Interfaces.hpp"

class KeyAle : public Key{
private:
    Keyboard *keyboard;
    char symbol;
    Digit digit;
    Operator operation;
    Control control;
    bool isDigit = false;
    bool isOperation = false;
    bool isControl = false;

public:
    KeyAle(char, Digit);
    KeyAle(char, Operator);
    KeyAle(char, Control);
    void press();
    void setKeyboard(Keyboard &);
    char getSymbol();
};