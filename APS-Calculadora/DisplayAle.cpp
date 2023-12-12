#include <stdio.h>
#include "DisplayAle.hpp"

void DisplayAle::refresh() {
  console.set_color(Color::BG_Black);
  console.set_color(Color::FG_Red);
  console.clear_screen();

  if (this->decimalSeparatorCount > 0) {
    this->displayRefreshCount = this->digitsCount + 1;
  } else {
    this->displayRefreshCount = this->digitsCount;
  }

  if (signal == POSITIVE) {
    this->showDigitShape("    ", "    ", "    ", "    ", "    ", 0);
  } else {
    this->showDigitShape("    ", "    ", "XXXX", "    ", "    ", 0);
  }

  int i = 1;
  int j = this->decimal_position;
  for (int s = 1; s <= this->displayRefreshCount; s++) {
    if (s == this->decimal_position) {
      this->showDigitShape("    ", "    ", "    ", "  ", "  () ", s);
       continue;
    }

    switch (this->digits[i - 1]) {
      case ZERO:
        this->showDigitShape("XXXX", "X  X", "X  X" , "X  X" , "XXXX", s);
        i++;
        break;
      case ONE:
        this->showDigitShape("   X", "   X", "   X" , "   X" , "   X", s);
        i++;
        break;
      case TWO:
        this->showDigitShape("XXXX", "   X", "XXXX" , "X   " , "XXXX", s);
        i++;
        break;
      case THREE:
        this->showDigitShape("XXXX", "   X", " XXX" , "   X" , "XXXX", s);
        i++;
        break;
      case FOUR:
        this->showDigitShape("X  X", "X  X", "XXXX" , "   X" , "   X", s);
        i++;
        break;
      case FIVE:
        this->showDigitShape("XXXX", "X   ", "XXXX" , "   X" , "XXXX", s);
        i++;
        break;
      case SIX:
        this->showDigitShape("XXXX", "X   ", "XXXX" , "X  X" , "XXXX", s);
        i++;
        break;
      case SEVEN:
        this->showDigitShape("XXXX", "   X", "   X" , "   X" , "   X", s);
        i++;
        break;
      case EIGHT:
        this->showDigitShape("XXXX", "X  X", "XXXX" , "X  X" , "XXXX", s);
        i++;
        break;
      case NINE:
        this->showDigitShape("XXXX", "X  X", "XXXX" , "   X" , "XXXX", s);
        i++;
        break;
    }
  }
}

void DisplayAle::showDigitShape(const char *line1, const char *line2, const char *line3, const char *line4, const char *line5, unsigned char column) {
  this->console.set_cursor(1, 1 + column * 8);
  printf(line1);

  this->console.set_cursor(2, 1 + column * 8);
  printf(line2);

  this->console.set_cursor(3, 1 + column * 8);
  printf(line3);

  this->console.set_cursor(4, 1 + column * 8);
  printf(line4);

  this->console.set_cursor(5, 1 + column * 8);
  printf(line5);
}

DisplayAle::DisplayAle() {
  this->console.init(0, 0);
  this->decimal_position = -1;
  this->clear();
}

void DisplayAle::addDigit(Digit digit, bool withDot) {
  if (this->digitsCount < MAX_DIGITS) {
    digits[this->digitsCount++] = digit;
    if (withDot == true && this->decimal_position == -1) {
      this->decimal_position = digitsCount;
    }
  this->refresh();
  }
}

void DisplayAle::setSignal(Signal signal) {
  this->signal = signal;
  this->refresh();
}

void DisplayAle::clear() {
  this->intBlock = false;
  this->digitsCount = 0;
  this->decimal_position = -1;
  this->dotCount = 0;
  this->displayRefreshCount = 0;
  this->refresh();
}