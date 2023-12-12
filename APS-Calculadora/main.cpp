#include <iostream>
#include "Interfaces.hpp"
#include "CpuAle.hpp"
#include "DisplayAle.hpp"
#include "KeyboardAle.hpp"
#include "KeyAle.hpp"

void testCalculadora(Keyboard &keyboard) {
  /*try {
    keyboard.findKey('1').press();
    keyboard.findKey('+').press();
    keyboard.findKey('5').press();
    keyboard.findKey('=').press();
    keyboard.findKey('A').press();
    keyboard.findKey('D').press();
  }*/

  try {
    keyboard.findKey('6').press();
    keyboard.findKey('.').press();
    keyboard.findKey('4').press();
    keyboard.findKey('+').press();
    keyboard.findKey('1').press();
    keyboard.findKey('=').press();
    keyboard.findKey('A').press();
    keyboard.findKey('D').press();
  }

  /*try {
    keyboard.findKey('8').press();
    keyboard.findKey('-').press();
    keyboard.findKey('5').press();
    keyboard.findKey('=').press();
    keyboard.findKey('S').press();
    keyboard.findKey('D').press();
  }*/

  /*try {
    keyboard.findKey('7').press();
    keyboard.findKey('.').press();
    keyboard.findKey('4').press();
    keyboard.findKey('-').press();
    keyboard.findKey('5').press();
    keyboard.findKey('.').press();
    keyboard.findKey('6').press();
    keyboard.findKey('=').press();
    keyboard.findKey('S').press();
    keyboard.findKey('D').press();
  }*/

  /*try {
    keyboard.findKey('8').press();
    keyboard.findKey('7').press();
    keyboard.findKey('6').press();
    keyboard.findKey('5').press();
    keyboard.findKey('4').press();
    keyboard.findKey('3').press();
    keyboard.findKey('2').press();
    keyboard.findKey('+').press();
    keyboard.findKey('1').press();
    keyboard.findKey('=').press();
    keyboard.findKey('A').press();
    keyboard.findKey('D').press();
  }*/

  catch (const char *exception) {
    std::cerr << exception;
  }
}

int main() {
  DisplayAle d1;
  CpuAle c1;
  KeyboardAle kb1;

  KeyAle keyDot('.', DECIMAL_SEPARATOR);
  KeyAle keyZero('0', ZERO);
  KeyAle keyOne('1', ONE);
  KeyAle keyTwo('2', TWO);
  KeyAle keyThree('3', THREE);
  KeyAle keyFour('4', FOUR);
  KeyAle keyFive('5', FIVE);
  KeyAle keySix('6', SIX);
  KeyAle keySeven('7', SEVEN);
  KeyAle keyEight('8', EIGHT);
  KeyAle keyNine('9', NINE);

  KeyAle keySUM('+', SUM);
  KeyAle keySubtraction('-', SUBTRACTION);
  KeyAle keyMultiplication('x', MULTIPLICATION);
  KeyAle keyDivision('/', DIVISION);
  KeyAle keySquare('V', SQUARE_ROOT);
  KeyAle keyEqual('=', EQUAL);

  KeyAle keyMadd('A', MEMORY_SUM);
  KeyAle keyMsub('S', MEMORY_SUBTRACTION);
  KeyAle keyMshow('D', MEMORY_READ_CLEAR);

  c1.setDisplay(d1);
  kb1.setCpu(c1);

  kb1.addKey(keyDot);
  kb1.addKey(keyZero);
  kb1.addKey(keyOne);
  kb1.addKey(keyTwo);
  kb1.addKey(keyThree);
  kb1.addKey(keyFour);
  kb1.addKey(keyFive);
  kb1.addKey(keySix);
  kb1.addKey(keySeven);
  kb1.addKey(keyEight);
  kb1.addKey(keyNine);

  kb1.addKey(keySUM);
  kb1.addKey(keySubtraction);
  kb1.addKey(keyMultiplication);
  kb1.addKey(keyDivision);
  kb1.addKey(keySquare);
  kb1.addKey(keyEqual);

  kb1.addKey(keyMsub);
  kb1.addKey(keyMadd);
  kb1.addKey(keyMshow);

  testCalculadora(kb1);
}