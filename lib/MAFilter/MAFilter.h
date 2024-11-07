#ifndef MAFILTER_H
#define MAFILTER_H

#include <Arduino.h>

class MAFilter {
  public:
    MAFilter(uint8_t taps);
    ~MAFilter(void);
    int16_t filter(int16_t input);

  private:
    int16_t *x;         // Buffer for input samples
    uint8_t taps;       // Number of taps (coefficients)
    uint8_t index = 0;
};


#endif
