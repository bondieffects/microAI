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
    PRESCALER_2,
    PRESCALER_4,
    PRESCALER_8,
    PRESCALER_16,
    PRESCALER_32,
    PRESCALER_64,
    PRESCALER_128,
};

void ADC_Initialise( void );

void ADC_Enable( void );

void ADC_Disable( void );

void ADC_ChannelSelect( uint8_t positiveInput, uint8_t negativeInput );

void ADC_ConversionStart( void );

uint16_t ADC_ConversionResultGet( void );

void ADC_InterruptsClear(uint8_t interruptMask);

void ADC_InterruptsEnable(uint8_t interruptMask);

void ADC_InterruptsDisable(uint8_t interruptMask);

void ADC_EnterSleep( void );

void ADC_Awake( void );



void ADC_SetPrescaler(uint8_t prescaler) 
{
    switch (prescaler) {
        ADCSRA &= ~((1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0));
        
        case PRESCALER_2;

        break;
            case PRESCALER_4:   
            ADCSRA |=  (1 << ADPS1) ;
        break;
            case PRESCALER_8:
            ADSCRA |=  (1 << ADPS1) | (1 << ADPS0);
        break;
        case PRESCALER_16:
            ADCSRA |= (1 << ADPS2);
            break;
        case PRESCALER_32:  
            ADCSRA |= (1 << ADPS2) | (1 << ADPS0);
            break;
        case PRESCALER_64:
            // set registers for a prescaler of 64
            ADCSRA |= (1 << ADPS2) | (1 << ADPS1);
            break;
        case PRESCALER_128:
            //
            ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
            break;
    }
}


#ifdef __cplusplus  // Provide C++ Compatibility

    }

#endif

#endif // _DRIVER_ADC_H