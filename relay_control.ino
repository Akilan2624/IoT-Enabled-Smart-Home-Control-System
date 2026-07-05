#define RELAY_PIN 26

void setup() {
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, HIGH);
}

void loop() {
  digitalWrite(RELAY_PIN, LOW);   // Relay ON
  delay(3000);

  digitalWrite(RELAY_PIN, HIGH);  // Relay OFF
  delay(3000);
}
