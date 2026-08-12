// Smart Toxic Gas Early-Warning & Worker Safety System
// LT HackFest 2026

// Smart Toxic Gas Early-Warning & Worker Safety System
// LT HackFest 2026

// ================================================================
// SMART TOXIC GAS EARLY-WARNING & WORKER SAFETY SYSTEM
// LT HackFest 2026
// Controller: ESP32
// ================================================================

// -------------------- LIBRARIES --------------------
#include <Wire.h>
#include <SPI.h>
#include <MFRC522.h>
#include <DHT.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// -------------------- OLED --------------------
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

#define OLED_SDA 21
#define OLED_SCL 22

Adafruit_SSD1306 display(
  SCREEN_WIDTH,
  SCREEN_HEIGHT,
  &Wire,
  -1
);

// -------------------- DHT11 --------------------
#define DHT_PIN 4
#define DHT_TYPE DHT11

DHT dht(DHT_PIN, DHT_TYPE);

// -------------------- MQ-135 --------------------
#define GAS_SENSOR_PIN 34

// Prototype thresholds.
// These values MUST be calibrated for the actual sensor.
const int GAS_WARNING_LEVEL = 1400;
const int GAS_DANGER_LEVEL  = 2000;

// -------------------- RFID RC522 --------------------
#define RFID_SS_PIN 5
#define RFID_RST_PIN 27

#define RFID_SCK_PIN 18
#define RFID_MISO_PIN 19
#define RFID_MOSI_PIN 23

MFRC522 rfid(
  RFID_SS_PIN,
  RFID_RST_PIN
);

// -------------------- OUTPUTS --------------------
#define RED_LED     26
#define YELLOW_LED  14
#define GREEN_LED   12

#define BUZZER_PIN  25

// Fan control pin.
// DO NOT connect a fan directly to this GPIO.
// Use a suitable transistor/MOSFET driver.
#define FAN_PIN     33

// -------------------- EMERGENCY BUTTON --------------------
#define EMERGENCY_BUTTON 13

// -------------------- WORKER ACCOUNTABILITY --------------------
const int MAX_WORKERS = 20;

String workerUIDs[MAX_WORKERS];
bool workerPresent[MAX_WORKERS];

int workerCount = 0;

// -------------------- SYSTEM STATES --------------------
enum SystemState {
  SAFE,
  WARNING,
  DANGER,
  EMERGENCY
};

SystemState currentState = SAFE;

// -------------------- TIMING --------------------
unsigned long lastSensorRead = 0;
const unsigned long SENSOR_INTERVAL = 2000;

unsigned long lastDisplayUpdate = 0;
const unsigned long DISPLAY_INTERVAL = 1000;


// ================================================================
// SETUP
// ================================================================

void setup() {

  Serial.begin(115200);

  // -------------------- OUTPUT PINS --------------------
  pinMode(RED_LED, OUTPUT);
  pinMode(YELLOW_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);

  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(FAN_PIN, OUTPUT);

  // Emergency button uses internal pull-up resistor
  pinMode(EMERGENCY_BUTTON, INPUT_PULLUP);

  // Start with safe outputs
  digitalWrite(RED_LED, LOW);
  digitalWrite(YELLOW_LED, LOW);
  digitalWrite(GREEN_LED, HIGH);

  digitalWrite(BUZZER_PIN, LOW);
  digitalWrite(FAN_PIN, LOW);

  // -------------------- DHT --------------------
  dht.begin();

  // -------------------- OLED --------------------
  Wire.begin(OLED_SDA, OLED_SCL);

  if (!display.begin(
        SSD1306_SWITCHCAPVCC,
        0x3C
      )) {

    Serial.println("OLED initialization failed!");
  }
  else {

    Serial.println("OLED initialized.");

    display.clearDisplay();
    display.setTextColor(SSD1306_WHITE);

    display.setTextSize(1);
    display.setCursor(0, 0);
    display.println("SMART GAS SAFETY");

    display.setCursor(0, 20);
    display.println("ESP32 Starting...");

    display.display();

    delay(2000);
  }

  // -------------------- RFID --------------------
  SPI.begin(
    RFID_SCK_PIN,
    RFID_MISO_PIN,
    RFID_MOSI_PIN,
    RFID_SS_PIN
  );

  rfid.PCD_Init();

  Serial.println("RFID initialized.");

  // -------------------- START MESSAGE --------------------
  Serial.println();
  Serial.println("================================");
  Serial.println(" SMART TOXIC GAS SAFETY SYSTEM");
  Serial.println(" LT HackFest 2026");
  Serial.println("================================");
  Serial.println("System started successfully.");
  Serial.println();
}


