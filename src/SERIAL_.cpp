#include "SERIAL_.h"

String inputString = "";
bool stringComplete = false;

void serialEvent()
{
  if (Serial.available() > 0)
  {
    char inChar = (char)Serial.read(); // get the new byte:
    inputString += inChar;             // add it to the inputString:
    if (inChar == '\n')
    { // if the incoming character is a newline, set a flag so the main loop cando something about it:
      stringComplete = true;
    }
  }
}

void confronta_stringhe()
{
  stringComplete = false;

  String confronto = String(inputString);
  //Serial.println(confronto);
  //Serial.println("");
  /*if (confronto.indexOf("!QUARZO") != -1)
  {
    Serial.println("");
    Serial.println("{\"name\":\"description\",\"value\":\"\"}");
    Serial.println("");
    TEST_quarzo();
  }
  else*/ 
  
  /*if (confronto.indexOf("!EEPROM") != -1)
  {
    TEST_eeprom();
  }
  else */
  //if (confronto.indexOf("!CANBUS") != -1)
  if (confronto.equals("1\n") == 1)
  {
    TEST_canbus();
  }
  //else if (confronto.indexOf("!I2C") != -1)
  else if (confronto.equals("2\n") == 1)
  {
    TEST_i2c();
  }
  //else if (confronto.indexOf("!INGRESSI") != -1)
  else if (confronto.equals("3\n") == 1)
  {
    TEST_ingressi();
  }
  //else if (confronto.indexOf("!RELE") != -1)
  else if (confronto.equals("4\n") == 1)
  {
    TEST_rele();
  }
  //else if (confronto.indexOf("!INV") != -1)
  else if (confronto.equals("5\n") == 1)
  {
    TEST_inv();
  }
  //else if (confronto.indexOf("!SSR") != -1)
  else if (confronto.equals("6\n") == 1)
  {
    TEST_ssr();
  }
  //else if (confronto.indexOf("!TRAZIONE") != -1)
  else if (confronto.equals("7\n") == 1)
  {
    TEST_trazione();
  }
  /*else if (confronto.indexOf("!MOTORI") != -1)
  {
    TEST_motori();
  }*/
  //else if (confronto.indexOf("!ALZO") != -1)
  else if (confronto.equals("8\n") == 1)
  {
    //TEST_alzo();
    TEST_alzo();
  }
  //else if (confronto.indexOf("!FOTOCELLULE") != -1)
  else if (confronto.equals("9\n") == 1)
  {
    TEST_fotocellule();
  }
  //else if (confronto.indexOf("!FUNGHI") != -1)
  else if (confronto.equals("10\n") == 1)
  {
    TEST_funghi();
  }
  /*else if (confronto.indexOf("!EMERGENZE") != -1)
  {
    TEST_emergenze();
  }*/
  else /*if (confronto.indexOf("!TEST") != -1)*/
  {
    if ((confronto.equals("\n") != 1) && (isValidMessage(confronto))) {   //  SE RICEVO "\n" OPPURE UNO O PIU' CARATTERI SPECIALI, ALLORA NON LI PRENDO IN CONSIDERAZIONE
      Serial.println("");
      //Serial.println("[\"!QUARZO\",\"!EEPROM\",\"!CANBUS\",\"!I2C\",\"!INGRESSI\",\"!RELE\",\"!INV\",\"!SSR\",\"!TRAZIONE\",\"!ALZO\",\"!EMERGENZE\"]");
      //Serial.println("[\"!EEPROM\",\"!CANBUS\",\"!I2C\",\"!INGRESSI\",\"!RELE\",\"!INV\",\"!SSR\",\"!TRAZIONE\",\"!ALZO\",\"!FOTOCELLULE\",\"!FUNGHI\",\"!EMERGENZE\"]");
      //Serial.println("[\"!CANBUS\",\"!I2C\",\"!INGRESSI\",\"!RELE\",\"!INV\",\"!SSR\",\"!TRAZIONE\",\"!FOTOCELLULE\",\"!FUNGHI\"]");
      Serial.println("[\"1\",\"2\",\"3\",\"4\",\"5\",\"6\",\"7\",\"8\",\"9\",\"10\"]");
      Serial.println("");
    }
  }
  /*else
  {
    Serial.println("{\"name\":\"description\",\"value\":\"Input error, digitare il nome di un test\"}");
  }*/

  inputString = ""; // clear the string:
  stringComplete = false;
}

bool isValidMessage(String message) {
  for (unsigned int i = 0; i < message.length(); i++) {
    char c = message.charAt(i);
    if (!isPrintable(c)) {
      return false; // Contains special character, not a valid message
    }
  }
  return true; // No special characters found, valid message
}

bool isPrintable(char c) {
  // Check if character is printable and not a special character
  // ASCII values 32 (space) to 126 (~) are printable characters
  return (c >= 32 && c <= 126);
}
