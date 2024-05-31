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
extern byte ALZO_mode;

/*
// motori

uint16_t MOT_max_current = 8000; // mA
uint8_t MOT_max_temp = 80;  //°
bool MOT_max_temp_flag = 0;
bool MOT_state;
bool MOT_state_old = 0;

uint8_t MOT_vel_avanti;

bool MOT_driver_fault = 0;

uint32_t MOT_on_time = 0;
uint32_t MOT_on_time_tmp = 0;
uint32_t MOT_on_last = 0;

uint16_t log_interval = 2000;
unsigned long last_log = 0;


uint16_t ALZO_max_current = 5000; // mA
uint8_t ALZO_max_temp = 80;  //°
bool ALZO_max_temp_flag = 0;
bool ALZO_state = 0;
bool ALZO_state_old = 0;
bool ALZO_dir = 0;
bool ALZO_last_dir = 0;

bool ALZO_driver_fault = 0;

uint16_t ALZO_log_interval_act = 500;
uint16_t ALZO_log_interval_inact = 30000;
unsigned long ALZO_last_log = 0;


uint32_t ALZO_stop_last = 0;
uint16_t ALZO_stop_delay = 100;
bool ALZO_stop_flag = 0;

uint32_t ALZO_cicli = 0;
uint32_t ALZO_on_time = 0;
uint32_t ALZO_on_last = 0;
bool ALZO_last_dir_time_ok = 0;


uint8_t ALZO_auto_down_high_speed = 255;
uint8_t ALZO_auto_down_low_speed = 100;
uint8_t ALZO_auto_up_low_speed = 128;
uint8_t ALZO_min_press_speed = 128;


bool funzione_speciale = 0;
uint8_t MOT_stato_pre_funzione_speciale = 0;

// contagiri
bool contagiri_fault;
uint32_t contagiri_last_ch;
uint32_t contagiri_ch_timeout = 15000;

uint32_t giri = 0;
uint32_t giri_old = 0;
byte in_port = 0;
bool in_port_old = 0;
float mmxstep = 0.911;
uint32_t millimetri_old = 0;
uint32_t millimetri = 0;
float millimetri_fraction = 0;

uint32_t last_cycle = 0;

uint8_t preset_dist = 0;     // variabile preset attivo
uint32_t setpoint_dist = 0;
uint32_t prev_dist = 0;

//uint8_t preset_press = 0;     // variabile preset attivo
//uint8_t old_preset_press = 0;
uint8_t setpoint_press = 0;
uint8_t preset_press_tolerance = 8;

// pressione
byte pressione = 0;
byte press_max = 245;

// temperatura
byte max_temp = 40;
byte isteresi_temp = 10;
bool tastierino_ok;
*/

extern String inputString_m;
extern bool stringComplete_m;

void setPwmFrequency(int pin, byte mode);

void serialEvent_m();
void next_m();    //  attesa del comand !NEXT dalla seriale per passare al test successivo

void TEST_trazione();
void TEST_alzo();
void TEST_motori();
void TEST_motore_alzo();


#endif