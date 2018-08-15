#include "eeprom.h"

void EEPROM_Read(uint8_t *buf, uint8_t addr, uint8_t len) {
  for (uint8_t i = 0; i < len; i++) {
    EEADR = addr++;
    EECON1bits.EEPGD = 0;
    EECON1bits.CFGS = 0;
	EECON1bits.RD = 1;
    buf[i] = EEDATA;
  }
}

void EEPROM_Write(uint8_t *buf, uint8_t addr, uint8_t len) {
  for (uint8_t i = 0; i < len; i++) {
	EEADR = addr++;
    EECON1bits.EEPGD = 0;
    EECON1bits.CFGS = 0;
	EEDATA = buf[i];
	EECON1bits.WREN = 1;
    EECON2 = 0x55;
    EECON2 = 0xAA;
	EECON1bits.WR = 1;
	while(EECON1bits.WR);
	EECON1bits.WREN = 0;
  }
}
