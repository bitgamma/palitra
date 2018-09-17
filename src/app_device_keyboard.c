/*******************************************************************************
Copyright 2016 Microchip Technology Inc. (www.microchip.com)

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.

To request to license the code under the MLA license (www.microchip.com/mla_license), 
please contact mla_licensing@microchip.com
*******************************************************************************/

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************
#include <stdint.h>
#include <string.h>

#include "mcc.h"

#include "usb.h"
#include "usb_device_hid.h"

#include "app_button_matrix.h"
#include "app_page_selector.h"

#include "eeprom.h"

#define HID_REPORT_KEYBOARD 1
#define HID_REPORT_CONFIG 2

#define HID_CMD_READ 0
#define HID_CMD_WRITE 1
#define HID_CMD_BOOTLOADER 2
#define HID_CMD_VERSION 3

#define HID_CMD_BOOTLOADER_KEY1 0xB0 
#define HID_CMD_BOOTLOADER_KEY2 0x07
#define BOOTLOADER_ADDRESS 0x1C

#define APP_KEYBOARD_VALIDATE_ADDR(p, k) ((p < APP_PAGE_COUNT) && (k < APP_BUTTON_MATRIX_SIZE))
#define APP_KEYBOARD_VALIDATE_ABS_ADDR(p, k) ((uint8_t)((p * APP_BUTTON_MATRIX_SIZE * 7) + (k * 7)))

/* This creates a storage type for all of the information required to track the
 * current state of the keyboard. */
typedef struct
{
    USB_HANDLE lastINTransmission;
    USB_HANDLE lastOUTTransmission;
    int8_t oldKeyIndex;
    int8_t keyIndex;
    uint8_t pendingConfigResponseSize;
} KEYBOARD;

// *****************************************************************************
// *****************************************************************************
// Section: File Scope or Global Variables
// *****************************************************************************
// *****************************************************************************
static KEYBOARD keyboard;

static uint8_t inputReport[HID_INT_IN_EP_SIZE] KEYBOARD_INPUT_REPORT_DATA_BUFFER_ADDRESS_TAG;
static volatile uint8_t outputReport[HID_INT_OUT_EP_SIZE] KEYBOARD_OUTPUT_REPORT_DATA_BUFFER_ADDRESS_TAG;

static uint8_t cmdResponse[HID_INT_IN_EP_SIZE-1];

// *****************************************************************************
// *****************************************************************************
// Section: Private Prototypes
// *****************************************************************************
// *****************************************************************************
static void APP_KeyboardProcessOutputReport(void);

//Exteranl variables declared in other .c files
extern volatile signed int SOFCounter;

//Application variables that need wide scope
signed int keyboardIdleRate;
signed int LocalSOFCount;
static signed int OldSOFCount;

// *****************************************************************************
// *****************************************************************************
// Section: Macros or Functions
// *****************************************************************************
// *****************************************************************************

static inline void APP_KeyboardReadShortcut(uint8_t page, uint8_t idx, uint8_t* output) {
    EEPROM_Read(output, APP_KEYBOARD_VALIDATE_ABS_ADDR(page, idx), 7);    
}

static inline void APP_KeyboardWriteShortcut(uint8_t page, uint8_t idx, uint8_t* input) {
    EEPROM_Write(input, APP_KEYBOARD_VALIDATE_ABS_ADDR(page, idx), 7);    
}

static void APP_KeyboardUpdateInputReport() {
    inputReport[0] = HID_REPORT_KEYBOARD;
    
    if (keyboard.keyIndex < 0) {
        for(uint8_t i = 1; i < sizeof(inputReport); i++) inputReport[i] = 0;
    } else {
        APP_KeyboardReadShortcut(APP_PageSelectorGetIndex(), (uint8_t)keyboard.keyIndex, &inputReport[2]);
        inputReport[1] = inputReport[2]; inputReport[2] = 0x00;
    }    
}

