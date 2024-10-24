#ifndef _RING_BUFFER_H
    #define _RING_BUFFER_H

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************
/* This section lists the other files that are included in this file.
*/
#include <Arduino.h>
#include <stdint.h>

#ifdef __cplusplus // Provide C Compatibility

    extern "C" {

#endif

// *****************************************************************************
// *****************************************************************************
// Section: Macro definitions
// *****************************************************************************
// *****************************************************************************
/* These following macros are defined for the FIR filter functions
*/
#define RING_BUFFER_LENGTH (16)

// *****************************************************************************
// *****************************************************************************
// Section: Data Types
// *****************************************************************************
// *****************************************************************************
/* The following data type definitions are used by the functions in this
    interface and should be considered part it.
*/
typedef struct {
    float buf[RING_BUFFER_LENGTH];

    uint8_t n;           // Tracks the number of items in the buffer
    uint8_t readHead;           // Index for reading from the buffer
    uint8_t writeHead;          // Index for writing to the buffer
} RingBuffer;

// *****************************************************************************
// *****************************************************************************
// Section: Interface Routines
// *****************************************************************************
// *****************************************************************************
/* The following functions make up the methods (set of possible operations) of
    this interface.
*/
void RingBuffer_Initialise(RingBuffer *buffer);

void RingBuffer_Push(RingBuffer *buffer, float data);

uint16_t RingBuffer_Pop(RingBuffer *buffer);

#ifdef __cplusplus  // Provide C++ Compatibility

    }

#endif

#endif
