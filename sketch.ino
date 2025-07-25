#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>

#define DHTPIN 3
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

LiquidCrystal_I2C lcd(0x27, 16, 2);

const int switchPin = 2;
const int buzzerPin = 7;
const int ledPins[] = {8, 9, 10, 11, 12};

String stages[] = {
  "IDLE", "HEATING", "STABILIZING", "TARGET OK", "OVERHEAT"
};

float temperature = 0.0;
int currentStage = 0;

bool heatingActive = false;
bool overheatTriggered = false;
bool testMode = true;  // SET TO FALSE for real DHT behavior

unsigned long lastTempUpdate = 0;
unsigned long lastLCDUpdate = 0;
unsigned long overheatStartTime = 0;

const unsigned long lcdUpdateInterval = 1000;
const unsigned long overheatHoldTime = 5000;
const unsigned long tempStepInterval = 6000;

int tempStep = 0;
float tempSequence[] = {23.0, 30.0, 34.0, 37.0, 40.0};

void setup() {
  lcd.init();
  lcd.backlight();
  dht.begin();

  pinMode(switchPin, INPUT_PULLUP);
  pinMode(buzzerPin, OUTPUT);

  for (int i = 0; i < 5; i++) {
    pinMode(ledPins[i], OUTPUT);
    digitalWrite(ledPins[i], LOW);
  }

  lcd.setCursor(0, 0);
  lcd.print("Smart Heater Init");
  delay(1000);
  lcd.clear();
}

void updateLEDs() {
  for (int i = 0; i < 5; i++) {
    digitalWrite(ledPins[i], (i == currentStage) ? HIGH : LOW);
  }
}

void simulateTemperature() {
  unsigned long now = millis();
  if (now - lastTempUpdate >= tempStepInterval) {
    if (tempStep < sizeof(tempSequence) / sizeof(float)) {
      temperature = tempSequence[tempStep];
      tempStep++;
    } else {
      temperature = tempSequence[sizeof(tempSequence) / sizeof(float) - 1];
    }
    lastTempUpdate = now;
  }
}

void determineStageFromTemp() {
  if (temperature < 25) currentStage = 0;
  else if (temperature < 32) currentStage = 1;
  else if (temperature < 36) currentStage = 2;
  else if (temperature < 39) currentStage = 3;
  else currentStage = 4;
}
void loop() {
  unsigned long now = millis();

  // === Check for switch press to start heating ===
  if (!heatingActive && digitalRead(switchPin) == LOW) {
    heatingActive = true;
    lcd.clear();
    lastTempUpdate = now; // reset simulation timing
    tempStep = 0;
  }

  // === All logic only runs after switch is pressed ===
  if (heatingActive) {
    // === Temperature update ===
    if (testMode) {
      simulateTemperature();
    } else {
      float t = dht.readTemperature();
      if (!isnan(t)) {
        temperature = t;
      }
    }

    determineStageFromTemp();
    updateLEDs();

    // === Overheat detection ===
    if (currentStage == 4 && !overheatTriggered) {
      overheatTriggered = true;
      overheatStartTime = now;
    }

    // === Auto reset after overheat hold ===
    if (overheatTriggered && (now - overheatStartTime >= overheatHoldTime)) {
      heatingActive = false;
      overheatTriggered = false;
      currentStage = 0;
      tempStep = 0;
      updateLEDs();
    }

    // === Buzzer during overheat ===
    if (currentStage == 4) {
      tone(buzzerPin, 1000);
    } else {
      noTone(buzzerPin);
    }
  } else {
    noTone(buzzerPin);  // ensure buzzer is off before starting
  }

  // === LCD Update ===
  if (now - lastLCDUpdate >= lcdUpdateInterval) {
    lastLCDUpdate = now;
    lcd.setCursor(0, 0);
    lcd.print("Temp: ");
    lcd.print(temperature);
    lcd.print((char)223);
    lcd.print("C   ");

    lcd.setCursor(0, 1);
    lcd.print("Stage: ");
    lcd.print(stages[currentStage]);
    lcd.print("     ");
  }
}
