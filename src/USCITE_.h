#ifndef USCITE__H
#define USCITE__H

#include <Arduino.h>

//\\//\\//\\//\\// RELE' SERVIZIO \\//\\//\\//\\//\\//
// PORT J PIN 5 6 4
#define REL_SERV_1          83//32//33
#define REL_SERV_2          84//33//34
#define REL_ASPIR           82//37

//\\//\\//\\//\\// RELE' LINEA \\//\\//\\//\\//\\//
//PORT C PIN 7 6 5 4
#define REL_MARCIA          30//34//35
#define REL_STOP            31//35//36
#define REL_RESET_LINEA     32
#define REL_EMERG           33//36//37

//\\//\\//\\//\\//\\//  INVERTER  \\//\\//\\//\\//\\//\\//
// PORT J PIN 1 2 3
#define INV_AVANTI          14//30//31
#define INV_INDIETRO        80//31//32
#define INV_ARRESTO         81
#define INV_0_10            44

//\\//\\//\\//\\//\\// USCITA SSR \\//\\//\\//\\//\\//\\//
#define SSR_3               55//22

//\\//\\//\\//\\//\\// VENTOLA \\//\\//\\//\\//\\//\\//
//#define VENTOLA              4

extern String inputString_u;      // = "";        // a String to hold incoming data
extern bool stringComplete_u;     // = false;     // whether the string is complete

void serialEvent_u();

void BEGIN_uscite();

void TEST_rele();
void TEST_inv();
void TEST_ssr();
//void TEST_ventola();


#endif