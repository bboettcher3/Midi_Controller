/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"


//==============================================================================
/**
*/
class JoggerPluginAudioProcessorEditor  :   public AudioProcessorEditor,
											public Button::Listener,
											public ChangeListener,
											private Timer
{
public:
    JoggerPluginAudioProcessorEditor (JoggerPluginAudioProcessor&);
    ~JoggerPluginAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;
	void timerCallback() override;
private:
	void updateGUI();
	/*enum TransportState
	{
		Stopped,
		Starting,
		Playing,
		Stopping
	}; */
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.

    JoggerPluginAudioProcessor& processor;
	TextButton openButton;
	TextButton playButton;
	TextButton stopButton;

	AudioFormatManager formatManager;

	void buttonClicked(Button *button) override;
	void changeListenerCallback(ChangeBroadcaster* source) override;
	void changeState(JoggerPluginAudioProcessor::TransportState newState);
	void openButtonClicked();
	void playButtonClicked();
	void stopButtonClicked();

	Label debug;


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (JoggerPluginAudioProcessorEditor)
};
