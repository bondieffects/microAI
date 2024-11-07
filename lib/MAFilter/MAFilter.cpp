#include <MAFilter.h>


/*! @brief Constructor: Initialise the Moving Average Filter object.
        1. Set the number of taps
        2. Set the index
        3. Allocate memory for the input buffer
    @param taps Select how many samples to average together
*/
MAFilter::MAFilter(uint8_t taps) 
{
    this->taps = (taps + 1);
    index = 0;
    x = (int16_t *)calloc((taps + 1), sizeof(int16_t));
}

/*! @brief Destructor: Free up memory allocated to the buffer
*/
MAFilter::~MAFilter(void)
{
    if (x) {
        free(x);
        x = NULL;
    }
}

/*!
    @brief Process the input through the Moving Average Filter.
    @param input the input sample.
    @return The Moving Average Filtered output.
    @note 
*/
int16_t MAFilter::filter(int16_t input) {

    // Confirm that buffer memory has been allocated before proceeding
    if (x == NULL) return input;

    int16_t output = 0;
    int32_t sum = 0;

    if(index >= taps) {

        x[index-taps] = input;

        for(int8_t i = 0; i < taps -1; i++){
            sum += x[i];
        }

        output = sum / (taps-1);
    }
    else {
        x[index] = input;
    }

    index++;

    if (index >= (2 * taps)){
        index -=taps;
    }

    return output;
}