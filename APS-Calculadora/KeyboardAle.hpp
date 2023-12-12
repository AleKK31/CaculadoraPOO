#pragma once

#include <iostream>
#include "Interfaces.hpp"

#define MAX_KEYS 101

class KeyboardAle : public Keyboard {
  private:
    Cpu *cpu;
    Key *keys[MAX_KEYS];
    unsigned char keysCount = 0;

  public:
    void setCpu(Cpu &);
    
    void addKey(Key &);
    Key &findKey(char);
    void receiveDigit(Digit);
    void receiveOperator(Operator);
    void receiveControl(Control);
};