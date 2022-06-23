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

void Setup_ADC(void)
{
    Uint16 acqps;

    if(ADC_RESOLUTION_12BIT == AdcaRegs.ADCCTL2.bit.RESOLUTION)
        acqps = 14;
    else
        acqps = 63;

    EALLOW;                                  //Enable to edit
    CpuSysRegs.PCLKCR13.bit.ADC_A = 1;       //Enable ADC clock
    AdcaRegs.ADCCTL2.bit.PRESCALE = 6;       //Set ADCCLK divider to /4
    AdcSetMode(ADC_ADCA, ADC_RESOLUTION_12BIT, ADC_SIGNALMODE_SINGLE);
    AdcaRegs.ADCCTL1.bit.INTPULSEPOS = 1;    //Set oulso um ciclo antes do resultado
    AdcaRegs.ADCCTL1.bit.ADCPWDNZ = 1;       //Power up the ADC

    DELAY_US(1000);

    AdcaRegs.ADCSOC0CTL.bit.CHSEL = 3;        //
    AdcaRegs.ADCSOC0CTL.bit.ACQPS = acqps;
    AdcaRegs.ADCSOC0CTL.bit.TRIGSEL =

    AdcaRegs.ADCSOC1CTL.bit.CHSEL = 4;
    AdcaRegs.ADCSOC1CTL.bit.ACQPS = acqps;
    AdcaRegs.ADCSOC1CTL.bit.TRIGSEL =

    AdcaRegs.ADCINTSEL1N2.bit.INT1SEL = 0x01;  //End of SOC1 will set INT1 flag
    AdcaRegs.ADCINTSEL1N2.bit.INT1E = 1;       //enable INT1 flag
    AdcaRegs.ADCINTFLGCLR.bit.ADCINT1 = 1;     //make sure INT1 flag is clear

    EDIS;
}


