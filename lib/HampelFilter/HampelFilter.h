#ifndef HAMPELFILTER_H
#define HAMPELFILTER_H

#include <Arduino.h>

class HampelFilter {
  public:
    HampelFilter(uint8_t  windowLength, float threshold);
    ~HampelFilter(void);

    int16_t filter(int16_t input);

  private:
    int16_t getMedian(int16_t *array, int16_t n);
    int16_t getMAD(int16_t *array, int16_t n, int16_t median);

    int16_t* window;            // pointer to the window buffer
    uint8_t windowLength;
    uint8_t index;
    uint16_t scaledThreshold;
    bool windowReady = false;   // flag to indicate if the window is ready for processing
};

#endif
