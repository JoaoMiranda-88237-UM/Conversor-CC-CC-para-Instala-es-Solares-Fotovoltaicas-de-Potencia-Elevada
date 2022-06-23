/*
 * Peripheral_Setup.c
 *
 *  Created on: 27/02/2022
 *      Author: JoaoMiranda
 */

#include "Peripheral_Setup.h"

/**< F2837xD GPIO Pin Registers
 * GPxDIR -> [0 - Input | 1 - Output]
 * GPxPUD -> [0 - Internal Pull-Up enable | 1 - Internal Pull-Up disable]
 * GPxODR -> [0 - Normal | 1 - Open Drain]
 * GPxMUX -> Define if that pin will be used to GPIO or to (ex: PWM / Serial Pin) -> [tms320f28379d.pdf [49/229]]
 * GPxCSEL -> Define which CPU will be used
 * */
void Setup_GPIO(void)
{
   EALLOW;                                  //Enable to edit
   GpioCtrlRegs.GPAPUD.bit.GPIO2 = 1;       //Disable pull-up on GPIO2 (EPWM2A)
   GpioCtrlRegs.GPAPUD.bit.GPIO3 = 1;       //Disable pull-up on GPIO3 (EPWM2B)
   GpioCtrlRegs.GPAMUX1.bit.GPIO2 = 1;      //Configure GPIO2 as EPWM2A
   GpioCtrlRegs.GPAMUX1.bit.GPIO3 = 1;      //Configure GPIO3 as EPWM2B

   //Configure GPIO as output pin
   GpioCtrlRegs.GPAMUX1.bit.GPIO0 = 0;      //Pin configured as GPIO0
   GpioCtrlRegs.GPADIR.bit.GPIO0 = 1;       //Configure GPIO0 as output pin
   GpioCtrlRegs.GPAMUX1.bit.GPIO1 = 0;      //Pin configured as GPIO1
   GpioCtrlRegs.GPADIR.bit.GPIO1 = 1;       //Configure GPIO1 as output pin
   GpioCtrlRegs.GPACSEL1.bit.GPIO1 = GPIO_MUX_CPU2;     //GPIO1 is controlled by CPU2 (used in Lab 11)

   GpioCtrlRegs.GPAMUX2.bit.GPIO31 = 0;     //LED BLUE
   GpioCtrlRegs.GPADIR.bit.GPIO31 = 1;
   GpioCtrlRegs.GPBMUX1.bit.GPIO34 = 0;     //LED RED
   GpioCtrlRegs.GPBDIR.bit.GPIO34 = 1;
   EDIS;                                    //Disable to edit
}


