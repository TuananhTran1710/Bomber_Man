#include "BulletObject.h"
BulletObject::BulletObject() {
	bullet_time = 0;
	is_move = false;
	bullet_type = BOM;
	x_val = 0;
	y_val = 0;
}

void BulletObject::HandleMove_Dan(const int& x_border, const int& y_border)
{
	if (bullet_dir == DIR_RIGHT)
	{                                    
		rect.x += x_val;
		if (rect.x < x_border && rect.x >= lim_dis) is_move = false;    // TH chưa vượt qua giới hạn map nhưng vượt qua tầm bắn
		else if (rect.x >= x_border) is_move = false;
	}
	else if (bullet_dir == DIR_LEFT)
	{
		rect.x -= x_val;
		if (rect.x <= lim_dis && rect.x > 185) is_move = false;      // TH chưa vượt qua giới hạn map nhưng vượt qua tầm bắn
		else if (rect.x <= 185)  is_move = false;
	}
	else if (bullet_dir == DIR_DOWN)
	{
		rect.y += y_val;
		if (rect.y < y_border && rect.y >= lim_dis) is_move = false;
		else if (rect.y >= y_border) is_move = false;
	}
	else if (bullet_dir == DIR_UP)
	{
		rect.y -= y_val;
		if (rect.y > 60 && rect.y <= lim_dis) is_move = false;
		else if (rect.y < 60) is_move = false;
	}
}

void BulletObject::HandleMove_TenLua(const int& x_border, const int& y_border)
{
	if (bullet_dir == DIR_RIGHT)
	{
		rect.x += x_val;
		if (rect.x > x_border) is_move = false;
	}
	else if (bullet_dir == DIR_LEFT)
	{
		rect.x -= x_val;
		if (rect.x <= 185)  is_move = false;
	}
	else if (bullet_dir == DIR_DOWN)
	{
		rect.y += y_val;
		if (rect.y >= y_border) is_move = false;
	}
	else if (bullet_dir == DIR_UP)
	{
		rect.y -= y_val;
		if (rect.y < 15) is_move = false;
	}
}

void BulletObject::LoadImgBullet(SDL_Renderer* des)
{
	if (bullet_type == MIN)
	{
		LoadImg("map1/min.png", des);
	}
	else if (bullet_type == SUNG_DAN)
	{
		LoadImg("map1/dan.png", des);
	}
	else if (bullet_type == SUNG_LUA)
	{
		LoadImg("map1/lua_right.png", des);
	}
	else if (bullet_type == TEN_LUA)
	{
		LoadImg("map1/ten_lua1.png", des);
	}
	else if (bullet_type == SUNG_DIEN)
	{
		LoadImg("map1/lazer_ngang.png", des);
	}
	else
	{
		LoadImg("map1/bom.png", des);
	}
}

