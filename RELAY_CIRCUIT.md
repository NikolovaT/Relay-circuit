2024-08-20
Set relay on and off durations by turning potentiometers. Controled by Arduino Nano. 
### Components:
- Arduino Nano board
- JQC-3FC 5VDC relay
- Potentiometer THT 10k Vertical x2
- Resistor 1$k \Omega$ 
- Diode 1N4148
- Screw Terminal 01x02 
- Screw Terminal 01x03
- LED red
- Perfboard


## Arduino Connections

| Arduino Nano | Other                                       |
| ------------ | ------------------------------------------- |
| A6           | Potentiometer1 base                         |
| A7           | Potentiometer2 base                         |
| 5V           | Potentiometer1 pin3 and Potentiometer2 pin3 |
| D4           | LED anode                                   |

## Schematic

![[relay_nano_schematic.png]]


## PCB layout

![[relay_nano_pcb.png]]


## Code
```
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
```
