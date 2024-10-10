#ifndef _DRIVER_ADC_H
    #define _DRIVER_ADC_H

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************
/* This section lists the other files that are included in this file.
*/

#include <avr/io.h>
#include <avr/sleep.h>
#include <avr/interrupt.h>

#ifdef __cplusplus // Provide C Compatibility

    extern "C" {

#endif

// *****************************************************************************
// *****************************************************************************
// Section: Interface Routines
// *****************************************************************************
// *****************************************************************************
/* The following functions make up the methods (set of possible operations) of
    this interface.
*/

enum Prescalers {
    PRESCALER_64,
    PRESCALER_256,
};

void ADC_Initialise( void );

void ADC_Enable( void );

void ADC_Disable( void );

void ADC_ChannelSelect( uint8_t positiveInput, uint8_t negativeInput );

void ADC_ConversionStart( void );

uint16_t ADC_ConversionResultGet( void );

void ADC_EnterSleep( void );

void ADC_Awake( void );

void ADC_SetPrescaler(uint8_t prescaler) 
{
    switch (prescaler) {
        case PRESCALER_64:
            // set registers for a prescaler of 64
            ADCSRA |= (1 << ADIE) | (1 << ADPS1) | (1 << ADPS0);
            break;
        case PRESCALER_256:
            //
            break;
    }
}


#ifdef __cplusplus  // Provide C++ Compatibility

    }

#endif

#endif // _DRIVER_ADC_H