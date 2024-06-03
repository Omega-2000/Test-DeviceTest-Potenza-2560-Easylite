#include "EMERGENZE_.h"

void TEST_send_result(String test_name, bool test_success, String test_message) {
  String result = " { \"name\": \"" + test_name +
                  "\", \"result\": \"" + (test_success ? "ok" : "error") +
                  "\", \"message\": \"" + test_message + "\"} ";
  Serial.println(result);
}

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
