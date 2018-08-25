/**
  @Generated Pin Manager Header File

  @Company:
    Microchip Technology Inc.

  @File Name:
    pin_manager.h

  @Summary:
    This is the Pin Manager file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  @Description
    This header file provides APIs for driver for .
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.65.2
        Device            :  PIC18F14K50
        Driver Version    :  2.01
    The generated drivers are tested against the following:
        Compiler          :  XC8 1.45
        MPLAB 	          :  MPLAB X 4.15	
*/

/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
*/

#ifndef PIN_MANAGER_H
#define PIN_MANAGER_H

#define INPUT   1
#define OUTPUT  0

#define HIGH    1
#define LOW     0

#define ANALOG      1
#define DIGITAL     0

#define PULL_UP_ENABLED      1
#define PULL_UP_DISABLED     0

// get/set BTN_COL_1 aliases
#define BTN_COL_1_TRIS                 TRISBbits.TRISB4
#define BTN_COL_1_LAT                  LATBbits.LATB4
#define BTN_COL_1_PORT                 PORTBbits.RB4
#define BTN_COL_1_WPU                  WPUBbits.WPUB4
#define BTN_COL_1_ANS                  ANSELHbits.ANS10
#define BTN_COL_1_SetHigh()            do { LATBbits.LATB4 = 1; } while(0)
#define BTN_COL_1_SetLow()             do { LATBbits.LATB4 = 0; } while(0)
#define BTN_COL_1_Toggle()             do { LATBbits.LATB4 = ~LATBbits.LATB4; } while(0)
#define BTN_COL_1_GetValue()           PORTBbits.RB4
#define BTN_COL_1_SetDigitalInput()    do { TRISBbits.TRISB4 = 1; } while(0)
#define BTN_COL_1_SetDigitalOutput()   do { TRISBbits.TRISB4 = 0; } while(0)
#define BTN_COL_1_SetPullup()          do { WPUBbits.WPUB4 = 1; } while(0)
#define BTN_COL_1_ResetPullup()        do { WPUBbits.WPUB4 = 0; } while(0)
#define BTN_COL_1_SetAnalogMode()      do { ANSELHbits.ANS10 = 1; } while(0)
#define BTN_COL_1_SetDigitalMode()     do { ANSELHbits.ANS10 = 0; } while(0)

// get/set BTN_COL_2 aliases
#define BTN_COL_2_TRIS                 TRISBbits.TRISB5
#define BTN_COL_2_LAT                  LATBbits.LATB5
#define BTN_COL_2_PORT                 PORTBbits.RB5
#define BTN_COL_2_WPU                  WPUBbits.WPUB5
#define BTN_COL_2_ANS                  ANSELHbits.ANS11
#define BTN_COL_2_SetHigh()            do { LATBbits.LATB5 = 1; } while(0)
#define BTN_COL_2_SetLow()             do { LATBbits.LATB5 = 0; } while(0)
#define BTN_COL_2_Toggle()             do { LATBbits.LATB5 = ~LATBbits.LATB5; } while(0)
#define BTN_COL_2_GetValue()           PORTBbits.RB5
#define BTN_COL_2_SetDigitalInput()    do { TRISBbits.TRISB5 = 1; } while(0)
#define BTN_COL_2_SetDigitalOutput()   do { TRISBbits.TRISB5 = 0; } while(0)
#define BTN_COL_2_SetPullup()          do { WPUBbits.WPUB5 = 1; } while(0)
#define BTN_COL_2_ResetPullup()        do { WPUBbits.WPUB5 = 0; } while(0)
#define BTN_COL_2_SetAnalogMode()      do { ANSELHbits.ANS11 = 1; } while(0)
#define BTN_COL_2_SetDigitalMode()     do { ANSELHbits.ANS11 = 0; } while(0)

// get/set BTN_COL_3 aliases
#define BTN_COL_3_TRIS                 TRISBbits.TRISB6
#define BTN_COL_3_LAT                  LATBbits.LATB6
#define BTN_COL_3_PORT                 PORTBbits.RB6
#define BTN_COL_3_WPU                  WPUBbits.WPUB6
#define BTN_COL_3_SetHigh()            do { LATBbits.LATB6 = 1; } while(0)
#define BTN_COL_3_SetLow()             do { LATBbits.LATB6 = 0; } while(0)
#define BTN_COL_3_Toggle()             do { LATBbits.LATB6 = ~LATBbits.LATB6; } while(0)
#define BTN_COL_3_GetValue()           PORTBbits.RB6
#define BTN_COL_3_SetDigitalInput()    do { TRISBbits.TRISB6 = 1; } while(0)
#define BTN_COL_3_SetDigitalOutput()   do { TRISBbits.TRISB6 = 0; } while(0)
#define BTN_COL_3_SetPullup()          do { WPUBbits.WPUB6 = 1; } while(0)
#define BTN_COL_3_ResetPullup()        do { WPUBbits.WPUB6 = 0; } while(0)

