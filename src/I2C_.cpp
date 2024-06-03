#include "I2C_.h"

void TEST_i2c() {
  Serial.println("");
  Serial.println("TEST I2C");

  byte error, address;
  int nDevices = 0;
  bool foundTarget_1 = false;
  bool foundTarget_2 = false;

  const char* deviceNames[2] = { "EEPROM1" , "EEPROM2"};      //  se serve cambiare il numero di indirizzi da trovare, cambiare grandezza array e cambiare nomi devices
  int targetDevices[2] = { 0x50 , 0x58};                      //  se serve cambiare il numero di indirizzi da trovare, cambiare grandezza array cambiare indirizzi devices     //  se serve cambiare indirizzi i2c da trovare, modificare gli indirizzi da questo array

  Serial.println("Scanning for I2C devices ...");

  // Scan I2C addresses from 1 to 127
  for (address = 1; address < 127; address++) {
    // Start communication with the I2C address
    Wire.beginTransmission(address);
    error = Wire.endTransmission();

    // Check for acknowledgment
    if (error == 0) {
      Serial.print("I2C device found at address 0x");
      if (address < 16) {
        Serial.print("0");
      }
      Serial.print(address, HEX);
      Serial.println("  !");

      // Check if the found address matches the target device address
      if (address == targetDevices[0]) foundTarget_1 = true;              //  se serve cambiare il numero di indirizzi da trovare, aggiungi o rimuovi variabili "foundTarget_x"
      if (address == targetDevices[1]) foundTarget_2 = true;

      nDevices++;
    } else if (error == 4) {
      Serial.print("Unknown error at address 0x");
      if (address < 16) {
        Serial.print("0");
      }
      Serial.println(address, HEX);
    }
  }

  // If no I2C devices found, print a message
  if (nDevices == 0) {
    Serial.println("No I2C devices found\n");
  } else {
    Serial.println("done\n");
  }

  //  If both I2C devices found
  if ((nDevices == 2) && foundTarget_1 && foundTarget_2) {                //  se serve cambiare il numero di indirizzi da trovare, aggiungi o rimuovi variabili "foundTarget_x" e cambia il numero da comparare con la variabile "nDevices"
    Serial.println("Test OK");
    Serial.println("{ \"name\": \"I2C\", \"result\": \"ok\"}");
  } else {
    Serial.print("{ \"name\": \"I2C\", \"result\": \"error\", \"error\": \"");
  }

  Serial.println("");
  Serial.println("FINE TEST I2C");
  Serial.println("");
}
