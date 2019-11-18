void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial1.begin(115200);
}

void loop() {
  byte data = 0;
  // put your main code here, to run repeatedly:
  if(Serial1.available() >= 4) {
    for(int i = 0; i != 4; i++) {
      data = Serial1.read();
      Serial.print(data, DEC);
      Serial.print(", ");
    }
    Serial.print("\n");
  }
}
