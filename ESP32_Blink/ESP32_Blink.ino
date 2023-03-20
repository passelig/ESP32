#define blueLedPin 2 // This is not the same pin as Arduino uno

void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(blueLedPin, OUTPUT);
  Serial.begin(9600);
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(blueLedPin, HIGH);  // turn the LED on (HIGH is the voltage level)
  Serial.println("ON");
  delay(1000);                      // wait for a second
  digitalWrite(blueLedPin, LOW);   // turn the LED off by making the voltage LOW
  Serial.println("OFF");
  delay(1000);                      // wait for a second
}