#include<SPI.h>

volatile byte received_data;
volatile bool received;

void setup() {
  Serial.begin(9600);
  pinMode(MISO,OUTPUT);
  SPCR |= _BV(SPE);
  SPI.attachInterrupt();
  digitalWrite(13, LOW);
  Serial.println("setup done");
}

void loop() {
  if (received) {
    Serial.println("received");
    Serial.println(received_data);
    Serial.println((char)received_data);
    received = false;
  }
  SPDR = 'C';
  delay(100);
}

ISR (SPI_STC_vect) {
  received_data = SPDR;                  
  received = true;
}
