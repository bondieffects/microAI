#include <Arduino.h>
#include <HampelFilter.h>

// SAMPLE RATE 9615 HZ //

// #define FIR 1
//#define IIR 1
#define HAMPEL 1

uint32_t t = 0;
uint32_t printTimer = 0;
#define PRINT_INTERVAL (100)

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
  // Create a Hampel filter object with a window size of 5 and a threshold of 1
  HampelFilter hampel(5, 1);

  // Hampel works best if we give it enough time to create an outlier
  #define HAMPEL_INTERVAL (500)
  uint32_t hampelTimer = 0;
#endif

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("Setup begun");
}



void loop() {
  // put your main code here, to run repeatedly:
  t = millis();


  int16_t input = analogRead(A0);
  int32_t output;

  #ifdef FIR
    // Apply the FIR filter
    output = fir.process(input);
  #endif
  #ifdef IIR
    output = iir.process(input);
  #endif
  
  #ifdef HAMPEL
    if (t - hampelTimer > HAMPEL_INTERVAL) {
      hampelTimer = millis();
      output = hampel.process(input);
    }
  #endif



  //float sensorValue = analogRead(A0);
  // Process the sensor value with the Hampel filter
  //float filteredValue = filter.process(sensorValue);

  if (t - printTimer > PRINT_INTERVAL) {
    printTimer = millis();

    // Output the result
    Serial.print(">");
    Serial.print("OriginalValue:");
    Serial.print(input);
    Serial.print(", FilteredValue:");
    Serial.println(output);
  }

}




