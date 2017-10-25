/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
JoggerPluginAudioProcessorEditor::JoggerPluginAudioProcessorEditor (JoggerPluginAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
	addAndMakeVisible(&openButton);
	openButton.setButtonText("Open...");
	openButton.addListener(this);

	addAndMakeVisible(&playButton);
	playButton.setButtonText("Play");
	playButton.addListener(this);
	playButton.setColour(TextButton::buttonColourId, Colours::green);
	playButton.setEnabled(false);

	addAndMakeVisible(&stopButton);
	stopButton.setButtonText("Stop");
	stopButton.addListener(this);
	stopButton.setColour(TextButton::buttonColourId, Colours::red);
	stopButton.setEnabled(false);
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 300);

	formatManager.registerBasicFormats();       // [1]
	processor.transportSource.addChangeListener(this);

}

JoggerPluginAudioProcessorEditor::~JoggerPluginAudioProcessorEditor()
{
}

void JoggerPluginAudioProcessorEditor::changeState(JoggerPluginAudioProcessor::TransportState newState)
{
	if (processor.state != newState)
	{
		processor.state = newState;

		switch (processor.state)
		{
		case JoggerPluginAudioProcessor::Stopped:                           // [3]
			stopButton.setEnabled(false);
			//playButton.setEnabled(true);
			processor.transportSource.setPosition(0.0);
			break;

		case JoggerPluginAudioProcessor::Starting:                          // [4]
			playButton.setEnabled(false);
			processor.transportSource.start();
			break;

		case JoggerPluginAudioProcessor::Playing:                           // [5]
			stopButton.setEnabled(true);
			break;

		case JoggerPluginAudioProcessor::Stopping:                          // [6]
			processor.transportSource.stop();
			break;
		}
	}
}

void JoggerPluginAudioProcessorEditor::changeListenerCallback(ChangeBroadcaster* source)
{
	if (source == &processor.transportSource)
	{
		if (processor.transportSource.isPlaying()) {
			changeState(JoggerPluginAudioProcessor::Playing);
		} else {
			changeState(JoggerPluginAudioProcessor::Stopped);
		}
			
	}
}

void JoggerPluginAudioProcessorEditor::buttonClicked(Button* button)
{
	if (button == &openButton)  openButtonClicked();
	if (button == &playButton)  playButtonClicked();
	if (button == &stopButton)  stopButtonClicked();
}

void JoggerPluginAudioProcessorEditor::openButtonClicked()
{
	FileChooser chooser("Select a Wave file to play...",
		File::nonexistent,
		"*.wav");                                        // [7]

	if (chooser.browseForFileToOpen())                                    // [8]
	{
		File file(chooser.getResult());                                  // [9]
		AudioFormatReader* reader = formatManager.createReaderFor(file); // [10]

		if (reader != nullptr)
		{
			ScopedPointer<AudioFormatReaderSource> newSource = new AudioFormatReaderSource(reader, true); // [11]
			processor.transportSource.setSource(newSource, 0, nullptr, reader->sampleRate);                         // [12]
			playButton.setEnabled(true);                                                                  // [13]
			processor.readerSource = newSource.release();                                                            // [14]
		}
	}
}

void JoggerPluginAudioProcessorEditor::playButtonClicked()
{
	changeState(JoggerPluginAudioProcessor::Starting);
}

void JoggerPluginAudioProcessorEditor::stopButtonClicked()
{
	changeState(JoggerPluginAudioProcessor::Stopping);
}

//==============================================================================
void JoggerPluginAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

    g.setColour (Colours::white);
    g.setFont (15.0f);
    g.drawFittedText ("Hello World!", getLocalBounds(), Justification::centred, 1);
}

void JoggerPluginAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
	openButton.setBounds(10, 10, getWidth() - 20, 20);
	playButton.setBounds(10, 40, getWidth() - 20, 20);
	stopButton.setBounds(10, 70, getWidth() - 20, 20);
}
