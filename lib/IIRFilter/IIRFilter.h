#ifndef IIRFILTER_H
#define IIRFILTER_H

#include <Arduino.h>

class IIRFilter {
  public:
    IIRFilter(int32_t *a, int32_t *b, uint8_t order);
    ~IIRFilter(void);
    int16_t filter(int16_t input);

  private:
    int32_t *a;       // denominator, feedback
    int32_t *b;       // numerator, feedforward. In DSP by Smith, the name conventions are swapped
    int32_t *x;       // Buffer for input samples
    int32_t *Y;       // Buffer for previous outputs
    uint8_t order;    // Filter order
};

/*!
    Filter Coefficients for a 2nd Order Low Pass Butterworth Filter
    Filter Order: 2
    Type: Low Pass, Butterworth
    Filter Cutoff: 500 Hz
    Sample Rate: 9615 Hz
*/
static int32_t LPF_500HZ_A[3] = {65536, -101176, 41291};
static int32_t LPF_500HZ_B[3] = {1413, 2826, 1413};

/*!
    Filter Coefficients for a 2nd Order Low Pass Butterworth Filter
    Filter Order: 2
    Type: Low Pass, Butterworth
    Filter Cutoff: 1000 Hz
    Sample Rate: 9615 Hz
*/
static int32_t LPF_1KHZ_A[3] = {65536, -72780, 26130};
static int32_t LPF_1KHZ_B[3] = {4721, 9442, 4721};

/*!
    Filter Coefficients for a 2nd Order Low Pass Butterworth Filter
    Filter Order: 2
    Type: Low Pass, Butterworth
    Filter Cutoff: 2000 Hz
    Sample Rate: 9615 Hz
*/
static int32_t LPF_2KHZ_A[3] = {65536, -20314, 12360};
static int32_t LPF_2KHZ_B[3] = {14395, 28790, 14395};

/*!
    Filter Coefficients for a 2nd Order High Pass Butterworth Filter
    Filter Order: 2
    Type: High Pass, Butterworth
    Filter Cutoff: 500 Hz
    Sample Rate: 9615 Hz
*/
static int32_t HPF_500HZ_A[3] = {65536, -101175, 41291};
static int32_t HPF_500HZ_B[3] = {52000, -104001, 52000};

/*!
    Filter Coefficients for a 2nd Order High Pass Butterworth Filter
    Filter Order: 2
    Type: High Pass, Butterworth
    Filter Cutoff: 1000 Hz
    Sample Rate: 9615 Hz
*/
static int32_t HPF_1KHZ_A[3] = {65536, -72780, 26130};
static int32_t HPF_1KHZ_B[3] = {41111, -82223, 41111};

/*!
    Filter Coefficients for a 2nd Order High Pass Butterworth Filter
    Filter Order: 2
    Type: High Pass, Butterworth
    Filter Cutoff: 2000 Hz
    Sample Rate: 9615 Hz
*/
static int32_t HPF_2KHZ_A[3] = {65536, -20314, 12360};
static int32_t HPF_2KHZ_B[3] = {24552, -49105, 24552};

#endif
