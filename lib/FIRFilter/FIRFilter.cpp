#include "FIRFilter.h"

/*! @brief Constructor: Initialise the FIR filter object.
        1. Point to the impulse response coefficients
        2. Set the number of taps
        3. Allocate memory for the input buffer
    @param IR Pointer to the impulse response coefficients
    @param taps The number of taps (order) of the FIR filter
*/
FIRFilter::FIRFilter(int32_t *IR, uint8_t taps)
{
    this->IR = IR;
    this->taps = taps;

    x = (int16_t *)calloc(taps, sizeof(int16_t));
}

/*! @brief Destructor: Free up memory allocated to the buffer
*/
FIRFilter::~FIRFilter(void)
{
    if (x) {
        free(x);
        x = NULL;
    }
}

/*! @brief Process the input through the FIR Filter.
    1. Update the input buffer with the latest sample and throw away the oldest sample
    2. Convolution: sum of weighted inputs
    3. The coefficients are scaled by 2^16 to avoid floating point math,
       so they must be scaled down by 2^16 before returning the result.
            @note Filter coefficients are all scaled up by 2^16 to avoid using
                  floating point maths.
    @param input The input sample.
    @return The FIR Filtered output.
*/
int16_t FIRFilter::filter(int16_t input)
{

    // Confirm that buffer memory has been allocated before proceeding
    if (x == NULL) return input;

    // Update the input buffer with the latest sample and throw away the oldest sample
    for (uint8_t i = taps - 1; i > 0; i--) {
        x[i] = x[i - 1];
    }
    x[0] = input;

    int32_t y = 0;
    // Perform convolution on the input buffer and impulse response
    for (uint8_t i = 0; i < taps; i++) {
        y += (int32_t)x[i] * IR[i];
    }

    // Scale the result down by 2^16, because coefficients have been scaled up to avoid FP maths
    return y >> 16;
}
