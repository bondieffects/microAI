#include "HampelFilter.h"

// Constructor
HampelFilter::HampelFilter(int window_size, float threshold) {
  this->window_size = window_size;
  this->threshold = threshold;
  window = new float[window_size];
  index = 0;
  is_window_full = false;
}

// Add a new value and process it
float HampelFilter::process(float value) {
  // Add new value to the window
  window[index] = value;
  index = (index + 1) % window_size;
  if (index == 0) is_window_full = true;
  
  // Only process if we have enough data
  int current_size = is_window_full ? window_size : index;
  if (current_size < 2) return value; // Can't filter with less than 2 points
  
  // Compute the median of the window
  float median = computeMedian(window, current_size);
  
  // Compute the standard deviation
  float stddev = computeStdDev(window, current_size, median);
  
  // Check if the value is an outlier
  if (abs(value - median) > threshold * stddev) {
    // Outlier detected, return the median instead
    return median;
  } else {
    // No outlier, return the original value
    return value;
  }
}

// Compute the median of an array
float HampelFilter::computeMedian(float arr[], int size) {
  float* temp = new float[size];
  memcpy(temp, arr, size * sizeof(float));
  // Sort the temporary array
  for (int i = 0; i < size - 1; i++) {
    for (int j = i + 1; j < size; j++) {
      if (temp[i] > temp[j]) {
        float swap = temp[i];
        temp[i] = temp[j];
        temp[j] = swap;
      }
    }
  }
  
  // Compute median
  float median;
  if (size % 2 == 0) {
    median = (temp[size / 2 - 1] + temp[size / 2]) / 2;
  } else {
    median = temp[size / 2];
  }
  
  delete[] temp;
  return median;
}

// Compute the standard deviation
float HampelFilter::computeStdDev(float arr[], int size, float median) {
  float sum = 0;
  for (int i = 0; i < size; i++) {
    sum += pow(arr[i] - median, 2);
  }
  return sqrt(sum / size);
}

// Set the threshold for outlier detection
void HampelFilter::setThreshold(float threshold) {
  this->threshold = threshold;
}

// Set the window size (if needed to adjust dynamically)
void HampelFilter::setWindowSize(int size) {
  delete[] window;
  window_size = size;
  window = new float[window_size];
  index = 0;
  is_window_full = false;
}
