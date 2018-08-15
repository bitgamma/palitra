#ifndef APP_PAGE_SELECTOR_H
#define	APP_PAGE_SELECTOR_H

#include "mcc.h"

#define APP_PAGE_COUNT 4

uint8_t APP_PageSelectorGetIndex();
void APP_PageSelectorUpdate(void);
void APP_PageSelectorInit(void);

#endif	/* APP_PAGE_SELECTOR_H */

