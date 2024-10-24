// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************
/* This section lists the other files that are included in this file.
*/
#include <fir.h>

/*! @brief The FIR filter coefficients.
    Sample Rate: 9615 Hz
    Filter Length: 64
    Shift Samples: 32
    Window: Hamming
    Type: Low Pass Filter
    Cutoff Frequency: 1000 Hz

*/
static float FIR_1KHZ_9615[FIR_FILTER_LENGTH] = {
    0.0007628,    0.000903379,  0.000695882,  0.000118328, -0.000725766, 
   -0.001551183, -0.001923669, -0.001427583,  0.000071713,  0.002203664,
    0.004074170,  0.004555222,  0.002830214, -0.001030896, -0.005785655,
   -0.009278172, -0.009274038, -0.004599675,  0.003920456,  0.013264255,
    0.019048928,  0.017266197,  0.006316368, -0.011525299, -0.029990376,
   -0.040372916, -0.034414213, -0.007556661,  0.038677419,  0.096221168,
    0.152299644,  0.193091426,  0.208008320,  0.193091426,  0.152299644,
    0.096221168,  0.038677419, -0.007556661, -0.034414213, -0.040372916,
   -0.029990376, -0.011525299,  0.006316368,  0.017266197,  0.019048928,
    0.013264255,  0.003920456, -0.004599675, -0.009274038, -0.009278172,
   -0.005785655, -0.001030896,  0.002830214,  0.004555222,  0.004074170,
    0.002203664,  0.000071713, -0.001427583, -0.001923669, -0.001551183,
   -0.000725766,  0.000118328,  0.000695882,  0.000903379
};

/*! @brief The FIR filter coefficients.
    Sample Rate: 19231 Hz
    Filter Length: 64
    Shift Samples: 32
    Window: Hamming
    Type: Low Pass Filter
    Cutoff Frequency: 1000Hz

*/
static float FIR_1KHZ_19231[FIR_FILTER_LENGTH] = {
    -0.0007417f, -0.0005923f, -0.0003738f, -0.0000587f,  0.0003778f,  0.0009422f,
     0.0016085f,  0.0023079f,  0.0029265f,  0.0033130f,  0.0032972f,  0.0027184f,
     0.0014592f, -0.0005191f, -0.0031455f, -0.0062199f, -0.0094089f, -0.0122616f,
    -0.0142444f, -0.0147946f, -0.0133851f, -0.0095957f, -0.0031791f,  0.0058854f,
     0.0173601f,  0.0307445f,  0.0453014f,  0.0601115f,  0.0741527f,  0.0863959f,
     0.0959054f,  0.1019338f,  0.1039988f,  0.1019338f,  0.0959054f,  0.0863959f,
     0.0741527f,  0.0601115f,  0.0453014f,  0.0307445f,  0.0173601f,  0.0058854f,
    -0.0031791f, -0.0095957f, -0.0133851f, -0.0147946f, -0.0142444f, -0.0122616f,
    -0.0094089f, -0.0062199f, -0.0031455f, -0.0005191f,  0.0014592f,  0.0027184f,
     0.0032972f,  0.0033130f,  0.0029265f,  0.0023079f,  0.0016085f,  0.0009422f,
     0.0003778f, -0.0000587f, -0.0003738f, -0.0005923f
};

/*! @brief The FIR filter coefficients.
    Sample Rate: 38462 Hz
    Filter Length: 64
    Shift Samples: 32
    Window: Hamming
    Type: Low Pass Filter
    Cutoff Frequency: 1000Hz

*/
static float FIR_1KHZ_38462[FIR_FILTER_LENGTH] = {
    -0.0007527f, -0.0008594f, -0.0009977f, -0.0011699f, -0.0013704f, -0.0015857f, 
    -0.0017935f, -0.0019631f, -0.0020564f, -0.0020291f, -0.0018330f, -0.0014180f, 
    -0.0007354f,  0.0002597f,  0.0016051f,  0.0033286f,  0.0054455f,  0.0079569f, 
     0.0108477f,  0.0140860f,  0.0176232f,  0.0213950f,  0.0253227f,  0.0293158f, 
     0.0332751f,  0.0370963f,  0.0406739f,  0.0439056f,  0.0466959f,  0.0489609f, 
     0.0506311f,  0.0516546f,  0.0519994f,  0.0516546f,  0.0506311f,  0.0489609f, 
     0.0466959f,  0.0439056f,  0.0406739f,  0.0370963f,  0.0332751f,  0.0293158f, 
     0.0253227f,  0.0213950f,  0.0176232f,  0.0140860f,  0.0108477f,  0.0079569f, 
     0.0054455f,  0.0033286f,  0.0016051f,  0.0002597f, -0.0007354f, -0.0014180f, 
    -0.0018330f, -0.0020291f, -0.0020564f, -0.0019631f, -0.0017935f, -0.0015857f, 
    -0.0013704f, -0.0011699f, -0.0009977f, -0.0008594f
};

