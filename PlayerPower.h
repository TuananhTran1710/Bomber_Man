#ifndef PLAYER_POWER_H_
#define PLAYER_POWER_H_

#include "CommonFunc.h"
#include "BaseObject.h"

class PlayerPower : public BaseObject
{
public:
	PlayerPower();
	~PlayerPower();
	
	void SetNum(const int& num) { number = num; }
	void AddPos(const int& xPos);

	void Show(SDL_Renderer* screen, double y);
	void Init(SDL_Renderer* screen);

	void InitIncrease();
	void Decrease();

private: 
	int number;
	std::vector <int > pos_list;
};



#endif