#include <iostream>
#include <cstdio>
#include <stdlib.h>
#include <math.h>
#include "CpuAle.hpp"

CpuAle::CpuAle() {
  this->digitsOperand1Count = 0;
  this->digitsOperand2Count = 0;

  this->dotControlFirstOp = -1;
  this->dotControlSecondOp = -1;

  this->memo = 0;
  this->memo1 = 0;
  this->memo2 = 0;

  this->decimal_separator = false;
}

void CpuAle::setDisplay(Display &display) {
  this->display = &display;
}

void CpuAle::receiveDigit(Digit digit) {
  this->digitsOperand1Count == 0 && this->operation == NO ? this->display->clear() : void();

  if (this->operation == NO) {
    this->digitsOperand1[this->digitsOperand1Count++] = digit;
  } else {
    this->digitsOperand2[this->digitsOperand2Count++] = digit;
  }

  this->display->addDigit(digit, this->decimal_separator);
}

void CpuAle::receiveOperator(Operator op) { 
  if ((this->operation != NO) && (this->digitsOperand2Count > 0)) {
    this->operate();
  }

  this->display->clear();
  this->operation = op;
}

void CpuAle::receiveControl(Control control) { 
  switch (control) {
    case ON_CLEAR_ERROR:
      this->display->clear();
      this->memo = 0;
      this->memo1 = 0;
      this->memo2 = 0;

      this->operation = NO;
      this->display ? this->display->clear() : void();
      this->display ? this->display->addDigit(ZERO) : void();

      this->decimal_separator = false;

      this->digitsOperand1Count = 0;
      this->digitsOperand2Count = 0;
      this->resultCount = 0;
      break;
    case OFF:
      break;
    case MEMORY_READ_CLEAR:
      this->control_mrc++;
      if (this->control_mrc >= 2) {
        this->memory = 0;
        this->control_mrc = 0;
        this->digitsMemoryCount = 0;
      } else {
        showDigit(this->digitsMemory, &this->digitsMemoryCount, &this->dotControlMemory);
      }
      break;
    case MEMORY_SUBTRACTION:
      if (this->controlOp == 0 && this->digitsOperand2Count == 0) {
        digitsToChar(this->memo1Char, this->digitsOperand1, this->digitsOperand1Count, this->dotOne, this->dotControlFirstOp, this->memo1Signal);
        this->memo1 = charToFloat(this->memo1Char);
        this->memory = this->memory - this->memo1;
        return;
      }

      if (this->digitsOperand1Count > 0) {
        digitsToChar(this->memo2Char, this->digitsOperand2, this->digitsOperand2Count, this->dotSec, this->dotControlSecondOp, this->memo2Signal);
        this->memo2 = charToFloat(this->memo2Char);
        this->memory = this->memory - this->memo2;
        return;
      }
      break;
    case MEMORY_SUM:
      if (this->controlOp == 0 && this->digitsOperand2Count == 0) {
        digitsToChar(this->memo1Char, this->digitsOperand1, this->digitsOperand1Count, this->dotOne, this->dotControlFirstOp, this->memo1Signal);
        this->memo1 = charToFloat(this->memo1Char);
        this->memory = this->memory + this->memo1;
        return;
      }

      if (this->digitsOperand1Count > 0) {
        digitsToChar(this->memo2Char, this->digitsOperand2, this->digitsOperand2Count, this->dotSec, this->dotControlSecondOp, this->memo2Signal);
        this->memo2 = charToFloat(this->memo2Char);
        this->memory = this->memory + this->memo2;
        return;
      }
      break;
    case DECIMAL_SEPARATOR:
        if (this->operation == NO) {
          if (this->dotOne == false) {
            this->dotControlFirstOp = this->digitsOperand1Count - 1;
            this->dotOne = true;
          }
        } else {
          if (this->dotSec == false) {
            this->dotControlSecondOp = this->digitsOperand2Count - 1;
            this->dotSec = true;
          }
        }
        break;
    case EQUAL:
      this->operate();
      break;
    }
}

void CpuAle::memoryCopy(Digit* source, int size) {
  for (int i = 0; i < size; i++) {
    this->digitsMemory[this->digitsMemoryCount++] = source[i];
  }
    debug(this->digitsMemory, this->digitsMemoryCount);
}

float CpuAle::charToFloat(char *str) {
  char *vIn = str;
  float vOut = (float)strtod(vIn, NULL);
  return vOut;
}

