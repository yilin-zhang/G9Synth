# Group9 Synth
The final project for MUSI-6202/4459 2021 Spring

## What is it?
This project is a monophonic subtractive synthesizer plug-in that deploys three wavetable synthesized oscillators, one state variable filter, and various modulated effects.

We used wavetable synthesis techniques to create three oscillators: sine wave, sawtooth wave, and square wave. The subtractive synthesis design uses a state variable filter that produces different frequency response outputs. The three modulated effects include delay, vibrato, and ring modulation. The convolution-based effect is an impulse response convolution. An ADSR is added to produce an envelope control. A bitcrusher effect demonstrates its control over outputting sample rate and bit depth. 

## How does it work?
You can adjust all of the knobs to achieve your desired audio output.

There are three gain controls for the three oscillators and three pitch-shift controls for sin wave, sawtooth wave, and square wave. For SVF, there is a filter-type menu and three knobs for filter cutoff, resonance, and mix. For delay effect, there are three knobs for time, feedback and mix. For the vibrato effect, there are three knobs for depth, frequency, and mix. A similar parameter layout will be applied to the ring modulator. A .wav file is required for the impulse response. The global gain is also configurable.

## How to run it
Download your desired format of our most recent release at https://github.com/yilin-zhang/G9Synth/releases to the custom plug-in folder of your DAW, and start playing!

![Release](https://user-images.githubusercontent.com/70708796/117074450-548c8580-ad01-11eb-864b-83c94bb48671.png)
