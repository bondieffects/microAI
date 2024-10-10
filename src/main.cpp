#include <Arduino.h>
#include <noise.h>
#include <statistics.h>

//Interrupt Service Routine(ISR) handle interupt when complete
//microcontroller wake up from sleep, main program continue
ISR(ADC_vect){

}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  int n = sizeof(noisyData16) / sizeof(uint16_t);
  //n /= sizeof(uint16_t);

  Serial.print("n: "); Serial.println(n);
  float val = mean(noisyData16, n);
  Serial.print("mean: "); Serial.println(val);

  val = variance(noisyData16, n, val);
  Serial.print("variance: "); Serial.println(val);

  val = stddev(val);
  Serial.print("standard deviation: "); Serial.println(val);

  val = median(noisyData16, n);
  Serial.print("median: "); Serial.println(val);

  val = mode(noisyData16, n);
  Serial.print("mode: "); Serial.println(val);
}

void loop() {
  // put your main code here, to run repeatedly:

}