void APP_KeyboardInit(void)
{
    //initialize the variable holding the handle for the last
    // transmission
    keyboard.lastINTransmission = 0;
    
    keyboard.keyIndex = -1;
    keyboard.oldKeyIndex = -1;
    
    keyboard.pendingConfigResponseSize = 0;

    //Set the default idle rate to 500ms (until the host sends a SET_IDLE request to change it to a new value)
    keyboardIdleRate = 500;

    //Copy the (possibly) interrupt context SOFCounter value into a local variable.
    //Using a while() loop to do this since the SOFCounter isn't necessarily atomically
    //updated and therefore we need to read it a minimum of twice to ensure we captured the correct value.
    while(OldSOFCount != SOFCounter)
    {
        OldSOFCount = SOFCounter;
    }

    //enable the HID endpoint
    USBEnableEndpoint(HID_EP, USB_IN_ENABLED|USB_OUT_ENABLED|USB_HANDSHAKE_ENABLED|USB_DISALLOW_SETUP);

    //Arm OUT endpoint so we can receive caps lock, num lock, etc. info from host
    keyboard.lastOUTTransmission = HIDRxPacket(HID_EP, (uint8_t *)outputReport, sizeof(outputReport) );
}

void APP_KeyboardCheckPress(signed int TimeDeltaMilliseconds) {
    bool needToSendNewReportPacket;

    keyboard.keyIndex = APP_ButtonMatrixGetIndex();

    //Check to see if the new packet contents are somehow different from the most
    //recently sent packet contents.
    needToSendNewReportPacket = (bool) (keyboard.keyIndex != keyboard.oldKeyIndex);

    //Check if the host has set the idle rate to something other than 0 (which is effectively "infinite").
    //If the idle rate is non-infinite, check to see if enough time has elapsed since
    //the last packet was sent, and it is time to send a new repeated packet or not.
    if(keyboardIdleRate != 0)
    {
        //Check if the idle rate time limit is met.  If so, need to send another HID input report packet to the host
        if(TimeDeltaMilliseconds >= keyboardIdleRate)
        {
            needToSendNewReportPacket = true;
        }
    }

    //Now send the new input report packet, if it is appropriate to do so (ex: new data is
    //present or the idle rate limit was met).
    if(needToSendNewReportPacket == true)
    {
        //Save the old input report packet contents.  We do this so we can detect changes in report packet content
        //useful for determining when something has changed and needs to get re-sent to the host when using
        //infinite idle rate setting.
        keyboard.oldKeyIndex = keyboard.keyIndex;

        APP_KeyboardUpdateInputReport();

        /* Send the 9 byte packet over USB to the host. */
        keyboard.lastINTransmission = HIDTxPacket(HID_EP, inputReport, 9);
        OldSOFCount = LocalSOFCount;    //Save the current time, so we know when to send the next packet (which depends in part on the idle rate setting)
    }    
}

