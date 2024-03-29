
#ifndef MAIN_OBJECT_H
#define MAIN_OBJECT_H

#include "CommonFunc.h"
#include "BaseObject.h"
#include "BulletObject.h"

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
	void Show(SDL_Renderer* des);             // load 1 frame len man hinh                       
	void HandleInputAction(SDL_Event events, SDL_Renderer* screen, Map & map_data); // xu ly su kien
	void set_clips();

	void DoPlayer(Map& map_data);
	void CheckToMap(Map& map_data);

	void UpdateImagePlayer(SDL_Renderer* des);

	void set_bullet_list(std::vector <BulletObject*> Bullet_list) {
		bullet_list = Bullet_list;
	}
	std::vector <BulletObject*>  get_bullet_list() const { return bullet_list; }
	void HandleBullet(SDL_Renderer* des);

	void RemoveBullet(Map & map_data);
private:

	std::vector <BulletObject* > bullet_list; // vector chua c�c vi�n dann 
	float x_val, y_val, x_pos, y_pos;

	int width_frame, height_frame;  // luu w, h cua moi frame 

	SDL_Rect frame_clip[8]; // luu x,y,w,h cua tung frame de load len 
	Input input_type;

	int frame;   // luu chi so frame 
	int status;  // xem la WALK_Right hay left , up , down 
	int soluongdattoida;
};


#endif