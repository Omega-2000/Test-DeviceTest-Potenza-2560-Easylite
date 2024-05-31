#include "MOTORE_.h"

MotorDriver MOT = MotorDriver(0, MOT_PWM, MOT_INA, MOT_INB, MOT_CSENSE, MOT_ENA, MOT_ENB, MOT_NTC, 0);
MotorDriver ALZO = MotorDriver(0, ALZO_PWM, ALZO_INA, ALZO_INB, ALZO_CSENSE, ALZO_ENA, ALZO_ENB, ALZO_NTC, ALZO_FINE_CORSA);
byte ALZO_mode = ALZO_MODE_MAN;

void setPwmFrequency(int pin, byte mode) {
  // Registri timer 5 https://www.robotshop.com/community/forum/t/arduino-101-timers-and-interrupts/13072
  //https://www.avrfreaks.net/forum/can-someone-explain-me-significance-com1a1com1a0
  // TCCRA
  TCCR5A =  0b10101010; //  11 8kHz/pre-10bit 10 15kHz/pre-9bit 01 31kHz/pre-8bit
  //          ^ ^ ^    cmp out mode normale non-invertente
  TCCR5B =  0b00000001;
  //               ^^^ prescaler 1/8/64/256
}

String inputString_m = "";
bool stringComplete_m = false;

void serialEvent_m() {
  while (Serial.available())
  {
    char inChar = (char)Serial.read(); // get the new byte:
    inputString_m += inChar;             // add it to the inputString:
    if (inChar == '\n')
    { // if the incoming character is a newline, set a flag so the main loop cando something about it:
      stringComplete_m = true;
    }
  }
}

void next_m() {
  bool next = 0;
  while(!next) {
      serialEvent_m();
      if (stringComplete_m)
      {
          //  confronta_stringhe
          stringComplete_m = false;
          String confronto = String(inputString_m);
          Serial.println(confronto);
          Serial.println("");
          if (confronto.indexOf("!NEXT") != -1) next = 1;
          //

          //Serial.println("");
          //Serial.println("In attesa...");
          //return;
      }

      delay(10);
  }
}

/*void TEST_trazione() {
  //bool next = 0;
  Serial.println("{\"name\":\"description\",\"value\":\"Cliccare su 'SI' se si vede il motore trazione girare, oppure cliccare su 'NO'\"");
  MOT.start(100, 0);

  next_m(); //  aspetta !NEXT

  MOT.stop();
  Serial.println("{\"name\":\"description\",\"value\":\"Cliccare su 'SI' se si vede il motore trazione girare dalla parte opposta rispetto a prima, oppure cliccare su 'NO'\"");
  MOT.start(100, 1);

  next_m(); //  aspetta !NEXT

  MOT.stop();
}*/

/*void TEST_alzo() {
  //bool next = 0;
  Serial.println("{\"name\":\"description\",\"value\":\"Cliccare su 'SI' se si vede il motore alzo, alzare il ''rullo'', oppure cliccare su 'NO'\"");
  ALZO.start(100, 0);

  next_m(); //  aspetta !NEXT

  ALZO.stop();
  Serial.println("{\"name\":\"description\",\"value\":\"Cliccare su 'SI' se si vede il motore alzo, abbassare il ''rullo'', oppure cliccare su 'NO'\"");
  ALZO.start(100, 1);

  next_m(); //  aspetta !NEXT

  ALZO.stop();
}*/

void TEST_trazione() {
  Serial.println("");
  Serial.println("TEST TRAZIONE");

  Serial.println("Cliccare il pulsante di RESET sulla tastiera per resettare l'emergenze e abilitare i motori. Attendere 5 secondi\"}");
  delay(5000);
  Serial.println("Cliccare su 'SI' se si vede il motore girare in entrambi le direzioni, oppure cliccare su 'NO' se il motore non gira o si blocca");

  MOT.start(100, 0);
  uint32_t tstms = millis();
  while (millis() - tstms < 5000) {
    ALZO.loop();
    MOT.loop();
    //INV.loop();
    delay(10);
    //if (ALZO.getEndstopHit()) break;
  }
  MOT.stop(0);
  MOT.loop();
  delay(500);
  MOT.start(100, 1);
  tstms = millis();
  while (millis() - tstms < 5000) {
    ALZO.loop();
    MOT.loop();
    //INV.loop();
    delay(10);
    //if()break;
  }
  MOT.stop(1);
  MOT.loop();
  //TEST_send_result("DRIVERRISE", true, "");

  Serial.println("");
  Serial.println("FINE TEST TRAZIONE");
  Serial.println("");
}


