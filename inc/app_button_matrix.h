#ifndef APP_BUTTON_MATRIX_H
#define	APP_BUTTON_MATRIX_H

#include "mcc.h"

#define APP_BUTTON_MATRIX_SIZE 9

int8_t APP_ButtonMatrixGetIndex();
void APP_ButtonMatrixScan(void);
void APP_ButtonMatrixInit(void);

#endif	/* APP_BUTTON_MATRIX_H */

