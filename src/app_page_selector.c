#include "app_page_selector.h"

static uint8_t pageIndex;
static bool waitsKeyRelease;

inline uint8_t APP_PageSelectorGetIndex() {
    return pageIndex;
}

static void APP_PageSelectorNext(void) {
    switch (pageIndex) {
        case 0:
            pageIndex = 1;
            LED_1_SetLow();
            LED_2_SetHigh();
            break;
        case 1:
            pageIndex = 2;
            LED_2_SetLow();
            LED_3_SetHigh();
            break;
        case 2:
            pageIndex = 3;
            LED_3_SetLow();
            LED_4_SetHigh();
            break;
        case 3:
            pageIndex = 0;
            LED_4_SetLow();
            LED_1_SetHigh();
            break;
    }
}
void APP_PageSelectorUpdate(void) {
    if (!SWT_IN_GetValue()) {
        if (!waitsKeyRelease) {
            APP_PageSelectorNext();
            waitsKeyRelease = true;
        }
    } else {
        waitsKeyRelease = false;
    }
}

void APP_PageSelectorInit(void) {
    pageIndex = 0;
    waitsKeyRelease = false;
    LED_1_SetHigh();
}

