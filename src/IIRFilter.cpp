#include "IIRFilter.h"

/*!
    @brief Constructor: Initializes the IIR filter with coefficients and order.
    @param a_coeffs A pointer to the denominator coefficients array.
    @param b_coeffs A pointer to the numerator coefficients array.
    @param order The order of the IIR filter.
*/
IIRFilter::IIRFilter(int32_t *a_coeffs, int32_t *b_coeffs, uint8_t order) {
    this->order = order;
    this->a_coeffs = a_coeffs;
    this->b_coeffs = b_coeffs;
    this->input_buffer = new int32_t[order + 1]();
    this->output_buffer = new int32_t[order]();
}

/*!
    @brief Processes the input signal and returns the filtered output.
    @param input The current input signal.
    @return The filtered output signal.
    @note Coefficients are scaled by 2^16 to use fixed-point arithmetic.
*/
int16_t IIRFilter::process(int16_t input) {
    // Shift input buffer
    for (int i = order; i > 0; i--) {
        input_buffer[i] = input_buffer[i - 1];
    }
    input_buffer[0] = input;

    // Calculate the output
    int32_t accumulator = 0;
    for (int i = 0; i <= order; i++) {
        accumulator += b_coeffs[i] * input_buffer[i];
    }
    for (int i = 1; i <= order; i++) {
        accumulator -= a_coeffs[i] * output_buffer[i - 1];
    }

    // Scale the result and update output buffer
    int16_t output = accumulator >> 16;
    for (int i = order - 1; i > 0; i--) {
        output_buffer[i] = output_buffer[i - 1];
    }
    output_buffer[0] = output;

    return output;
}
