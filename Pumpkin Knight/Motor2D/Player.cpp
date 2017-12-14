#include "Player.h"
#include "j1Gui.h"
#include "j1Render.h"
#include "j1Fonts.h"

Player::Player(int x, int y) : Entity(x, y)
{
	App->entity_manager->player = true;
	//collider = App->collisions->AddCollider({(int)pos.x, (int)pos.y, 25, 40}, COLLIDER_PLAYER, (j1Module*)App->entity_manager);
	animation = NULL;
	graphics = NULL;
	
	heart = { 4344, 2670, 122, 114 };

	idle.PushBack({ 1,48,30,46 });
	idle.PushBack({ 32,48,30,46 });
	idle.PushBack({ 63,48,30,46 });
	idle.PushBack({ 94,48,30,46 });
	idle.PushBack({ 125,48,30,46 });
	idle.PushBack({ 156,48,30,46 });
	idle.PushBack({ 187,48,30,46 });
	idle.PushBack({ 218,48,30,46 });
	idle.PushBack({ 249,48,30,46 });
	idle.PushBack({ 280,48,30,46 });
	idle.PushBack({ 311,48,30,46 });
	idle.loop = true;
	idle.speed = 0.01f;

	forward.PushBack({ 1, 1, 30, 46 });
	forward.PushBack({ 32, 1, 30, 46 });
	forward.PushBack({ 63, 1, 30, 46 });
	forward.PushBack({ 94, 1, 30, 46 });
	forward.PushBack({ 125, 1, 30, 46 });
	forward.PushBack({ 156, 1, 30, 46 });
	forward.PushBack({ 187, 1, 30, 46 });
	forward.PushBack({ 218, 1, 30, 46 });
	forward.PushBack({ 249, 1, 30, 46 });
	forward.PushBack({ 280, 1, 30, 46 });
	forward.PushBack({ 311, 1, 30, 46 });
	forward.PushBack({ 342, 1, 30, 46 });
	forward.PushBack({ 373, 1, 30, 46 });
	forward.loop = true;
	forward.speed = 0.02f;

	/*jump.PushBack({ 1, 95, 30, 46 });
	jump.PushBack({ 32, 95, 30, 46 });
	jump.PushBack({ 63, 95, 30, 46 });
	jump.PushBack({ 63, 95, 30, 46 });
	jump.PushBack({ 94, 95, 30, 46 });
	jump.PushBack({ 125, 95, 30, 46 });*/
	jump.PushBack({ 156, 95, 30, 46 });
	/*jump.PushBack({ 187, 95, 30, 46 });
	jump.PushBack({ 218, 95, 30, 46 });
	jump.PushBack({ 218, 95, 30, 46 });
	jump.PushBack({ 249, 95, 30, 46 });
	jump.PushBack({ 280, 95, 30, 46 });*/
	jump.loop = false;
	jump.speed = 0.04f;

	//animation = &idle;
	initial_pos = original_pos.x;

	scoreChar = App->font->Print("SCORE:", { 255,255,255 }, App->gui->font);
}


Player::~Player()
{
	App->tex->UnLoad(sprites);

}

bool Player::Start()
{
	LOG("Loading Player");

	collider = App->collisions->AddCollider({ (int)pos.x, (int)pos.y, 18 * 3, 27 * 3 }, COLLIDER_PLAYER, (j1Module*)App->entity_manager);
	sprites = App->tex->Load("assets/Pumpkin sprites.png");

	return true;
}

bool Player::Awake(pugi::xml_node& config)
{
	pugi::xml_document	config_file;
	pugi::xml_node		config2;

	config2 = App->LoadConfig(config_file);

	config2 = config2.child("entities").child("player");

	velocity.x = config2.child("velocity").attribute("value").as_float();
	velocity.y = config2.child("velocity").attribute("value").as_float();
	acceleration.x = config2.child("acceleration").attribute("x").as_float();
	acceleration.y = config2.child("acceleration").attribute("y").as_float();
	gravity = config2.child("gravity").attribute("value").as_float();
	jump_speed.y = config2.child("jump").attribute("velocity_y").as_float();
	jump_height = config2.child("jump").attribute("height").as_float();
	jump_speed.x = config2.child("jump").attribute("velocity_x").as_float();
	x_scale = config2.child("scale").attribute("x").as_int();
	y_scale = config2.child("scale").attribute("x").as_int();

	return true;
}

