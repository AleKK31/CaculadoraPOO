#include "KeyboardAle.hpp"

void KeyboardAle::receiveDigit(Digit digit) {
  this->cpu->receiveDigit(digit);
}

void KeyboardAle::receiveOperator(Operator op) {
  this->cpu->receiveOperator(op);
}

void KeyboardAle::receiveControl(Control control) {
  this->cpu->receiveControl(control);
}

void KeyboardAle::addKey(Key &key) {
  this->keys[this->keysCount++] = &key;
  key.setKeyboard(*this);
}

Key &KeyboardAle::findKey(char symbol) {
  for (int i = 0; i < this->keysCount; i++) {
    if (this->keys[i]->getSymbol() == symbol) {
      return *this->keys[i];
    }
  }
    throw "NOT_FOUND";
}

void KeyboardAle::setCpu(Cpu &cpu) {
  this->cpu = &cpu;
}