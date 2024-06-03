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
  
  if (confronto.equals("1\n") == 1)
  {
    TEST_canbus();
  }
  else if (confronto.equals("2\n") == 1)
  {
    TEST_i2c();
  }
  else if (confronto.equals("3\n") == 1)
  {
    TEST_ingressi();
  }
  else if (confronto.equals("4\n") == 1)
  {
    TEST_rele();
  }
  else if (confronto.equals("5\n") == 1)
  {
    TEST_inv();
  }
  else if (confronto.equals("6\n") == 1)
  {
    TEST_ssr();
  }
  else if (confronto.equals("7\n") == 1)
  {
    TEST_trazione();
  }
  else if (confronto.equals("8\n") == 1)
  {
    TEST_alzo();
  }
  else if (confronto.equals("9\n") == 1)
  {
    TEST_fotocellule();
  }
  else if (confronto.equals("10\n") == 1)
  {
    TEST_funghi();
  }
  else
  {
    if ((confronto.equals("\n") != 1) && (isValidMessage(confronto))) {   //  SE RICEVO "\n" OPPURE UNO O PIU' CARATTERI SPECIALI, ALLORA NON LI PRENDO IN CONSIDERAZIONE
      Serial.println("");
      //Serial.println("[\"!CANBUS\",\"!I2C\",\"!INGRESSI\",\"!RELE\",\"!INV\",\"!SSR\",\"!TRAZIONE\",\"!FOTOCELLULE\",\"!FUNGHI\"]");
      Serial.println("[\"1\",\"2\",\"3\",\"4\",\"5\",\"6\",\"7\",\"8\",\"9\",\"10\"]");
      Serial.println("");
    }
  }

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
