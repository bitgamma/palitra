#include "app_page_selector.h"

static uint8_t pageIndex;
static bool waitsKeyRelease;

inline uint8_t APP_PageSelectorGetIndex() {
    return pageIndex;
}

static void APP_PageSelectorMakeInput(void) {
    switch (pageIndex) {
        case 0:
            PAGE_SEL_1_SetDigitalInput();
            break;
        case 1:
            PAGE_SEL_2_SetDigitalInput();
            break;
        case 2:
            PAGE_SEL_3_SetDigitalInput();
            break;
        case 3:
            PAGE_SEL_4_SetDigitalInput();
            break;
    }
}

void APP_PageSelectorUpdate(void) {
    if (pageIndex != 0 && !PAGE_SEL_1_GetValue()) {
        APP_PageSelectorMakeInput();
        pageIndex = 0;
        PAGE_SEL_1_SetDigitalOutput();
    } else if (pageIndex != 1 && !PAGE_SEL_2_GetValue()) {
        APP_PageSelectorMakeInput();
        pageIndex = 1;
        PAGE_SEL_2_SetDigitalOutput();        
    } else if (pageIndex != 2 && !PAGE_SEL_3_GetValue()) {
        APP_PageSelectorMakeInput();
        pageIndex = 2;
        PAGE_SEL_3_SetDigitalOutput();               
    } else if (pageIndex != 3 && !PAGE_SEL_4_GetValue()) {
        APP_PageSelectorMakeInput();
        pageIndex = 3;
        PAGE_SEL_4_SetDigitalOutput();
    }
}

void APP_PageSelectorInit(void) {
    pageIndex = 0;
    PAGE_SEL_1_SetDigitalOutput();
}
