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
#include <Arduino.h>

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

// Sample Rate ≈ (FCPU / PRESCALER) / 13 ≈ 9,615 samples per second (Hz).
// ADC conversion takes 13 clock cycles
enum Prescalers {
    PRESCALER_2,        // Sample Rate: 615385 Hz
    PRESCALER_4,        // Sample Rate: 307692 Hz
    PRESCALER_8,        // Sample Rate: 153846 Hz
    PRESCALER_16,       // Sample Rate: 76923 Hz
    PRESCALER_32,       // Sample Rate: 38462 Hz
    PRESCALER_64,       // Sample Rate: 19231 Hz
    PRESCALER_128,      // Sample Rate: 9615 Hz
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

void ADC_SetPrescaler(uint8_t prescaler) 
{
    switch (prescaler) {
        
    
        case PRESCALER_2:
        ADCSRA &= ~((1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0));
        break;
        case PRESCALER_4:
            ADCSRA |=  (1 << ADPS1) ;
            ADCSRA &= ~((1 << ADPS2) | (1 << ADPS0));
        break;
        case PRESCALER_8:
            ADCSRA |=  (1 << ADPS1) | (1 << ADPS0);
            ADCSRA &= ~(1 << ADPS2);
        break;
        case PRESCALER_16:
            ADCSRA |= (1 << ADPS2);
            ADCSRA &= ~((1 << ADPS1) |(1 << ADPS0));
            break;
        case PRESCALER_32:
            ADCSRA |= (1 << ADPS2) | (1 << ADPS0);  // set bits 2 and 0
            ADCSRA &= ~(1 << ADPS1);                // clear bit 1
            break;
        case PRESCALER_64:
            // set registers for a prescaler of 64
            ADCSRA |= (1 << ADPS2) | (1 << ADPS1);
            ADCSRA &= ~(1 << ADPS0);
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