// get/set BTN_ROW_1 aliases
#define BTN_ROW_1_TRIS                 TRISCbits.TRISC0
#define BTN_ROW_1_LAT                  LATCbits.LATC0
#define BTN_ROW_1_PORT                 PORTCbits.RC0
#define BTN_ROW_1_ANS                  ANSELbits.ANS4
#define BTN_ROW_1_SetHigh()            do { LATCbits.LATC0 = 1; } while(0)
#define BTN_ROW_1_SetLow()             do { LATCbits.LATC0 = 0; } while(0)
#define BTN_ROW_1_Toggle()             do { LATCbits.LATC0 = ~LATCbits.LATC0; } while(0)
#define BTN_ROW_1_GetValue()           PORTCbits.RC0
#define BTN_ROW_1_SetDigitalInput()    do { TRISCbits.TRISC0 = 1; } while(0)
#define BTN_ROW_1_SetDigitalOutput()   do { TRISCbits.TRISC0 = 0; } while(0)
#define BTN_ROW_1_SetAnalogMode()      do { ANSELbits.ANS4 = 1; } while(0)
#define BTN_ROW_1_SetDigitalMode()     do { ANSELbits.ANS4 = 0; } while(0)

// get/set BTN_ROW_2 aliases
#define BTN_ROW_2_TRIS                 TRISCbits.TRISC1
#define BTN_ROW_2_LAT                  LATCbits.LATC1
#define BTN_ROW_2_PORT                 PORTCbits.RC1
#define BTN_ROW_2_ANS                  ANSELbits.ANS5
#define BTN_ROW_2_SetHigh()            do { LATCbits.LATC1 = 1; } while(0)
#define BTN_ROW_2_SetLow()             do { LATCbits.LATC1 = 0; } while(0)
#define BTN_ROW_2_Toggle()             do { LATCbits.LATC1 = ~LATCbits.LATC1; } while(0)
#define BTN_ROW_2_GetValue()           PORTCbits.RC1
#define BTN_ROW_2_SetDigitalInput()    do { TRISCbits.TRISC1 = 1; } while(0)
#define BTN_ROW_2_SetDigitalOutput()   do { TRISCbits.TRISC1 = 0; } while(0)
#define BTN_ROW_2_SetAnalogMode()      do { ANSELbits.ANS5 = 1; } while(0)
#define BTN_ROW_2_SetDigitalMode()     do { ANSELbits.ANS5 = 0; } while(0)

// get/set BTN_ROW_3 aliases
#define BTN_ROW_3_TRIS                 TRISCbits.TRISC2
#define BTN_ROW_3_LAT                  LATCbits.LATC2
#define BTN_ROW_3_PORT                 PORTCbits.RC2
#define BTN_ROW_3_ANS                  ANSELbits.ANS6
#define BTN_ROW_3_SetHigh()            do { LATCbits.LATC2 = 1; } while(0)
#define BTN_ROW_3_SetLow()             do { LATCbits.LATC2 = 0; } while(0)
#define BTN_ROW_3_Toggle()             do { LATCbits.LATC2 = ~LATCbits.LATC2; } while(0)
#define BTN_ROW_3_GetValue()           PORTCbits.RC2
#define BTN_ROW_3_SetDigitalInput()    do { TRISCbits.TRISC2 = 1; } while(0)
#define BTN_ROW_3_SetDigitalOutput()   do { TRISCbits.TRISC2 = 0; } while(0)
#define BTN_ROW_3_SetAnalogMode()      do { ANSELbits.ANS6 = 1; } while(0)
#define BTN_ROW_3_SetDigitalMode()     do { ANSELbits.ANS6 = 0; } while(0)

