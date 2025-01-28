const int MP1 = 16;

void setup(){
    PinMode(MP1, OUTPUT);
}
void loop(){
    digitalWrite(MP1, HIGH);
    delay(3000);
    digitalWrite(MP1, LOW);
    delay(3000);
}