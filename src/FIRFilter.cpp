#include "FIRFilter.h"

/*! @brief Constructor: Initialises the FIR filter with the filter
    coefficients and number of taps.
    @param filter a pointer to the filter coefficients
    @param n_taps the number of taps (order) of the filter
*/
FIRFilter::FIRFilter(int16_t *filter, uint8_t n_taps) {
    this->n_taps = n_taps;
    this->filter = filter;
    this->buffer = new int16_t[n_taps];  // Allocate buffer for previous inputs
    memset(this->buffer, 0, n_taps * sizeof(int16_t));  // Initialize buffer to 0
}

/*! @brief Processes the input and returns the filter output.
    1. Shifts the the contents of the input buffer
    2. Perform the filter operations
        a. Scale each member of the input array by the filter coefficients
        b. Sum the results
    3. Scale the result down by 2^16 and then return the result.
    @param input the current input signal
    @return the filtered output
    @note Filter coefficients are all scaled up by 2^16 to avoid using
    floating point maths. They are then normalised by >> 16 before returning
    the filtered output value.
*/
int16_t FIRFilter::process(int16_t input) {
    // Shift the buffer contents (delay line)
    for (int8_t i = n_taps - 1; i > 0; i--) {
        buffer[i] = buffer[i - 1];
    }
    buffer[0] = input;

    // Perform the FIR filter operation
    int32_t accumulator = 0;
    for (int8_t i = 0; i < n_taps; i++) {
        accumulator += (int32_t)buffer[i] * filter[i];
    }

    // Scale down the result and return the output
    return accumulator >> 16;
}
