#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "Scene.h"

#include "Defs.h"
#include "Log.h"

Scene::Scene() : Module()
{
	name.Create("scene");
}

// Destructor
Scene::~Scene()
{}

// Called before render is available
bool Scene::Awake()
{
	LOG("Loading Scene");
	bool ret = true;

	return ret;
}

// Called before the first frame
bool Scene::Start()
{
	laserR = app->tex->Load("Assets/Textures/bullet_red.png");
	laserB = app->tex->Load("Assets/Textures/bullet_blue.png");
	laserFx = app->audio->LoadFx("Assets/Audio/Fx/fx_laser.wav");

	SDL_QueryTexture(laserR, NULL, NULL, &dimensionLaserR.x, &dimensionLaserR.y);
	SDL_QueryTexture(laserB, NULL, NULL, &dimensionLaserB.x, &dimensionLaserB.y);

	//app->audio->PlayMusic("Assets/Audio/Music/music_spy.ogg");

	return true;
}

// Called each loop iteration
bool Scene::PreUpdate()
{
	return true;
}

// Called each loop iteration
bool Scene::Update(float dt)
{
	//if(app->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT)
	//	app->render->camera.y -= 1;

	//if(app->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT)
	//	app->render->camera.y += 1;

	//if(app->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
	//	app->render->camera.x -= 1;

	//if(app->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
	//	app->render->camera.x += 1;

	

	return true;
}

// Called each loop iteration
bool Scene::PostUpdate()
{
	bool ret = true;

	app->render->DrawTexture(laserR, (WINDOW_WIDTH * 0.5) - (dimensionLaserR.x * 0.5), WINDOW_HIGHT * 0.5 - (dimensionLaserR.y * 0.5));
	app->render->DrawTexture(laserB, (WINDOW_WIDTH * 0.5) - (dimensionLaserB.x * 0.5), WINDOW_HIGHT * 0.5 - (dimensionLaserB.y * 0.5));

	if(app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
		ret = false;

	return ret;
}

// Called before quitting
bool Scene::CleanUp()
{
	LOG("Freeing scene");

	app->tex->UnLoad(laserR);
	app->tex->UnLoad(laserB);

	return true;
}
