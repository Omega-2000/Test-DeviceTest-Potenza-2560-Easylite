#ifndef SERIAL__H
#define SERIAL__H

#include <Arduino.h>

#include "CANBUS_.h"
#include "I2C_.h"
#include "EMERGENZE_.h"
#include "INGRESSI_.h"

extern String inputString;      // = "";        // a String to hold incoming data
extern bool stringComplete;     // = false;     // whether the string is complete

void serialEvent();
void confronta_stringhe();
bool isValidMessage(String message);
bool isPrintable(char c);

#endif