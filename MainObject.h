
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
	void Show(SDL_Renderer* des, double rect_x , double rect_y);
	void HandleInputAction1(SDL_Event events, SDL_Renderer* screen, Map& map_data, Mix_Chunk* bullet_sound[4]); // xu ly su kien cho nhan vat 1 
	void HandleInputAction2(SDL_Event events, SDL_Renderer* screen, Map& map_data, Mix_Chunk* bullet_sound[4]);  // xu ly su kien cho nhan vat 2 

	void set_clips();

	void DoPlayer(Map& map_data, SDL_Renderer*des);
	void CheckToMap(Map& map_data, SDL_Renderer *des);


	void HandleBullet(SDL_Renderer* des);

	void RemoveBullet_Bom(Map& map_data, SDL_Renderer* des, Mix_Chunk* sound[2]);
	void RemoveBullet_Min(Map& map_data, SDL_Renderer* des);


	void set_pos2(float x, float y);

	int get_width_frame() { return width_frame; }
	int get_height_frame() { return height_frame; }

	std::vector <std::pair <NoBom, NoBom>> get_no_bom_list() const { return nobom; }
	std::vector <std::pair <NoBom, NoBom>> get_no_min_list() const { return nomin; }
	std::vector <std::pair <NoBom, NoBom>> get_no_tenlua_list() const { return no_tenlua; }


	void set_bat_tu(bool con) { bat_tu = con; }
	bool get_bat_tu() { return bat_tu; }

	void set_num_life(int x) { num_life = x; }
	int get_num_life() { return num_life; }
	void Increase_num_life() { num_life++; }
	void Decrease_num_life() { num_life--; input_type.die = 1; }
	
	void set_max_bom(int x) { max_bom = x; }
	int	 get_max_bom() { return max_bom; }
	void Increase_max_bom() { max_bom++; }
	void Decrease_max_bom() { max_bom--; }

	int get_num_kill() { return num_kill; }
	void set_num_kill(int x) { num_kill = x; }
	void Increase_num_kill() { num_kill++; }

	void check_item_lachan( int val_1 ,int val_2);
	void check_item_bom(int val_1, int val_2);
	void check_item_min(int val_1, int val_2);

	int get_have_lachan() { return have_lachan; }
	void set_have_lachan(int x) { have_lachan = x; }

	// xử lý hình ảnh thông tin lá chắn
	void init_lachan(SDL_Renderer* screen , double x, double y);
	void show_la_chan(SDL_Renderer* screen);

	void init_min(SDL_Renderer* screen, double x, double y);
	void show_min(SDL_Renderer* screen);

	void init_sung_dan(SDL_Renderer* screen, double x, double y);
	void show_sung_dan(SDL_Renderer* screen);

	void init_sung_lua(SDL_Renderer* screen, double x, double y);
	void show_sung_lua(SDL_Renderer* screen);

	void init_ten_lua(SDL_Renderer* screen, double x, double y);
	void show_ten_lua(SDL_Renderer* screen);

	void check_item_tenlua(int val_1, int val_2);

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

	void check_col_min(int val_1, int val_2, Map& map_data, SDL_Renderer* des);

	void set_bullet_list(std::vector <BulletObject*> Bullet_list) {	bullet_list_bom = Bullet_list; }

	std::vector <BulletObject*>  get_bullet_list_bom() const { return bullet_list_bom; }

	std::vector <BulletObject*>  get_bullet_list_min() const { return bullet_list_min; }
	
	std::vector<BulletObject*> get_bullet_list() { return bullet_list; }

	void check_item_sungdan(int val_1, int val_2);

	void check_item_sunglua(int val_1, int val_2);

	void HandleBullet_Dan(SDL_Renderer* des);


	void check_col_sungdan(Map& map_data);

	void RemoveBullet_Col(const int& idx);

	void RemoveTenLua_Col(const int& idx);
	std::vector<BulletObject*> get_bullet_list_lua() { return bullet_list_lua; }

	std::vector<BulletObject*> get_bullet_list_tenlua() { return bullet_list_tenlua; }

	void HandleBullet_Lua(SDL_Renderer* des);

	void HandleBullet_TenLua(SDL_Renderer* des,Map& map_data);

	void RemoveBullet_Lua(Map& map_data, SDL_Renderer* des);

	void check_col_tenlua(Map& map_data,SDL_Renderer *des,Mix_Chunk * sound[4]);

	void RemoveBullet_Tenlua(Map& map_data, SDL_Renderer*des,BulletObject* p_bullet, int map_y, int map_x, Mix_Chunk* sound[4]);

	void check_around_MainObject(Map& map_data, SDL_Renderer* des, BulletObject* p_bullet, double x_pos, double y_pos);

	void AddList_NoMin(BulletObject* p_bullet, SDL_Renderer * des);

	int Rand(int l, int r);

	void RemoveBullet_Min(const int& idx);

	int get_status() { return status; }

	void set_num_min() { num_min--; }

	void set_type_bullet(int x) { type_bullet = x; }
	
private:
	std::vector <BulletObject* > bullet_list;

	std::vector <BulletObject* > bullet_list_lua;
	std::vector <BulletObject* > bullet_list_tenlua;
	std::vector <BulletObject* > bullet_list_min;
	std::vector <BulletObject* > bullet_list_bom; //vector chua c�c vi�n dann 
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
	std::vector< std::pair <NoBom, NoBom>> nomin;

	std::vector<std::pair<NoBom, NoBom>> no_tenlua;

	int num_kill;
	int have_lachan;

	int num_sung_dan;
	int num_sung_lua;
	int num_ten_lua;
	int num_min;
	int num_sung_dien;

	int type_bullet;
	BaseObject lachan, sung_dan, sung_lua, ten_lua, min_, sung_dien;
};


#endif