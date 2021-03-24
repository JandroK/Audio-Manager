## Audio and Music Manager

I am [Alejandro Moreno](https://www.linkedin.com/in/alejandro-moreno-0b01ab1b2/), student of the [Bachelor’s Degree in Video Games by UPC at CITM](https://www.linkedin.com/school/centre-de-la-imatge-i-la-tecnologia-multim-dia-upc-/mycompany/). This content is generated for the second year’s subject Project 2, under supervision of lecturer [Ramón Santamaria](https://www.linkedin.com/in/raysan/).

## Intoduction

This research talks about the implementation of the Audio Manager to manage all music and sound effects of a video game, and the internal functioning of the functions used by the Audio Manager. 

The main focus of this research is: 

* Develop a music manager
* Every entity can potentially generate audio
* Discard entities that are too far
* Check camera position/zoom to play the audio spatially
* Music Manager: Chain a playlist with fading

## Music Manager

The music manager is a module or code structure selfmade that allow the developer to handle different audio inputs from several sources, load and erasing those fx’s or audio at will. In this research we will be using audio.h and audio.cpp. In orther to follow the explanation it’s recommended to take a look to the [SDL_Mixer](https://www.libsdl.org/projects/SDL_mixer/docs/SDL_mixer.pdf) documentation.

## Spatial audio

Spatial Audio is any audio which gives you a sense of space beyond conventional stereo, allowing the user to pinpoint where sound is coming from, whether this is above, below, or a full 360 degrees around you. For example stereo allows you to hear things in front left and right, but you can’t get a sense of surround, height or sounds from below you. With the introduction of the 3rd dimension, you have a sense of the exact location of sound sources from all around. This definition also appeals to 3D audio.

Let's see the differences with the other types of audio:

The stereo audio have 2 channels:

![](/docs/Images/dolby_atmos_stereo.png)

The surround sound have 5-7 channels:

![](/docs/Images/surround_sound.png)

The spatial sound full 360 degrees around you:

![](/docs/Images/spatial_sound.png)

Spatial audio is a manipulation of the sound that makes the feeling of a 3D space, you can listen [here](https://upfa3d.wordpress.com/category/spatial-audio/) videos that show this effect.

You can also check the audio difference in the following videos:

* [LST 3D Sound Demo](https://www.youtube.com/watch?v=QFaSIti5_d0)

* [Call of Duty Warzone Sound: Stereo vs. Dolby Atmos vs. Windows Sonic](https://www.youtube.com/watch?v=xLxjRnpxhB0)

* [Resident Evil 2 Remake: Windows Sonic vs Dolby Atmos vs DTS Headphone:X [HRTF]](https://www.youtube.com/watch?v=cKx4UOyCDpo)

