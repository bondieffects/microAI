#ifndef HAMPELFILTER_H
#define HAMPELFILTER_H

#include <Arduino.h>

class HampelFilter {
  public:
    // Constructor
    HampelFilter(int window_size, float threshold);

    // Add a new value and get filtered result
    float process(float value);

    // Set the threshold for outlier detection
    void setThreshold(float threshold);

    // Set the window size
    void setWindowSize(int size);

  private:
    // Function to compute median
    float computeMedian(float arr[], int size);

    // Function to compute standard deviation
    float computeStdDev(float arr[], int size, float median);

    // Circular buffer to hold window values
    float* window;
    int window_size;
    int index;
    float threshold;
    bool is_window_full;
};

#endif
