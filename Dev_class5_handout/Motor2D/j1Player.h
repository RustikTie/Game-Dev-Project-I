#pragma once
#ifndef __j1PLAYER_H__
#define __j1PLAYER_H__

#include "j1Module.h"
struct SDL_Texture;

class j1Player
{
public:
	j1Player();
	~j1Player();

	bool Start();
	bool PreUpdate();
	bool Update();
	bool PostUpdate();
	bool CleanUp();

private:
	SDL_Texture* graphics = nullptr;
	SDL_Texture* textures = nullptr;
};

#endif