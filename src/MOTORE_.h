#ifndef MOTORE__H
#define MOTORE__H

#include <Arduino.h>
#include "MotorDriver.h"

#include "EMERGENZE_.h"
#include "INGRESSI_.h"

//  TRAZIONE
#define MOT_INA          26
#define MOT_ENA          27
#define MOT_INB          29
#define MOT_ENB          28
#define MOT_PWM          45
#define MOT_CSENSE       59//A5    // analog 5
#define MOT_NTC          58//A4    // analog 4
//#define CONTA_GIRI        2
#define FINE_MAT          7
//#define VENTOLA           4

extern MotorDriver MOT;

//  ALZO
#define ALZO_INA         22
#define ALZO_ENA         23
#define ALZO_INB         25
#define ALZO_ENB         24
#define ALZO_PWM         46
#define ALZO_CSENSE      57//A3    // analog 3
#define ALZO_NTC         56//A2    // analog 2
#define ALZO_FINE_CORSA  70
//#define FINE_CORSA_2
//#define TRIM_ALT_RULLI 54

extern MotorDriver ALZO;

// alzo
#define ALZO_MODE_MAN   0
#define ALZO_MODE_MAX   1
#define ALZO_MODE_MIN   2
#define ALZO_MODE_AUTO  3
//extern byte ALZO_mode;

void setPwmFrequency(int pin, byte mode);

void TEST_trazione();
void TEST_alzo();

//  DA AGGIUNGERE IL TEST PER L INGRESSO "RESET_EM" E "MODULO_EM"

#endif