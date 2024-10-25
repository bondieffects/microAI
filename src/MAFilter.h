#ifndef MAFILTER_H
#define MAFILTER_H

#include <Arduino.h>

class MAFilter {
  public:
    MAFilter(uint8_t n_average);
    int16_t process(int16_t input);

  private:
    int16_t *buffer;    // Buffer to store previous inputs (delay line)
    uint8_t n_average;     // Number of filter coefficients (taps)
    uint8_t n_last;
};


#endif