//void TEST_motori() {
/*void TEST_trazione() {            //  DA AGGIUNGERE IL TEST PER L INGRESSO "RESET_EM" E "MODULO_EM"
  Serial.println("");
  Serial.println("TEST TRAZIONE");

  //bool stato_prima = digitalRead(RESET_EM);

  Serial.println("Cliccare il pulsante di RESET sulla tastiera per resettare l'emergenze e abilitare i motori. Attendere 10 secondi\"}");

  //next_m();
  delay(10000);

  //bool stato_dopo = digitalRead(RESET_EM);
  //if (stato_prima == stato_dopo) Serial.println("{\"name\":\"!TRAZIONE\",\"result\":\"error\",\"error\":\"L'ingresso 'RESET_EM' non funziona\"}"); else Serial.println("Il RESET funziona\n");

  Serial.println("Cliccare su 'SI' se si vede il motore girare in entrambi le direzioni, oppure cliccare su 'NO' se il motore non gira o si blocca");

  uint8_t v = 255 / 3;
  uint32_t tstms = millis();
  uint32_t tst_old_giri;
  uint32_t tst_giri_time[3];
  uint32_t tst_giri_last_ms;
  uint32_t tst_giri_last_ms_old;
  uint8_t error;
  Serial.println(F("motore avanti"));


  for (uint8_t i = 0; i < 3; i++) {
    MOT.start(v * (i + 1), 0);
    //ALZO.start(v * (i + 1), 0);
    tstms = millis();
    while (millis() - tstms < 5000) {
      //ALZO.loop();
      MOT.loop();
      //INV.loop();
      if (giri != tst_old_giri) {
        tst_giri_last_ms_old = tst_giri_last_ms;
        tst_giri_last_ms = millis();
      }
      delay(10);
      tst_old_giri = giri;
    }
    tst_giri_time[i] = tst_giri_last_ms - tst_giri_last_ms_old;
    tst_giri_time[i] *= (i + 1);
  }

  float tst_diff_1 = abs((int32_t)tst_giri_time[0] - (int32_t)tst_giri_time[1]);
  float tst_diff_2 = abs((int32_t)tst_giri_time[1] - (int32_t)tst_giri_time[2]);

  tst_diff_1 /= tst_giri_time[1];
  tst_diff_2 /= tst_giri_time[1];

  Serial.printf("diff %d% %d%\n", tst_diff_1 * 100, tst_diff_2 * 100);

  if (tst_diff_1 > 0.5) {
    error |= 1;
  }
  if (tst_diff_2 > 0.5) {
    error |= 2;
  }

  //ALZO.stop(1);
  MOT.stop(0);
  //INV.stop(1);
  //ALZO.loop();
  MOT.loop();
  //INV.loop();

  delay(500);

  MOT.start(100, 1);
  //ALZO.start(255, 1);
  tstms = millis();
  while (millis() - tstms < 5000) {
    //ALZO.loop();
    MOT.loop();
    //INV.loop();
    if (giri != tst_old_giri) {
      tst_giri_last_ms_old = tst_giri_last_ms;
      tst_giri_last_ms = millis();
    }
    delay(10);
    tst_old_giri = giri;
  }

  //ALZO.stop(1);
  MOT.stop(0);
  //INV.stop(1);
  //ALZO.loop();
  MOT.loop();
  //INV.loop();*/

  /*tst_giri_time[1] = tst_giri_last_ms - tst_giri_last_ms_old;
  tst_diff_2 = abs((int32_t)tst_giri_time[1] - (int32_t)tst_giri_time[2]);
  if (tst_diff_2 > 0.5) {
    error |= 4;
  }
  switch (error) {
    case 0: // tutto ok
      TEST_send_result("MOTOR", true, "");
      break;
    case 1: // errore avanti lento
    case 2: // errore avanti veloce
    case 3: // errore avanti totale
      TEST_send_result("MOTOR", false, "Errore motore direzione AVANTI");
      break;
    case 4: // errore indietro
      TEST_send_result("MOTOR", false, "Errore motore direzione INDIETRO");
      break;
    case 5: // errore tutto
    case 6: // errore indietro
    case 7: // errore tutto
      TEST_send_result("MOTOR", false, "Errore motore o sensore distanza");
      break;
  }*/

  /*Serial.println("");
  Serial.println("FINE TEST TRAZIONE");
  Serial.println("");
}*/

/*void TEST_trazione() {            //  DA AGGIUNGERE IL TEST PER L INGRESSO "RESET_EM" E "MODULO_EM"
  Serial.println("");
  Serial.println("TEST TRAZIONE");

  Serial.println("Cliccare il pulsante di RESET sulla tastiera per resettare l'emergenze e abilitare i motori. Attendere 10 secondi\"}");
  delay(10000);

  Serial.println("Cliccare su 'SI' se si vede il motore girare in entrambi le direzioni, oppure cliccare su 'NO' se il motore non gira o si blocca");

  Serial.println(F("motore avanti"));
  uint8_t v = 255 / 3;
  for (uint8_t i = 0; i < 3; i++) {
    MOT.start(v * (i + 1), 0);
    MOT.loop();
    //delay(10);
  }
  MOT.stop(0);
  MOT.loop();
  //delay(500);

  Serial.println(F("motore indietro"));
  v = 255 / 3;
  for (uint8_t i = 0; i < 3; i++) {
    MOT.start(v * (i + 1), 1);
    MOT.loop();
    //delay(10);
  }
  MOT.stop(0);
  MOT.loop();
  //delay(500);

  Serial.println("");
  Serial.println("FINE TEST TRAZIONE");
  Serial.println("");
}*/

//void TEST_motore_alzo() {
void TEST_alzo() {
  Serial.println("");
  Serial.println("TEST ALZO");

  Serial.println("{\"name\":\"description\",\"value\":\"Cliccare su 'SI' se si vede il 'rullo' salire e scendere, oppure cliccare su 'NO' se 'rullo' non si muove'\"}");

  ALZO.start(255, 0);
  uint32_t tstms = millis();
  while (millis() - tstms < 5000) {
    ALZO.loop();
    MOT.loop();
    //INV.loop();
    delay(10);
    //if (ALZO.getEndstopHit()) break;
  }
  ALZO.stop(0);
  ALZO.loop();
  delay(500);
  ALZO.start(255, 1);
  tstms = millis();
  while (millis() - tstms < 5000) {
    ALZO.loop();
    MOT.loop();
    //INV.loop();
    delay(10);
    //if()break;
  }
  ALZO.stop(1);
  ALZO.loop();
  TEST_send_result("DRIVERRISE", true, "");

  Serial.println("");
  Serial.println("FINE TEST ALZO");
  Serial.println("");
}
