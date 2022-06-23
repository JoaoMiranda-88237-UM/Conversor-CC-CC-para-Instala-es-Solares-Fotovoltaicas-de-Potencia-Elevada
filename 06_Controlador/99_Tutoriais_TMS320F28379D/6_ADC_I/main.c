#include "Peripheral_Setup.h"

/**
 * main.c
 */
uint32_t count = 0;

__interrupt void isr_cpu_timer0(void);

int main(void)
{
    /**< Initialize System Control [with some clocks] -> CPU1 | _LAUNCHXL_F28379D;
     * Configure Clock [CLKIN is a 10 MHz]
     * After Clock is defined as 10MHz * 40 / 2 = 200 MHz */
    InitSysCtrl();
    DINT;                               // Disable CPU interrupts (INTM)
    InitPieCtrl();                      // Initialize the PIE (peripherals) control registers to their default state [Clear all interrupt vector]
    IER = 0x0000;                       // Disable CPU interrupts
    IFR = 0x0000;                       // Clear all CPU interrupt flags
    /**< Initialize the PIE (peripherals) vector table [interrupts table [12 lines and each line with 16 colums]]
     * 12 interrupts
     * 16 peripherals
     * Peripheral Interrupts = 12*16 = 192
     *  */
    InitPieVectTable();

    Setup_GPIO();

    EALLOW;
    PieVectTable.TIMER0_INT = &isr_cpu_timer0;      //Mapping function to access this function when timing trigger
    PieCtrlRegs.PIEIER1.bit.INTx7 = 1;              //Enable Column 7 - line 1 [TINT0 - Timer0 interrupt]
    EDIS;
    IER |= M_INT1;                                  //Enable interrupt on line 1
    //{In case of add other interrupt on line 2 -> IER |= M_INT1 | M_INT2;}

    InitCpuTimers();                                //This function initializes all three CPU timers to a known state [fclock = 200 MHz]
    ConfigCpuTimer(&CpuTimer0, 200, 500000);        //The "Freq" is entered as "MHz" and the period in "uSeconds". The period is time at time to trigger
    CpuTimer0Regs.TCR.all = 0x4001;                 //Enable TIE [Time interrupt enable] {0100 0000 0000 0001 = 0x4001}
    //or CpuTimer0Regs.TCR.bit.TIE = 1;

    EINT;                               // Enable Global interrupt INTM
    ERTM;                               // Enable Global real time interrupt DBGM (Debug)

    GpioDataRegs.GPBDAT.bit.GPIO34 = 1; // Write on Pin - LED BLUE -> DISABLE
    GpioDataRegs.GPADAT.bit.GPIO31 = 0; // Write on Pin - LED RED -> Enable
    while(1){
        for(count = 0; count < 0x000FFFFF; count++);
        GpioDataRegs.GPBTOGGLE.bit.GPIO34 = 1;  // Toggle pin
    }
	return 0;
}

__interrupt void isr_cpu_timer0(void){
    GpioDataRegs.GPATOGGLE.bit.GPIO31 = 1;      // Toggle pin
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;     // Acknowledge -> Clear flag of interrupt
}
