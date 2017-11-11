#include <Bounce.h> //used for buttons
#include <Encoder.h> //used for rotary encoder

//#define POT_PIN 3 //analog
//#define TX_PIN 1 //digital
#define CHANNEL 1 //MIDI channel
#define BUTTON_1 0 //digital
#define BUTTON_2 1 //digital
#define BUTTON_3 2 //digital
#define BUTTON_4 3 //digital
#define ENCODER_BUTTON 6 //digital
#define FADER A0 //analog
#define ENCODERPIN_1 4 //digital
#define ENCODERPIN_2 5 //digital

int faderVal = 0; //current fader position
int lastFaderVal = 0; //last received fader position
long encoderVal = 0; //current encoder value
long oldEncoderVal = 0; //last received encoder value
//buttons
Bounce button1 = Bounce(BUTTON_1, 5); //CC1
Bounce button2 = Bounce(BUTTON_2, 5); //CC2
Bounce button3 = Bounce(BUTTON_3, 5); //CC3
Bounce button4 = Bounce(BUTTON_4, 5); //CC4
Bounce enc_button = Bounce(ENCODER_BUTTON, 5); //encoder button (CC5)
Encoder encoder(ENCODERPIN_1, ENCODERPIN_2); //jog wheel (rotary encoder) (CC20)

void setup() {
  //configure pins
  pinMode(BUTTON_1, INPUT_PULLUP);
  pinMode(BUTTON_2, INPUT_PULLUP);
  pinMode(BUTTON_3, INPUT_PULLUP);
  pinMode(BUTTON_4, INPUT_PULLUP);
  pinMode(ENCODER_BUTTON, INPUT_PULLUP);
}

void loop() {
  //update buttons, fader and encoder
  button1.update();
  button2.update();
  button3.update();
  button4.update();
  enc_button.update();
  encoderVal = encoder.read();
  faderVal = analogRead(FADER) / 8; //divide by 8 to put in 0-127 range

  //check for button presses
  if (button1.fallingEdge()) {
    //sendControlChange(control, value, channel)
    usbMIDI.sendControlChange(1, 10, CHANNEL);
    Serial.println("pressed 1");
  }
  if (button2.fallingEdge()) {
    //sendControlChange(control, value, channel)
    usbMIDI.sendControlChange(2, 10, CHANNEL);
    Serial.println("pressed 2");
  }
  if (button3.fallingEdge()) {
    //sendControlChange(control, value, channel)
    usbMIDI.sendControlChange(3, 10, CHANNEL);
    Serial.println("pressed 3");
  }
  if (button4.fallingEdge()) {
    //sendControlChange(control, value, channel)
    usbMIDI.sendControlChange(4, 10, CHANNEL);
    Serial.println("pressed 4");
  }
  if (enc_button.fallingEdge()) {
    //sendControlChange(control, value, channel)
    usbMIDI.sendControlChange(5, 10, CHANNEL);
    Serial.println("pressed encoder");
  }
  //check for change in fader or encoder
  if (faderVal != lastFaderVal) {
    usbMIDI.sendControlChange(10, faderVal, CHANNEL);
    lastFaderVal = faderVal;
    Serial.print("Fader: ");
    Serial.println(faderVal);
  }
  if (encoderVal != oldEncoderVal) {
    usbMIDI.sendControlChange(20, encoderVal, CHANNEL);
    oldEncoderVal = encoderVal;
    Serial.print("Encoder: ");
    Serial.println(encoderVal);
  }
  delay(10); // to prevent slight fluctuations from sending through
  // MIDI Controllers should discard incoming MIDI messages.
  while (usbMIDI.read()) {
  }
}


