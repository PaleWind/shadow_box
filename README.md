This is my first attempt at using a microcontroller (ESP-32) to create a lighting fixture. It is a custom-built facade for DJ performances made with eight WS2812B LED strips formed into rectangles (rectangles, Patrick!). It is powered by a ac-dc rectifier rated for 80 amps and requires a hard-wired MIDI-out capable device to drive the lights. This can be a MIDI keyboard, or almost any DAW. There are 12 light patterns onboard, each one mapped to a note between C and B (1-12). Each rectangle is then assigned an octave from left to right, 1-8. so playing a D#3 would make the 3rd rectangle perform the corresponding pattern. This mapping makes it easy to script light shows in a DAW, but others are possible. Check out the videos below.

[![Preview video 1](https://img.youtube.com/vi/Bd3a6nxfuBI/0.jpg)](https://www.youtube.com/watch?v=Bd3a6nxfuBI)


[![Preview video 2](https://img.youtube.com/vi/NWVAufJtODM/0.jpg)](https://www.youtube.com/watch?v=NWVAufJtODM)
