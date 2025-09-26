/*
Experiment 1: Pressure 
"Echoes of Pressure - Breathe and Heartbeat" Yubang
OCADU DIGF-6037 Creation & Computation - taught by Kate Hartman & Nick Puckett
*/

// LED pins
const int ledPins[15] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, A7};
const int numLEDs = 15;

// Pressure sensor pin
const int sensorPin = A0;

// Maximum pressure mapping value
const int maxPressure = 700;

// Wave effect speed
const int waveDelay = 50; // milliseconds

void setup() {
  for (int i = 0; i < numLEDs; i++) {
    pinMode(ledPins[i], OUTPUT);
    analogWrite(ledPins[i], 0); // Turn off all LEDs
  }
  Serial.begin(9600);
}

// Fade LED function
void fadeLED(int pin, int brightness) {
  analogWrite(pin, brightness);
}

void loop() {
  int pressure = analogRead(sensorPin);
  Serial.print("Pressure: ");
  Serial.println(pressure);

  if (pressure < 777) {
    // Pressure-controlled progress bar
    int ledsToLight = map(pressure, 150, maxPressure, 0, numLEDs);
    ledsToLight = constrain(ledsToLight, 0, numLEDs);

    // If pressure <= 150, no lights will be turned on. (The previous setting was 50)
      if (pressure <= 150) {
      ledsToLight = 0;
    }

    // First, fade out all LEDs
    for (int i = 0; i < numLEDs; i++) {
      fadeLED(ledPins[i], 0);
    }

    // Then, fade in the corresponding number of LEDs
    for (int i = 0; i < ledsToLight; i++) {
      for (int b = 0; b <= 255; b += 15) { // Gradually increase brightness
        fadeLED(ledPins[i], b);
        delay(5);
      }
    }

  } else {
    // Wave effect when pressure is 777 or higher
    for (int i = 0; i < numLEDs; i++) {
      // Turn off all LEDs first
      for (int j = 0; j < numLEDs; j++) fadeLED(ledPins[j], 0);

      // Fade in the current LED
      for (int b = 0; b <= 255; b += 25) {
        fadeLED(ledPins[i], b);
        delay(waveDelay / 10);
      }
    }
  }

  delay(50);
}
