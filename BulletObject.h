#ifndef BULLET_OBJECT_H
#define BULLET_OBJECT_H


#include "BaseObject.h"
#include "CommonFunc.h"
#include "NoBom.h"

class BulletObject : public BaseObject
{
public:
	BulletObject();
	//~BulletObject();


	void set_is_move(const bool& isMove) { is_move = isMove; }
	bool get_is_move() const { return is_move; }

	int get_bullet_time() { return bullet_time; }
	void set_bullet_time(int time) { bullet_time = time; }

	NoBom get_nobom_doc() { return doc; }
	void set_nobom_doc(NoBom no) { doc = no; }

	NoBom get_nobom_ngang() { return ngang; }
	void set_nobom_ngang(NoBom no) { ngang = no; }


	void set_bullet_type(const int& bulletType) { bullet_type = bulletType; }
	int get_bullet_type() const { return bullet_type; }


	enum BulletType
	{
		SUNG_LUA = 9,
		SUNG_DAN = 10,
		MIN = 11,
		TEN_LUA = 12,
		LA_CHAN = 13,
		SUNG_DIEN = 14,
		BOM = 15,
	};

	void LoadImgBullet(SDL_Renderer* des);

private:
	NoBom doc;
	NoBom ngang;
	bool is_move;
	int bullet_time;
	int bullet_type;
};


#endif 
