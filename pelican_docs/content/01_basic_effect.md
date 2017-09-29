Title: Making an AUV3 plugin with JUCE and gen~
Date: 2017-09-24 18:32
Category: JUCE


# Goal
Make an AUV3 audio effect that I can load into an iOS plugin host for AUV3s, like [AUM](http://kymatica.com/Software/AUM). I want basic MIDI control over one or two parameters of the plugin. I want to implement this using

* [gen](https://docs.cycling74.com/max7/vignettes/gen_overview) : so I can develop in an interactive environment, and generate cross-platform code. I guess Faust is also a good candidate, but I have less experience with it.

* [JUCE](https://juce.com/) : to compile the plugin and keep the overall code cross-platform. I also know it's reliable for audio. I could use CoreAudio but the C-API is kind of a hassle, is platform-specific. AudioKit is interesting too, but also very platform-specific and there's not (yet?) an obvious way to inject c++ code in the audio callback. Juce is powering Max/MSP, that's enough of a guarantee for audio capabilities.

## Background

The plan is basically to start off by patching together two existing resources:

* Code from this JUCE tutorial: [Create a basic audio/midi plugin](https://juce.com/doc/tutorial_create_projucer_basic_plugin)

* The github repo referenced in [this thread](https://cycling74.com/forums/gen~-juce)

## Steps

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


---
