#include "HampelFilter.h"

/*! @brief Default Constructor: Initialise the Hampel Filter object
           with a default window length of 5 and threshold of 3.
           Allocate some memory for the window.
 */
HampelFilter::HampelFilter(void)
{
    windowLength = 5;
    threshold = 3;
    index = 0;

    window = (int16_t *)calloc(windowLength, sizeof(int16_t));
    windowReady = false;
}

/*! @brief Constructor: Initialise the Hampel Filter object with the
           specified window length and threshold.
           Allocate some memory for the window.
    @param windowLength The length of the window.
    @param threshold How many median absolute deviations makes an outlier?
*/
HampelFilter::HampelFilter(uint8_t windowLength, uint8_t threshold)
{
    if (windowLength > 0) this->windowLength = windowLength;
    if (threshold > 0) this->threshold = threshold;
    index = 0;

    window = (int16_t *)calloc(windowLength, sizeof(int16_t));
    windowReady = false;
}

/*! @brief Destructor: Free up the memory allocated to the window
*/
HampelFilter::~HampelFilter(void)
{
    if (window) {
        free(window);
        window = NULL;
    }
}

/*! @brief Process the input through the Hampel Filter.
    1. Update the window with the input sample.
    2. Calculate the median.
    3. Calculate the median absolute deviation.
    4. Check if the input is an outlier, and if so replace it with the median.
    @param input The input sample.
    @return The Hampel Filtered output.
*/
int16_t HampelFilter::filter(int16_t input)
{
    // Confirm that window memory has been allocated before proceeding
    if (window == NULL) return input;

    // Update the window
    window[index] = input;
    index = (index + 1) % windowLength;
    if (index == 0) windowReady = true;

    // No point filtering unless the window is full
    int16_t n = windowReady ? windowLength : index;
    if (n < 2) return input;

    // Calculate the window median
    int16_t median = getMedian(window, n);

    // Calculate the window median absolute deviation
    int16_t mad = getMAD(window, n, median);

    // Calculate the absolute difference from the median
    int16_t delta = abs(input - median);

    // If the number is an outlier return the median
    if (delta > (mad * threshold)) return median;
    else return input;
}

/*! @brief Compare two integers for qsort
    From: https://www.geeksforgeeks.org/program-for-mean-and-median-of-an-unsorted-array/
*/
int compare(const void* a, const void* b)
{
    return (*(int16_t*)a - *(int16_t*)b);
}

/*! @brief Calculate the median of an array.
    @param array The input array.
    @param n The length of the array.
    @return The median.
*/
int16_t HampelFilter::getMedian(int16_t *array, int16_t n)
{
    // Copy the data into a temporary array for sorting
    int16_t* temp = (int16_t *)malloc(n * sizeof(int16_t));
    memcpy(temp, array, n * sizeof(int16_t));

    // Sort the array
    qsort(temp, n, sizeof(int16_t), compare);

    int16_t median;
    // If n is odd, return the middle value
    if (n % 2 != 0)
        median = (int16_t)temp[n / 2];
    // If n is even, return the average of the two middle values
    else median = (temp[n / 2 - 1] + temp[n / 2]) >> 1;

    // Destroy the temporary array
    free(temp);

    return median;
}

/*! @brief Calculate the median absolute deviation.
    @param array The input array.
    @param n The length of the array.
    @param median The median of the array.
    @return The median absolute deviation.
*/
int16_t HampelFilter::getMAD(int16_t *array, int16_t n, int16_t median)
{
    int32_t mad = 0;

    // Average the absolute deviations from the median
    for (int16_t i = 0; i < n; i++)
    {
        mad += (int32_t)abs(array[i] - median);
    }

    mad = mad / n;

    return (int16_t)mad;
}