#include <MAFilter.h>


/*! @brief Constructor: Initialises the Moving Average Filter
     length of buffer.
    @param n_average Select how many samples to average together
*/
MAFilter::MAFilter(uint8_t n_average) {
    uint8_t n = n_average +1;
    this->n_average = n;
    this->n_last = 0;
    this->buffer = new int16_t[n];  // Allocate buffer for previous inputs
    memset(this->buffer, 0, n * sizeof(int16_t));  // Initialize buffer to 0
}


/*!
    @brief Processes the input signal and returns the filtered output.
    @param input The current input signal.
    @return The filtered output signal.
    @note 
*/
int16_t MAFilter::process(int16_t input) {
    int16_t output;
    int32_t sum;
    sum = 0;
    output = 0;
    if(n_last >= n_average){
        buffer[n_last-n_average] = input;
        for(int8_t i = 0; i < n_average -1; i++){
            sum += buffer[i];
        }

        output = sum/(n_average-1);

    } else {
        buffer[n_last] = input;
    }

    n_last++;

    if (n_last >= 2*n_average){
        n_last -=n_average;
    }

    return output;
}