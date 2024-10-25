#ifndef HAMPELFILTER_H
#define HAMPELFILTER_H

#include <Arduino.h>

/*! @brief HampelFilter class for detecting outliers in real-time data.
    The Hampel filter works by comparing each data point to the median of 
    its neighbors and detects if the point is an outlier based on a 
    configurable threshold and window size.
*/
class HampelFilter {
  public:

    HampelFilter(int16_t  window_size, int32_t threshold);
    int32_t process(int32_t value);
    void setThresholdShift(int32_t threshold);
    void setWindowSize(int16_t size);

  private:

    int32_t getMedian(int32_t arr[], int16_t size);
    int32_t getStdDev(int32_t arr[], int16_t size, int32_t median);

    int32_t* window;         // Circular buffer for the window
    int16_t window_size;     // Size of the window
    int16_t index;           // Current index in the window
    int32_t threshold;       // How many standard deviations is an outlier?
    bool is_window_full;     // Flag to indicate if the window is full
};

#endif
