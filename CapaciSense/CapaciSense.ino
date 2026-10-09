/* CapaciSense - Arduino Uno R3 capacitive touch LED.
   D2 -- 10 megohm resistor -- D4 -- foil
   Optional external LED: D13 -- 220 ohm -- anode; cathode -- GND.
   The Uno's built-in LED also works without an external LED.
*/
#include <CapacitiveSensor.h>

CapacitiveSensor touchSensor(2, 4); // Send pin, receive pin.
const int ledPin = LED_BUILTIN;
const long touchThreshold = 500;   // Tune using Serial Monitor.
const long releaseThreshold = 350; // Keep lower than touchThreshold.
bool touched = false;

void setup() {
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
  Serial.begin(9600);
  // Prevent a long touch from being treated as the new baseline.
  touchSensor.set_CS_AutocaL_Millis(0xFFFFFFFF);
  touchSensor.set_CS_Timeout_Millis(200);
  Serial.println("CapaciSense ready. Keep hands away initially.");
}

void loop() {
  long reading = touchSensor.capacitiveSensor(30);

  if (reading < 0) {
    touched = false;
    digitalWrite(ledPin, LOW);
    Serial.println("Sensor error: check resistor and D2/D4 wiring.");
    delay(100);
    return;
  }

  // Two thresholds prevent rapid flickering near the switching point.
  if (!touched && reading > touchThreshold) {
    touched = true;
  } else if (touched && reading < releaseThreshold) {
    touched = false;
  }

  digitalWrite(ledPin, touched ? HIGH : LOW);
  Serial.print("Reading: ");
  Serial.print(reading);
  Serial.print("  LED: ");
  Serial.println(touched ? "ON" : "OFF");
  delay(20);
}
