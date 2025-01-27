#include <Bluepad32.h>

// Declare Bluepad32 object
Bluepad32 bp32;

GamepadPtr myGamepad;

// Pin for the built-in LED
const int LED_PIN = 2;

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
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  // Update the Bluepad32 instance
  bp32.update();

  // If a gamepad is connected
  if (myGamepad && myGamepad->isConnected()) {
    // Get the left stick Y-axis value
    int leftStickY = myGamepad->axisY(); // Range: -512 to 512

    // Map the stick value to LED brightness (0-255)
    int brightness = map(leftStickY, -512, 0, 0, 255);

    // Clamp the brightness to valid range (0-255)
    brightness = constrain(brightness, 0, 255);
    if (leftStickY > -20) {
      analogWrite(LED_PIN, 0);
    }
    
    // Set the LED brightness
    analogWrite(LED_PIN, brightness);

    Serial.print("Left Stick Y: ");
    Serial.print(leftStickY);
    Serial.print(" -> LED Brightness: ");
    Serial.println(brightness);
    
  }
}