void Player::MoveEntity(float dt)
{
	dt = dt / 1000;

	idle.speed = 10.f*dt;
	forward.speed = 10.f*dt;
	jump.speed = 10.f*dt;

	//pos = original_pos;
	//animation = &idle;

	//MOVEMEMT
	//JUMP
	if (App->input->GetKey(SDL_SCANCODE_W) == KEY_DOWN && !falling)
	{
		jumping = true;
		max_height = (pos.y - jump_height);
	}
	if (App->input->GetKey(SDL_SCANCODE_W) == KEY_UP)
	{
		jumping = false;
		falling = true;
	}
	if (App->input->GetKey(SDL_SCANCODE_W) == KEY_DOWN && pos.y - max_height != jump_height && !contact)
	{
		jumping = false;
		double_jumping = true;
		contact = true;
		max_height = (pos.y - jump_height);
	}
	if (App->input->GetKey(SDL_SCANCODE_W) == KEY_UP)
	{
		double_jumping = false;
		falling = true;
	}
	//FORWARD
	if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
	{
		flip = false;
		animation = &forward;
		speed = velocity.x;
	}

	//BACKWARD
	else if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
	{
		animation = &forward;
		speed = -velocity.x;
		flip = true;
	}
	//IDLE 
	else
	{
		speed = 0;
		animation = &idle;
	}

	Jump(dt);
	//JUMP LEFT OR RIGHT

	if (jumping == true)
	{
		if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
		{
			pos.x += speed*dt;
		}
		if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
		{
			pos.x += speed*dt;
		}
		pos.y -= jump_speed.y*dt;
	}
	if (!dead && !jumping)
	{
		speed;
		pos.x += speed*dt;
	}

	//if (collider->CheckCollision(App->map->collider) == false)
	//{
	//	//speed = gravity*dt;
	//	pos.y += gravity*dt;
	//}

	if (falling)
	{
		animation = &jump;
	}

	if (App->input->GetKey(SDL_SCANCODE_F10))
	{
		if (!godmode)
		{
			godmode = true;
		}
		else
		{
			godmode = false;
		}
	}
	////DRAW PLAYER -----------------------------------------
	////App->render->Blit(graphics, pos.x, pos.y, 3, 3, flip, &(animation->GetCurrentFrame()), 1.0f);

	App->render->camera.x = (-pos.x + 400);

	//if (playercollider != nullptr)
	//{
	//	playercollider->SetPos(pos.x + 10, pos.y + 50);
	//}

	if (pos.y > 500)
	{
		if (pos.y > 800)
		{
			pos.x = 100;
			pos.y = 200;
			lives -= 1;
		}

	}

}

void Player::Jump(float dt)
{
	if (!jumping)
	{
		pos.y += gravity*dt;
	}
	if (jumping)
	{
		if (pos.y >= max_height)
		{
			jumping_speed.y = jump_speed.y*dt;
			animation = &jump;
			pos.y -= jumping_speed.y;
		}
		if (pos.y < max_height)
		{
			jumping_speed.y = 0;
			jumping = false;
			jump.Reset();
			falling = true;
		}
	}

	if (double_jumping)
	{
		jumping_speed.y = 0;
		if (pos.y >= max_height)
		{
			jumping_speed.y = jump_speed.y*dt * 2;
			animation = &jump;
			pos.y -= jumping_speed.y;
		}
		if (pos.y < max_height)
		{
			jumping_speed.y = 0;
			double_jumping = false;
			jump.Reset();
			falling = true;
		}
	}
}

void Player::Draw(float dt)
{
	//animation->speed = 10.f*dt;
	collider->SetPos(pos.x + 10, pos.y + 50);
	App->render->Blit(sprites, pos.x, pos.y, x_scale, y_scale, flip, &(animation->GetCurrentFrame()));

	if (lives >= 1)
	{
		App->render->Blit(App->gui->GetGuiAtlas(), pos.x-5, pos.y, 0.2, 0.2, false, &heart);
	}
	if (lives >= 2)
	{
		App->render->Blit(App->gui->GetGuiAtlas(), pos.x +25, pos.y, 0.2, 0.2, false, &heart);
	}
	if (lives >= 3)
	{
		App->render->Blit(App->gui->GetGuiAtlas(), pos.x + 55, pos.y, 0.2, 0.2, false, &heart);

	}
	
}