// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************
/* This section lists the other files that are included in this file.
*/
#include <peripheral/adc.h>

// *****************************************************************************
// *****************************************************************************
// Section: Global Data
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
// *****************************************************************************
// Section: ADC Implementation
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************

/* Initialise ADC module */
void ADC_Initialise( void )
{
    // Disable the ADC (ADEN)
    ADCSRA &= ~(1 << ADEN);

    // Enable the ADC Conversion Complete interrupt (ADIE) and set the prescaler to 64 by default (ADPSx)
    ADCSRA |= (1 << ADIE) | (1 << ADPS1) | (1 << ADPS0);

    // Set reference to AVCC

    // Can reduce power consumption with (PRADC)
    PRR &= ~(1 << PRADC);
    //ADMUX set ref voltage anf analogue pin
    ADMUX = (1 << REFS0);
    ADMUX = (ADMUX & 0xF0) | ( 0x00 & 0x0F);

    //ADATE = auto trigger
    ADCSRA |= (1 << ADATE);

    // Enable after ADC is initialised
    ADCSRA |= (1 << ADEN);  // set the ADEN bit
}

void ADC_Enable( void )
{
    ADCSRA |= (1 << ADEN);  // set the ADEN bit
}

void ADC_Disable( void )
{
    ADCSRA &= ~(1 << ADEN); // clear the ADEN bit
}


// ADMUX(MUX[x]) selects the input
void ADC_ChannelSelect( uint8_t positiveInput, uint8_t negativeInput )
{

}

void ADC_ConversionStart( void )
{
    //Start ADC Conversion 
    ADCSRA |= (1 << ADSC);
}

/* Read the conversion result */
uint16_t ADC_ConversionResultGet( void )
{
    // ADCH and ADCL
    uint16_t result = (ADC << 8) | ADCL;
    return result;
}

void ADC_InterruptsClear(uint8_t interruptMask)
{
    // clear the interrupt flag
}

void ADC_InterruptsEnable(uint8_t interruptMask)
{
    // enable interrupts
}

void ADC_InterruptsDisable(uint8_t interruptMask)
{
    // disable interrupts
}

// The ADC does not consume power when ADEN is cleared, so it is recommended to 
// switch off the ADC before entering power saving sleep modes
void ADC_EnterSleep ( void )
{
    ADCSRA &= ~(1 << ADEN); // clear the ADEN bit

    //Sleep mode for noise reduction 
    set_sleep_mode(SLEEP_MODE_ADC);
    sleep_enable();
}

void ADC_Awake( void )
{
    //Enter sleep mode during convert
    sleep_cpu();
    //wake up after compete
    sleep_disable();
}