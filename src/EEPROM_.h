#ifndef EEPROM__H
#define EEPROM__H

#include <Arduino.h>
#include <EEPROM.h>

#define maxMemory 1024  // Assumendo una EEPROM da 1024 byte

/*
#define disk1         0x50

// celle libere tra 0x0A e 0xff
#define EEP_MOT_MAX_CURR 0x10 // 2 byte
#define EEP_ALZO_MAX_CURR 0x12  // 2 byte

#define EEP_MILLIMETRI 0x14 // 4 byte
#define EEP_MMXSTEP 0x18 // 4 byte

#define EEP_MOT_ON_TIME 0x1C // 4 byte

#define EEP_ALZO_CICLI 0x20 // 4 byte

#define EEP_OPTIONAL 0x24 // 1 byte

#define EEP_MOT_MAX_TEMP 0x25 // 1 byte
#define EEP_ALZO_MAX_TEMP 0x26 // 1 byte


#define EEP_ALZO_AUTO_SPEEDS 0x28 // 4 byte ciascuno
*/

void TEST_eeprom();
bool writeEEPROMString(int address, const char* data);
String readEEPROMString(int address, bool* success = nullptr);
bool clearEEPROMString(int address);

#endif