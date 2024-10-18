#define RELAY_PIN 4
#define ON_PIN A6
#define OFF_PIN A7

bool relayState = LOW;
unsigned long previousSeconds = 0;
unsigned long onDurationSeconds;
unsigned long offDurationSeconds;

void setup() {
  pinMode(RELAY_PIN, OUTPUT);
}

void loop() {
  onDurationSeconds = map(analogRead(ON_PIN), 0, 1023, 0, 300);
  offDurationSeconds = map(analogRead(OFF_PIN), 0, 1023, 0, 300);

  unsigned long currentSeconds = millis()/1000;
  
  if ((relayState == LOW && currentSeconds - previousSeconds >= offDurationSeconds && onDurationSeconds != 0)
    || (relayState == HIGH && currentSeconds - previousSeconds >= onDurationSeconds && offDurationSeconds != 0)) {
    relayState = !relayState;
    digitalWrite(RELAY_PIN, relayState);
    previousSeconds = currentSeconds;
  }

  delay(1000);
}
