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
#include <stdlib.h>     // For qsort()
#include <ringbuffer.h> // For Ring Buffer

// *****************************************************************************
// *****************************************************************************
// Section: Macro definitions
// *****************************************************************************
// *****************************************************************************
/* These following macros are defined for the statistical functions
*/
#define HAMPEL_FILTER_LENGTH (16)
#define WINDOW_SIZE (6)  // The window size for the Hampel Filter
#define HALF_WINDOW_SIZE (WINDOW_SIZE / 2)
#define THRESHOLD_MULTIPLIER 1  // How many absolute deviations from the median before filtering? Typically 3

// *****************************************************************************
// *****************************************************************************
// Section: Data Types
// *****************************************************************************
// *****************************************************************************
/* The following data type definitions are used by the functions in this
    interface and should be considered part it.
*/
typedef enum {
    INIT,
    FILL_WINDOW,
    CALC_MEDIAN,
    CHECK_OUTLIERS,
    DONE
} HampelState;

typedef struct {
    float out[HAMPEL_FILTER_LENGTH];
    uint8_t index;

    HampelState hampelState;
    uint16_t currentIndex = 0;
    uint16_t count = 0;
    float window[WINDOW_SIZE];
    float absDev[WINDOW_SIZE];
    float wMedian;
    float medAbsDev;
} HampelFilter;

// *****************************************************************************
// *****************************************************************************
// Section: Interface Routines
// *****************************************************************************
// *****************************************************************************
/* The following functions make up the methods (set of possible operations) of
    this interface.
*/
float mean(float* inp, uint16_t n);

float variance(float* inp, uint16_t n, float mean);

float stddev(float variance);

int compare(const void* a, const void* b);

float median(float* inp, uint16_t n);

float mode(float *inp, uint16_t n);

void Hampel_Initialise(HampelFilter *hampel);

float *Hampel_Filter(RingBuffer *buffer, HampelFilter *hampel);

float *Hampel_Filter_NonBlocking(RingBuffer *buffer, HampelFilter *hampel);

#endif