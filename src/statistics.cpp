// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************
/* This section lists the other files that are included in this file.
*/
#include <statistics.h>

// *****************************************************************************
// *****************************************************************************
// Section: Interface Routines
// *****************************************************************************
// *****************************************************************************
/* The following functions make up the methods (set of possible operations) of
   this interface.
*/

/*! @brief Returns the mean of an array
    @param inp the input array
    @param n the length of the array
*/
float mean(float* inp, uint16_t n) {

  float sum = 0;

  for (uint16_t i; i < n; i++) {
    sum+= inp[i];
  }
  Serial.print("sum: "); Serial.println(sum);

  return sum / n;
}

/*! @brief Returns the variance of an array
    @param inp the input array
    @param n the length of the array
    @param mean the mean of the array
*/
float variance(float* inp, uint16_t n, float mean) {

  float var = 0;

  // Step 2: Calculate the variance
  for (uint16_t i = 0; i < n; i++) {
      var += (inp[i] - mean) * (inp[i] - mean);
  }
  var /= n; // For population variance
  // variance /= (n - 1); // For sample variance

  return var;
}

/*! @brief Calculates the standard deviation of a variance
    @param the variance of the array
*/
float stddev(float variance)
{
  return sqrt(variance);
}

/*! @brief Comparison function for qsort
*/
int compare(const void* a, const void* b)
{
    return (*(int*)a - *(int*)b);
}

/*! @brief Returns the median of an array
    @param inp the input array
    @param n the length of the input array
*/
float median(float* inp, uint16_t n)
{
    uint16_t *temp = (uint16_t *)malloc(sizeof(uint16_t) * n);
    for (uint16_t i = 0; i < n; i++) {
        temp[i] = inp[i];
    }

    // Sort the array in ascending order
    qsort(temp, n, sizeof(uint16_t), compare);

    // If the size of the array is even, return the average
    // of the two middle elements
    if (n % 2 == 0) {
        return (temp[n / 2 - 1] + temp[n / 2]) / 2.0;
    }
    // If the size is odd, return the middle element
    // directly
    else {
        return temp[n / 2];
    }
}

/*! @brief Returns the mode of an array
    @param inp the input array
    @param n the length of the input array
*/
float mode(float *inp, uint16_t n) {

    uint16_t *temp = (uint16_t *)malloc(sizeof(uint16_t) * n);
    for (uint16_t i = 0; i < n; i++) {
        temp[i] = inp[i];
    }

    // Sort the array
    qsort(temp, n, sizeof(uint16_t), compare);

    // Initialize mode variables
    int mode = temp[0];
    int curr_count = 1;
    int max_count = 1;

    // Iterate through the sorted array to find the mode
    for (uint16_t i = 1; i < n; ++i) {
        if (temp[i] == temp[i - 1]) {
            // Increment the count if the current element is
            // equal to the previous one
            ++curr_count;
        }
        else {
            // Check if the count of the previous element is
            // greater than the maximum count
            if (curr_count > max_count) {
                max_count = curr_count;
                mode = temp[i - 1];
            }
            // Reset the count for the current element
            curr_count = 1;
        }
    }

    // Check the count of the last element
    if (curr_count > max_count) {
        mode = temp[n - 1];
    }

    return mode;
}

void Hampel_Initialise(HampelFilter *hampel)
{
  // Clear the filter buffer
    for (uint8_t n=0; n < HAMPEL_FILTER_LENGTH; n++) {
        hampel->out[n] = 0.0f;
    }
    hampel->hampelState = INIT;
    hampel->currentIndex = 0;
    hampel->count = 0;
    hampel->wMedian = 0.0;
    hampel->medAbsDev = 0.0;
}

/*! @brief Hampel Outlier Filter:
    Divide the input array into windows of N samples.
    If a sample is more than 3 absolute deviations
    from the window median, replace it with the window median.


    1. Calculate the median from the last N samples
    2. Calculate the standard deviation of the last N samples
    3. If the sample is greater than M absolute deviations replace it with the median

    @param buffer a pointer to the input Ring Buffer instance
    @returns a pointer to an output array
*/
float *Hampel_Filter(RingBuffer *buffer, HampelFilter *hampel) 
{
    // Instantiate an array for the window
    float window[WINDOW_SIZE];
    // Instantiate an array for the absolute deviation
    float absDev[WINDOW_SIZE];

    // Iterate through the input array
    for (uint16_t i = 0; i < buffer->n; i++) {

        // Populate the window
        uint16_t count = 0;
        for (uint16_t j = max(0, i - HALF_WINDOW_SIZE); j <= min(buffer->n - 1, i + HALF_WINDOW_SIZE); j++)  {
            window[count++] = buffer->buf[j];
        }

        // Calculate the median of the window
        float wMedian = median(window, count);

        // Estimate the standard deviation of each sample about its window median using the median absolute deviation.
        for (uint16_t j = 0; j < count; j++) {
            absDev[j] = abs(window[j] - wMedian);       // Calculate the absolute deviations from the median
        }

        float medAbsDev = median(absDev, count);        // Calculate the median of the absolute deviations

        // How many absolute deviations should the threshold be?
        float threshold = THRESHOLD_MULTIPLIER * medAbsDev;

        // If a sample differs from the median by more than the threshold, it is replaced with the median.
        if (abs(buffer->buf[i] - wMedian) > threshold) {
            hampel->out[i] = wMedian;
            //Serial.print("Replaced "); Serial.print(inp[i]); Serial.print(" with "); Serial.println(wMedian);
        }
        else hampel->out[i] = buffer->buf[i];
    } // end for loop
    return hampel->out;
}

float *Hampel_Filter_NonBlocking(RingBuffer *buffer, HampelFilter *hampel) {
    switch (hampel->hampelState) {
        case INIT:
            hampel->currentIndex = 0;
            hampel->hampelState = FILL_WINDOW;
            break;

        case FILL_WINDOW:
            hampel->count = 0;
            for (uint16_t j = max(0, hampel->currentIndex - HALF_WINDOW_SIZE); j <= min(buffer->n - 1, hampel->currentIndex + HALF_WINDOW_SIZE); j++) {
                hampel->window[hampel->count++] = buffer->buf[j];
            }
            hampel->hampelState = CALC_MEDIAN;
            break;

        case CALC_MEDIAN:
            hampel->wMedian = median(hampel->window, hampel->count);
            for (uint16_t j = 0; j < hampel->count; j++) {
                hampel->absDev[j] = abs(hampel->window[j] - hampel->wMedian);
            }
            hampel->medAbsDev = median(hampel->absDev, hampel->count);
            hampel->hampelState = CHECK_OUTLIERS;
            break;

        case CHECK_OUTLIERS:
            float threshold = THRESHOLD_MULTIPLIER * hampel->medAbsDev;
            if (abs(buffer->buf[hampel->currentIndex] - hampel->wMedian) > threshold) {
                hampel->out[hampel->currentIndex] = hampel->wMedian;
            } else {
                hampel->out[hampel->currentIndex] = buffer->buf[hampel->currentIndex];
            }
            hampel->currentIndex++;
            if (hampel->currentIndex >= buffer->n) {
                hampel->hampelState = DONE;
            } else {
                hampel->hampelState = FILL_WINDOW;
            }
            break;

        case DONE:
            hampel->hampelState = INIT; // Reset state for the next run
            return hampel->out;
    }
    return NULL;  // Not finished yet
}