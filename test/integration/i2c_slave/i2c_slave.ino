#include <Wire.h>

bool status;

void setup() {
  Serial.begin(9600);
  Wire.begin(0x1A);
  Wire.onReceive(receiveEvent);
  Wire.onRequest(requestEvent);
  pinMode(13,OUTPUT);
  digitalWrite(13, LOW);
  status = false;
  Serial.println("setup done");
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(100);
}

void requestEvent() {
  Wire.write("test");
}

void receiveEvent(int howMany) {
  if (Wire.available()){
    char c;
    c = (char)Wire.read();
    Serial.println(c);
    if (status) {
      digitalWrite(13, LOW);
    }
    else {
      digitalWrite(13, HIGH);
    }
    status = !status;
  }
}
