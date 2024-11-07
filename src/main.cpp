#include <Arduino.h>


// SAMPLE RATE 9615 HZ //

//#define DEBUG_PRINTS 1
//#define FIR 1
//#define IIR 1
#define HAMPEL 1
//#define MA 1

uint32_t t = 0;

#ifdef DEBUG_PRINTS
  uint32_t printTimer = 0;
  #define PRINT_INTERVAL (100)
#endif

#ifdef FIR
  #include <FIRFilter.h>
  // Create FIRFilter object with the coefficients, number of taps, and scaling factor
  FIRFilter fir(LPF_2000HZ, 64);
#endif

#ifdef IIR
  #include "IIRFilter.h"
  // Initialize the filter with the coefficients and order (2 for a second-order filter)
  IIRFilter iir(LPF_2KHZ_A, LPF_2KHZ_B, 2);
#endif

#ifdef HAMPEL
  #include <HampelFilter.h>
  // Create a Hampel filter object with a window size of 5 and a threshold of 3.0
  HampelFilter hampel(5, 3.0f);

  // Hampel works best if we give it enough time to create an outlier
  #define HAMPEL_INTERVAL (500)
  uint32_t hampelTimer = 0;
#endif

#ifdef MA
  #include "MAFilter.h"
  const int n = 40;
  int8_t read = n/2;
  int8_t write = 0;
  MAFilter Mafilter(n);
  int16_t delayhold[n];
#endif

void setup() {
  // put your setup code here, to run once:
  #ifdef DEBUG_PRINTS
    Serial.begin(115200);
    Serial.println("Setup begun");
  #endif

  // MA filter delays output, so this shifts graph back inline
  #ifdef MA 
  for(int i = 0; i < n; i++){
    delayhold[i] = 0;
  }
  #endif
  //analogWrite(3, 127);
}



void loop() {
  // put your main code here, to run repeatedly:
  t = millis();

  int16_t input = Serial.parseInt();
  int32_t output;

  #ifdef FIR
    // Apply the FIR filter
    output = fir.filter(input);
  #endif
  #ifdef IIR
    output = iir.filter(input);
  #endif
  
  #ifdef HAMPEL
    if (t - hampelTimer > HAMPEL_INTERVAL) {
      hampelTimer = millis();
      output = hampel.filter(input);
    }
  #endif

  #ifdef MA
    output = Mafilter.filter(input);
  #endif

  #ifdef DEBUG_PRINTS

        // MA filter is delayed, so this shifts graph back inline.
    #ifdef MA
      delayhold[write] = input;
      write++;
      if(write >= n){
          write= 0;
      }
      input = delayhold[read];
      read++;
      if(read >= n){
          read = 0;
       }
    #endif

    //if (t - printTimer > PRINT_INTERVAL) {
      //printTimer = millis();

      // Output the result
      //Serial.print(">");
      //Serial.print("OriginalValue:");
      //Serial.println(input);
      //Serial.print("> FilteredValue:");
      Serial.println(output);
    //}
  #endif

}