void APP_KeyboardTasks(void)
{
    signed int TimeDeltaMilliseconds;

    /* If the USB device isn't configured yet, we can't really do anything
     * else since we don't have a host to talk to.  So jump back to the
     * top of the while loop. */
    if( USBGetDeviceState() < CONFIGURED_STATE )
    {
        return;
    }

    /* If we are currently suspended, then we need to see if we need to
     * issue a remote wakeup.  In either case, we shouldn't process any
     * keyboard commands since we aren't currently communicating to the host
     * thus just continue back to the start of the while loop. */
    if( USBIsDeviceSuspended() == true )
    {
        return;
    }
    
    //Copy the (possibly) interrupt context SOFCounter value into a local variable.
    //Using a while() loop to do this since the SOFCounter isn't necessarily atomically
    //updated and we need to read it a minimum of twice to ensure we captured the correct value.
    while(LocalSOFCount != SOFCounter)
    {
        LocalSOFCount = SOFCounter;
    }

    //Compute the elapsed time since the last input report was sent (we need
    //this info for properly obeying the HID idle rate set by the host).
    TimeDeltaMilliseconds = LocalSOFCount - OldSOFCount;
    //Check for negative value due to count wraparound back to zero.
    if(TimeDeltaMilliseconds < 0)
    {
        TimeDeltaMilliseconds = (32767 - OldSOFCount) + LocalSOFCount;
    }
    //Check if the TimeDelay is quite large.  If the idle rate is == 0 (which represents "infinity"),
    //then the TimeDeltaMilliseconds could also become infinity (which would cause overflow)
    //if there is no recent button presses or other changes occurring on the keyboard.
    //Therefore, saturate the TimeDeltaMilliseconds if it gets too large, by virtue
    //of updating the OldSOFCount, even if we haven't actually sent a packet recently.
    if(TimeDeltaMilliseconds > 5000)
    {
        OldSOFCount = LocalSOFCount - 5000;
    }

    /* Check if the IN endpoint is busy, and if it isn't check if we want to send
     * keystroke data to the host. */
    if(HIDTxHandleBusy(keyboard.lastINTransmission) == false)
    {
        if (keyboard.pendingConfigResponseSize > 0) {
            inputReport[0] = HID_REPORT_CONFIG;
            memcpy(&inputReport[1], cmdResponse, keyboard.pendingConfigResponseSize);
            keyboard.lastINTransmission = HIDTxPacket(HID_EP, inputReport, 11);
            keyboard.pendingConfigResponseSize = 0;
        } else {
            APP_KeyboardCheckPress(TimeDeltaMilliseconds);
        }
    }

    if(HIDRxHandleBusy(keyboard.lastOUTTransmission) == false)
    {
        APP_KeyboardProcessOutputReport();
        keyboard.lastOUTTransmission = HIDRxPacket(HID_EP, (uint8_t *)outputReport, sizeof(outputReport));
    }
    
    return;		
}

static void APP_KeyboardProcessOutputReport(void)
{
    if(outputReport[0] == HID_REPORT_CONFIG) {
        switch (outputReport[1]) {
            case HID_CMD_READ:
                if(APP_KEYBOARD_VALIDATE_ADDR(outputReport[2], outputReport[3])) {
                  memcpy(cmdResponse, &outputReport[1], 3);
                  APP_KeyboardReadShortcut(outputReport[2], outputReport[3], &cmdResponse[3]);
                  keyboard.pendingConfigResponseSize = 10;
                }
                break;
            case HID_CMD_WRITE:
                if(APP_KEYBOARD_VALIDATE_ADDR(outputReport[2], outputReport[3])) {
                  APP_KeyboardWriteShortcut(outputReport[2], outputReport[3], (uint8_t*)&outputReport[4]);
                }                
                break;
            case HID_CMD_BOOTLOADER:
                if (outputReport[2] == HID_CMD_BOOTLOADER_KEY1 && outputReport[3] == HID_CMD_BOOTLOADER_KEY2){
                    PIN_MANAGER_Initialize();
                    #asm
                        goto BOOTLOADER_ADDRESS;
                    #endasm
                }
                break;
            case HID_CMD_VERSION:
                cmdResponse[0] = HID_CMD_VERSION;
                cmdResponse[1] = (APP_FIRMWARE_VERSION >> 8) & 0xff;
                cmdResponse[2] = APP_FIRMWARE_VERSION & 0xff;
                keyboard.pendingConfigResponseSize = 3;
                break;                
        }
    }
}

static void USBHIDCBSetReportComplete(void)
{
    memcpy(outputReport, CtrlTrfData, sizeof(outputReport));
    APP_KeyboardProcessOutputReport();
}

void USBHIDCBSetReportHandler(void)
{
    /* Prepare to receive the keyboard LED state data through a SET_REPORT
     * control transfer on endpoint 0.  The host should only send 1 byte,
     * since this is all that the report descriptor allows it to send. */
    USBEP0Receive((uint8_t*)CtrlTrfData, sizeof(outputReport), USBHIDCBSetReportComplete);
}


//Callback function called by the USB stack, whenever the host sends a new SET_IDLE
//command.
void USBHIDCBSetIdleRateHandler(uint8_t reportID, uint8_t newIdleRate)
{
    //Make sure the report ID matches the keyboard input report id number.
    //If however the firmware doesn't implement/use report ID numbers,
    //then it should be == 0.
    if(reportID == 1)
    {
        keyboardIdleRate = newIdleRate;
    }
}
