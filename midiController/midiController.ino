#include <MIDI.h>

#define POT_PIN 3 //analog
#define TX_PIN 1 //digital
#define CHANNEL 1 //MIDI channel

int potVal = 0;
int lastVal = 0;

MIDI_CREATE_DEFAULT_INSTANCE();

void setup() {
  // Set MIDI baud rate:
  delay(500);
  MIDI.begin();
  delay(10);
}

void loop() {
  potVal = analogRead(POT_PIN) / 8; //divide by 8 to put in 0-127 range
  if (potVal != lastVal) {
    MIDI.sendControlChange(16, potVal, CHANNEL);
    //MIDI.sendNoteOn(20, 120, CHANNEL);
    lastVal = potVal;
  }
  delay(10); // to prevent slight fluctuations from sending through
}


