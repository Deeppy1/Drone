#include <Bluepad32.h>

GamepadPtr myGamepad;
float leftSticky = 0.0f;

void onGamepadConnected(GamepadPtr gp) {
    myGamepad = gp;
}

void setup() {
    Serial.begin(115200);
    BP32.setup(&onGamepadConnected);
}

void loop() {
    BP32.update();
    if (myGamepad) {
        leftSticky = myGamepad->axisY();
    }
    Serial.println(leftSticky);
}
