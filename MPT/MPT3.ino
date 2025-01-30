#include <Bluepad32.h>
const int MP1 =16;
GamepadPtr myGamepad;
float leftSticky = 0.0f;

void onGamepadConnected(GamepadPtr gp) {
    myGamepad = gp;
}

void setup() {
    Serial.begin(115200);
    BP32.setup(&onGamepadConnected);
    pinMode(MP1, OUTPUT);
    ledcSetup(0, 5000, 8); 
    ledcAttachPin(MP1, 0);
}

void loop() {
    BP32.update();
    if (myGamepad) {
        leftSticky = myGamepad->axisY();
    }
    Serial.println(leftSticky);
    ledcWrite(0, leftSticky);
}
