#include "HampelFilter.h"

/*! @brief Constructor: Initializes the Hampel filter with the specified window size and threshold.
    @param window_size The size of the window.
    @param threshold How many absolute deviations makes an outlier?
*/
HampelFilter::HampelFilter(int16_t window_size, int32_t threshold)
{
    this->window_size = window_size;
    this->threshold = threshold;
    window = new int32_t[window_size];
    index = 0;
    is_window_full = false;
}

/*! @brief Processes the input value and returns the filtered result.
    1. Adds the new value to the sliding window.
    2. Computes the median of the current window.
    3. Computes the absolute deviation.
    4. Detects outliers based on the assigned threshold.
    @param value The current input value.
    @return The filtered value (the median if the input is an outlier).
*/
int32_t HampelFilter::process(int32_t value)
{

    // Add new value to the window
    window[index] = value;
    index = (index + 1) % window_size;
    if (index == 0) is_window_full = true;

    // Only process if we have enough data
    int16_t current_size = is_window_full ? window_size : index;
    if (current_size < 2) return value;

    // Compute the median of the window
    int32_t median = getMedian(window, current_size);

    // Compute the absolute deviation
    int32_t stddev = getStdDev(window, current_size, median);

    // Check if the value is an outlier
    if (abs(value - median) > (stddev << (threshold - 1))) {
        // Outlier detected, return the median instead
        return median;
    } else {
        // No outlier, return the original value
        return value;
    }
}

/*! @brief Compute the median of an array.
    The function sorts the array and returns the median value.
    @param arr The array of values.
    @param size The size of the array.
    @return The median value.
*/
int32_t HampelFilter::getMedian(int32_t arr[], int16_t size)
{

    int32_t* temp = new int32_t[size];
    memcpy(temp, arr, size * sizeof(int32_t));

    // Sort the temporary array
    for (int16_t i = 0; i < size - 1; i++) {
        for (int16_t j = i + 1; j < size; j++) {
            if (temp[i] > temp[j]) {
                int32_t swap = temp[i];
                temp[i] = temp[j];
                temp[j] = swap;
            }
        }
    }

    // Compute the median
    int32_t median;
    if (size % 2 == 0) {
        median = (temp[size / 2 - 1] + temp[size / 2]) >> 1; // Averaging two middle elements
    } else {
        median = temp[size / 2];
    }

    delete[] temp;
    return median;
}

/*! @brief Compute an approximate standard deviation.
    The function calculates the variance and scales it down so that we only use integer maths.
    @param arr The array of values.
    @param size The size of the array.
    @param median The median value of the array.
    @return The approximate standard deviation.
*/
int32_t HampelFilter::getStdDev(int32_t arr[], int16_t size, int32_t median)
{
    int32_t sum = 0;
    for (int16_t i = 0; i < size; i++) {
        int32_t diff = arr[i] - median;
        sum += (diff * diff) >> 2;
    }
    return sum / size;
}

/*! @brief Set the threshold scaling for outlier detection.
    @param threshold The bit-shift used to scale the threshold.
*/
void HampelFilter::setThresholdShift(int32_t threshold)
{
    this->threshold = threshold;
}

/*! @brief Set the window size for the filter.
    Dynamically changes the size of the sliding window.
    @param size The new size of the sliding window.
*/
void HampelFilter::setWindowSize(int16_t size)
{
    delete[] window;
    window_size = size;
    window = new int32_t[window_size];
    index = 0;
    is_window_full = false;
}
