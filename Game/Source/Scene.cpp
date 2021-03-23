#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "Scene.h"

#include "Defs.h"
#include "Log.h"

#define MARGIN 50

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

	player.x = (WINDOW_WIDTH * 0.5) - (dimensionLaserR.x * 0.5);
	player.y = (WINDOW_HIGHT * 0.5) - (dimensionLaserR.y * 0.5);

	return true;
}

// Called each loop iteration
bool Scene::PreUpdate()
{
	ListItem<Bullet*>* item;
	for (item = bullets.start; item != NULL; item = item->next)
	{
		if(item->data->pendingToDelete == true) 
			DeleteBody(item->data);
	}
	return true;
}

// Called each loop iteration
bool Scene::Update(float dt)
{
	ListItem<Bullet*>* item;
	if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
	{
		AddBullet();

		// Play Fx
		for (item = bullets.start; item != NULL; item = item->next)
		{
			app->audio->PlayFx(item->data->channel, laserFx);
		}
	}
	// Explosion bullets all direction
	if (app->input->GetKey(SDL_SCANCODE_A) == KEY_DOWN)
	{
		for (int i = 0; i < 360 / offsetAngle; i++)
		{
			AddBullet();

			// Play Fx
			for (item = bullets.start; item != NULL; item = item->next)
			{
				app->audio->PlayFx(item->data->channel, laserFx);
			}
		}
	}

	// Update entities positions
	for (item = bullets.start; item != NULL; item = item->next)
	{
		item->data->pos.x += speed * cos(item->data->angle * PI/180);
		item->data->pos.y += speed * sin(item->data->angle * PI/180);
	}

	// Update distance and direction
	for (item = bullets.start; item != NULL; item = item->next)
	{
		app->audio->SetDistanceFx(item->data->channel, item->data->angle, DistanceToListener(player, item->data->pos), WINDOW_WIDTH/2);
	}

	// Check if the bullet is off-camera
	for (item = bullets.start; item != NULL; item = item->next)
	{
		if (item->data->pos.x > WINDOW_WIDTH + MARGIN || item->data->pos.x < 0 - MARGIN
			|| item->data->pos.y > WINDOW_HIGHT + MARGIN || item->data->pos.y < 0 - MARGIN)
		{
			item->data->pendingToDelete = true;
		}
	}

	// Up/Down Music
	if (app->input->GetKey(SDL_SCANCODE_KP_PLUS) == KEY_DOWN)
		app->audio->ChangeMusicVolume(10);
	if (app->input->GetKey(SDL_SCANCODE_KP_MINUS) == KEY_DOWN)
		app->audio->ChangeMusicVolume(-10);

	// Play Music
	if (app->input->GetKey(SDL_SCANCODE_Z) == KEY_DOWN)
	{
		app->audio->PlayMusic("Assets/Audio/Music/galactic_empire.ogg");
	}
	if (app->input->GetKey(SDL_SCANCODE_X) == KEY_DOWN)
	{
		app->audio->PlayMusic("Assets/Audio/Music/imperial_march.ogg");
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
		b->laserTex = laserR;
	else
		b->laserTex = laserB;

	//Assign position
	b->pos.x = player.x;
	b->pos.y = player.y;

	// Assign direction
	if (bullets.Count() == 1)
		b->angle = 0;
	else
		b->angle = bullets.end->prev->data->angle + offsetAngle;

	// Assign new channel
	b->channel = app->audio->SetChannel();
}

int Scene::DistanceToListener(iPoint player, fPoint channel)
{
	iPoint pos;
	pos.x = player.x - channel.x;
	pos.y = player.y - channel.y;

	return sqrt(pow(pos.x,2)+pow(pos.y,2));
}

// Delete one bullet
void Scene::DeleteBody(Bullet* body)
{
	ListItem<Bullet*>* item;

	for (item = bullets.start; item != NULL; item = item->next)
	{
		if (item->data == body)
		{
			for (ListItem<Bullet*>* item2 = item->next; item2 != NULL; item2 = item2->next)
			{
				item2->data->channel = item2->prev->data->channel;
			}
			bullets.Del(item);
			app->audio->DeleteChannel();

			break;
		}
	}
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