/*! @brief The FIR filter coefficients.
    Sample Rate: 76923 Hz
    Filter Length: 64
    Shift Samples: 32
    Window: Hamming
    Type: Low Pass Filter
    Cutoff Frequency: 1000Hz

*/
static float FIR_1KHZ_76923[FIR_FILTER_LENGTH] = {
    0.0004356f,  0.0005240f,  0.0006474f,  0.0008170f,  0.0010436f,  0.0013373f, 
    0.0017075f,  0.0021621f,  0.0027074f,  0.0033482f,  0.0040869f,  0.0049240f, 
    0.0058577f,  0.0068836f,  0.0079953f,  0.0091837f,  0.0104379f,  0.0117446f, 
    0.0130889f,  0.0144543f,  0.0158232f,  0.0171767f,  0.0184959f,  0.0197615f, 
    0.0209545f,  0.0220565f,  0.0230504f,  0.0239203f,  0.0246524f,  0.0252346f, 
    0.0256575f,  0.0259140f,  0.0260000f,  0.0259140f,  0.0256575f,  0.0252346f, 
    0.0246524f,  0.0239203f,  0.0230504f,  0.0220565f,  0.0209545f,  0.0197615f, 
    0.0184959f,  0.0171767f,  0.0158232f,  0.0144543f,  0.0130889f,  0.0117446f, 
    0.0104379f,  0.0091837f,  0.0079953f,  0.0068836f,  0.0058577f,  0.0049240f, 
    0.0040869f,  0.0033482f,  0.0027074f,  0.0021621f,  0.0017075f,  0.0013373f, 
    0.0010436f,  0.0008170f,  0.0006474f,  0.0005240f
};

/*! @brief The FIR filter coefficients.
    Sample Rate: 153846 Hz
    Filter Length: 64
    Shift Samples: 32
    Window: Hamming
    Type: Low Pass Filter
    Cutoff Frequency: 1000Hz

*/
static float FIR_1KHZ_153846[FIR_FILTER_LENGTH] = {
    0.0008350f,  0.0008733f,  0.0009557f,  0.0010839f,  0.0012592f,  0.0014820f, 
    0.0017522f,  0.0020690f,  0.0024309f,  0.0028359f,  0.0032811f,  0.0037633f, 
    0.0042785f,  0.0048222f,  0.0053895f,  0.0059750f,  0.0065730f,  0.0071775f, 
    0.0077823f,  0.0083809f,  0.0089671f,  0.0095344f,  0.0100767f,  0.0105880f, 
    0.0110625f,  0.0114948f,  0.0118801f,  0.0122139f,  0.0124925f,  0.0127126f, 
    0.0128717f,  0.0129678f,  0.0130000f,  0.0129678f,  0.0128717f,  0.0127126f, 
    0.0124925f,  0.0122139f,  0.0118801f,  0.0114948f,  0.0110625f,  0.0105880f, 
    0.0100767f,  0.0095344f,  0.0089671f,  0.0083809f,  0.0077823f,  0.0071775f, 
    0.0065730f,  0.0059750f,  0.0053895f,  0.0048222f,  0.0042785f,  0.0037633f, 
    0.0032811f,  0.0028359f,  0.0024309f,  0.0020690f,  0.0017522f,  0.0014820f, 
    0.0012592f,  0.0010839f,  0.0009557f,  0.0008733f
};


