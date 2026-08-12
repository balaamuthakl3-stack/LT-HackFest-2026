// Smart Toxic Gas Early-Warning & Worker Safety System
// LT HackFest 2026

// Smart Toxic Gas Early-Warning & Worker Safety System
// LT HackFest 2026

const int GAS_SENSOR_PIN = 34;

void setup() {
  Serial.begin(115200);

  Serial.println("Smart Toxic Gas Safety System");
  Serial.println("ESP32 Started Successfully");

  pinMode(GAS_SENSOR_PIN, INPUT);
}

void loop() {

  int gasValue = analogRead(GAS_SENSOR_PIN);

  Serial.print("Gas Sensor Value: ");
  Serial.println(gasValue);

  if (gasValue > 2000) {
    Serial.println("WARNING: Abnormal Gas Level Detected!");
  }
  else {
    Serial.println("Status: SAFE");
  }

  Serial.println("----------------------");

  delay(2000);
}
