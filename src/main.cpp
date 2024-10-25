#include <Arduino.h>
#include <HampelFilter.h>

// SAMPLE RATE 9615 HZ //

// Create a Hampel filter object with a window size of 5 and a threshold of 3
//HampelFilter filter(5, 3.0);

#include <FIRFilter.h>
// Create FIRFilter object with the coefficients, number of taps, and scaling factor
FIRFilter myFilter(LPF_2000HZ, 64);

#include "IIRFilter.h"
// Initialize the filter with the coefficients and order (2 for a second-order filter)
IIRFilter myIIRFilter(LPF_2KHZ_A, LPF_2KHZ_B, 2);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("Setup begun");
}

uint32_t t = 0;
uint32_t printTimer = 0;
#define PRINT_INTERVAL (100)

void loop() {
  // put your main code here, to run repeatedly:
  t = millis();


  int16_t input = analogRead(A0);
  // Apply the FIR filter
  //int16_t output = myFilter.process(input);

  int16_t output = myIIRFilter.process(input);

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




