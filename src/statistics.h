#ifndef _STATISTICS_H
    #define _STATISTICS_H

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************
/* This section lists the other files that are included in this file.
*/
#include <Arduino.h>
#include <stdlib.h>  // For qsort()

// *****************************************************************************
// *****************************************************************************
// Section: Macro definitions
// *****************************************************************************
// *****************************************************************************
/* These following macros are defined for the statistical functions
*/
#define WINDOW_SIZE (6)  // The window size for the Hampel Filter
#define HALF_WINDOW_SIZE (WINDOW_SIZE / 2)
#define THRESHOLD_MULTIPLIER 1  // How many absolute deviations from the median before filtering? Typically 3

// *****************************************************************************
// *****************************************************************************
// Section: Interface Routines
// *****************************************************************************
// *****************************************************************************
/* The following functions make up the methods (set of possible operations) of
    this interface.
*/
float mean(uint16_t* x, uint16_t n);

float variance(uint16_t* x, uint16_t n, float mean);

float stddev(float variance);

int compare(const void* a, const void* b);

float median(uint16_t* x, uint16_t n);

float mode(uint16_t *x, uint16_t n);

void hampel(uint16_t *x, uint16_t n);

#endif