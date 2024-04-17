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

	enum BulletDir
	{
		DIR_RIGHT = 30,
		DIR_LEFT = 31,
		DIR_UP = 32,
		DIR_DOWN = 33,
	};

	void LoadImgBullet(SDL_Renderer* des);


	void set_x_val(const int& x) { x_val = x; }
	int get_x_val() { return x_val; }

	void set_y_val(const int& x) { y_val = x; }
	int get_y_val() { return y_val; }

	void HandleMove(const int& x_border, const int& y_border);

	void set_bullet_dir(const int& x) { bullet_dir = x; }
	int get_bullet_dir() { return bullet_dir; }

	int get_lim_dis() { return lim_dis; }
	void set_lim_dis(int x) { lim_dis = x; }

private:
	NoBom doc;
	NoBom ngang;
	bool is_move;
	int bullet_time;
	int bullet_type;
	int bullet_dir;
	int x_val, y_val;
	int lim_dis;
};


#endif 
