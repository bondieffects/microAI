// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************
/* This section lists the other files that are included in this file.
*/
#include <peripheral/adc/adc.h>

// *****************************************************************************
// *****************************************************************************
// Section: Global Data
// *****************************************************************************
// *****************************************************************************

#define ADC_LINEARITY0_POS  (27U)
#define ADC_LINEARITY0_Msk   ((0x1FUL << ADC_LINEARITY0_POS))

#define ADC_LINEARITY1_POS  (0U)
#define ADC_LINEARITY1_Msk   ((0x7U << ADC_LINEARITY1_POS))

#define ADC_BIASCAL_POS  (3U)
#define ADC_BIASCAL_Msk   ((0x7U << ADC_BIASCAL_POS))

// *****************************************************************************
// *****************************************************************************
// Section: ADC Implementation
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************

/* Initialize ADC module */
void ADC_Initialise( void )
{
    // Disable the ADC (ADEN)
    ADCSRA &= ~(1 << ADEN);

    // Enable the ADC Conversion Complete interrupt (ADIE) and set the prescaler to 64 by default (ADPSx)
    ADCSRA |= (1 << ADIE) | (1 << ADPS1) | (1 << ADPS0);

    // Set reference to AVCC

    // Can reduce power consumption with (PRADC)

    //ADMUX set ref voltage anf analogue pin
    ADMUX = (1 << REFS0)
    ADMUX = (ADMUX & 0xF0) | (pin & 0x0F);

    //ADATE = auto trigger
    ADCSRA |= (1 << ADATE);
}

void ADC_Enable( void )
{
    ADCSRA |= (1 << ADEN);
}

void ADC_Disable( void )
{
    ADCSRA &= ~(1 << ADEN);
}


// ADMUX(MUX[x]) selects the input
void ADC_ChannelSelect( ADC_POSINPUT positiveInput, ADC_NEGINPUT negativeInput )
{

}

void ADC_ConversionStart( void )
{
    //Start ADC Conversion 
    ADCSRA |= (1 << ADSC);
}


uint16_t ADC_ConversionResultGet( void )
{
    return (uint16_t)ADC->RESULT.reg;
}

/* Read the conversion result */
uint16_t ADC_ConversionResultGet( void )
{
    // ADCH and ADCL
    
}

void ADC_InterruptsClear(ADC_STATUS interruptMask)
{
    ADC->INTFLAG.reg = interruptMask;
}

void ADC_InterruptsEnable(ADC_STATUS interruptMask)
{
    ADC->INTENSET.reg = interruptMask;
}

void ADC_InterruptsDisable(ADC_STATUS interruptMask)
{
    ADC->INTENCLR.reg = interruptMask;
}

// The ADC does not consume power when ADEN is cleared, so it is recommended to 
// switch off the ADC before entering power saving sleep modes
void ADC_EnterSleep ( void )
{
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