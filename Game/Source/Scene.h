#ifndef __SCENE_H__
#define __SCENE_H__

#include "Module.h"

struct SDL_Texture;

class Bullet
{
public:
	fPoint pos;
	SDL_Texture* laserTex;
	int angle;
	int channel;
};

class Scene : public Module
{
public:

	Scene();

	// Destructor
	virtual ~Scene();

	// Called before render is available
	bool Awake();

	// Called before the first frame
	bool Start();

	// Called before all Updates
	bool PreUpdate();

	// Called each loop iteration
	bool Update(float dt);

	void AddBullet();

	// Called before all Updates
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();

private:
	float speed = 0.1f;

	SDL_Texture* laserR;
	SDL_Texture* laserB;

	iPoint dimensionLaserR;
	iPoint dimensionLaserB;

	uint laserFx;

	List<Bullet*> bullets;
};

#endif // __SCENE_H__