#include <Bounce.h>

//#define POT_PIN 3 //analog
//#define TX_PIN 1 //digital
#define CHANNEL 1 //MIDI channel
#define BUTTON_1 0 //digital
#define BUTTON_2 1 //digital
#define BUTTON_3 2 //digital
#define BUTTON_4 3 //digital

//int potVal = 0;
//int lastVal = 0;
int buttonVal = 0;
Bounce button1 = Bounce(BUTTON_1, 5);
Bounce button2 = Bounce(BUTTON_2, 5);
Bounce button3 = Bounce(BUTTON_3, 5);
Bounce button4 = Bounce(BUTTON_4, 5);

void setup() {
  // Set MIDI baud rate:
  //delay(500);
  pinMode(BUTTON_1, INPUT_PULLUP);
  pinMode(BUTTON_2, INPUT_PULLUP);
  pinMode(BUTTON_3, INPUT_PULLUP);
  pinMode(BUTTON_4, INPUT_PULLUP);
}

void loop() {
    button1.update();
    button2.update();
    button3.update();
    button4.update();
  //potVal = analogRead(POT_PIN) / 8; //divide by 8 to put in 0-127 range
  if (button1.fallingEdge()) {
    //sendControlChange(control, value, channel)
    usbMIDI.sendControlChange(16, 10, CHANNEL);
    Serial.println("pressed");
  }
  if (button2.fallingEdge()) {
    //sendControlChange(control, value, channel)
    usbMIDI.sendControlChange(17, 10, CHANNEL);
    Serial.println("pressed");
  }
  if (button3.fallingEdge()) {
    //sendControlChange(control, value, channel)
    usbMIDI.sendControlChange(18, 10, CHANNEL);
    Serial.println("pressed");
  }
  if (button4.fallingEdge()) {
    //sendControlChange(control, value, channel)
    usbMIDI.sendControlChange(18, 10, CHANNEL);
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


