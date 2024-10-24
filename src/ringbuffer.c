#include <ringbuffer.h>

/*! 
    @brief
        1. Initialises all values in the buffer to 0
        2. Initialises the number of items, readHead and writeHead to 0.
*/
void RingBuffer_Initialise(RingBuffer *buffer)
{
  // Clear the filter buffer
    for (uint8_t n=0; n < RING_BUFFER_LENGTH; n++) {
        buffer->buf[n] = 0.0f;
    }

    buffer->n = 0;
    buffer->readHead = 0;
    buffer->writeHead = 0;
}


/*!
    @brief 
*/
void RingBuffer_Push(RingBuffer *buffer, float data)
{
  // Add elements to the buffer
  //if (buffer->n < RING_BUFFER_LENGTH) {
  buffer->buf[buffer->writeHead] = data;
  buffer->writeHead = (buffer->writeHead + 1) % RING_BUFFER_LENGTH;
  buffer->n++;
  if (buffer->n >= RING_BUFFER_LENGTH) buffer->n = RING_BUFFER_LENGTH;
  //}
}

/*!
    @brief Reads the ___ element from the buffer and then removes it
*/
uint16_t RingBuffer_Pop(RingBuffer *buffer)
{
    // Read and remove elements from the buffer
    if (buffer->n > 0) {
        uint16_t value = buffer->buf[buffer->readHead];  // Read the next element
        buffer->readHead = (buffer->readHead + 1) % RING_BUFFER_LENGTH;
        buffer->n--;
        return value;
    }
    else return 0;
}