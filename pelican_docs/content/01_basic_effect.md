Title: Making an AUV3 plugin with JUCE and gen~
Date: 2017-09-24 18:32
Category: JUCE


# Goal
Make an AUV3 audio effect that I can load into an iOS plugin host for AUV3s, like [AUM](http://kymatica.com/Software/AUM). I want basic MIDI control over one or two parameters of the plugin. I want to implement this using
* [gen](https://docs.cycling74.com/max7/vignettes/gen_overview) : so I can develop in an interactive environment, and generate platform-agnostic code. I guess Faust is also a good candidate, but I have less experience with it.
* [JUCE](https://juce.com/) : to compile the plugin and keep the overall code cross-platform. I also know it's reliable for audio. I could use CoreAudio but the C-API is kind of a hassle, is platform-spcific. AudioKit is interesting too, but also very platform-spcific and there's not (yet?) an obvious way to inject c++ code in the audio callback. Juce is powering Max/MSP, that's enough of a guarantee for audio capabilities.

## Background
The plan is basically to start off by patching together two existing resources:
* Code from this JUCE tutorial: [Create a basic audio/midi plugin](https://juce.com/doc/tutorial_create_projucer_basic_plugin)
* The github repo referenced in this thread https://cycling74.com/forums/gen~-juce




This is a c++ code block:

```c++
class AUv3SynthEditor   : public AudioProcessorEditor,
                          public ButtonListener,
                          public Slider::Listener,
                          private Timer
```

---
* Unordered list can use asterisks
- Or minuses
+ Or pluses

---