/*! @brief The FIR filter coefficients.
    Sample Rate: 307692 Hz
    Filter Length: 64
    Shift Samples: 32
    Window: Hamming
    Type: Low Pass Filter
    Cutoff Frequency: 1000Hz

*/
static float FIR_1KHZ_307692[FIR_FILTER_LENGTH] = {
    0.0005258f,  0.0005416f,  0.0005840f,  0.0006532f,  0.0007487f,  0.0008699f, 
    0.0010160f,  0.0011857f,  0.0013776f,  0.0015901f,  0.0018213f,  0.0020690f, 
    0.0023310f,  0.0026047f,  0.0028876f,  0.0031770f,  0.0034701f,  0.0037640f, 
    0.0040557f,  0.0043426f,  0.0046216f,  0.0048901f,  0.0051453f,  0.0053847f, 
    0.0056059f,  0.0058066f,  0.0059849f,  0.0061389f,  0.0062672f,  0.0063682f, 
    0.0064412f,  0.0064853f,  0.0065000f,  0.0064853f,  0.0064412f,  0.0063682f, 
    0.0062672f,  0.0061389f,  0.0059849f,  0.0058066f,  0.0056059f,  0.0053847f, 
    0.0051453f,  0.0048901f,  0.0046216f,  0.0043426f,  0.0040557f,  0.0037640f, 
    0.0034701f,  0.0031770f,  0.0028876f,  0.0026047f,  0.0023310f,  0.0020690f, 
    0.0018213f,  0.0015901f,  0.0013776f,  0.0011857f,  0.0010160f,  0.0008699f, 
    0.0007487f,  0.0006532f,  0.0005840f,  0.0005416f
};


/*! @brief The FIR filter coefficients.
    Sample Rate: 615385 Hz
    Filter Length: 64
    Shift Samples: 32
    Window: Hamming
    Type: Low Pass Filter
    Cutoff Frequency: 1000Hz

*/
static float FIR_1KHZ_615385[FIR_FILTER_LENGTH] = {
    0.0002776f,  0.0002849f,  0.0003063f,  0.0003415f,  0.0003902f,  0.0004520f, 
    0.0005264f,  0.0006127f,  0.0007100f,  0.0008175f,  0.0009341f,  0.0010587f, 
    0.0011902f,  0.0013272f,  0.0014685f,  0.0016127f,  0.0017585f,  0.0019043f, 
    0.0020488f,  0.0021906f,  0.0023283f,  0.0024605f,  0.0025861f,  0.0027037f, 
    0.0028123f,  0.0029107f,  0.0029981f,  0.0030735f,  0.0031362f,  0.0031856f, 
    0.0032213f,  0.0032428f,  0.0032500f,  0.0032428f,  0.0032213f,  0.0031856f, 
    0.0031362f,  0.0030735f,  0.0029981f,  0.0029107f,  0.0028123f,  0.0027037f, 
    0.0025861f,  0.0024605f,  0.0023283f,  0.0021906f,  0.0020488f,  0.0019043f, 
    0.0017585f,  0.0016127f,  0.0014685f,  0.0013272f,  0.0011902f,  0.0010587f, 
    0.0009341f,  0.0008175f,  0.0007100f,  0.0006127f,  0.0005264f,  0.0004520f, 
    0.0003902f,  0.0003415f,  0.0003063f,  0.0002849f
};

/*! @brief Initializes the FIR filter by clearing its buffer and resetting the index.
    @param fir Pointer to the FIR filter structure that holds buffer data and index.
    1. Clears the filter's buffer
    2. Rets the buffer index to 0,
    3. Resets the output to ensure the filter is ready for new input data.
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

/*! @brief Updates the FIR filter with a new input sample and computes the filtered output.
    @param fir Pointer to the FIR filter structure that holds buffer data and index.
    @param inp The new input sample to be processed.
    @returns The filtered output as a floating-point number.

    This function updates the filter's circular buffer with the latest input sample,
    processes the buffer using the FIR impulse response,
    and calculates the filtered output sample.
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
        fir->out += FIR_1KHZ_9615[n] * fir->buf[sumIndex];
    }

    // Return filtered output
    return fir->out;
}
