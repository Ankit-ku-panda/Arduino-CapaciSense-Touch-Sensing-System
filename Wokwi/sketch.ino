// CapaciSense Wokwi: button simulates touch; values are artificial.
const int buttonPin = 4;
const int ledPin = LED_BUILTIN;
const long touchThreshold = 500;
const long releaseThreshold = 350;
bool touched = false;
void setup() {
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
  Serial.begin(9600);
  pinMode(buttonPin, INPUT_PULLUP);
  Serial.println("SIMULATION: hold button for touch; release to stop.");
}
void loop() {
  long reading = digitalRead(buttonPin) == LOW ? 1000 : 50;
  if (!touched && reading > touchThreshold) touched = true;
  else if (touched && reading < releaseThreshold) touched = false;
  digitalWrite(ledPin, touched ? HIGH : LOW);
  Serial.print("Reading: "); Serial.print(reading);
  Serial.print("  LED: "); Serial.println(touched ? "ON" : "OFF");
  delay(20);
}
