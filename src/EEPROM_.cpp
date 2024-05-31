#include "EEPROM_.h"

void TEST_eeprom() {
  Serial.println("");
  Serial.println("TEST EEPROM");

  int i = 0;
  bool success = true;
  const char* myData = "HELLO WORLD";

  while (i < 4 && success) {
    // Scrivi la stringa nella memoria EEPROM all'indirizzo 0
    bool writeSuccess = writeEEPROMString(0, myData);
    if (!writeSuccess) {
      success = false;
      Serial.println("Errore durante la scrittura nella EEPROM.");
      break;
    }
    Serial.println("Scritta la stringa nella EEPROM.");

    // Leggi la stringa dalla memoria EEPROM all'indirizzo 0
    String readData = readEEPROMString(0);
    if (readData != String(myData)) {
      success = false;
      Serial.println("Errore durante la lettura dalla EEPROM.");
      break;
    }
    Serial.print("Letta dalla EEPROM: ");
    Serial.println(readData);

    // Cancella la stringa dalla memoria EEPROM all'indirizzo 0
    bool clearSuccess = clearEEPROMString(0);
    if (!clearSuccess) {
      success = false;
      Serial.println("Errore durante la cancellazione nella EEPROM.");
      break;
    }
    Serial.println("Cancellata la stringa dalla EEPROM.");

    // Verifica se la stringa è stata cancellata
    readData = readEEPROMString(0);
    if (readData != "") {
      success = false;
      Serial.println("Errore: la memoria EEPROM non è stata cancellata correttamente.");
      break;
    }
    Serial.print("Dopo la cancellazione, letto dalla EEPROM: ");
    Serial.println(readData);

    delay(10);  // Aggiungi un piccolo ritardo tra le iterazioni
    i++;
  }

  if (success) {
    Serial.println("---> TEST OK <---");
    Serial.println("{ \"name\": \"!EEPROM\", \"result\": \"ok\"}");
  } else {
    Serial.println("---> TEST ERROR <---");
    Serial.println("{ \"name\": \"!EEPROM\", \"result\": \"error\"}");
  }

  Serial.println("");
  Serial.println("FINE TEST EEPROM");
  Serial.println("");
}

bool writeEEPROMString(int address, const char* data) {
  // Verifica se l'indirizzo specificato è valido
  if (address < 0 || address >= maxMemory) {
    // Indirizzo non valido, restituisci false
    return false;
  }

  int i = 0;
  // Scrivi la stringa nella memoria EEPROM
  while (data[i] != '\0' && (address + i) < maxMemory) {
    EEPROM.write(address + i, data[i]);
    i++;
  }
  // Scrivi il terminatore di stringa, se c'è spazio nella memoria EEPROM
  if ((address + i) < maxMemory) {
    EEPROM.write(address + i, '\0');
    return true;  // Scrittura avvenuta con successo
  } else {
    return false;  // Non c'è spazio sufficiente per il terminatore di stringa
  }
}

String readEEPROMString(int address, bool* success = nullptr) {
  // Inizializza la stringa vuota
  String data = "";

  // Verifica se l'indirizzo specificato è valido
  if (address < 0 || address >= maxMemory) {
    // Indirizzo non valido, restituisci false se il parametro success è fornito
    if (success != nullptr) {
      *success = false;
    }
    return data;
  }

  // Leggi la stringa dalla memoria EEPROM
  char c = EEPROM.read(address);
  int i = 0;
  while (c != '\0' && (address + i) < maxMemory) {
    data += c;
    i++;
    c = EEPROM.read(address + i);
  }

  // Verifica se la lettura è stata interrotta a causa di un indirizzo non valido
  if ((address + i) >= maxMemory) {
    // Se il parametro success è fornito, impostalo su false
    if (success != nullptr) {
      *success = false;
    }
    return data;  // Restituisci la stringa parziale
  }

  // Se il parametro success è fornito, impostalo su true
  if (success != nullptr) {
    *success = true;
  }

  // Restituisci la stringa letta dalla EEPROM
  return data;
}

// Funzione per cancellare una stringa dalla memoria EEPROM
bool clearEEPROMString(int address) {
  // Verifica se l'indirizzo specificato è valido
  if (address < 0 || address >= maxMemory) {
    // Indirizzo non valido, restituisci false
    return false;
  }

  int i = 0;
  char c = EEPROM.read(address);

  // Cancella ogni byte finché non si incontra il terminatore di stringa ('\0')
  while (c != '\0' && (address + i) < maxMemory) {
    EEPROM.write(address + i, 0);  // Cancella ogni byte
    i++;
    c = EEPROM.read(address + i);
  }

  // Verifica se il ciclo è terminato perché abbiamo raggiunto il terminatore di stringa
  if ((address + i) < maxMemory) {
    // Cancella il terminatore di stringa ('\0')
    EEPROM.write(address + i, 0);
    return true;  // Operazione di cancellazione avvenuta con successo
  } else {
    // Se abbiamo superato i limiti della memoria EEPROM, restituiamo false
    return false;
  }
}