// get/set PAGE_SEL_4 aliases
#define PAGE_SEL_4_TRIS                 TRISCbits.TRISC3
#define PAGE_SEL_4_LAT                  LATCbits.LATC3
#define PAGE_SEL_4_PORT                 PORTCbits.RC3
#define PAGE_SEL_4_ANS                  ANSELbits.ANS7
#define PAGE_SEL_4_SetHigh()            do { LATCbits.LATC3 = 1; } while(0)
#define PAGE_SEL_4_SetLow()             do { LATCbits.LATC3 = 0; } while(0)
#define PAGE_SEL_4_Toggle()             do { LATCbits.LATC3 = ~LATCbits.LATC3; } while(0)
#define PAGE_SEL_4_GetValue()           PORTCbits.RC3
#define PAGE_SEL_4_SetDigitalInput()    do { TRISCbits.TRISC3 = 1; } while(0)
#define PAGE_SEL_4_SetDigitalOutput()   do { TRISCbits.TRISC3 = 0; } while(0)
#define PAGE_SEL_4_SetAnalogMode()      do { ANSELbits.ANS7 = 1; } while(0)
#define PAGE_SEL_4_SetDigitalMode()     do { ANSELbits.ANS7 = 0; } while(0)

// get/set PAGE_SEL_3 aliases
#define PAGE_SEL_3_TRIS                 TRISCbits.TRISC4
#define PAGE_SEL_3_LAT                  LATCbits.LATC4
#define PAGE_SEL_3_PORT                 PORTCbits.RC4
#define PAGE_SEL_3_SetHigh()            do { LATCbits.LATC4 = 1; } while(0)
#define PAGE_SEL_3_SetLow()             do { LATCbits.LATC4 = 0; } while(0)
#define PAGE_SEL_3_Toggle()             do { LATCbits.LATC4 = ~LATCbits.LATC4; } while(0)
#define PAGE_SEL_3_GetValue()           PORTCbits.RC4
#define PAGE_SEL_3_SetDigitalInput()    do { TRISCbits.TRISC4 = 1; } while(0)
#define PAGE_SEL_3_SetDigitalOutput()   do { TRISCbits.TRISC4 = 0; } while(0)

// get/set PAGE_SEL_2 aliases
#define PAGE_SEL_2_TRIS                 TRISCbits.TRISC6
#define PAGE_SEL_2_LAT                  LATCbits.LATC6
#define PAGE_SEL_2_PORT                 PORTCbits.RC6
#define PAGE_SEL_2_ANS                  ANSELHbits.ANS8
#define PAGE_SEL_2_SetHigh()            do { LATCbits.LATC6 = 1; } while(0)
#define PAGE_SEL_2_SetLow()             do { LATCbits.LATC6 = 0; } while(0)
#define PAGE_SEL_2_Toggle()             do { LATCbits.LATC6 = ~LATCbits.LATC6; } while(0)
#define PAGE_SEL_2_GetValue()           PORTCbits.RC6
#define PAGE_SEL_2_SetDigitalInput()    do { TRISCbits.TRISC6 = 1; } while(0)
#define PAGE_SEL_2_SetDigitalOutput()   do { TRISCbits.TRISC6 = 0; } while(0)
#define PAGE_SEL_2_SetAnalogMode()      do { ANSELHbits.ANS8 = 1; } while(0)
#define PAGE_SEL_2_SetDigitalMode()     do { ANSELHbits.ANS8 = 0; } while(0)

// get/set PAGE_SEL_1 aliases
#define PAGE_SEL_1_TRIS                 TRISCbits.TRISC7
#define PAGE_SEL_1_LAT                  LATCbits.LATC7
#define PAGE_SEL_1_PORT                 PORTCbits.RC7
#define PAGE_SEL_1_ANS                  ANSELHbits.ANS9
#define PAGE_SEL_1_SetHigh()            do { LATCbits.LATC7 = 1; } while(0)
#define PAGE_SEL_1_SetLow()             do { LATCbits.LATC7 = 0; } while(0)
#define PAGE_SEL_1_Toggle()             do { LATCbits.LATC7 = ~LATCbits.LATC7; } while(0)
#define PAGE_SEL_1_GetValue()           PORTCbits.RC7
#define PAGE_SEL_1_SetDigitalInput()    do { TRISCbits.TRISC7 = 1; } while(0)
#define PAGE_SEL_1_SetDigitalOutput()   do { TRISCbits.TRISC7 = 0; } while(0)
#define PAGE_SEL_1_SetAnalogMode()      do { ANSELHbits.ANS9 = 1; } while(0)
#define PAGE_SEL_1_SetDigitalMode()     do { ANSELHbits.ANS9 = 0; } while(0)

void PIN_MANAGER_Initialize(void);

#endif // PIN_MANAGER_H
