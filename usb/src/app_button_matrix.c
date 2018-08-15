#include "app_button_matrix.h"

static int8_t keyIndex;

int8_t APP_ButtonMatrixGetIndex() {
    return keyIndex;
}

void APP_ButtonMatrixScan(void) {
    keyIndex = -1;
    
    BTN_ROW_1_SetLow();
    BTN_COL_1_GetValue(); // wait for row to transition to low
    
    if (!BTN_COL_1_GetValue()) {
        keyIndex = 0;
    } else if (!BTN_COL_2_GetValue()) {
        keyIndex = 1;
    } else if (!BTN_COL_3_GetValue()) {
        keyIndex = 2;
    }
    
    BTN_ROW_1_SetHigh();
    
    if (keyIndex != -1) return;
    
    BTN_ROW_2_SetLow();
    BTN_COL_1_GetValue(); // wait for row to transition to low
    
    if (!BTN_COL_1_GetValue()) {
        keyIndex = 3;
    } else if (!BTN_COL_2_GetValue()) {
        keyIndex = 4;
    } else if (!BTN_COL_3_GetValue()) {
        keyIndex = 5;
    }
    
    BTN_ROW_2_SetHigh();
    if (keyIndex != -1) return; 
    
    BTN_ROW_3_SetLow();
    BTN_COL_1_GetValue(); // wait for row to transition to low
    
    if (!BTN_COL_1_GetValue()) {
        keyIndex = 6;
    } else if (!BTN_COL_2_GetValue()) {
        keyIndex = 7;
    } else if (!BTN_COL_3_GetValue()) {
        keyIndex = 8;
    }
    
    BTN_ROW_3_SetHigh();
}

void APP_ButtonMatrixInit(void) {
    keyIndex = -1;
}
