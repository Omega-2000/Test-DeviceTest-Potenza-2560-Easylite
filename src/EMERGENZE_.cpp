#include "EMERGENZE_.h"

const byte EMERG_PORT =   B11100000;
const byte EMERG_ARMO =   B10000000;
const byte EMERG_RESET =  B00000001;
uint8_t emerg_port;
bool emerg_attiva = 0;
bool emerg_armata = 0;
bool fotocell_attive = 0;
bool fotocell_armate = 0;
bool reset_emerg = 0;
bool arresto_emergenza = 0;
bool old_arresto_emergenza = 0;
bool send_emergenze = 0;
bool SAFETY_MODULE = 0;

String inputString_e = "";
bool stringComplete_e = false;

void serialEvent_e() {
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

void next_e() {
  bool next = 0;
  while(!next) {
      serialEvent_e();
      if (stringComplete_e)
      {
          //  confronta_stringhe
          stringComplete_e = false;
          String confronto = String(inputString_e);
          Serial.println(confronto);
          Serial.println("");
          if (confronto.indexOf("!NEXT") != -1) next = 1;
          //

          Serial.println("");
          Serial.println("In attesa...");
          return;
      }

      delay(10);
  }
}

void emergenze_begin() {
  noInterrupts();
  PCICR |=  B00000100; // attivo pcint 2 (3° bit del registro)
  PCMSK2 |= 0xff;//*0b00001101;/*/EMERG_PORT; // setto la maschera sulla porta per leggere solo i pin attivi
  if (!SAFETY_MODULE) attachInterrupt(digitalPinToInterrupt(FOTOCELLULA), check_fotocellule, CHANGE);
  interrupts();
  pinMode(FOTOCELLULA, INPUT);
  pinMode(TEST_FOTOCELLULA, OUTPUT);
  digitalWrite(TEST_FOTOCELLULA, 1);
}

void check_emerg() {
  Serial.println(F("check emergenze"));
  emerg_port = EMERG_PORT_READ; // leggo la porta
  emerg_attiva = emerg_port & EMERG_PORT & ~EMERG_ARMO; // & !EMERG_RESET;
  emerg_armata = !(emerg_port & EMERG_ARMO);
  if (!SAFETY_MODULE) {
    reset_emerg = !(emerg_port & EMERG_RESET);
    if (reset_emerg) fotocell_armate = 1;
  } else {
    reset_emerg = 0;
    fotocell_armate = 1;
  }
  check_fotocellule();
  //attiva_emergenza();
  Serial.printf("Em stato: %x, %x, %x\n", emerg_port, emerg_attiva, emerg_armata);
}

void check_fotocellule() {
  if (!SAFETY_MODULE) {
    fotocell_attive = digitalRead(FOTOCELLULA);
    //Serial.println("fotocell nn att");
  } else {
    fotocell_attive = 0;
  }
  attiva_emergenza();

  Serial.println(F("check fotocellule"));
}

void attiva_emergenza() {
  Serial.println(F("inizio emergenza"));
  if (fotocell_attive && ((MOT.getState() && !MOT.getDirection()) || (ALZO.getState() && ALZO.getDirection()) || ((ALZO_mode != ALZO_MODE_MAN) && (ALZO_mode != ALZO_MODE_MAX))) && !reset_emerg) { //MODO
    fotocell_armate = 0;
    Serial.println("fotocell attiveeeeh");
  }
  arresto_emergenza = emerg_attiva || !emerg_armata || (!fotocell_armate && !reset_emerg && !SAFETY_MODULE);
  if (arresto_emergenza) {
    if (!MOT.getDirection()) MOT.stop(1);
    //if (!INV.getDirection()) INV.stop(1);
    if (ALZO.getDirection()) ALZO.stop(1);
    if ((ALZO_mode == ALZO_MODE_MIN) || (ALZO_mode == ALZO_MODE_AUTO)) {
      ALZO_mode = ALZO_MODE_MAN;
      ALZO.stop(1);
    }

    send_emergenze = 1; //CAN_send_emergenze();
    //Serial.printf("emergenzaaaaaaaa %d, %d, %d\n", fotocell_armate, reset_emerg, reset_emerg);
    //CAN_send_parameter(0xf0, 0x0100 + (emerg_port & EMERG_PORT), 2, CAN_universal_id);
    if (!old_arresto_emergenza) {
      Serial.println(F("invio stato in emergenza"));
      MOT.loop();
      //INV.loop();
      //CAN_send_state();
    }
  } else {
    delay(1000);
    //CAN_send_parameter(0xf0, 0x0000, 2, CAN_universal_id);
    send_emergenze = 1; //CAN_send_emergenze();
    delay(100);
    Serial.println("emergenza okksssss");
  }

  digitalWrite(REL_EMERG, !arresto_emergenza); //scrivo lo stato sul relè in uscita
  digitalWrite(REL_RESET_LINEA, reset_emerg); //scrivo lo stato sul relè in uscita
  old_arresto_emergenza = arresto_emergenza;
}

void TEST_send_button(uint8_t num, bool st) {
  String result = " { \"name\": \"" + String(num) +
                  "\", \"result\": \"" + (st ? "pressed" : "released") +
                  "\", \"message\": \"" + "\"} ";
  Serial.println(result);
}

void TEST_send_result(String test_name, bool test_success, String test_message) {
  String result = " { \"name\": \"" + test_name +
                  "\", \"result\": \"" + (test_success ? "ok" : "error") +
                  "\", \"message\": \"" + test_message + "\"} ";
  Serial.println(result);
}

void TEST_funghi_() {
  bool next = 0;
  uint8_t oldport = EMERG_PORT_READ;
  while (!next) {
    uint8_t em_st = EMERG_PORT_READ ^ oldport; // leggo la porta

    if (em_st) {
      if (em_st & B01000000) {
        TEST_send_button(1, EMERG_PORT_READ & B01000000);
      }
      if (em_st & B00100000) {
        TEST_send_button(2, EMERG_PORT_READ & B00100000);
      }
      if (em_st & EMERG_RESET) {
        TEST_send_button(3, EMERG_PORT_READ & EMERG_RESET);
      }
      if (em_st & EMERG_ARMO) {
        TEST_send_button(4, EMERG_PORT_READ & EMERG_ARMO);
      }
    }

    /*if (TEST_receive()) {
      if (TEST_cmd == "!EXIT") {
        Serial.println("uscita TEST");
        TEST_send_result("BUTTONS", true, "");
        return;
      }
    }*/

    serialEvent_e();
    if (stringComplete_e)
    {
      //  confronta_stringhe
      stringComplete_e = false;
      String confronto = String(inputString_e);
      Serial.println(confronto);
      Serial.println("");
      if (confronto.indexOf("!NEXT") != -1) next = 1;
      //

      Serial.println("");
      Serial.println("In attesa...");
      return;
    }
  }
}

/*void TEST_fotocellule() {
  digitalWrite(TEST_FOTOCELLULA, 1);
  delay(10);
  bool fc1 = digitalRead(FOTOCELLULA);
  bool fc2 = digitalRead(FOTOCELLULA_2);

  digitalWrite(TEST_FOTOCELLULA, 0);
  delay(10);
  bool fc1_ = digitalRead(FOTOCELLULA);
  bool fc2_ = digitalRead(FOTOCELLULA_2);
  digitalWrite(TEST_FOTOCELLULA, 1);

  if (fc1 && fc2 && fc1_ && fc2_) {
    TEST_send_result("PHOTOCELLS", true, "");
  } else {
    String errmsg = "Errore fotocellula ";
    if (!fc1 || !fc1_) {
      errmsg += "1 " + String(!fc1 ? "sempre interrotta, " : "") + String(!fc1_ ? "non si interrompe, " : "");
    }
    if (!fc2 || !fc2_) {
      errmsg += "2 " + String(!fc2 ? "sempre interrotta, " : "") + String(!fc2_ ? "non si interrompe, " : "");
    }

    TEST_send_result("PHOTOCELLS", false, errmsg);
  }
}*/

void TEST_funghi() {
  Serial.println("");
  Serial.println("TEST FUNGHI");

  bool end = 0;
  bool stato_fotoc_1 = digitalRead(FUNGO_1);
  bool stato_fotoc_2 = digitalRead(FUNGO_2);
  bool cambia_stato = 0;
  bool cambia_stato_2 = 0;
  unsigned long t_fotoc = millis();
  Serial.println("Premere i due interruttori che simulano le due funghi");

  while(!end) {
    if (!cambia_stato && (digitalRead(FUNGO_1) != stato_fotoc_1)) {      //  se premuto, il pedale cambia stato
        cambia_stato = 1;
    }
    if (!cambia_stato_2 && (digitalRead(FUNGO_2) != stato_fotoc_2)) {      //  se premuto, il pedale cambia stato
        cambia_stato_2 = 1;
    }

    if (cambia_stato && cambia_stato_2) {
      end = 1;
      Serial.println("FUNZIONANO ENTRAMBI I FUNGHI");
      Serial.println("{\"name\":\"Funghi\",\"result\":\"ok\"}");
    }
    
    if ((millis() - t_fotoc) > 10000) {
      end = 1;     //  timeout
      Serial.println("TIMEOUT");
    }
  }

  if (!cambia_stato && cambia_stato_2) {
    Serial.println("{\"name\":\"Funghi\",\"result\":\"error\",\"error\":\"L'ingresso 'FUNGO_1' non funziona\"}");
    //return;
  } else if (cambia_stato && !cambia_stato_2) {
    Serial.println("{\"name\":\"Funghi\",\"result\":\"error\",\"error\":\"L'ingresso 'FUNGO_2' non funziona\"}");
    //return;
  } else if (!cambia_stato && !cambia_stato_2) {
    Serial.println("{\"name\":\"Funghi\",\"result\":\"error\",\"error\":\"I due ingressi 'FUNGO_1' e 'FUNGO_2' non funzionano\"}");
    //return;
  }

  Serial.println("");
  Serial.println("FINE TEST FUNGHI");
  Serial.println("");
}

//void TEST_emergenze() {
void TEST_fotocellule() {
  Serial.println("");
  Serial.println("TEST FOTOCELLULE");

  bool end = 0;
  bool stato_fotoc_1 = digitalRead(FOTOCELLULA);
  bool stato_fotoc_2 = digitalRead(FOTOCELLULA_2);
  bool cambia_stato = 0;
  bool cambia_stato_2 = 0;
  unsigned long t_fotoc = millis();
  Serial.println("Premere i due interruttori che simulano le due fotocellule");

  while(!end) {
    if (!cambia_stato && (digitalRead(FOTOCELLULA) != stato_fotoc_1)) {      //  se premuto, il pedale cambia stato
        cambia_stato = 1;
    }
    if (!cambia_stato_2 && (digitalRead(FOTOCELLULA_2) != stato_fotoc_2)) {      //  se premuto, il pedale cambia stato
        cambia_stato_2 = 1;
    }

    if (cambia_stato && cambia_stato_2) {
      end = 1;
      Serial.println("FUNZIONANO ENTRAMBE LE FOTOCELLULE");
      Serial.println("{\"name\":\"Fotocellule\",\"result\":\"ok\"}");
    }
    
    if ((millis() - t_fotoc) > 10000) {
      end = 1;     //  timeout
      Serial.println("TIMEOUT");
    }
  }

  if (!cambia_stato && cambia_stato_2) {
    Serial.println("{\"name\":\"Fotocellule\",\"result\":\"error\",\"error\":\"L'ingresso 'FOTOCELLULA' non funziona\"}");
    //return;
  } else if (cambia_stato && !cambia_stato_2) {
    Serial.println("{\"name\":\"Fotocellule\",\"result\":\"error\",\"error\":\"L'ingresso 'FOTOCELLULA_2' non funziona\"}");
    //return;
  } else if (!cambia_stato && !cambia_stato_2) {
    Serial.println("{\"name\":\"Fotocellule\",\"result\":\"error\",\"error\":\"I due ingressi 'FOTOCELLULA' e 'FOTOCELLULA_2' non funzionano\"}");
    //return;
  }

  Serial.println("");
  Serial.println("FINE TEST FOTOCELLULE");
  Serial.println("");
}
