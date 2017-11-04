#include <Bounce.h>

//#define POT_PIN 3 //analog
//#define TX_PIN 1 //digital
#define CHANNEL 1 //MIDI channel
#define BUTTON_PIN 2 //digital

//int potVal = 0;
//int lastVal = 0;
int buttonVal = 0;
Bounce button1 = Bounce(BUTTON_PIN, 5);

void setup() {
  // Set MIDI baud rate:
  delay(500);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
}

void loop() {
    button1.update();
  //potVal = analogRead(POT_PIN) / 8; //divide by 8 to put in 0-127 range
  if (button1.fallingEdge()) {
    //sendControlChange(control, value, channel)
    usbMIDI.sendControlChange(16, 10, CHANNEL);
    Serial.println("pressed");
  }
  
  //if (potVal != lastVal) {
  //  MIDI.sendControlChange(16, potVal, CHANNEL);
  //  //MIDI.sendNoteOn(20, 120, CHANNEL);
  //  lastVal = potVal;
  //}
  //delay(10); // to prevent slight fluctuations from sending through
  // MIDI Controllers should discard incoming MIDI messages.
  while (usbMIDI.read()) {
  }
}


