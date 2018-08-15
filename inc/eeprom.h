#ifndef EEPROM_H
#define	EEPROM_H

#include "mcc.h"

void EEPROM_Read(uint8_t *buf, uint8_t addr, uint8_t len);
void EEPROM_Write(uint8_t *buf, uint8_t addr, uint8_t len);

#endif	/* EEPROM_H */

