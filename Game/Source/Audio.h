#ifndef __AUDIO_H__
#define __AUDIO_H__

#include "Module.h"

#define DEFAULT_MUSIC_FADE_TIME 2.0f

struct _Mix_Music;
struct Mix_Chunk;

class Audio : public Module
{
public:

	Audio();

	// Destructor
	virtual ~Audio();

	// Called before render is available
	bool Awake(pugi::xml_node&);

	// Called before quitting
	bool CleanUp();

	// Play a music file
	bool PlayMusic(const char* path, float fadeTime = DEFAULT_MUSIC_FADE_TIME);
	void PauseMusic();
	void ResumeMusic();
	void StopMusic();
	void RewindMusic();
	void MusicPos(double second);
	void SetMusicVolume(int volume);

	// Load a WAV in memory
	unsigned int LoadFx(const char* path);

	// Play a previously loaded WAV
	bool PlayFx(int channel, unsigned int fx, int repeat = 0);
	void SetDistanceFx(int channel, int angle, uint distance, uint maxDistance);
	int SetChannel();
	void DeleteChannel();
	bool RemoveChannel();
	void PauseFx(int channel);
	void ResumeFx(int channel);
	void StopFx(int channel);
	void ChangeMusicVolume(int volume);
	void ChangeFxVolume(int volume);

	// Save and Load volume
	bool LoadState(pugi::xml_node& node);
	bool SaveState(pugi::xml_node& node)const;

	// Return volume music
	int GetVolumeMusic() { return volumeMusic; }
	bool GetPendingToDelete() { return pendingToDelete; }

private:

	_Mix_Music* music;
	List<Mix_Chunk *>	fx;

	// TODO: Create the varaibles you need
	int maxNumChannels = 10;
	int numChannels = 0;
	int volumeMusic = 128; // 128 = MIX_MAX_VOLUME
	int volumeFx = 128;
	bool pendingToDelete = false;
};

#endif // __AUDIO_H__