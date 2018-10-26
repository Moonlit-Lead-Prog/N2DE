#include "Game.h"
#include "TextureManager.h"
#include "Map.h"

#include "Engine/ECS/Components.h"
#include "Engine/Additions/Vector2.h"

#include "Engine/ECS/Collision.h"

Map* map;
Manager manager;

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;

auto& player(manager.addEntity());
auto& wall(manager.addEntity());

Game::Game() 
{}
Game::~Game()
{}

void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
{
	int flags = 0;
	if (fullscreen) flags = SDL_WINDOW_FULLSCREEN;

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		std::cout << "Subsystems Initialised!" << std::endl;

		window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		if (window)
		{
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			std::cout << "Window created" << std::endl;
		}

		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer)
		{
			std::cout << "Renderer created" << std::endl;
		}

		isRunning = true;
	}
	else isRunning = false;

	map = new Map();

	player.addComponent<TransformComponent>(352,224,32,32,1);
	player.addComponent<SpriteComponent>("assets/char.png");
	player.addComponent<keyboardController>();
	player.addComponent<ColliderComponent>("Player");

	wall.addComponent<TransformComponent>(300, 180, 192, 32, 1);
	wall.addComponent<SpriteComponent>("assets/Wall1.png");
	wall.addComponent<ColliderComponent>("wall");
}

void Game::handleEvents()
{
	SDL_PollEvent(&event);
	switch (event.type)
	{
	case SDL_QUIT:
		isRunning = false;
		break;
	default:
		break;
	}
}

bool walkRight = true;

Uint32 lastMoveTime;
int timePassed;

int counterNum = 0;

void Game::update()
{
	manager.refresh();
	manager.update();

	if (Collision::AABB(player.getComponent<ColliderComponent>().collider,
		wall.getComponent<ColliderComponent>().collider))
	{
		std::cout << "Wall Hit" << std::endl;
		player.getComponent<TransformComponent>().velocity * -1;
	}

	//player.getComponent<SpriteComponent>().setTex("assets/Dirt1.png");

}

void Game::render()
{
	SDL_RenderClear(renderer);
	map->DrawMap();
	manager.draw();
	SDL_RenderPresent(renderer);
}

void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "Cleaned up game";
}