void CpuAle::operate() {
  digitsToChar(this->memo1Char, this->digitsOperand1, this->digitsOperand1Count, this->dotOne, this->dotControlFirstOp, this->memo1Signal);
  digitsToChar(this->memo2Char, this->digitsOperand2, this->digitsOperand2Count, this->dotSec, this->dotControlSecondOp, this->memo2Signal);

  this->memo1 = charToFloat(this->memo1Char);
  this->memo2 = charToFloat(this->memo2Char);

  switch (this->operation) {
    case SUM:
      this->memo = this->memo1 + this->memo2;
      std::cout << '+';
      break;
    case SUBTRACTION:
      this->memo = this->memo1 - this->memo2;
      std::cout << '-';
      break;
    case MULTIPLICATION:
      this->memo = this->memo1 * this->memo2;
      std::cout << 'x';
      break;
    case DIVISION:
      this->memo = this->memo1 / this->memo2;
      std::cout << '/';
      break;
    case SQUARE_ROOT:
      this->memo = sqrt(this->memo1);
      break;
    case PERCENTAGE:
      this->memo = this->memo1 / 100;
      break;
    default:
       break;
  }

  floatToChar(this->memo, this->memochar);
  this->memoCount = countChar(this->memochar);
  convertResultToDigit(this->memo, this->memoCount);

  this->controlOp++;

  debug(this->digitsOperand1, this->digitsOperand1Count);

  this->display->clear();
  showDigit(this->digitsOperand1, &this->digitsOperand1Count, &this->dotControlFirstOp);
}

void CpuAle::digitsToChar(char* vet, Digit* digit, int size, bool dot, int pos, bool sig) {
  if (dot == true) {
    size = size + 1;
  }

  int i = 0;
  int j = 0;

  if (sig == false) {
    vet[0] = '-';
    i = 1;
    size = size + 1;
  }

  for (i; i < size; i++) {
    if (dot == true && i == pos + 1) {
      vet[i] = '.';
      continue;
    }

    switch (digit[j++]) {
      case ZERO:
        vet[i] = '0';
        break;
      case ONE:
        vet[i] = '1';
        break;
      case TWO:
        vet[i] = '2';
        break;
      case THREE:
        vet[i] = '3';
        break;
      case FOUR:
        vet[i] = '4';
        break;
      case FIVE:
        vet[i] = '5';
        break;
      case SIX:
        vet[i] = '6';
        break;
      case SEVEN:
        vet[i] = '7';
        break;
      case EIGHT:
        vet[i] = '8';
        break;
      case NINE:
        vet[i] = '9';
        break;
      default:
        vet[i] = ' ';
        break;
    }
  }
}

void CpuAle::floatToChar(float num, char *str) {
  if (this->dotControlFirstOp == -1 && this->dotControlSecondOp == -1) {
    std::sprintf(str, "%.0f", num);
  } else {
    std::sprintf(str, "%.4f", num);
  }
}

void CpuAle::convertResultToDigit(float num, int size) {
  char result[100];

  this->floatToChar(num, result);

  if (num < 0 || result[0] == '-') {
    this->display->setSignal(NEGATIVE);
    this->memo1Signal = false;
  } else {
    this->display->setSignal(POSITIVE);
    this->memo1Signal = true;
  }

  this->digitsOperand1Count = 0;
  this->digitsOperand2Count = 0;

  for (int i = 0; i < size; i++) {
    switch (result[i]) {
      case '0':
        this->digitsOperand1[this->digitsOperand1Count++] = ZERO;
        break;
      case '1':
        this->digitsOperand1[this->digitsOperand1Count++] = ONE;
        break;
      case '2':
        this->digitsOperand1[this->digitsOperand1Count++] = TWO;
        break;
      case '3':
        this->digitsOperand1[this->digitsOperand1Count++] = THREE;
        break;
      case '4':
        this->digitsOperand1[this->digitsOperand1Count++] = FOUR;
        break;
      case '5':
        this->digitsOperand1[this->digitsOperand1Count++] = FIVE;
        break;
      case '6':
        this->digitsOperand1[this->digitsOperand1Count++] = SIX;
        break;
      case '7':
        this->digitsOperand1[this->digitsOperand1Count++] = SEVEN;
        break;
      case '8':
        this->digitsOperand1[this->digitsOperand1Count++] = EIGHT;
        break;
      case '9':
        this->digitsOperand1[this->digitsOperand1Count++] = NINE;
        break;
      case '.':

      if (result[0] == ' ') {
        this->dotControlFirstOp = i - 1;
      } else {
        this->dotControlFirstOp = i;
      }
      break;
    }
  }
}

void CpuAle::showDigit(Digit* memo, int* size, int* dotPos) {
  for (int i = 0; i < *size; i++) {
    if (i == *dotPos) {
      this->display->addDigit(memo[i], true);
    } else {
      this->display->addDigit(memo[i]);
    }
  }
}

void CpuAle::debug(Digit *digit, int size) {

  for (int i = 0; i < size; i++) {
    switch (digit[i]) {
      case ZERO:
        printf("0");
      break;
      case ONE:
        printf("1");
      break;
      case TWO:
        printf("2");
        break;
      case THREE:
        printf("3");
        break;
      case FOUR:
        printf("4");
        break;
      case FIVE:
        printf("5");
        break;
      case SIX:
        printf("6");
        break;
      case SEVEN:
        printf("7");
        break;
      case EIGHT:
        printf("8");
        break;
      case NINE:
        printf("9");
        break;
      default:
        printf(" ");
      break;
    }
  }
}

int CpuAle::countChar(char *str) {
  int count = 0;
  int i = 0;

  while (str[i] != '\0') {
    count++;
    i++;
  }
return count;
}