#include "MOTORE_.h"

MotorDriver MOT = MotorDriver(0, MOT_PWM, MOT_INA, MOT_INB, MOT_CSENSE, MOT_ENA, MOT_ENB, MOT_NTC, 0);
MotorDriver ALZO = MotorDriver(0, ALZO_PWM, ALZO_INA, ALZO_INB, ALZO_CSENSE, ALZO_ENA, ALZO_ENB, ALZO_NTC, ALZO_FINE_CORSA);

void setPwmFrequency(int pin, byte mode) {
  // Registri timer 5 https://www.robotshop.com/community/forum/t/arduino-101-timers-and-interrupts/13072
  //https://www.avrfreaks.net/forum/can-someone-explain-me-significance-com1a1com1a0
  // TCCRA
  TCCR5A =  0b10101010; //  11 8kHz/pre-10bit 10 15kHz/pre-9bit 01 31kHz/pre-8bit
  //          ^ ^ ^    cmp out mode normale non-invertente
  TCCR5B =  0b00000001;
  //               ^^^ prescaler 1/8/64/256
}

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
