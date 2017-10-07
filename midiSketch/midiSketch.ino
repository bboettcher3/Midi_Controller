#include <MIDI.h>

void setup() {
  // put your setup code here, to run once:
  MIDI_CREATE_DEFAULT_INSTANCE();
  MIDI.begin(MIDI_CHANNEL_OMNI);
}

void loop() {
  // put your main code here, to run repeatedly:
  MIDI.sendNoteOn(42, 127, 1);

  MIDI.read();
}








