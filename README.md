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
- "SERIAL" : libreria personalizzata per gestire i comandi inviati in seriale
- "CANBUS" : libreria personalizzata per il test del canbus
- "I2C" : libreria personalizzata per il test dell'i2c
- "INGRESSI" : libreria personalizzata per il test dei vari ingressi utilizzati in macchina
- "USCITE" : libreria personalizzata per il test delle varie uscite utilizzate in macchina
- "MOTORE" : libreria personalizzata per il test dei 2 motori che vengono gestiti dalla scheda
- "EMERGENZE" : libreria personalizzata per il test dell'emergenze gestite dalla scheda

LIBRERIE UTILIZZATEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

**FUNZIONAMENTO IN SINTESI**
- Il contatore dell'encoder continuerà sempre a contare e quando scatterà l'interrupt della fotocellula, il programma calcolerà il numero di step contati dall'inizio alla fine dell'antina. Quando si riceverà il messaggio canbus inviato dalla scheda arduino che avrà contato a sua volta il numero di step, verrà inviata una riposta contenente il numero di step contati da questa scheda. Inoltre verrà scritta all'interno dell'sd una stringa contenente id_anta, n.ro di step contati da questa scheda e il n.ro di step contati dalla scheda arduino, così da poter tenere traccia della differenza di step contati da una scheda e dall'altra. Il numero di step contati da questa scheda verrà elaborato dalla scheda arduino che deciderà se accettare oppure no questo valore. Successivamente il numero di step verrà convertito in millimetri (mm) e verrà inviato al server e alle altre schede.

**FUNZIONAMENTO CODICE**

- TWAI.c
    - TWAI_init() : inizializza il CANBUS

    - TWAI_send(uint32_t id, uint16_t flag, uint8_t len, uint8_t data[]) : utilizzata per inviare un messaggio

    - TWAI_get() : utilizzata per ricevere i messaggi

    - TWAI_handle_rx_message(twai_message_t message) : (funzione privata) utilizzata da TWAI_get() per leggere e dividere il contenuto di un messaggio

    - CAN_send_step_pezzo(uint32_t len, uint8_t idAnta) : utilizzata per inviare il messaggio contenente il numero di step contati
  
- SD.c
    - SD_init(Sd* sd) : inizializza SPI e SD
