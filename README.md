# Midi_Controller

A MIDI Controller made with Teensy 3.2 and Arduino + A VST plugin enabling its use in Ableton made with JUCE and Maximilian

## Functionality
The goal of the controller and plugin is to allow scratching of audio clips through Ableton for live performance use. Instead of having to
choose between mixing through a program like Serato or Tracktor or performing using a program like Ableton, you can now use the controller
to trigger and manipulate audio clips while performing live.

## [The Controller](./midiController) (**Arduino C**)

Using a Teensy 3.2 board as the microcontroller, the controller features 4 [push buttons](https://www.digikey.com/products/en?keywords=401-1989-ND)
, a [fader](https://www.digikey.com/products/en?keywords=PTA3043-2010CIB103-ND) and a [jog wheel](https://www.digikey.com/products/en?keywords=EM14A0D-C24-L064S-ND). 
All code for the controller was written in C using the Arduino IDE.

## [The Plugin](./JoggerPlugin) (**C++**)

The VST plugin uses JUCE for the UI and audio pipeline, and Maximilian for DSP. The plugin loads a piece of audio and allows scrubbing
through the clip.
