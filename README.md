# Audio and Music Manager

## Presentation

I am [Alejandro Moreno](https://www.linkedin.com/in/alejandro-moreno-0b01ab1b2/), student of the [Bachelor’s Degree in Video Games by UPC at CITM](https://www.linkedin.com/school/centre-de-la-imatge-i-la-tecnologia-multim-dia-upc-/mycompany/). This content is generated for the second year’s subject Project 2, under supervision of lecturer [Ramón Santamaria](https://www.linkedin.com/in/raysan/).

## Description

This research talks about the implementation of the Audio Manager to manage all music and sound effects of a video game, and the internal functioning of the functions used by the Audio Manager. 
The program is a bullet system in which each entity is assigned a different channel. All bullets spawn from the center of the screen and depending on the direction in which they go the listener will be heard from one direction or another, thus getting to check the spatial sound in 360 degrees.

#### Music Manager

The music manager is a module or code structure selfmade that allow the developer to handle different audio inputs from several sources, load and erasing those fx’s or audio at will. In this research we will be using audio.h and audio.cpp. In orther to follow the explanation it’s recommended to take a look to the [SDL_Mixer](https://www.libsdl.org/projects/SDL_mixer/docs/SDL_mixer.pdf) documentation.

#### Spatial audio

Spatial Audio is any audio which gives you a sense of space beyond conventional stereo, allowing the user to pinpoint where sound is coming from, whether this is above, below, or a full 360 degrees around you. For example stereo allows you to hear things in front left and right, but you can’t get a sense of surround, height or sounds from below you. With the introduction of the 3rd dimension, you have a sense of the exact location of sound sources from all around. This definition also appeals to 3D audio.

Let's see the differences with the other types of audio:

The stereo audio have 2 channels:

![](https://github.com/JandroK/Audio-Manager/blob/gh-pages/docs/Images/dolby_atmos_stereo.png)

The surround sound have 5-7 channels:

![](https://github.com/JandroK/Audio-Manager/blob/gh-pages/docs/Images/surround_sound.png)

The spatial sound full 360 degrees around you:

![](https://github.com/JandroK/Audio-Manager/blob/gh-pages/docs/Images/spatial_sound.png)

## Key Features

* Develop a music manager
* Every entity can potentially generate audio
* Discard entities that are too far
* Check camera position/zoom to play the audio spatially
* Music Manager: Chain a playlist with fading
 
## Controls

* Space: Spawn a bullet to the east, and the next one has an offset of 10 degrees
* Mouse button: Spawn a bullet towards the direction of the mouse position.
* A: Spaw 36 bullets in all directions forming a perfect circle
* +/-: Up/Down Music
* Arrow Up/ Arrow Down: Up/Down Fx
* Z: PlayMusic 1
* X: PlayMusic 2
* ESC: Exit program

## License

This project is licensed under an unmodified MIT license, which is an OSI-certified license that allows static linking with closed source software. Check [LICENSE](https://github.com/JandroK/Audio-Manager/blob/master/LICENSE) for further details.
