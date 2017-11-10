#include <Bounce.h> //used for buttons
#include <Encoder.h> //used for rotary encoder

//#define POT_PIN 3 //analog
//#define TX_PIN 1 //digital
#define CHANNEL 1 //MIDI channel
#define BUTTON_1 0 //digital
#define BUTTON_2 1 //digital
#define BUTTON_3 2 //digital
#define BUTTON_4 3 //digital
#define FADER A0 //analog
#define ENCODERPIN_1 4 //digital
#define ENCODERPIN_2 5 //digital

int faderVal = 0;
int lastFaderVal = 0;
long encoderVal = 0;
long oldEncoderVal = 0;
//buttons
Bounce button1 = Bounce(BUTTON_1, 5);
Bounce button2 = Bounce(BUTTON_2, 5);
Bounce button3 = Bounce(BUTTON_3, 5);
Bounce button4 = Bounce(BUTTON_4, 5);
//jog wheel
Encoder encoder(ENCODERPIN_1, ENCODERPIN_2);

void setup() {
  // Set MIDI baud rate:
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
  encoderVal = encoder.read();
  faderVal = analogRead(FADER) / 8; //divide by 8 to put in 0-127 range
  //Serial.println(analogRead(0));
  delay(10);
  if (button1.fallingEdge()) {
    //sendControlChange(control, value, channel)
    usbMIDI.sendControlChange(16, 10, CHANNEL);
    Serial.println("pressed 1");
  }
  if (button2.fallingEdge()) {
    //sendControlChange(control, value, channel)
    usbMIDI.sendControlChange(17, 10, CHANNEL);
    Serial.println("pressed 2");
  }
  if (button3.fallingEdge()) {
    //sendControlChange(control, value, channel)
    usbMIDI.sendControlChange(18, 10, CHANNEL);
    Serial.println("pressed 3");
  }
  if (button4.fallingEdge()) {
    //sendControlChange(control, value, channel)
    usbMIDI.sendControlChange(19, 10, CHANNEL);
    Serial.println("pressed 4");
  }
  if (faderVal != lastFaderVal) {
    usbMIDI.sendControlChange(20, faderVal, CHANNEL);
    lastFaderVal = faderVal;
    Serial.print("Fader: ");
    Serial.println(faderVal);
    //delay(10);
  }
  if (encoderVal != oldEncoderVal) {
    oldEncoderVal = encoderVal;
    Serial.print("Encoder: ");
    Serial.println(encoderVal);
  }
  delay(10); // to prevent slight fluctuations from sending through
  // MIDI Controllers should discard incoming MIDI messages.
  while (usbMIDI.read()) {
  }
}


