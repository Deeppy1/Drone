const int MP1 = 16;
const int pot = 15;
int potval;
void setup(){
    pinMode(MP1, OUTPUT);
    pinMode(pot, INPUT);
    Serial.begin(115200);

  Serial.begin(115200);

  // Setup PWM for motor pins using native LEDC functions
  ledcSetup(0, 5000, 8); // Channel 0, 5kHz, 8-bit resolution
  ledcAttachPin(MP1, 0);
}

void Estop() {
  digitalWrite(MP1, 0);
}


void loop(){
    potval = analogRead(pot);
    Serial.println(potval);
    int potval2 = map(potval, 4095, 0, 1000, 0 );
    ledcWrite(0, potval2);
    
}
