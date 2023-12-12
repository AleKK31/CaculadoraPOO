#include "KeyAle.hpp"

KeyAle::KeyAle(char symbol, Digit digit) {
  this->isDigit = true;
  this->symbol = symbol;
  this->digit = digit;
}

KeyAle::KeyAle(char symbol, Operator operation) {
  this->isOperation = true;
  this->symbol = symbol;
  this->operation = operation;
}

KeyAle::KeyAle(char symbol, Control control) {
  this->isControl = true;
  this->symbol = symbol;
  this->control = control;
}

void KeyAle::press() {
  if (this->isDigit)
    this->keyboard->receiveDigit(this->digit);
  if (this->isOperation)
    this->keyboard->receiveOperator(this->operation);
  if (this->isControl)
    this->keyboard->receiveControl(this->control);
}

void KeyAle::setKeyboard(Keyboard &keyboard) {
  this->keyboard = &keyboard;
}

char KeyAle::getSymbol() {
  return this->symbol;
}