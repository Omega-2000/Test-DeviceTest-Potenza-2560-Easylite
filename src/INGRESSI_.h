#ifndef INGRESSI__H
#define INGRESSI__H

#include <Arduino.h>

/*
//\\//\\//\\//\\// INGRESSI SERVIZIO \\//\\//\\//\\//\\//
// PORT H PIN 2 3 4 5
#define PEDALE            73
#define IN_SERVIZIO       6
#define FINE_MATERIALE    7
#define PRESSOSTATO       8

extern bool man_pedale;


//\\//\\//\\//\\// INGRESSI LINEA \\//\\//\\//\\//\\//
// PORT D PIN 4 5 6 7
#define IN_MARCIA         77
#define IN_STOP           78
#define IN_EMERG          79
#define IN_RESET_LINEA    38
*/

#define PEDALE              73
#define CONTA_GIRI           2
#define ALZO_FINE_CORSA     70//16//11
#define TRIM_ALT_RULLI      54

#define MOT_NTC          58
#define ALZO_NTC         56

extern uint32_t giri;

void contagiri();   //  interrupt
float get_temperature(uint8_t ntc);     //  per test ntc

void BEGIN_ingressi();
void TEST_ingressi();


#endif