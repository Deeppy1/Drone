#include <Bluepad32.h>

// Declare Bluepad32 object
Bluepad32 bp32;

GamepadPtr myGamepad;
bool arm = 0; // Arming flag

// Motor Pins (Use PWM-capable pins on the ESP32)
const int MotorPin1 = 16;
const int MotorPin2 = 17;
const int MotorPin3 = 18;
const int MotorPin4 = 19;

int MotorSpeed = 0;
int VerticalSpeed = 0;
int LeftSticky = 0;
int ForwardSpeed = 0;
int RightSticky = 0;

// Timer for non-blocking delays
unsigned long previousMillis = 0;
const unsigned long interval = 500; // 500ms interval for status messages

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

// Set all motor speeds to the same value (vertical control)
void SetVerticalSpeed(int MotorSpeed) {
  ledcWrite(0, MotorSpeed);
  ledcWrite(1, MotorSpeed);
  ledcWrite(2, MotorSpeed);
  ledcWrite(3, MotorSpeed);
}

// Set forward/backward speed (differential control)
void SetForwardSpeed(int FMotorSpeed) {
  FMotorSpeed = abs(FMotorSpeed) / 3; // Scale forward speed
  ledcWrite(0, MotorSpeed - FMotorSpeed);
  ledcWrite(1, MotorSpeed - FMotorSpeed);
  ledcWrite(2, MotorSpeed + FMotorSpeed);
  ledcWrite(3, MotorSpeed + FMotorSpeed);
}

// Emergency stop function (sets all motors to zero)
void Estop() {
  digitalWrite(MotorPin1, 0);
  digitalWrite(MotorPin2, 0);
  digitalWrite(MotorPin3, 0);
  digitalWrite(MotorPin4, 0);
}

void setup() {
  Serial.begin(115200);

  // Initialize Bluepad32
  bp32.setup(&onGamepadConnected, &onGamepadDisconnected);

  // Setup PWM for motor pins using native LEDC functions
  ledcSetup(0, 5000, 8); // Channel 0, 5kHz, 8-bit resolution
  ledcAttachPin(MotorPin1, 0);

  ledcSetup(1, 5000, 8); // Channel 1, 5kHz, 8-bit resolution
  ledcAttachPin(MotorPin2, 1);

  ledcSetup(2, 5000, 8); // Channel 2, 5kHz, 8-bit resolution
  ledcAttachPin(MotorPin3, 2);

  ledcSetup(3, 5000, 8); // Channel 3, 5kHz, 8-bit resolution
  ledcAttachPin(MotorPin4, 3);
}

void loop() {
  // Update the Bluepad32 instance
  bp32.update();

  // Non-blocking delay for status messages
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    if (!myGamepad || !myGamepad->isConnected()) {
      Estop();
      Serial.println("No controller connected");
    }
  }

  // Process gamepad inputs if connected
  if (myGamepad && myGamepad->isConnected()) {
    // Toggle arming state with the "A" button
    if (myGamepad->a()) {
      arm = !arm; // Toggle arm state
      Serial.println(arm ? "Drone armed" : "Drone disarmed");
      delay(300); // Debounce delay
    }

    // Read gamepad sticks
    LeftSticky = myGamepad->axisY();    // Vertical control
    RightSticky = myGamepad->axisRY(); // Forward control

    // Map and constrain stick values
    VerticalSpeed = map(LeftSticky, -512, -30, 255, 0);
    VerticalSpeed = constrain(VerticalSpeed, 0, 255);

    ForwardSpeed = map(RightSticky, -512, 512, -255, 255); // Allow negative for reverse
    ForwardSpeed = constrain(ForwardSpeed, -255, 255);

    if (arm) {
      // Set motor speeds based on stick inputs
      if (abs(LeftSticky) > -30) { // Dead zone for stability
        ledcWrite(0, MotorSpeed);
        ledcWrite(1, MotorSpeed);
        ledcWrite(2, MotorSpeed);
        ledcWrite(3, MotorSpeed);
        
      } else {
        //SetVerticalSpeed(VerticalSpeed);
        //SetForwardSpeed(ForwardSpeed);
      }

      // Debug output for motor speeds
      Serial.print("Left Stick Y: ");
      Serial.print(LeftSticky);
      Serial.print(" -> Motor Vertical Speed: ");
      Serial.println(VerticalSpeed);

      //Serial.print("Right Stick Y: ");
      //Serial.print(RightSticky);
      //Serial.print(" -> Motor Forward Speed: ");
      //Serial.println(ForwardSpeed);
    } else {
      // Drone unarmed
      Estop();
      Serial.println("Drone unarmed. Waiting for arm command.");
    }
  } else {
    // No controller connected
    Estop();
  }
}
