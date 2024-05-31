#include "SERIAL_.h"

#define versione T1
// unsigned long t = 0;
//int command = 0;
//char receivedChar;

void setup()
{
  Serial.begin(9600);

  BEGIN_uscite();
  BEGIN_ingressi();

  while (!Serial)
    ;

  Wire.begin(); //  20 , 21

  setPwmFrequency(MOT_PWM, 0x01);
  MOT.begin();
  ALZO.begin();

  //emergenze_begin();
  //check_emerg();

  ////////////////////////////////////////////////////////////////////////

  inputString.reserve(200); // reserve 200 bytes for the inputString

  Serial.println("");
  Serial.println("[SETUP] In attesa...");
}

void loop()
{
  serialEvent();
  if (stringComplete)
  {
    confronta_stringhe();
    //Serial.println("");
    //Serial.println("In attesa...");
    return;
  }

  /*if (Serial.available() > 0) {
    char receivedChar = (char)Serial.read();

    if (receivedChar == '1')        TEST_canbus();
    else if (receivedChar == '2')   TEST_i2c();
    else if (receivedChar == '3')   TEST_ingressi();
    else if (receivedChar == '4')   TEST_rele();
    else if (receivedChar == '5')   TEST_inv();
    else if (receivedChar == '6')   TEST_ssr();
    else if (receivedChar == '7')   TEST_trazione();
    else if (receivedChar == '8')   TEST_alzo();
    else if (receivedChar == '9')   TEST_fotocellule();
    else if (receivedChar == '10')  TEST_funghi();
    else {
      Serial.println("receivedChar:");
      Serial.println(receivedChar);
      if (receivedChar != '\n') {
        Serial.println();
        Serial.println("[\"1\",\"2\",\"3\",\"4\",\"5\",\"6\",\"7\",\"8\",\"9\",\"10\"]");
        Serial.println();
      }
    }
  }*/

}
