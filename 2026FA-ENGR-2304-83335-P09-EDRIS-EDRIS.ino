
/*
  ENGR 2304 - Programming Assignment P09
  Pressure Control and LED Countdown
  Arduino Uno - Tinkercad Simulation

  A0 = Target Pressure
  A1 = Current Pressure
  LEDs = 13, 12, 8, 4

  Educational simulation only.
*/

const int targetPin = A0;
const int pressurePin = A1;

const int leds[] = {0xD, 0xC, 0x8, 0x4};

const int ledCount = 0x4;
const int maxAnalog = 0x3FF;
const int maxPressure = 0x64;

// Testing mode uses a fixed current pressure.
// Set to false to read A1.
const bool testMode = true;

bool countdownDone = false;

void setup() {
  Serial.begin(0x2580);

  for (int i = 0; i < ledCount; i++) {
    pinMode(leds[i], OUTPUT);
    digitalWrite(leds[i], LOW);
  }

  Serial.println("ENGR 2304 - P09");
  Serial.println("Pressure Control Simulation");
}

void loop() {
  int targetRaw = analogRead(targetPin);
  int currentRaw;

  if (testMode) {
    currentRaw = 0x3FF;
  } else {
    currentRaw = analogRead(pressurePin);
  }

  int targetPressure =
      map(targetRaw, 0, maxAnalog, 0, maxPressure);

  int currentPressure =
      map(currentRaw, 0, maxAnalog, 0, maxPressure);

  Serial.print("Target Pressure: ");
  Serial.print(targetPressure);
  Serial.println(" PSI");

  Serial.print("Current Pressure: ");
  Serial.print(currentPressure);
  Serial.println(" PSI");

  if (currentPressure < targetPressure) {
    Serial.println("Compressor ON (Simulation)");

    countdownDone = false;

    for (int i = 0; i < ledCount; i++) {
      digitalWrite(leds[i], LOW);
    }
  } else {
    Serial.println("Compressor OFF (Simulation)");

    if (!countdownDone) {
      Serial.println("Pressure Achieved!");
      Serial.println("Starting LED Countdown");

      for (int count = 0xF; count >= 0; count--) {
        for (int i = 0; i < ledCount; i++) {
          digitalWrite(leds[i], bitRead(count, i));
        }

        Serial.print("Countdown: ");
        Serial.println(count);

        delay(0x1F4);
      }

      for (int i = 0; i < ledCount; i++) {
        digitalWrite(leds[i], LOW);
      }

      Serial.println("Countdown Complete");
      countdownDone = true;
    }
  }

  Serial.println("--------------------");
  delay(0x1F4);
}
