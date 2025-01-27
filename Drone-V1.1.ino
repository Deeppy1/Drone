#include <Bluepad32.h>

// Declare Bluepad32 object
Bluepad32 bp32;

GamepadPtr myGamepad;
bool arm = False

//Motor Pins
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
void SetVerticalSpeed(int MotorSpeed){
    analogWrite(MotorPin1, MotorSpeed);
    analogWrite(MotorPin2, MotorSpeed);
    analogWrite(MotorPin3, MotorSpeed);
    analogWrite(MotorPin4, MotorSpeed);

}
void SetForwardSpeed(int FMotorSpeed){
    if (ForwardSpeed < 0) {
    ForwardSpeed = -ForwardSpeed;
  } else {
    ForwardSpeed = ForwardSpeed;
  }
    FMotorSpeed = (ForwardSpeed / 3)
    analogWrite(MotorPin1, MotorSpeed - FMotorSpeed);
    analogWrite(MotorPin2, MotorSpeed - FMotorSpeed);
    analogWrite(MotorPin3, MotorSpeed + FMotorSpeed);
    analogWrite(MotorPin4, MotorSpeed + FMotorSpeed);

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

    if (myGamepad->a()) {
      Serial.println("Button A pressed!");
      arm = True; // Turn LED on
    } 

    // Get the left stick Y-axis value
    LeftSticky = myGamepad->axisY(); // Range: -512 to 512

    // Map the stick value to LED VerticalSpeed (0-255)
    VerticalSpeed = map(LeftSticky, -512, 0, 0, 255);

    // Clamp the VerticalSpeed to valid range (0-255)
    VerticalSpeed = constrain(VerticalSpeed, 0, 255);
    if (LeftSticky > -20) {
      SetVerticalSpeed(0);

    }

    // Set the Motor Vertical Speed
    RightSticky = myGamepad->axisRY()
    ForwardSpeed = map(RightSticky, -512, 0 , 255)


    if(arm == True){
      Serial.print("Left Stick Y: ");
      Serial.print(LeftSticky);
      Serial.print(" -> Motor Vertical Speed: ");
      Serial.println(VerticalSpeed);
      SetVerticalSpeed(LeftSticky);
      Serial.print("Right Stick Y: ");
      Serial.print(RightSticky);
      Serial.print(" -> Motor Vertical Speed: ");
      Serial.println(ForwardSpeed);
      SetVerticalSpeed(LeftSticky);
      SetForwardSpeed(RightSticky)
    }else(){
      Serial.println("Drone unarmed")
      delay(500)
    }
  }
}