// ================================================================
// MAIN LOOP
// ================================================================

void loop() {

  // Check emergency button
  checkEmergencyButton();

  // Read sensors periodically
  if (millis() - lastSensorRead >= SENSOR_INTERVAL) {

    lastSensorRead = millis();

    readSensors();
  }

  // Check RFID continuously
  checkRFID();

  // Update OLED
  if (millis() - lastDisplayUpdate >= DISPLAY_INTERVAL) {

    lastDisplayUpdate = millis();

    updateDisplay();
  }
}


// ================================================================
// READ SENSORS
// ================================================================

void readSensors() {

  // Read MQ-135
  int gasValue = analogRead(GAS_SENSOR_PIN);

  // Read DHT11
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  // Print values to Serial Monitor
  Serial.println("------------------------------");

  Serial.print("Gas Value: ");
  Serial.println(gasValue);

  if (isnan(temperature)) {

    Serial.println("Temperature: Sensor Error");

  } else {

    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.println(" C");
  }

  if (isnan(humidity)) {

    Serial.println("Humidity: Sensor Error");

  } else {

    Serial.print("Humidity: ");
    Serial.print(humidity);
    Serial.println(" %");
  }

  Serial.print("Workers Present: ");
  Serial.println(workerCount);

  // Determine system state
  if (currentState != EMERGENCY) {

    if (gasValue >= GAS_DANGER_LEVEL) {

      currentState = DANGER;

    }
    else if (gasValue >= GAS_WARNING_LEVEL) {

      currentState = WARNING;

    }
    else {

      currentState = SAFE;
    }
  }

  // Apply output actions
  applySafetyActions();

  // Print status
  Serial.print("System Status: ");

  if (currentState == SAFE) {
    Serial.println("SAFE");
  }
  else if (currentState == WARNING) {
    Serial.println("WARNING");
  }
  else if (currentState == DANGER) {
    Serial.println("DANGER");
  }
  else {
    Serial.println("EMERGENCY");
  }
}


// ================================================================
// SAFETY ACTIONS
// ================================================================

void applySafetyActions() {

  // Turn everything OFF first
  digitalWrite(RED_LED, LOW);
  digitalWrite(YELLOW_LED, LOW);
  digitalWrite(GREEN_LED, LOW);

  digitalWrite(BUZZER_PIN, LOW);
  digitalWrite(FAN_PIN, LOW);


  // ---------------- SAFE ----------------

  if (currentState == SAFE) {

    digitalWrite(GREEN_LED, HIGH);

    // Fan OFF during safe condition
    digitalWrite(FAN_PIN, LOW);
  }


  // ---------------- WARNING ----------------

  else if (currentState == WARNING) {

    digitalWrite(YELLOW_LED, HIGH);

    // Ventilation demonstration
    digitalWrite(FAN_PIN, HIGH);

    // Slow warning beeps can be implemented later
  }


  // ---------------- DANGER ----------------

  else if (currentState == DANGER) {

    digitalWrite(RED_LED, HIGH);

    digitalWrite(BUZZER_PIN, HIGH);

    // Turn ventilation ON
    digitalWrite(FAN_PIN, HIGH);
  }


  // ---------------- EMERGENCY ----------------

  else if (currentState == EMERGENCY) {

    digitalWrite(RED_LED, HIGH);

    digitalWrite(BUZZER_PIN, HIGH);

    digitalWrite(FAN_PIN, HIGH);
  }
}


