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

void TEST_send_result(String test_name, bool test_success, String test_message);

void TEST_funghi();
void TEST_fotocellule();


#endif