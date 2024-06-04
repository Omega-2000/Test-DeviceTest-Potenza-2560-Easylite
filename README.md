# Test-DeviceTest-Potenza-2560-Easylite

**HARDWARE**
- Scheda Potenza Easylite (montata in piattaforma di test con il resto delle schede del kit Easylite)
- Microcontrollore ATMEGA2560
- Alimentazione 24V per poter fare anche il test "trazione" e il test "alzo", altrimenti per gli altri test basterebbero i 5V
- Scheda collegata al DeviceTest che indicherà le istruzioni su come eseguire i vari test

**AMBIENTE DI SVILUPPO**
- Visual Studio Code con estensione "PlatformIO"
- Ambiente e librerie di Arduino

**LINGUAGGIO DI PROGRAMMAZIONE**
- C++

**LIBRERIE**
- "SERIAL_" : libreria personalizzata per gestire i comandi inviati in seriale
- "CANBUS_" : libreria personalizzata per il test del canbus, basata sulla libreria "CAN" in cui bisogna specificare i gpio dei pin "CAN_CS" e "CAN_INT" (all'interno del file MCP2515.h)
- "I2C_" : libreria personalizzata per il test dell'i2c, basata sulla libreria "Wire"
- "INGRESSI_" : libreria personalizzata per il test dei vari ingressi utilizzati in macchina
- "USCITE_" : libreria personalizzata per il test delle varie uscite utilizzate in macchina
- "MOTORE_" : libreria personalizzata per il test dei 2 motori che vengono gestiti dalla scheda, basata sulla classe "MotorDriver"
- "EMERGENZE_" : libreria personalizzata per il test dell'emergenze gestite dalla scheda

**FUNZIONAMENTO IN SINTESI**
- Il programma rimarrà in attesa finchè non gli sarà inviato un comando in seriale. Un numero corrisponderà a un test da avviare e se il comando non sarà riconosciuto, verrà inviata la lista dei comandi da poter inviare. Una volta avviato il test, in seriale verranno stampate alcune istruzioni su come effettuare i test, che verranno ulteriormente arricchite sull'interfaccia del devicetest. Alcuni di questi test sono composti da più step e solo una parte di questi richiederà l'invio di un comando per avanzare allo step successivo, oppure il programma potrebbe attendere il comando di fine test. Per inviare il comando "next" si potrà scrivere il numero "98" in seriale, mentre si potrà scrivere il numero "99" per completare il test. Gli altri test invece saranno automatici (test eseguiti dal programma che ritornerà direttamente il risultato), oppure semiautomatici che richiederanno delle interazioni dall'operatore prima di poter ritornare un risultato.

**LISTA TEST**
- CANBUS
- I2C
- INGRESSI (test PEDALE, CONTAGIRI, FINECORSA_ALZO, TRIM_ALT_RULLI, NTC)
- RELE
- INV (uscita INV_0_10)
- SSR (uscita SSR_3)
- TRAZIONE
- ALZO
- FOTOCELLULE
- FUNGHI

**FUNZIONAMENTO CODICE**
- SERIAL_
  - serialEvent() : funzione che legge la seriale e all'invio di "\n" ritorna "true" che indicherà la lettura della seriale avvenuta e si potrà passare al controllo del comando ricevuto

  - confronta_stringhe() : funzione che avvia il test a seconda del comando ricevuto in seriale

  - isValidMessage(String message) : funzione a cui si passa una stringa e che ritorna true se la stringa non contiene caratteri speciali, oppure false se la stringa non è valida

  - isPrintable(char c) : funzione che controlla se il carattere che gli viene passato è un carattere speciale oppure no

- CANBUS_
  - ***CONTROLLARE ALL'INTERNO DEL FILE MCP2515.h E IMPOSTARE CORRETTAMENTE IL NUMERO DEI GPIO DEI PIN "MCP2515_DEFAULT_CS_PIN" E "MCP2515_DEFAULT_INT_PIN"***
  - TEST_canbus() : funzione che testa in automatico il canbus e che ritorna il risultato del test

- I2C_
  - ***LE NUOVE EEPROM MONTATE MOSTRANO 2 INDIRIZZI I2C (0x50 e 0x58), MENTRE LE EEPROM MONTATE SULLE VECCHIE SCHEDE NE MOSTRANO SOLO UNO (0x50), QUINDI SAREBBE DA CONTROLLARE QUESTA COSA QUANDO SI ESEGUE IL TEST, OPPURE MODIFICARE LA FUNZIONE DI TEST***
  - TEST_i2c() : funzione che testa in automatico l'i2c e che ritorna il risultato del test

- INGRESSI_
  - contagiri() : funzione di interrupt che incrementa un contatore, utilizzata per il test del contagiri

  - get_temperature(uint8_t ntc) : funzione che converte il valore analogico letto dall'ingresso ntc in gradi Celsius, utlizzata per il test degli ntc

  - BEGIN_ingressi() : funzione che inizializza tutti i gpio che si andranno a testare nel test degli ingressi

  - TEST_ingressi() : funzione che testa tutti gli ingressi utilizzati in macchina e ritorna il risultato del test, seguire le istruzioni per effettuare il test correttamente
  - ***IL TEST NON E' PRECISO IN TUTTI GLI STEP CHE SI TESTANO E SAREBBE DA RIFARE E DIVIDERE I VARI STEP IN TEST SEPARATI***

- USCITE_
  - serialEvent_u() : funzione che legge la seriale e all'invio di "\n" ritorna "true" che indicherà la lettura della seriale avvenuta e si potrà passare al controllo del comando ricevuto

  - BEGIN_uscite() : funzione che inizializza tutti i gpio che si andranno a testare nel test delle uscite

  - TEST_rele() : funzione utlizzata per testare tutti i relè (richiede il comando "next" per avanzare nel test)

  - TEST_inv() : funzione utilizzata per testare l'uscita "INV_0_10" (richiede il comando "end" per completare il test)

  - TEST_ssr() : funzione utilizzata per testare l'uscita "SSR_3" (richiede il comando "end" per completare il test)

- MOTORE_
  - setPwmFrequency(int pin, byte mode) : funzione utilizzata internamente richiesta dalla classe usata in questa libreria

  - TEST_trazione() : funzione utilizzata per testare il motore di trazione, seguire le istruzioni per effettuare il test correttamente

  - TEST_alzo() : funzione utilizzata per testare il motore alzo motorizzato, seguire le istruzioni per effettuare il test correttamente

- EMERGENZE_
  - TEST_send_result(String test_name, bool test_success, String test_message) : funzione utilizzata internamente dalla funzione TEST_alzo() per stampare una stringa in seriale

  - TEST_fotocellule() : funzione utilizzata per testare gli ingressi delle fotocellule e che ritorna il risultato del test, seguire le istruzioni per effettuare il test correttamente

  - TEST_funghi() : funzione utilizzata per testare gli ingressi dei funghi utilizzati in macchina (2 funghi) e che ritorna il risultato del test, seguire le istruzioni per effettuare il test correttamente
