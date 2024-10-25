#ifndef IIRFILTER_H
#define IIRFILTER_H

#include <Arduino.h>

class IIRFilter {
  public:
    IIRFilter(int32_t *a_coeffs, int32_t *b_coeffs, uint8_t order);
    int16_t process(int16_t input);

  private:
    int32_t *a_coeffs;  // Denominator coefficients
    int32_t *b_coeffs;  // Numerator coefficients
    int32_t *input_buffer;  // Buffer for past inputs
    int32_t *output_buffer; // Buffer for past outputs
    uint8_t order;          // Filter order
};

static int32_t LPF_500HZ_A[3] = {65536, -101175, 41291};  // Denominator coefficients
static int32_t LPF_500HZ_B[3] = {1412, 2825, 1412};       // Numerator coefficients

static int32_t LPF_1KHZ_A[3] = {65536, -72780, 26130};
static int32_t LPF_1KHZ_B[3] = {4721, 9442, 4721};

static int32_t LPF_2KHZ_A[3] = {65536, -20314, 12360};
static int32_t LPF_2KHZ_B[3] = {14395, 28790, 14395};

static int32_t HPF_500HZ_A[3] = {65536, -101175, 41291};  // Denominator coefficients
static int32_t HPF_500HZ_B[3] = {52000, -104001, 52000};  // Numerator coefficients

static int32_t HPF_1KHZ_A[3] = {65536, -72780, 26130};
static int32_t HPF_1KHZ_B[3] = {41111, -82223, 41111};

static int32_t HPF_2KHZ_A[3] = {65536, -20314, 12360};
static int32_t HPF_2KHZ_B[3] = {24552, -49105, 24552};

#endif
