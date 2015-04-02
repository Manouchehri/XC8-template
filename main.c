/*
 * Author: David Manouchehri
 * License: See LICENSE.txt (BSD 4-clause)
 * Source: https://github.com/Manouchehri/
 * Purpose: 
 */

#include <xc.h>
#include <stdio.h>
#include <stdlib.h>
#include "config.h"
#include "pins.h"

void setupIO(void) {
        TRISD = 0xFE; /* Set output */
}
setPWM(unsigned int pin, unsigned int dutyCycle)
{
        switch(pin)
        {
                case 1:
                {
                        CCPR1L = dutyCycle>>2;
                        CCP1CON &= 0xCF;
                        CCP1CON |= (0x30&(dutyCycle<<4));
                        break;
                }
                case 2:
                {
                        CCPR2L = dutyCycle>>2;
                        CCP2CON &= 0xCF;
                        CCP2CON |= (0x30&(dutyCycle<<4));
                        break;
                }
        }
}
void initPWM(void)
{
        // Set up pins
        TRISC1 = 0;
        TRISC2 = 0;
        
        // Set up PWM mode
        CCP1CON = 0x1C;
        CCP2CON = 0x1C;

        PR2 = 0xFF; // Timer2 period
        T2CON = 0x04; // Prescaler to 1

        setPWM(1, 100);
        setPWM(2, 500);

        TMR2ON = 1; // Turn it on
}

void main(void) {
        setupIO();
        initPWM();
        while(1)
        {
                if(INPUT1)
                {
                        LED1 = !LED1;
                        while(INPUT1);
                }
        }
}

