#ifndef FIRFILTER_H
#define FIRFILTER_H

#include <Arduino.h>

class FIRFilter {
  public:
    FIRFilter(int32_t *IR, uint8_t taps);
    ~FIRFilter(void);
    int16_t filter(int16_t input);

  private:
    int32_t *IR;      // Pointer to impulse response coefficients
    int16_t *x;       // Buffer for input samples
    uint8_t taps;     // Number of taps (coefficients)
};

/*!
    Filter Coefficients for a Low Pass Filter
    Filter Order: 64
    Type: Low Pass
    Filter Cutoff: 500 Hz
    Window Function: Hamming
    Sample Rate: 9615 Hz
*/
static int32_t LPF_500HZ[64] = {
    -49,   -39,   -25,    -4,    25,    62,   105,   151, 
    192,   217,   216,   178,    96,   -34,  -206,  -407, 
   -617,  -804,  -934,  -970,  -877,  -629,  -209,   385, 
   1137,  2015,  2969,  3939,  4860,  5662,  6286,  6681, 
   6816,  6681,  6286,  5662,  4860,  3939,  2969,  2015, 
   1137,   385,  -209,  -629,  -877,  -970,  -934,  -804, 
   -617,  -407,  -206,   -34,    96,   178,   216,   217, 
    192,   151,   105,    62,    25,    -4,   -25,   -39
};

/*!
    Filter Coefficients for a Low Pass Filter
    Filter Order: 64
    Type: Low Pass
    Filter Cutoff: 1000 Hz
    Window Function: Hamming
    Sample Rate: 9615 Hz
*/
static int32_t LPF_1000HZ[64] = {
     50,    59,    46,     8,   -48,  -102,  -126,   -94, 
      5,   144,   267,   299,   185,   -68,  -379,  -608, 
   -608,  -301,   257,   869,  1248,  1132,   414,  -755, 
  -1965, -2646, -2255,  -495,  2535,  6306,  9981, 12654, 
  13632, 12654,  9981,  6306,  2535,  -495, -2255, -2646, 
  -1965,  -755,   414,  1132,  1248,   869,   257,  -301, 
   -608,  -608,  -379,   -68,   185,   299,   267,   144, 
      5,   -94,  -126,  -102,   -48,     8,    46,    59
};

/*!
    Filter Coefficients for a Low Pass Filter
    Filter Order: 64
    Type: Low Pass
    Filter Cutoff: 2000 Hz
    Window Function: Hamming
    Sample Rate: 9615 Hz
*/
static int32_t LPF_2000HZ[64] = {
    -47,    19,    66,    15,   -81,   -73,    72,   151, 
     -9,  -225,  -127,   240,   325,  -134,  -526,  -138, 
    625,   560,  -494, -1040,    31,  1398,   802, -1390, 
  -1938,   728,  3209,   983, -4380, -4791,  5206, 20095, 
  27264, 20095,  5206, -4791, -4380,   983,  3209,   728, 
  -1938, -1390,   802,  1398,    31, -1040,  -494,   560, 
    625,  -138,  -526,  -134,   325,   240,  -127,  -225, 
     -9,   151,    72,   -73,   -81,    15,    66,    19
};

/*!
    Filter Coefficients for a High Pass Filter
    Filter Order: 64
    Type: High Pass
    Filter Cutoff: 500 Hz
    Window Function: Hamming
    Sample Rate: 9615 Hz
*/
static int32_t HPF_500HZ[64] = {
     49,    39,    25,     4,   -25,   -62,  -105,  -151, 
   -192,  -217,  -216,  -178,   -96,    34,   206,   407, 
    617,   804,   934,   970,   877,   629,   209,  -385, 
  -1137, -2015, -2969, -3939, -4860, -5662, -6286, -6681, 
  58720, -6681, -6286, -5662, -4860, -3939, -2969, -2015, 
  -1137,  -385,   209,   629,   877,   970,   934,   804, 
    617,   407,   206,    34,   -96,  -178,  -216,  -217, 
   -192,  -151,  -105,   -62,   -25,     4,    25,    39
};

/*!
    Filter Coefficients for a High Pass Filter
    Filter Order: 64
    Type: High Pass
    Filter Cutoff: 1000 Hz
    Window Function: Hamming
    Sample Rate: 9615 Hz
*/
static int32_t HPF_1000HZ[64] = {
    -50,   -59,   -46,    -8,    48,   102,   126,    94, 
     -5,  -144,  -267,  -299,  -185,    68,   379,   608, 
    608,   301,  -257,  -869, -1248, -1132,  -414,   755, 
   1965,  2646,  2255,   495, -2535, -6306, -9981, -12654, 
  51904, -12654, -9981, -6306, -2535,   495,  2255,  2646, 
   1965,   755,  -414, -1132, -1248,  -869,  -257,   301, 
    608,   608,   379,    68,  -185,  -299,  -267,  -144, 
     -5,    94,   126,   102,    48,    -8,   -46,   -59
};

/*!
    Filter Coefficients for a High Pass Filter
    Filter Order: 64
    Type: High Pass
    Filter Cutoff: 2000 Hz
    Window Function: Hamming
    Sample Rate: 9615 Hz
*/
static int32_t HPF_2000HZ[64] = {
     47,   -19,   -66,   -15,    81,    73,   -72,  -151, 
      9,   225,   127,  -240,  -325,   134,   526,   138, 
   -625,  -560,   494,  1040,   -31, -1398,  -802,  1390, 
   1938,  -728, -3209,  -983,  4380,  4791, -5206, -20095, 
  38272, -20095, -5206,  4791,  4380,  -983, -3209,  -728, 
   1938,  1390,  -802, -1398,   -31,  1040,   494,  -560, 
   -625,   138,   526,   134,  -325,  -240,   127,   225, 
      9,  -151,   -72,    73,    81,   -15,   -66,   -19
};



#endif
