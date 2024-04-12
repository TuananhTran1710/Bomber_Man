#include "PlayerPower.h"

PlayerPower::PlayerPower()
{
	number = 0;
}

PlayerPower::~PlayerPower()
{

}

void PlayerPower::AddPos(const int& xp)
{
	pos_list.push_back(xp);
}


void PlayerPower::Init(SDL_Renderer* screen)
{
	LoadImg("map1/mang.png", screen);
	number = 3;
	if (pos_list.size() > 0)
	{
		pos_list.clear();
	}
	AddPos(100);
	AddPos(120);
	AddPos(140);
}

void PlayerPower::Decrease()
{
	number--;
	pos_list.pop_back();
}

void PlayerPower::InitIncrease()
{
	number++;
	int last_pos = pos_list.back();
	last_pos += 40;
	pos_list.push_back(last_pos);
}

void PlayerPower::Show(SDL_Renderer* screen, double y)
{
	for (int i = 0; i < pos_list.size(); i++)
	{
		rect.x = pos_list.at(i);
		rect.y = y;
		Render(screen);
	}
}