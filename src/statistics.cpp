#include <statistics.h>

float mean(uint16_t* x, int n) {
  
  float sum = 0;

  for (int i; i<n; i++) {
    sum+= x[i];
  }
  Serial.print("sum: "); Serial.println(sum);

  return sum / n;
}

float variance(uint16_t* x, int n, float mean) {

  float var = 0;

  // Step 2: Calculate the variance
  for (int i = 0; i < n; i++) {
      var += (x[i] - mean) * (x[i] - mean);
  }
  var /= n; // For population variance
  // variance /= (n - 1); // For sample variance

  return var;
}

float stddev(float variance)
{
  return sqrt(variance);
}

// Comparison function for qsort
int compare(const void* a, const void* b)
{
    return (*(int*)a - *(int*)b);
}


// Function to find the median of the array
float median(uint16_t* x, int n)
{
    // Sort the array in ascending order
    qsort(x, n, sizeof(int), compare);

    // If the size of the array is even, return the average
    // of the two middle elements
    if (n % 2 == 0) {
        return (x[n / 2 - 1] + x[n / 2]) / 2.0;
    }
    // If the size is odd, return the middle element
    // directly
    else {
        return x[n / 2];
    }
}

// mode
float mode(uint16_t *x, int n) {
  // Sort the array
  qsort(x, n, sizeof(uint16_t), compare);

  // Initialize mode variables
  int mode = x[0];
  int curr_count = 1;
  int max_count = 1;

  // Iterate through the sorted array to find the mode
  for (int i = 1; i < n; ++i) {
      if (x[i] == x[i - 1]) {
          // Increment the count if the current element is
          // equal to the previous one
          ++curr_count;
      }
      else {
          // Check if the count of the previous element is
          // greater than the maximum count
          if (curr_count > max_count) {
              max_count = curr_count;
              mode = x[i - 1];
          }
          // Reset the count for the current element
          curr_count = 1;
      }
  }

  // Check the count of the last element
  if (curr_count > max_count) {
      mode = x[n - 1];
  }

  return mode;
}