# MeowMu_Compressor_VST3
Variation of airwindows VariMu Compressor, In VST3  

<img src="screenshot.png"  width="200"/>

What it is for: nice vocal compressor.  
After searching a bunch of other airwindows compressors, VariMu was suitable for attack time tweaking.  
muMakeupgain is bypassed, and replaced output trim to Gain.  
By multipling muAttack by 5, we can get attack time of 5ms & release time of 120ms at Speed = 0.6.  
Less the Speed -> slow attack & release.  
More the Speed -> fast attack & release.  
So, this compressor might fall somewhere between Logical4 and VariMu.  

Anyone interested, please try it and leave a feedback.  

Windows only. No Mac nor Linux campatible.  

Built for VST3, but compatible to VST2 also.

<img src="VST_Compatible_Logo_Steinberg_with_TM.png"  width="100"/>


VSTSDK 3.7.7 used  
VSTGUI 4.12 used  

v1.0.0 : initial.  
v1.0.1 : Trim to gain.  
v1.0.2 : Typooooooooooooo.  
v1.0.3 : threshold down by +12 and -12 dB before & after main processing.  

TODO: 
  * threshold control knob maybe?  
  * attack knob?  