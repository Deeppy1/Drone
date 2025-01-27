#include <Bluepad32.h>

// Declare Bluepad32 object
Bluepad32 bp32;

GamepadPtr myGamepad;

// Pin for the built-in LED
const int MotorPin1 = 2;
const int MotorPin2 = 3;
const int MotorPin3 = 4;
const int MotorPin4 = 5;

int VerticalSpeed 
int LeftSticky

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
}

void loop() {
  // Update the Bluepad32 instance
  bp32.update();

  // If a gamepad is connected
  if (myGamepad && myGamepad->isConnected()) {
    // Get the left stick Y-axis value
    LeftSticky = myGamepad->axisY(); // Range: -512 to 512

    // Map the stick value to LED VerticalSpeed (0-255)
    VerticalSpeed = map(LeftSticky, -512, 0, 0, 255);

    // Clamp the VerticalSpeed to valid range (0-255)
    VerticalSpeed = constrain(VerticalSpeed, 0, 255);
    if (LeftSticky > -20) {
      analogWrite(MotorPin1, 0);
    }
    
    // Set the LED VerticalSpeed
    analogWrite(MotorPin1, VerticalSpeed);

    Serial.print("Left Stick Y: ");
    Serial.print(LeftSticky);
    Serial.print(" -> Motor VerticalSpeed: ");
    Serial.println(VerticalSpeed);
    
  }
}
