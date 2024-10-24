#include <Arduino.h>
#include <HampelFilter.h>

// Create a Hampel filter object with a window size of 5 and a threshold of 3
//HampelFilter filter(5, 3.0);
//#include <noise.h>
//#include <statistics.h>

#include <fir.h>
#include <ringbuffer.h>
RingBuffer rb;
FIRFilter lpf;

/*
//Interrupt Service Routine(ISR) handle interupt when complete
//microcontroller wake up from sleep, main program continue
ISR(ADC_vect){
}
*/



void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("Setup begun");


  // Initialise the ring buffer
  //RingBuffer_Initialise(&rb);

  // Initialise the hampel filter
  //Hampel_Initialise(&hampel);

  //// HAMPEL DEMO ////
  // Allocate some memory for the output array
  //hampel(inputData, n);
  //// END HAMPEL DEMO /////

  //uint16_t n = BUFFER_SIZE * sizeof(uint16_t);
  /*
  Serial.print("n: "); Serial.println(n);
  float val = mean(inputData, n);
  Serial.print("mean: "); Serial.println(val);

  val = variance(inputData, n, val);
  Serial.print("variance: "); Serial.println(val);

  val = stddev(val);
  Serial.print("standard deviation: "); Serial.println(val);

  val = median(inputData, n);
  Serial.print("median: "); Serial.println(val);

  val = mode(inputData, n);
  Serial.print("mode: "); Serial.println(val);*/

  /*
  FIRFilter_Init(&lpf);
  for (uint16_t i = 0; i < n; i++) {
    outputData[i] = FIRFilter_Update(&lpf, inputData[i]);
  }
  */

  /*
  //// FIR DEMO ////

  */
  /*
  // Print the output
  Serial.print(">");
  Serial.print("inputData:"); 
  Serial.print(inputData[0]);
  Serial.print(",");

  Serial.print("OutputData:"); 
  Serial.print(outputData[0]);
  Serial.print(",");
  Serial.println();
  delay(10);

  for (uint16_t i = 1; i<n; i++) {
    Serial.print(">");
    Serial.print("inputData:"); Serial.print(inputData[i]); Serial.print(",");
    Serial.print("OutputData:"); Serial.print(outputData[i]); Serial.print(",");
    Serial.println();
    delay(10);
  }
  */
}

uint32_t t = 0;
uint32_t printTimer = 0;
#define PRINT_INTERVAL (100)

void loop() {
  // put your main code here, to run repeatedly:
  //t = millis();
  uint16_t val = analogRead(A0); 
  RingBuffer_Push(&rb, (float)val);
  float out = FIRFilter_Update(&lpf, rb.buf[rb.writeHead]);

  //float sensorValue = analogRead(A0);
  // Process the sensor value with the Hampel filter
  //float filteredValue = filter.process(sensorValue);

  if (t - printTimer > PRINT_INTERVAL) {
    printTimer = millis();

    // Output the result
    Serial.print(">");
    Serial.print("OriginalValue:");
    Serial.print(val);
    Serial.print(", FilteredValue:");
    Serial.println(out);
  }

}