// ================================================================
// EMERGENCY BUTTON
// ================================================================

void checkEmergencyButton() {

  if (digitalRead(EMERGENCY_BUTTON) == LOW) {

    currentState = EMERGENCY;

    Serial.println();
    Serial.println("!!! EMERGENCY BUTTON PRESSED !!!");

    applySafetyActions();

    delay(300);
  }
}


// ================================================================
// RFID WORKER ACCOUNTABILITY
// ================================================================

void checkRFID() {

  // No new RFID card
  if (!rfid.PICC_IsNewCardPresent()) {
    return;
  }

  // Cannot read card
  if (!rfid.PICC_ReadCardSerial()) {
    return;
  }

  // Create UID string
  String uid = "";

  for (byte i = 0; i < rfid.uid.size; i++) {

    if (rfid.uid.uidByte[i] < 0x10) {
      uid += "0";
    }

    uid += String(
      rfid.uid.uidByte[i],
      HEX
    );
  }

  uid.toUpperCase();

  Serial.println();
  Serial.print("RFID Detected: ");
  Serial.println(uid);

  // Check whether worker is already registered
  int existingIndex = -1;

  for (int i = 0; i < MAX_WORKERS; i++) {

    if (workerPresent[i] &&
        workerUIDs[i] == uid) {

      existingIndex = i;
      break;
    }
  }


  // ---------------- WORKER LEAVES / SAFE-ZONE CONFIRMATION ----------------

  if (existingIndex != -1) {

    workerPresent[existingIndex] = false;

    if (workerCount > 0) {
      workerCount--;
    }

    Serial.println("Worker status: ACCOUNTED / LEFT");
    Serial.print("Workers remaining: ");
    Serial.println(workerCount);
  }


  // ---------------- NEW WORKER ----------------

  else {

    bool added = false;

    for (int i = 0; i < MAX_WORKERS; i++) {

      if (!workerPresent[i]) {

        workerUIDs[i] = uid;
        workerPresent[i] = true;

        workerCount++;

        added = true;

        Serial.println("Worker status: ENTERED / REGISTERED");

        Serial.print("Workers present: ");
        Serial.println(workerCount);

        break;
      }
    }

    if (!added) {

      Serial.println("Worker list is full!");
    }
  }

  // Stop communication with card
  rfid.PICC_HaltA();
  rfid.PCD_StopCrypto1();

  delay(1000);
}


// ================================================================
// OLED DISPLAY
// ================================================================

void updateDisplay() {

  int gasValue = analogRead(GAS_SENSOR_PIN);

  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  display.clearDisplay();

  display.setTextColor(SSD1306_WHITE);

  // Title
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println("SMART GAS SAFETY");

  // Zone
  display.setCursor(0, 10);
  display.print("ZONE: B");

  // Status
  display.setCursor(70, 10);

  if (currentState == SAFE) {

    display.print("SAFE");

  }
  else if (currentState == WARNING) {

    display.print("WARNING");

  }
  else if (currentState == DANGER) {

    display.print("DANGER");

  }
  else {

    display.print("EMERGENCY");
  }

  // Gas
  display.setCursor(0, 25);
  display.print("Gas: ");
  display.println(gasValue);

  // Temperature
  display.setCursor(0, 35);
  display.print("Temp: ");

  if (isnan(temperature)) {
    display.println("--");
  }
  else {
    display.print(temperature, 1);
    display.println(" C");
  }

  // Humidity
  display.setCursor(0, 45);
  display.print("Hum: ");

  if (isnan(humidity)) {
    display.println("--");
  }
  else {
    display.print(humidity, 1);
    display.println(" %");
  }

  // Workers
  display.setCursor(0, 56);
  display.print("Workers: ");
  display.print(workerCount);

  display.display();
}
