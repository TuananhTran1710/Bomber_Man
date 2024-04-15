﻿
#ifndef MAIN_OBJECT_H
#define MAIN_OBJECT_H

#include "CommonFunc.h"
#include "BaseObject.h"
#include "BulletObject.h"
#include "NoBom.h"
#define PLAYER_SPEED 7.5

class MainObject : public BaseObject
{
public:
	MainObject();

	~MainObject();
	enum WalkType
	{
		WALK_RIGHT,
		WALK_LEFT,
		WALK_UP,
		WALK_DOWN,
	};

	bool LoadImg(std::string path, SDL_Renderer* screen);   // load ca anh to len va lay width_frame, height_frame

	void Show1(SDL_Renderer* des);             // load 1 frame len man hinh       
	void Show2(SDL_Renderer* des);

	void HandleInputAction1(SDL_Event events, SDL_Renderer* screen, Map& map_data); // xu ly su kien cho nhan vat 1 
	void HandleInputAction2(SDL_Event events, SDL_Renderer* screen, Map& map_data);  // xu ly su kien cho nhan vat 2 

	void set_clips();

	void DoPlayer(Map& map_data);
	void CheckToMap(Map& map_data);

	void set_bullet_list(std::vector <BulletObject*> Bullet_list) {
		bullet_list = Bullet_list;
	}

	std::vector <BulletObject*>  get_bullet_list() const { return bullet_list; }

	void HandleBullet(SDL_Renderer* des);

	void RemoveBullet(Map& map_data, SDL_Renderer* des);

	void set_pos2(float x, float y);

	int get_width_frame() { return width_frame; }
	int get_height_frame() { return height_frame; }

	std::vector <std::pair <NoBom, NoBom>> get_no_bom_list() const { return nobom; }

	void set_bat_tu(bool con) { bat_tu = con; }
	bool get_bat_tu() { return bat_tu; }

	void set_num_life(int x) { num_life = x; }
	int get_num_life() { return num_life; }
	void Increase_num_life() { num_life++; }
	void Decrease_num_life() { num_life--; }

	void set_max_bom(int x) { max_bom = x; }
	int	 get_max_bom() { return max_bom; }
	void Increase_max_bom() { max_bom++; }
	void Decrease_max_bom() { max_bom--; }

	int get_num_kill() { return num_kill; }
	void set_num_kill(int x) { num_kill = x; }
	void Increase_num_kill() { num_kill++; }

	void check_item_lachan( int val_1 ,int val_2);
	void check_item_bom(int val_1, int val_2);
	void check_item_sung_dan(int val_1, int val_2);

	int get_have_lachan() { return have_lachan; }
	void set_have_lachan(int x) { have_lachan = x; }

	// xử lý hình ảnh thông tin lá chắn
	void init_lachan(SDL_Renderer* screen , double x, double y);
	void show_la_chan(SDL_Renderer* screen);

	int get_num_sung_dien() { return num_sung_dien; }
	void set_num_sung_dien(int x) { num_sung_dien = x; }

	int get_num_sung_dan() { return num_sung_dan; }
	void set_num_sung_dan(int x) { num_sung_dan = x; }

	int get_num_sung_lua() { return num_sung_lua; }
	void set_num_sung_lua(int x) { num_sung_lua = x; }

	int get_num_min() { return num_min; }
	void set_num_min(int x) { num_min = x; }

	int get_num_ten_lua() { return num_ten_lua; }
	void set_num_ten_lua(int x) { num_ten_lua = x; }
	
private:

	std::vector <BulletObject* > bullet_list; // vector chua c�c vi�n dann 
	float x_val, y_val, x_pos, y_pos;

	int width_frame, height_frame;  // luu w, h cua moi frame 
	bool bat_tu; 
	SDL_Rect frame_clip[8]; // luu x,y,w,h cua tung frame de load len 
	Input input_type;
	int frame;   // luu chi so frame 
	int status;  // xem la WALK_Right hay left , up , down 
	int max_bom;
	int num_life;
	std::vector< std :: pair <NoBom,NoBom> > nobom;
	int num_kill;
	int have_lachan;

	int num_sung_dan;
	int num_sung_lua;
	int num_ten_lua;
	int num_min;
	int num_sung_dien;

	BaseObject lachan, sung_dan, sung_lua, ten_lua, min_, sung_dien;
};


#endif