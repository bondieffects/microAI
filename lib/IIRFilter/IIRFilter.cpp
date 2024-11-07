#include "IIRFilter.h"

/*!
    @brief Constructor: Initialise the IIR Filter object.
        1. Point to the impulse response coefficients
        2. Set the order
        3. Allocate memory for the buffers
    @param a Pointer to feedback coefficients.
    @param b Pointer to feedforward coefficients.
    @param order The filter order
*/
IIRFilter::IIRFilter(int32_t *a, int32_t *b, uint8_t order) {

    this->a = a;
    this->b = b;
    this->order = order;

    // For an order of n, the input buffer is x[n+1]
    x = (int32_t *)calloc((order + 1), sizeof(int32_t));

    // For an order of n, the previous output buffer is Y[n]
    Y = (int32_t *)calloc(order, sizeof(int32_t));
}

/*! @brief Destructor: Free up the memory allocated to the buffers.
*/
IIRFilter::~IIRFilter(void)
{
    if (x) {
        free(x);
        x = NULL;
    }
    if (Y) {
        free(Y);
        Y = NULL;
    }
}

/*! @brief Process the input through the IIR Filter.
    1. Update the input buffer with the latest sample and throw away the oldest sample
    2. Convolution:
        a. Input buffer and feedforward coefficients
        b. Previous output bufffer and feedback coefficients.
            @note This step makes the filter recursive, which can cause instability.
    3. The coefficients are scaled by 2^16 to avoid floating point math,
       so they must be scaled down by 2^16 before returning the result.
            @note Filter coefficients are all scaled up by 2^16 to avoid using
                  floating point maths.
    @param input The input sample.
    @return The IIR Filtered output.
*/
int16_t IIRFilter::filter(int16_t input)
{
    // Confirm that buffer memory has been allocated before proceeding
    if (x == NULL || Y == NULL) return input;

    // Update the input buffer with the latest sample and throw away the oldest sample
    for (uint8_t i = order; i > 0; i--) {
        x[i] = x[i - 1];
    }
    x[0] = input;

    int32_t y = 0;
    // Perform convolution on the input buffer (x) and feedforward (b) coefficients
    // += for feedforward
    for (uint8_t i = 0; i <= order; i++) {
        y += b[i] * x[i];
    }
    // Perform convolution on the previous outputs buffer (Y) and feedback (a) coefficients
    // SciPy generates coefficients in standard form, which requires explicit negation, so we (-=)
    for (uint8_t j = 1; j <= order; j++) {
        y -= a[j] * Y[j-1];
    }

    // Scale the result down by 2^16, because coefficients have been scaled up to avoid FP maths
    int16_t output = y >> 16;

    // Update previous output buffer
    for (uint8_t u = (order-1); u > 0; u--) {
        Y[u] = Y[u - 1];
    }
    Y[0] = output;

    // Prevent output from going out of bounds
    output = constrain(output, 0, 1023);

    return output;
}
