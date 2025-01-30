const int MP1 = 16;
void setup(){
  Serial.begin(115200);
  pinMode(MP1, OUTPUT);
  ledcSetup(0, 5000, 8);
  ledcAttachPin(MP1, 0);
}
void loop(){
  Serial.println("digitalWrite");
  digitalWrite(MP1, 0);
  delay(3000);
  Serial.println("ledcWrite");
  ledcWrite(0, 0);
  delay(3000);
  Serial.println("analogWrite");
  analogWrite(MP1, 0);
  delay(3000);
}