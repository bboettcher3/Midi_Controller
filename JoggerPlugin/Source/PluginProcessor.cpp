/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
JoggerPluginAudioProcessor::JoggerPluginAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
	//contNum = (acceptsMidi()) ? 1 : 0;
}

JoggerPluginAudioProcessor::~JoggerPluginAudioProcessor()
{
}

//==============================================================================
const String JoggerPluginAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool JoggerPluginAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool JoggerPluginAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

double JoggerPluginAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int JoggerPluginAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int JoggerPluginAudioProcessor::getCurrentProgram()
{
    return 0;
}

void JoggerPluginAudioProcessor::setCurrentProgram (int index)
{
}

const String JoggerPluginAudioProcessor::getProgramName (int index)
{
    return {};
}

void JoggerPluginAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void JoggerPluginAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
	transportSource.prepareToPlay(samplesPerBlock, sampleRate);
}

void JoggerPluginAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
	transportSource.releaseResources();
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool JoggerPluginAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif


void JoggerPluginAudioProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
    const int totalNumInputChannels  = getTotalNumInputChannels();
    const int totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (int i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

	//process MIDI
	MidiMessage m;
	int time;
	for (MidiBuffer::Iterator i(midiMessages); i.getNextEvent(m, time);) {
		if (m.isController()) {
			contNum = m.getControllerNumber();
			if ((m.getControllerNumber() == 16) && !transportSource.isPlaying()) {
				transportSource.start();
			}
		} 
		else {
			contNum = m.getChannel();
		} 
		//if (m.isNoteOn() && m.getNoteNumber() == 16 && !transportSource.isPlaying()) {
		//	transportSource.start();
		//	state = Playing;
		//}
		//else {
		//	contNum = m.getNoteNumber();
		//}
		//contNum = 1;
	}
	//contNum = 2;

	AudioSourceChannelInfo bufferToFill;
	bufferToFill.buffer = &buffer;
	bufferToFill.startSample = 0;
	bufferToFill.numSamples = buffer.getNumSamples();
	transportSource.getNextAudioBlock(bufferToFill);

    // Process dat audio boii
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        float* channelData = buffer.getWritePointer (channel);
		//transportSource.getNextAudioBlock(buffer);
		
        // ..do something to the data...
    }
}


//==============================================================================
bool JoggerPluginAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* JoggerPluginAudioProcessor::createEditor()
{
    return new JoggerPluginAudioProcessorEditor (*this);
}

//==============================================================================
void JoggerPluginAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void JoggerPluginAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new JoggerPluginAudioProcessor();
}
