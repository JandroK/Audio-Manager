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
	// Load Textures and Fx
	laserR = app->tex->Load("Assets/Textures/bullet_red.png");
	laserB = app->tex->Load("Assets/Textures/bullet_blue.png");
	laserFx = app->audio->LoadFx("Assets/Audio/Fx/fx_laser.wav");

	// Get dimension of textures
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
	ListItem<Bullet*>* item;
	if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)// || app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_REPEAT)
	{
		AddBullet();

		// Play Fx
		for (item = bullets.start; item != NULL; item = item->next)
		{
			app->audio->PlayFx(item->data->channel, laserFx);
		}
	}
	// Explosion bullets all direction
	if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_REPEAT)
	{
		AddBullet();

		// Play Fx
		for (item = bullets.start; item != NULL; item = item->next)
		{
			app->audio->PlayFx(item->data->channel, laserFx);
		}
	}

	// Update entities positions
	for (item = bullets.start; item != NULL; item = item->next)
	{
		item->data->pos.x += speed * cos(item->data->angle * PI/180);
		item->data->pos.y += speed * sin(item->data->angle * PI/180);
	}

	// Update distance and  direction
	for (item = bullets.start; item != NULL; item = item->next)
	{
		app->audio->SetDistanceFx(item->data->channel, item->data->angle, 0, 255);
	}
	
	return true;
}

// Called each loop iteration
bool Scene::PostUpdate()
{
	bool ret = true;

	// Draw all bullets
	ListItem<Bullet*>* item;
	for (item = bullets.start; item != NULL; item = item->next)
	{
		app->render->DrawTexture(item->data->laserTex, item->data->pos.x, item->data->pos.y, 0, 1, item->data->angle);
	}

	if(app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
		ret = false;

	return ret;
}

void Scene::AddBullet()
{
	// Create new entity
	Bullet* b = new Bullet;
	bullets.Add(b);

	// Assign texture
	if (bullets.Count() % 2 == 0)
	{
		b->laserTex = laserR;
		b->pos.x = (WINDOW_WIDTH * 0.5) - (dimensionLaserR.x * 0.5);
		b->pos.y = (WINDOW_HIGHT * 0.5) - (dimensionLaserR.y * 0.5);
	}
	else
	{
		b->laserTex = laserB;
		b->pos.x = (WINDOW_WIDTH * 0.5) - (dimensionLaserB.x * 0.5);
		b->pos.y = (WINDOW_HIGHT * 0.5) - (dimensionLaserB.y * 0.5);
	}

	// Assign direction
	if (bullets.Count() == 1)
		b->angle = 0;
	else
		b->angle = bullets.end->prev->data->angle + 10;

	// Assign new channel
	b->channel = app->audio->SetChannel();
}

// Called before quitting
bool Scene::CleanUp()
{
	LOG("Freeing scene");

	app->tex->UnLoad(laserR);
	app->tex->UnLoad(laserB);

	bullets.Clear();

	return true;
}
