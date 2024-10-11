#include <Arduino.h>
#include <noise.h>
#include <statistics.h>

extern uint16_t *outputData;

//Interrupt Service Routine(ISR) handle interupt when complete
//microcontroller wake up from sleep, main program continue
ISR(ADC_vect){

}


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);


  uint16_t *inputData = hampelNoise;
  uint16_t n = sizeof(hampelNoise) / sizeof(uint16_t);

  //n /= sizeof(uint16_t);
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

  // Allocate some memory for the output array
  outputData = (uint16_t *)malloc(n * sizeof(uint16_t));
  hampel(inputData, n);
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
  

}

void loop() {
  // put your main code here, to run repeatedly:

}




