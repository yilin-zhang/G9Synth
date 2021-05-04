# Group9 Synth
Final project for MUSI-6202/4459 2021 Spring

## What is it?
This project is a monophonic subtractive synthesizer plug-in that deploys four wavetable synthesized oscillators, state variable filter design, and various modulated effects.
The two synth engine options are wavetable and subtractive. We used wavetable synthesis techniques to create four oscillators: sine wave, sawtooth wave, square wave, and noise. The subtractive synthesis design made use of a state variable filter that produces different frequency response outputs (e.g., highpass, lowpass, bandpass, notch, etc.). The 3 modulated effects include delay, vibrato, and ring modulation. The convolution-based effect is an impulse response convolution. An ADSR is be added to optimize audio output. A bitcrusher effect demonstrated its control over outputting sample rate and bit depth. 

## How does it work?
The plug-in takes in parameters as a VST. You can adjust all of the knobs to achieve your desired audio output. 
There are 4 gain controls for the 4 oscillators, and 3 pitch shift controls for sin wave, sawtooth wave, and square wave. For SVF, there is a filter type menu, and 3 knobs for filter cutoff, resonance, and mix. For delay effect, there are 3 knobs for time, feedback and mix. For vibrato effect, there are be 3 knobs for depth, frequency and mix. Similar parameter layout will be applied to the ring modulator. A .wav file input will be required for the impulse response. System gain is also configurable.

## How to run it
Download your desired format of our most recent release at https://github.com/yilin-zhang/G9Synth/releases to the custom plug-in folder of your DAW, and start playing!

![Release](https://user-images.githubusercontent.com/70708796/117074450-548c8580-ad01-11eb-864b-83c94bb48671.png)
