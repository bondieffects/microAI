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

};

void ADC_Initialise( void );

void ADC_Enable( void );

void ADC_Disable( void );

void ADC_ChannelSelect( uint8_t positiveInput, uint8_t negativeInput );

void ADC_ConversionStart( void );

uint16_t ADC_ConversionResultGet( void );

void ADC_EnterSleep( void );

void ADC_Awake( void );


#ifdef __cplusplus  // Provide C++ Compatibility

    }

#endif

#endif // _DRIVER_ADC_H