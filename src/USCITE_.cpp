#include "USCITE_.h"

String inputString_u = "";
bool stringComplete_u = false;

void serialEvent_u() {
  while (Serial.available())
  {
    char inChar = (char)Serial.read(); // get the new byte:
    inputString_u += inChar;             // add it to the inputString:
    if (inChar == '\n')
    { // if the incoming character is a newline, set a flag so the main loop cando something about it:
      stringComplete_u = true;
    }
  }
}

void BEGIN_uscite() {

    pinMode(REL_SERV_1, OUTPUT);
    pinMode(REL_SERV_2, OUTPUT);
    pinMode(REL_ASPIR, OUTPUT);

    pinMode(REL_MARCIA, OUTPUT);
    pinMode(REL_STOP, OUTPUT);
    pinMode(REL_RESET_LINEA, OUTPUT);
    pinMode(REL_EMERG, OUTPUT);

    pinMode(INV_AVANTI, OUTPUT);
    pinMode(INV_INDIETRO, OUTPUT);
    pinMode(INV_ARRESTO, OUTPUT);
    pinMode(INV_0_10, OUTPUT);          //  misurare V con multimetro se giusti

    pinMode(SSR_3, OUTPUT);             //  verificare che il led spia si accenda
    //pinMode(VENTOLA, OUTPUT);           //  verificare che la ventola giri
}

void TEST_rele() {
    Serial.println("");
    Serial.println("TEST RELE");

    unsigned long t_rele = 0;
    bool next = 0;
    uint8_t numero_rele = 0;
    uint8_t pin[] = {REL_SERV_1, REL_SERV_2, REL_ASPIR, REL_MARCIA, REL_STOP, REL_RESET_LINEA, REL_EMERG, INV_AVANTI, INV_INDIETRO, INV_ARRESTO};
    Serial.println("{\"name\":\"description\",\"value\":\"Cliccare su 'SI' se senti il relè scattare, oppure cliccare su 'NO' se non lo senti\"}");
    for (uint8_t i = 0 ; i < sizeof(pin) ; i++) {
        next = 0;
        numero_rele = i + 1;

        Serial.print(numero_rele);
        Serial.println("/10");

        while(!next) {     //  aspetta di ricevere in seriale un "ok, passa al prossimo" da davide
            if ((millis() - t_rele) > 1000) {
                digitalWrite(pin[i], !digitalRead(pin[i]));
                t_rele = millis();
            }

            serialEvent_u();
            if (stringComplete_u)
            {
                //  confronta_stringhe
                stringComplete_u = false;
                String confronto_u = String(inputString_u);
                //Serial.println(confronto_u);
                //Serial.println("");
                //if (confronto_u.indexOf("!NEXT") != -1) next = 1;
                if (confronto_u.equals("98\n") == 1) next = 1;

                //if (confronto_u.indexOf("!END") != -1) {
                if (confronto_u.equals("99\n") == 1) {
                    next = 1;
                    i = sizeof(pin) - 1;
                }
                //

                //Serial.println("");
                //Serial.println("In attesa...");
                //return;
                inputString_u = "";
                stringComplete_u = false;
            }

            /*inputString_u = "";
            stringComplete_u = false;*/

            //delay(10);
        }
    }

    //  disattiva tutti i relè
    for (uint8_t i = 0; i < sizeof(pin); i ++) {
        digitalWrite(pin[i], 0);
    }
    //t_rele = 0;

    inputString_u = "";
    stringComplete_u = false;

    Serial.println("");
    Serial.println("FINE TEST RELE");
    Serial.println("");
}

void TEST_inv() {
    Serial.println("");
    Serial.println("TEST USCITA INVERTER");

    Serial.println("{\"name\":\"description\",\"value\":\"Misurare la tensione con il multimetro se tra l'uscita di 'INV_0_10' e GND ci sono tra i 9.3V e i 10.3V e cliccare se 'SI' o 'NO'\"}");
    //  DA SPECIFICARE DOVE

    bool next = 0;
    analogWrite(INV_0_10, 255);
    while(!next) {
        serialEvent_u();
        if (stringComplete_u)
        {
            //  confronta_stringhe
            stringComplete_u = false;
            String confronto = String(inputString_u);
            //Serial.println(confronto);
            //Serial.println("");
            //if (confronto.indexOf("!END") != -1) next = 1;
            if (confronto.equals("99\n") == 1) next = 1;

            //

            //Serial.println("");
            //Serial.println("In attesa...");
            //return;
            inputString_u = "";
            stringComplete_u = false;

        }

        delay(10);
    }
    analogWrite(INV_0_10, 0);

    inputString_u = "";
    stringComplete_u = false;

    Serial.println("");
    Serial.println("FINE TEST USCITA INVERTER");
    Serial.println("");
}

void TEST_ssr() {
    Serial.println("");
    Serial.println("TEST SSR");

    Serial.println("{\"name\":\"description\",\"value\":\"Cliccare su 'SI' se si vede lampeggiare il led D2 'SSR_3', oppure cliccare su 'NO' se il led non lampeggia\"}");
    //  DA SPECIFICARE DOVE

    unsigned long t_ssr = 0;
    bool next = 0;
    while(!next) {
        if ((millis() - t_ssr) > 1000) {
            digitalWrite(SSR_3, !digitalRead(SSR_3));
            t_ssr = millis();
        }

        serialEvent_u();
        if (stringComplete_u)
        {
            //  confronta_stringhe
            stringComplete_u = false;
            String confronto = String(inputString_u);
            //Serial.println(confronto);
            //Serial.println("");
            //if (confronto.indexOf("!END") != -1) next = 1;
            if (confronto.equals("99\n") == 1) next = 1;

            //

            //Serial.println("");
            //Serial.println("In attesa...");
            //return;
            inputString_u = "";
            stringComplete_u = false;
        }

        delay(10);
    }
    digitalWrite(SSR_3, 0);

    inputString_u = "";
    stringComplete_u = false;

    Serial.println("");
    Serial.println("FINE TEST SSR");
    Serial.println("");
}

/*void TEST_ventola() {
    Serial.println("{\"name\":\"description\",\"value\":\"Cliccare su 'SI' se si vede la ventola girare, oppure cliccare su 'NO' se la ventola non gira\"}");
    bool next = 0;
    analogWrite(VENTOLA, 255);
    while(!next) {
        serialEvent_u();
        if (stringComplete_u)
        {
            //  confronta_stringhe
            stringComplete_u = false;
            String confronto = String(inputString_u);
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

    Serial.println("");
    //Serial.println("TEST COMPLETATO");
    Serial.println("{\"name\":\"end\"}");
}*/
