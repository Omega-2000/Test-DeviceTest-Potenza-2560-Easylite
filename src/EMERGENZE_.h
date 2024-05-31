#ifndef EMERGENZE__H
#define EMERGENZE__H

#include <Arduino.h>
#include "MOTORE_.h"
#include "USCITE_.h"

/*#define EMERGENZA_1  2
  #define EMERGENZA_2  3
  #define EMERGENZA_3  71
  #define EMERGENZA_4  72*/

#define FOTOCELLULA       19
#define FOTOCELLULA_2     18
#define TEST_FOTOCELLULA  42

#define EMERG_PORT_READ PINK //pine

#define FUNGO_1           68
#define FUNGO_2           67
#define MODULO_EM         69
#define RESET_EM          62

extern const byte EMERG_PORT;
extern const byte EMERG_ARMO;
extern const byte EMERG_RESET;
extern uint8_t emerg_port;

extern bool emerg_attiva;
extern bool emerg_armata;
extern bool fotocell_attive;
extern bool fotocell_armate;
extern bool reset_emerg;
extern bool arresto_emergenza;
extern bool old_arresto_emergenza;
extern bool send_emergenze;

extern bool SAFETY_MODULE;

extern String inputString_e;
extern bool stringComplete_e;

void serialEvent_e();
void next_e();    //  attesa del comando !NEXT dalla seriale per passare al test successivo

void emergenze_begin();
void check_emerg();
void check_fotocellule();
void attiva_emergenza();

void TEST_send_button(uint8_t num, bool st);
void TEST_send_result(String test_name, bool test_success, String test_message);

void TEST_funghi();
void TEST_fotocellule();
void TEST_emergenze();


#endif