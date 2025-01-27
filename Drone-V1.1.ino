#include <Bluepad32.h>

// Declare Bluepad32 object
Bluepad32 bp32;

GamepadPtr myGamepad;

//Motor Pins
const int MotorPin1 = 2;
const int MotorPin2 = 3;
const int MotorPin3 = 4;
const int MotorPin4 = 5;

int VerticalSpeed 
int LeftSticky

int RightSticky
// Callback when a gamepad is connected
void onGamepadConnected(GamepadPtr gp) {
  Serial.println("Gamepad connected!");
  myGamepad = gp;
}

// Callback when a gamepad is disconnected
void onGamepadDisconnected(GamepadPtr gp) {
  Serial.println("Gamepad disconnected!");
  myGamepad = nullptr;
}

void setup() {
  Serial.begin(115200);

  // Initialize Bluepad32
  bp32.setup(&onGamepadConnected, &onGamepadDisconnected);

  // Set up the built-in LED
  pinMode(MotorPin1, OUTPUT);
  pinMode(MotorPin2, OUTPUT);
  pinMode(MotorPin3, OUTPUT);
  pinMode(MotorPin4, OUTPUT);
}

void loop() {
  // Update the Bluepad32 instance
  bp32.update();

  // If a gamepad is connected
  if (myGamepad && myGamepad->isConnected()) {
    // Get the left stick Y-axis value
    LeftSticky = myGamepad->axisLY(); // Range: -512 to 512
    RightSticky = myGamepad->axisRY();
    // Map the stick value to LED VerticalSpeed (0-255)
    VerticalSpeed = map(LeftSticky, -512, 0, 0, 255);

    // Clamp the VerticalSpeed to valid range (0-255)
    VerticalSpeed = constrain(VerticalSpeed, 0, 255);
    if (LeftSticky > -20) {
      SetVerticalSpeed(0);

    }
    void SetVerticalSpeed(int MotorSpeed){
      analogWrite(MotorPin1, MotorSpeed);
      analogWrite(MotorPin2, MotorSpeed);
      analogWrite(MotorPin3, MotorSpeed);
      analogWrite(MotorPin4, MotorSpeed);

    }
    // Set the Motor Vertical Speed
    Void 

    Serial.print("Left Stick Y: ");
    Serial.print(LeftSticky);
    Serial.print(" -> Motor Vertical Speed: ");
    Serial.println(VerticalSpeed);
    SetVerticalSpeed(LeftSticky);
  }
}
