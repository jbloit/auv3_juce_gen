# Development log

## Goal
Make an AUV3 audio effect that I can load into an iOS plugin host for AUV3s, like [AUM](http://kymatica.com/Software/AUM). I want basic MIDI control over one or two parameters of the plugin. I want to implement this using

* [gen](https://docs.cycling74.com/max7/vignettes/gen_overview) : so I can develop in an interactive environment, and generate cross-platform code. I guess Faust is also a good candidate, but I have less experience with it.

* [JUCE](https://juce.com/) : to compile the plugin and keep the overall code cross-platform. I also know it's reliable for audio. I could use CoreAudio but the C-API is kind of a hassle, is platform-specific. AudioKit is interesting too, but also very platform-specific and there's not (yet?) an obvious way to inject c++ code in the audio callback. Juce is powering Max/MSP, that's enough of a guarantee for audio capabilities.

## Background

The plan is basically to start off by patching together two existing resources:

* Code from this JUCE tutorial: [Create a basic audio/midi plugin](https://juce.com/doc/tutorial_create_projucer_basic_plugin)

* The github repo referenced in [this thread](https://cycling74.com/forums/gen~-juce)

## Steps

NOTE: the steps correspond to tags in the repo.

### 1. first build

* Following along the first part of the [audio-plugin tutorial](https://juce.com/doc/tutorial_create_projucer_basic_plugin)

* In Max/MSP, opened up the Beap chorus effect, extracted only gen part of it and exported the code.
I add the generated source to Projucer's source files, in a folder called gen_chorus.

NB: I haven't tried, but there are several export options for the gen code, that let you choose the class name, the plugin type etc.

* Header files: XCode will need header search paths for locating lib files for gen dsp.
In the projucer, locate the the Exporters tab, and then for each debug and release scheme, add the the following to the Header Search Paths field:

```
$(PROJECT_DIR)/../../Source/gen_chorus
$(PROJECT_DIR)/../../Source/gen_chorus/gen_dsp
```

### 2. declare parameters
I can load the built AUV3 extension. However when I load the extension in a host (AUM app), it doesn't detect the extension's parameters yet. There is a slider in the interface, that I'd like to be able to map to midi messages.

The key basically holds in replacing the simple float parameter into an AudioParameterFloat

```
AudioParameterFloat* noteVelocity;
```
Then adding the boiler plate code for setter and getter, for state storing with the host, instantiation in the processor's constructor etc. I simply copied all that from the AUV3 synth demo code that shipped with juce.

### 3. process block with gen code
Following the example from the c74 repo, I can build the AUV3 and load the extention in AUM.
But it crashes as soon as the loading is done.

Q1: is this happening when building and loading as a VST3 instead?

->>  Weeeelll  actually, it's random. Sometimes it loads, sometimes not.


Since this fails, I'm trying to run the code from the example repo from C74. I'm able to run it, and it load consistently in the plugin host.

So what I'll do is take this code as a starting point now, basically copy the plugin processor code and the gen exported code into chorus project: ie replace the plugin part of the code but keep the processor part of the project (the chorus gen effect)

-> the resulting auv3 never loads...

### 4. Fresh start
Getting confused here, too many variables. I'll start fresh with a new plugin code, without gen, that loads. Then incrementally incorporate gen code to see when things stop working.

1. **Loads**: a fresh plugin is compiled, it loads. (note that I fist need to compile it and install it as a standalone, so that AUM registers it. Apparently though, the subsequent code changes don't require that standalone step in order to take effect)

2. **Add the gen code**: Only add it to the target and compile.

3. **init the gen code in processor constructor**  ok

4. **add buffer filling code**: crash happens now. It happens either with the standalone or extension targets. Seemingly random occurance, more that 50% the time.

5. **found the bug**: I wasn't initializing ```m_CurrentBufferSize``` in the constructor.

### 5. Parameters

1. Added GUI for the other gen parameters. It's sort of functional, I but no effort in the layout, so it's plain ugly. For managing multiple parameters, I figured I should use an [AudioProcessorValueTreeState](https://www.juce.com/doc/tutorial_audio_processor_value_tree_state) object anyway. Let's keep that for later. I want to make the control one-dimensional anyway.

### 6. one-knob control

I guess there are two ways for doing that: either bake the control reduction into gen~ , or implement a preset interpolation mechanism (ie save multiple state, and interpolate with a 1D control). Obviously, the first is simpler.

1. Hard-wired 1D reduction: some quick sound design to set a unique "knob" parameter. Accidentally added a connection that added some crunchiness that I liked, so it's now baked in. Not sure it sounds like a chorus anymore. But allowing happy accidents is the purpose of all this.

### 7. Save and recall states
Another way I'd like to control this, is to switch between presets when a new midi note message comes in. It looks like it's time for using ```AudioProcessorValueTreeState```.

1. replace parameter handling with AudioProcessorValueTreeState
Copied logic from tutorial

2. Add 2 buttons for testing

3. load state when hitting a button
yes. I. did. it.

4. toggle state with midi notes

### 8. Not thread safe?
I'm trying to change the state of some value tree param, from the process block. What I'm trying to do is to set parameters based on the incoming midi controller. It's working when I change states, but the parameters themselves are not updated.

Found [this thread](https://forum.juce.com/t/update-audioprocessorvaluetreestate-from-process-block/17958/12) on the forum. There seems to be some workaround code. But also some **big red flag** raised by Jules, the main developer. It's not thread safe to work with the value tree on in the audio thread. Need to use CachedValue instead. He also suggests working with a Synthesizer class instead of handling the midi messages yourself.

I'm not really sure what to decide right now. It looks like the value tree thing could backfire at some point. I should maybe keep it simpler: with the one knob approach, I only have 2 parameters anyway: one for a state, and one for the actual knob value. Maybe I should go back to the parameters approach, keep it simpler and safe. The one-knob approach is a nice constraint anyway.

1. implemented the cachedValue mechanism. It's working now (ie parameters update from audio thread - triggered my midi events).

### 9. Better recording of steps

1. Distinguish between an edit mode and a play mode. During edit mode, the control is played directly, but not being recorded to a state unless a noteOn message is received. In play mode, the current state is used to control the audio, and a noteOn message triggers the step increment.



















---
