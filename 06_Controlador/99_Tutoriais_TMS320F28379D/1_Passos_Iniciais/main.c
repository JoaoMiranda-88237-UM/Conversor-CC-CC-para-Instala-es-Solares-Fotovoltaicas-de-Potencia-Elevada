#include "Peripheral_Setup.h"

/**
 * main.c
 */
uint32_t count = 0;
int main(void)
{
    InitSysCtrl();                      // Initialize System Control [with some clocks] -> CPU1 | _LAUNCHXL_F28379D;
    DINT;                               // Disable CPU interrupts
    InitPieCtrl();                      // Initialize the PIE (peripherals) control registers to their default state
    IER = 0x0000;                       // Disable CPU interrupts
    IFR = 0x0000;                       // Clear all CPU interrupt flags
    InitPieVectTable();                 // Initialize the PIE (peripherals) vector table [interrupts table]

    Setup_GPIO();

    EINT;                               // Enable Global interrupt INTM
    ERTM;                               // Enable Global realtime interrupt DBGM

    GpioDataRegs.GPBDAT.bit.GPIO34 = 1; // Write on Pin - LED BLUE -> DISABLE
    GpioDataRegs.GPADAT.bit.GPIO31 = 1; // Write on Pin - LED RED -> DISABLE
    while(1){
        for(count = 0; count < 0x000FFFFF; count++);
        GpioDataRegs.GPBTOGGLE.bit.GPIO34 = 1;  // Toggle pin
        GpioDataRegs.GPATOGGLE.bit.GPIO31 = 1;  // Toggle pin
    }
	return 0;
}
