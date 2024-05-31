#include "INGRESSI_.h"

String inputString_i = "";
bool stringComplete_i = false;
//bool man_pedale;
uint32_t giri = 0;

void serialEvent_i() {
  while (Serial.available())
  {
    char inChar = (char)Serial.read(); // get the new byte:
    inputString_i += inChar;             // add it to the inputString:
    if (inChar == '\n')
    { // if the incoming character is a newline, set a flag so the main loop cando something about it:
      stringComplete_i = true;
    }
  }
}

void next() {
    bool next = 0;
    while(!next) {
        serialEvent_i();
        if (stringComplete_i)
        {
            //  confronta_stringhe
            stringComplete_i = false;
            String confronto = String(inputString_i);
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

void BEGIN_ingressi() {
    pinMode(PEDALE, INPUT);
    pinMode(CONTA_GIRI, INPUT);
    attachInterrupt(digitalPinToInterrupt(CONTA_GIRI), contagiri, CHANGE);  //  dato per scontato che il motorino del contagiri sia fermo finchè non dico io di farlo partire
    pinMode(ALZO_FINE_CORSA, INPUT);
    pinMode(TRIM_ALT_RULLI, INPUT);
    pinMode(MOT_NTC, INPUT);
    pinMode(ALZO_NTC, INPUT);
}

void contagiri() {
    giri++;
}

float get_temperature(uint8_t ntc) {
    int Vo;
    float R1 = 10000;
    float logR2, R2, T;
    float c1 = 1.009249522e-03, c2 = 2.378405444e-04, c3 = 2.019202697e-07;
    Vo = analogRead(ntc);
    R2 = R1 * (1023.0 / (float)Vo - 1.0);
    logR2 = log(R2);
    T = (1.0 / (c1 + c2 * logR2 + c3 * logR2 * logR2 * logR2));
    T = T - 273.15;
    return T;
}

void TEST_ingressi() {
    Serial.println("{\"name\":\"description\",\"value\":\"Seguire le istruzioni che verranno stampate in seriale\"}");

    Serial.println("");
    Serial.println("TEST INGRESSI");

    //  PEDALE
    Serial.println("");
    Serial.println("PEDALE");
    bool end = 0;
    unsigned long t_pedale = millis();
    bool stato_pedale = digitalRead(PEDALE);
    bool cambia_stato = 0;
    Serial.println("Premere l'interruttore che simula il PEDALE");
    while(!end) {
        if (digitalRead(PEDALE) != stato_pedale) {      //  se premuto, il pedale cambia stato
            cambia_stato = 1;
            end = 1;
        }
        if ((millis() - t_pedale) > 10000) end = 1;     //  timeout
    }
    if (!cambia_stato) {
        Serial.println("{\"name\":\"Ingressi\",\"result\":\"error\",\"error\":\"L'ingresso 'PEDALE' non funziona\"}");
        return;
    } else Serial.println("PEDALE : ok");

    delay(1000);
    //next(); //  aspetta !NEXT

    //  CONTAGIRI
    Serial.println("");
    Serial.println("CONTAGIRI");
    end = 0;
    uint8_t giri_prima = giri;
    uint8_t giri_step_1 = 0;
    uint8_t giri_step_2 = 0;
    bool test_contagiri = 0;
    bool step_1 = 0;
    bool step_2 = 0;
    unsigned long t_contagiri = millis();
    Serial.println("Collega i due cavetti e fai partire la ruota del CONTAGIRI");
    while(!end) {
        if ((step_1 == 0) && ((millis() - t_contagiri) > 15000)) {
            giri_step_1 = giri;

            if (giri_step_1 > giri_prima) {
                test_contagiri = 1;
                Serial.println();
                Serial.println("Scollega i due cavetti e attendi");
                Serial.println();
                step_1 = 1;
            } else end = 1;

            t_contagiri = millis();
        }

        /*if ((step_1 == 1) && ((millis() - t_contagiri) > 10000)) {
            giri_step_2 = giri;
            if (giri_step_2 == giri_step_1) test_contagiri = 1; else test_contagiri = 0;
            end = 1;
        }*/

        if ((step_1 == 1) && (step_2 == 0) && ((millis() - t_contagiri) > 5000)) {
            giri_step_1 = giri;
            step_2 = 1;
        }

        if ((step_1 == 1) && (step_2 == 1) && ((millis() - t_contagiri) > 10000)) {
            giri_step_2 = giri;
            if (giri_step_2 == giri_step_1) test_contagiri = 1; else test_contagiri = 0;
            end = 1;
        }
    }
    if (!test_contagiri) {
        Serial.println("{\"name\":\"Ingressi\",\"result\":\"error\",\"error\":\"L'ingresso 'CONTAGIRI' non funziona\"}");
        return;
    } else Serial.println("CONTAGIRI : ok");

    delay(1000);
    //next(); //  aspetta !NEXT


    ///*
    //  FINECORSA ALZO
    Serial.println("");
    Serial.println("FINECORSA ALZO");
    end = 0;
    step_1 = 0;
    bool test_finecorsa = 0;
    bool finecorsa_prima = 0;
    unsigned long t_finecorsa = millis();
    Serial.println("Tieni scoperto il sensore FINECORSA ALZO");
    while(!end) {
        if ((step_1 == 0) && ((millis() - t_finecorsa) > 10000)) {
            finecorsa_prima = digitalRead(ALZO_FINE_CORSA);
            step_1 = 1;
            Serial.println();
            Serial.println("Copri il sensore FINECORSA ALZO e attendi");
            Serial.println();
            t_finecorsa = millis();
        }
        if ((step_1 == 1) && ((millis() - t_finecorsa) > 10000)) {
            if (finecorsa_prima != digitalRead(ALZO_FINE_CORSA)) test_finecorsa = 1; else test_finecorsa = 0;
            end = 1;
        }
    }
    if (!test_finecorsa) {
        Serial.println("{\"name\":\"Ingressi\",\"result\":\"error\",\"error\":\"L'ingresso 'FINECORSA' non funziona\"}");
        return;
    } else Serial.println("FINECORSA ALZO : ok");

    delay(1000);
    //next(); //  aspetta !NEXT
    

    
    //  TRIM ALT RULLI
    Serial.println("");
    Serial.println("TRIM ALT RULLI");
    end = 0;
    unsigned long t_lettura = 0;
    uint16_t letture[10];
    uint8_t index = 0;
    bool tutti_uguali = 0;
    uint8_t uguali = 0;
    unsigned long t_trim = millis();
    Serial.println("Girare il sensore che simula il TRIM_ALT_RULLI finchè non vengono fatte 10 letture");
    while(!end) {
        if (((millis() - t_trim) > 5000) && ((millis() - t_trim) < 10000)) {
            if ((millis() - t_lettura) > 500) {
                letture[index] = analogRead(TRIM_ALT_RULLI);
                Serial.print(index);
                Serial.print(" : ");
                Serial.println(letture[index]);
                index++;
                t_lettura = millis();
            }
        }
        if ((millis() - t_trim) > 10000) {
            for (uint8_t i = 1 ; i < 10 ; i++) {
                if (letture[0] == letture[i]) uguali++; //    tutti_uguali = 1; else tutti_uguali = 0;
            }
            if (uguali == 9) tutti_uguali = 1; else tutti_uguali = 0;
            end = 1;
        }
    }
    if (tutti_uguali) {
        Serial.println("{\"name\":\"Ingressi\",\"result\":\"error\",\"error\":\"L'ingresso 'TRIM_ALT_RULLI' non funziona\"}");
        return;
    } else Serial.println("TRIM ALT RULLI : ok");

    delay(1000);
    //next(); //  aspetta !NEXT
    //*/

    //NTC
    Serial.println("");
    Serial.println("NTC");
    end = 0;
    bool test_ntc = 0;
    Serial.println("Sto leggendo la temperatura dei due NTC");
    if ((get_temperature(MOT_NTC) < 10.0) && (get_temperature(MOT_NTC) > 50.0)) {
        Serial.println("{\"name\":\"Ingressi\",\"result\":\"error\",\"error\":\"L'ingresso 'MOT_NTC' non funziona\"}");
        return;
    }
    if ((get_temperature(ALZO_NTC) < 10.0) && (get_temperature(ALZO_NTC) > 50.0)) {
        Serial.println("{\"name\":\"Ingressi\",\"result\":\"error\",\"error\":\"L'ingresso 'ALZO_NTC' non funziona\"}");
        return;
    }
    Serial.println("NTC : ok");

    delay(1000);

    Serial.println("{\"name\":\"Ingressi\",\"result\":\"ok\"}");

    Serial.println("");
    Serial.println("FINE TEST INGRESSI");
    Serial.println("");
}
