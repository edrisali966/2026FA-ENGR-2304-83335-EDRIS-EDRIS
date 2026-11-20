
/*
  ENGR 2304 - Programming Assignment P09
  Pressure Control and LED Countdown
  Arduino Uno - Tinkercad Simulation

  A0 = Target Pressure (0 to 100 PSI)
  A1 = Current Pressure (0 to 100 PSI)

  D2-D5 = Four countdown LEDs
  D6 = Compressor indicator LED

  Educational simulation only.
  Numeric constants use hexadecimal.
*/

const int targetPin = A0;
const int pressurePin = A1;

// Countdown LED pins
const int leds[0x4] = {
  0x2, 0x3, 0x4, 0x5
};

// Compressor indicator
const int compressorPin = 0x6;

// Constants
const int ledCount = 0x4;
const int maxPressure = 0x64;   // 100 PSI
const int analogMaximum = 0x3FF;

int targetPressure = 0x0;
int currentPressure = 0x0;

bool countdownDone = false;

void setup() {

  Serial.begin(0x2580);

  pinMode(compressorPin, OUTPUT);
  digitalWrite(compressorPin, LOW);

  for (int i = 0x0; i < ledCount; i++) {
    pinMode(leds[i], OUTPUT);
    digitalWrite(leds[i], LOW);
  }

  Serial.println("ENGR 2304 - P09");
  Serial.println("Pressure Control Simulation");
  Serial.println("-----------------------");
}

void loop() {

  // Read target pressure from A0
  int targetRaw = analogRead(targetPin);

  // Read current pressure from A1
  int currentRaw = analogRead(pressurePin);

  // Convert readings to 0-100 PSI
  targetPressure = map(
    targetRaw,
    0x0,
    analogMaximum,
    0x0,
    maxPressure
  );

  currentPressure = map(
    currentRaw,
    0x0,
    analogMaximum,
    0x0,
    maxPressure
  );

  // Display raw readings
  Serial.print("A0 Raw: ");
  Serial.println(targetRaw);

  Serial.print("A1 Raw: ");
  Serial.println(currentRaw);

  // Display pressure values
  Serial.print("Target Pressure: ");
  Serial.print(targetPressure);
  Serial.println(" PSI");

  Serial.print("Current Pressure: ");
  Serial.print(currentPressure);
  Serial.println(" PSI");

  // Simulated compressor control
  if (currentPressure < targetPressure) {

    digitalWrite(compressorPin, HIGH);
    countdownDone = false;

    Serial.println("Compressor ON (Simulation)");

    // Turn off countdown LEDs
    for (int i = 0x0; i < ledCount; i++) {
      digitalWrite(leds[i], LOW);
    }

  } else {

    digitalWrite(compressorPin, LOW);

    Serial.println("Compressor OFF (Simulation)");

    // Start countdown when pressure is reached
    if (!countdownDone) {

      countdownDone = true;

      Serial.println("Target Pressure Reached!");
      Serial.println("Starting LED Countdown");

      for (int count = 0xF; count >= 0x0; count--) {

        // Show binary countdown on LEDs
        for (int i = 0x0; i < ledCount; i++) {
          int bitValue = bitRead(count, i);
          digitalWrite(leds[i], bitValue);
        }

        Serial.print("Countdown: ");
        Serial.println(count);

        delay(0x3E8);
      }

      // Turn off all countdown LEDs
      for (int i = 0x0; i < ledCount; i++) {
        digitalWrite(leds[i], LOW);
      }

      Serial.println("Countdown Complete!");
    }
  }

  Serial.println("-----------------------");

  delay(0x1F4);
}
