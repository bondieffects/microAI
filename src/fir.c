// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************
/* This section lists the other files that are included in this file.
*/
#include <fir.h>

/*! @brief The FIR filter coefficients
*/
static float FIR_IMPULSE_RESPONSE[FIR_FILTER_LENGTH] = {};

/*! @brief Clears all the buffers and resets the index to 0
*/
void FIRFilter_Init(FIRFilter *fir) 
{
    // Clear the filter buffer
    for (uint8_t n=0; n < FIR_FILTER_LENGTH; n++) {
        fir->buf[n] = 0.0f;
    }

    // Reset the buffer index
    fir->bufIndex = 0;

    // Clear the filter output
    fir->out = 0.0f;
}

/*! @brief Clears all the buffers and resets the index to 0
*/
float FIRFilter_Update(FIRFilter *fir, float inp)
{
    // Populate the buffer with the latest sample
    fir->buf[fir->bufIndex] = inp;

    // Increment the index
    fir->bufIndex++;
    if (fir->bufIndex == FIR_FILTER_LENGTH) fir->bufIndex = 0;

    // Calculate the output sample
    fir->out = 0.0f;
    uint8_t sumIndex = fir->bufIndex;

    for (uint8_t n=0; n< FIR_FILTER_LENGTH; n++) {
        
        // Decrement the index
        if (sumIndex > 0 ) sumIndex--;
        else sumIndex = FIR_FILTER_LENGTH - 1;

        // Multiply the impulse response with the shifted input sample and add to the output
        fir->out += FIR_IMPULSE_RESPONSE[n] * fir->buf[sumIndex];
    }

    // Return filtered output
    return fir->out;
}
