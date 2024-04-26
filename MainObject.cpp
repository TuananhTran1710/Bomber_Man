#include "MainObject.h"
#include "ImpTimer.h"
std::vector< ImpTimer> Delay_time_bom;
std::vector< ImpTimer> Delay_time_min;
std::vector< ImpTimer> Delay_time_tenlua;
int dx[4] = { 1,-1,0,0 };
int dy[4] = { 0,0,-1,1 };
ImpTimer Delay_bullet;
ImpTimer Delay_bullet_dien;

MainObject::MainObject() {
	frame = 0;
	x_pos = 185;
	y_pos = 60;
	x_val = 0;
	y_val = 0;
	width_frame = 0;
	height_frame = 0;
	status = -1;
	input_type.left = 0;
	input_type.right = 0;
	input_type.down = 0;
	input_type.up = 0;
	input_type.die = 0;
	max_bom = 1;
	bat_tu = false;
	
	num_kill = 0;
	have_lachan = 0;
	type_bullet = 15;

	num_sung_dan=0;
	num_sung_lua=0;
	num_ten_lua=0;
	num_min=0;
	num_sung_dien=0;
	// đặt ben ngoai de cho cos thể bắn ra được viên đầu
	Delay_bullet.start();
	Delay_bullet_dien.start();
}
MainObject :: ~MainObject() {

}
//------------------------------------------------------------------------------------
void MainObject::set_pos2(float x, float y)
{
	x_pos = x;
	y_pos = y;
}
bool MainObject::LoadImg(std::string path, SDL_Renderer* screen) {
	bool ret = BaseObject::LoadImg(path, screen);
	if (ret == true) {
		width_frame = rect.w / 8;
		height_frame = rect.h;    
	}
	return ret;
}
void MainObject::set_clips() {
	if (width_frame > 0 && height_frame > 0) {

		for (int i = 0; i <= 7; i++) {
			frame_clip[i].x = i * width_frame;
			frame_clip[i].y = 0;
			frame_clip[i].w = width_frame;
			frame_clip[i].h = height_frame;
		}
	}
}

void MainObject::Show1(SDL_Renderer* des) {

	if (input_type.die == 1){
		LoadImg("map1/die.png", des);
	}
	else {
		if (status == WALK_LEFT) {
			LoadImg("map1/left.png", des);  // ham LoadImg nay la ham trong MainObject_1.h chu kp trong Object.h
		}
		else if (status == WALK_RIGHT)
		{
			LoadImg("map1/right.png", des);
		}
		else if (status == WALK_UP)
		{
			LoadImg("map1/up.png", des);
		}
		else if (status == WALK_DOWN)
		{
			LoadImg("map1/down.png", des);
		}
	}
	//
	if (input_type.left == 1 || input_type.right == 1 || input_type.up == 1 || input_type.down == 1 || input_type.die == 1) {
		frame++;
		if (input_type.die == 1) SDL_Delay(70);
	}
	else {
		frame = 0;
	}

	if (frame >= 8){
		if (input_type.die == 1)
		{
			input_type.die = 0;
			x_pos = 185;
			y_pos = 60;
		}
		frame = 0;
	}

		rect.x = x_pos;  // day la vi tri tren man hinh ma hien thi nhan vat len
		rect.y = y_pos;

		SDL_Rect* current_clip = &frame_clip[frame];

		SDL_Rect renderQuad = { rect.x ,rect.y , width_frame,height_frame };
		SDL_RenderCopy(des, p_object, current_clip, &renderQuad);
}
void MainObject::Show2(SDL_Renderer* des) {

	
	if (input_type.die == 1) {
		LoadImg("map1/die.png", des);
	}
	else
	{
		if (status == WALK_LEFT) {
			LoadImg("map1/left2.png", des);  // ham LoadImg nay la ham trong MainObject_1.h chu kp trong Object.h
		}
		else if (status == WALK_RIGHT)
		{
			LoadImg("map1/right2.png", des);
		}
		else if (status == WALK_UP)
		{
			LoadImg("map1/up2.png", des);
		}
		else if (status == WALK_DOWN)
		{
			LoadImg("map1/down2.png", des);
		}
	}
	//
	if (input_type.left == 1 || input_type.right == 1 || input_type.up == 1 || input_type.down == 1 || input_type.die == 1) {
		frame++;
		if (input_type.die == 1) SDL_Delay(70);
	}
	else {
		frame = 0;
	}

	if (frame >= 8) {
		if (input_type.die == 1)
		{
			input_type.die = 0;
			x_pos = 185 + 45 * 14;
			y_pos = 60;
		}
		frame = 0;
	}

	rect.x = x_pos;  // day la vi tri tren man hinh ma hien thi nhan vat len
	rect.y = y_pos;

	SDL_Rect* current_clip = &frame_clip[frame];

	SDL_Rect renderQuad = { rect.x ,rect.y , width_frame,height_frame };
	SDL_RenderCopy(des, p_object, current_clip, &renderQuad);
}
//-------------------------------------------------------------------------------------------
// xu ly sự kiện
void MainObject::HandleInputAction1(SDL_Event events, SDL_Renderer* screen, Map& map_data, Mix_Chunk* bullet_sound[4]) {
	if (events.type == SDL_KEYDOWN) {
		switch (events.key.keysym.sym)
		{
		case SDLK_d:
		{
			status = WALK_RIGHT;
			input_type.right = 1;
			input_type.left = 0;
			input_type.up = 0;
			input_type.down = 0;
			break;
		}
		case SDLK_a:
		{
			status = WALK_LEFT;
			input_type.left = 1;
			input_type.right = 0;
			input_type.up = 0;
			input_type.down = 0;

			break;
		}
		case SDLK_w:
		{
			status = WALK_UP;
			input_type.up = 1;
			input_type.right = 0;
			input_type.left = 0;
			input_type.down = 0;
			break;
		}
		case SDLK_s:
		{
			status = WALK_DOWN;
			input_type.down = 1;
			input_type.up = 0;
			input_type.left = 0;
			input_type.right = 0;
			break;
		}
		}
	}
	else if (events.type == SDL_KEYUP)
	{
		switch (events.key.keysym.sym)
		{
		case SDLK_d:
		{
			input_type.right = 0;
			break;
		}

		case SDLK_a:
		{
			input_type.left = 0;
			break;
		}
		case SDLK_w:
		{
			input_type.up = 0;
			break;
		}
		case SDLK_s:
		{
			input_type.down = 0;
			break;
		}
		}
	}
	// nhấn để bắn đạn 
	if (type_bullet == 15)
	{
		if (events.type == SDL_KEYDOWN)
		{
			if (events.key.keysym.sym == SDLK_SPACE)
			{

				if (bullet_list_bom.size() < max_bom)
				{
					BulletObject* p_bullet = new BulletObject();
					p_bullet->set_bullet_type(type_bullet);

					p_bullet->LoadImgBullet(screen);
					p_bullet->SetRect(185 + floor((this->x_pos - 185) / 45) * 45 + 2, 60 + floor((this->y_pos - 60) / 45) * 45 + 2);
					p_bullet->set_is_move(true); // chuyển sang true tức là cho phép đạn bắn ra 
					// nhu vậy phần trên đã khởi tạo xong viên đạn 

					bullet_list_bom.push_back(p_bullet);
					p_bullet->set_bullet_time(SDL_GetTicks() );				
					Mix_PlayChannel(-1, bullet_sound[0], 0);
				}

			}
		}
	}
	else if (type_bullet == 11)
	{
		if (events.type == SDL_KEYDOWN)
		{
			if (events.key.keysym.sym == SDLK_SPACE)
			{
				if (bullet_list_min.size() == 0)
				{
					BulletObject* p_bullet = new BulletObject();

					p_bullet->set_bullet_type(type_bullet);
					p_bullet->LoadImgBullet(screen);
					p_bullet->SetRect(185 + floor((this->x_pos - 185) / 45) * 45 + 2, 60 + floor((this->y_pos - 60) / 45) * 45 + 2);
					p_bullet->set_is_move(true); // chuyển sang true tức là cho phép đạn bắn ra 
					// nhu vậy phần trên đã khởi tạo xong viên đạn 

					bullet_list_min.push_back(p_bullet); // nạp đạn sẵn vào băng, chỉ ấn là đạn sẽ xuất hiện

				}
				else if (bullet_list_min.size() == 1)
				{
					for (int i = 0; i < bullet_list_min.size(); i++)      
					{
						BulletObject* p_bullet = bullet_list_min.at(i);
						bullet_list_min.erase(bullet_list_min.begin() + i);
						num_min--;
						if (num_min == 0)
						{
							max_bom++;
							type_bullet = 15;
						}
						int map_x; int map_y;
						map_x = (p_bullet->GetRect().x - 185) / 45;
						map_y = (p_bullet->GetRect().y - 15) / 45;
						/// 
						if (map_data.tile[map_y][map_x] == 20 || map_data.tile[map_y][map_x] == 0)
						{
							for (int k = 0; k < 4; k++)
							{
								if (map_x + dx[k] >= 0 && map_y + dy[k] > 0 && map_y + dy[k] < 14 && map_x + dx[k] <= 14)
								{
									if (!(map_data.tile[map_y + dy[k]][map_x + dx[k]] == 7 || map_data.tile[map_y + dy[k]][map_x + dx[k]] == 3))
									{
										if (map_data.tile[map_y + dy[k]][map_x + dx[k]] == 4 || map_data.tile[map_y + dy[k]][map_x + dx[k]] == 5 || map_data.tile[map_y + dy[k]][map_x + dx[k]] == 6)
										{
											map_data.tile[map_y + dy[k]][map_x + dx[k]] = Rand(9, 15);
										}
										else if (map_data.tile[map_y + dy[k]][map_x + dx[k]] >= 9 && map_data.tile[map_y + dy[k]][map_x + dx[k]] <= 15)  // tức là mìn khác bom ở chỗ sẽ nổ được cả các item
										{
											map_data.tile[map_y + dy[k]][map_x + dx[k]] = 0;
										}
									}
								}
							}
							map_data.tile[map_y][map_x] = 0;
						}

						// xử lý nổ mìn

						nomin.push_back({ p_bullet->get_nobom_doc(),p_bullet->get_nobom_ngang() });

						(*nomin.rbegin()).first.LoadImg("map1/nobom_doc.png", screen);
						(*nomin.rbegin()).second.LoadImg("map1/nobom_ngang.png", screen);

						(*nomin.rbegin()).first.SetRect(p_bullet->GetRect().x, p_bullet->GetRect().y - 45 - 2);
						(*nomin.rbegin()).second.SetRect(p_bullet->GetRect().x - 45 - 2, p_bullet->GetRect().y);

						ImpTimer ret; Delay_time_min.push_back(ret);
						(*Delay_time_min.rbegin()).start();

						if (p_bullet != NULL)
						{
							delete p_bullet;
							p_bullet = NULL;
						}
					}
				}
			}
		}
	}
	else if (type_bullet == 10)
	{
		if (events.type = SDL_KEYDOWN)
		{
			if (events.key.keysym.sym == SDLK_SPACE)
			{
				if (bullet_list.size() < num_sung_dan && Delay_bullet.get_ticks() > 300)
				{
					BulletObject* p_bullet = new BulletObject();

					p_bullet->set_bullet_type(type_bullet);
					p_bullet->LoadImgBullet(screen);

					if (status == WALK_LEFT)
					{
						p_bullet->set_bullet_dir(BulletObject::DIR_LEFT);
						p_bullet->SetRect(this->rect.x, this->rect.y + height_frame * 0.5);
						//set tam ban cho vien dan ( tầm bắn của súng này là 3 ô )
						p_bullet->set_lim_dis(this->rect.x - 45 * 3);
					}
					else if (status == WALK_RIGHT)
					{
						p_bullet->set_bullet_dir(BulletObject::DIR_RIGHT);
						p_bullet->SetRect(this->rect.x + width_frame - 10, this->rect.y + height_frame * 0.5);
						//set tam ban cho vien dan
						p_bullet->set_lim_dis(this->rect.x + width_frame + 45*3);
					}
					else if (status == WALK_UP)
					{
						p_bullet->set_bullet_dir(BulletObject::DIR_UP);
						p_bullet->SetRect(this->rect.x + 10, this->rect.y);

						p_bullet->set_lim_dis(this->rect.y - 45 * 3);
					}
					else if (status == WALK_DOWN)
					{
						p_bullet->set_bullet_dir(BulletObject::DIR_DOWN);
						p_bullet->SetRect(this->rect.x + 10, this->rect.y + height_frame);

						p_bullet->set_lim_dis(this->rect.y + height_frame + 45 * 3);
					}
					
					p_bullet->set_x_val(17);   // set tốc độ cho viên đạn
					p_bullet->set_y_val(17);
					p_bullet->set_is_move(true); 

					Delay_bullet.start();
					bullet_list.push_back(p_bullet);
					Mix_PlayChannel(-1, bullet_sound[2], 0);
				}
			}
		}
	}
	else if (type_bullet == 9)
	{
		if (events.type == SDL_KEYDOWN)
		{
			if (events.key.keysym.sym == SDLK_SPACE)
			{
				if (bullet_list_lua.size() < num_sung_lua)
				{
					BulletObject* p_bullet = new BulletObject();
					p_bullet->set_bullet_type(type_bullet);

					if (status == WALK_RIGHT)
					{
						p_bullet->LoadImg("map1/lua_right.png", screen);
						p_bullet->SetRect(this->rect.x + width_frame , this->rect.y + 10);
						p_bullet->set_bullet_dir(BulletObject::DIR_RIGHT);
					}
					else if (status == WALK_LEFT)
					{
						p_bullet->LoadImg("map1/lua_left.png", screen);
						p_bullet->SetRect(this->rect.x - p_bullet->GetRect().w , this->rect.y + 10);
						p_bullet->set_bullet_dir(BulletObject::DIR_LEFT);
					}
					else if (status == WALK_UP)
					{
						p_bullet->LoadImg("map1/lua_up.png", screen);
						p_bullet->SetRect(this->rect.x + 10, this->rect.y - p_bullet->GetRect().h);
						p_bullet->set_bullet_dir(BulletObject::DIR_UP);
					}
					else if (status == WALK_DOWN)
					{
						p_bullet->LoadImg("map1/lua_down.png", screen);
						p_bullet->SetRect(this->rect.x + 5, this->rect.y + height_frame);
						p_bullet->set_bullet_dir(BulletObject::DIR_DOWN);
					}
					p_bullet->set_is_move(true);
					bullet_list_lua.push_back(p_bullet);
					p_bullet->set_bullet_time(SDL_GetTicks());
					Mix_PlayChannel(-1, bullet_sound[3], 0);
				}
			}
		}
	}
	else if (type_bullet == 12)
	{
		if (events.type == SDL_KEYDOWN)
		{
			if (events.key.keysym.sym == SDLK_SPACE)
			{
				if (bullet_list_tenlua.size() < num_ten_lua)
				{
					BulletObject* p_bullet = new BulletObject();
					p_bullet->set_bullet_type(type_bullet);
					
					if (status == WALK_RIGHT)
					{
						p_bullet->LoadImg("map1/ten_lua_right.png", screen);
						p_bullet->SetRect(this->rect.x + width_frame -10, this->rect.y + 10);
						p_bullet->set_bullet_dir(BulletObject::DIR_RIGHT);
					}
					else if (status == WALK_LEFT)
					{
						p_bullet->LoadImg("map1/ten_lua_left.png", screen);
						p_bullet->SetRect(this->rect.x - p_bullet->GetRect().w, this->rect.y + 10);
						p_bullet->set_bullet_dir(BulletObject::DIR_LEFT);
					}
					else if (status == WALK_UP)
					{
						p_bullet->LoadImg("map1/ten_lua_up.png", screen);
						p_bullet->SetRect(this->rect.x + 10, this->rect.y - p_bullet->GetRect().h);
						p_bullet->set_bullet_dir(BulletObject::DIR_UP);
					}
					else if (status == WALK_DOWN)
					{
						p_bullet->LoadImg("map1/ten_lua_down.png", screen);
						p_bullet->SetRect(this->rect.x + 10, this->rect.y + height_frame - 10);
						p_bullet->set_bullet_dir(BulletObject::DIR_DOWN);
					}

					p_bullet->set_x_val(17);   // set tốc độ cho viên đạn
					p_bullet->set_y_val(17);
					p_bullet->set_is_move(true);
					bullet_list_tenlua.push_back(p_bullet);
					bullet_sound[1] = Mix_LoadWAV("Bomb+4.wav");
					Mix_PlayChannel(-1, bullet_sound[1], 0);
				}
			}
		}
	}
	else if (type_bullet == 14)
	{
		if (events.type = SDL_KEYDOWN)
		{
			if (events.key.keysym.sym == SDLK_SPACE)
			{
				if (bullet_list.size() < num_sung_dien && Delay_bullet_dien.get_ticks() > 300)
				{
					BulletObject* p_bullet = new BulletObject();

					p_bullet->set_bullet_type(type_bullet);

					if (status == WALK_LEFT)
					{
						p_bullet->LoadImg("map1/lazer_ngang.png", screen);
						p_bullet->set_bullet_dir(BulletObject::DIR_LEFT);
						p_bullet->SetRect(this->rect.x, this->rect.y + height_frame * 0.5);
						//set tam ban cho vien dan ( tầm bắn của súng này là 10 ô )
						p_bullet->set_lim_dis(this->rect.x - 45 * 10);
					}
					else if (status == WALK_RIGHT)
					{
						p_bullet->LoadImg("map1/lazer_ngang.png", screen);
						p_bullet->set_bullet_dir(BulletObject::DIR_RIGHT);
						p_bullet->SetRect(this->rect.x + width_frame - 10, this->rect.y + height_frame * 0.5);
						//set tam ban cho vien dan
						p_bullet->set_lim_dis(this->rect.x + width_frame + 45 * 10);
					}
					else if (status == WALK_UP)
					{
						p_bullet->LoadImg("map1/lazer_doc.png", screen);
						p_bullet->set_bullet_dir(BulletObject::DIR_UP);
						p_bullet->SetRect(this->rect.x + 10, this->rect.y);

						p_bullet->set_lim_dis(this->rect.y - 45 * 10);
					}
					else if (status == WALK_DOWN)
					{
						p_bullet->LoadImg("map1/lazer_doc.png", screen);
						p_bullet->set_bullet_dir(BulletObject::DIR_DOWN);
						p_bullet->SetRect(this->rect.x + 10, this->rect.y + height_frame);

						p_bullet->set_lim_dis(this->rect.y + height_frame + 45 * 10);
					}

					p_bullet->set_x_val(17);   // set tốc độ cho viên đạn
					p_bullet->set_y_val(17);
					p_bullet->set_is_move(true);

					Delay_bullet_dien.start();
					bullet_list.push_back(p_bullet);
					Mix_PlayChannel(-1, bullet_sound[2], 0);
				}
			}
		}
	}


	for (int i = 0; i < bullet_list_bom.size(); i++) {
		BulletObject* p_bullet = bullet_list_bom.at(i);
		int map_x; int map_y;
		map_x = (p_bullet->GetRect().x - 185) / 45;
		map_y = (p_bullet->GetRect().y - 15) / 45;
		/// 
		int x = (floor((this->x_pos - 185) / 45));
		int y = (floor((this->y_pos - 15) / 45));
		if (!(x == map_x && y == map_y)) {             // để cho sau khi đặt bom ( bom và người trùng 1 ô) thì người vẫn có thể di chuyển trong ô đó
			map_data.tile[map_y][map_x] = 8;			// đến khi nào người ra hẳn ngoài thì mới set cho ô đó thành ô không đi được 
		}
	}

	for (int i = 0; i < bullet_list_min.size(); i++) {
		BulletObject* p_bullet = bullet_list_min.at(i);
		if (p_bullet != NULL)
		{
			int map_x; int map_y;
			map_x = (p_bullet->GetRect().x - 185) / 45;
			map_y = (p_bullet->GetRect().y - 15) / 45;
			/// 
			int x = (floor((this->x_pos - 185) / 45));
			int y = (floor((this->y_pos - 15) / 45));
			if (!(x == map_x && y == map_y)) {             // để cho sau khi đặt min ( min và người trùng 1 ô) thì người vẫn có thể di chuyển trong ô đó mà không bị nổ
				map_data.tile[map_y][map_x] = 20;			// đến khi nào người ra hẳn ngoài thì mới set cho ô có mìn và khi đi vào thì bị nổ 
			}
		}
	}
}
void MainObject::HandleInputAction2(SDL_Event events, SDL_Renderer* screen, Map& map_data, Mix_Chunk* bullet_sound[4]) {
	if (events.type == SDL_KEYDOWN) {
		switch (events.key.keysym.sym)
		{
		case SDLK_RIGHT:
		{
			status = WALK_RIGHT;
			input_type.right = 1;
			input_type.left = 0;
			input_type.up = 0;
			input_type.down = 0;
			break;
		}
		case SDLK_LEFT:
		{
			status = WALK_LEFT;
			input_type.left = 1;
			input_type.right = 0;
			input_type.up = 0;
			input_type.down = 0;

			break;
		}
		case SDLK_UP:
		{
			status = WALK_UP;
			input_type.up = 1;
			input_type.right = 0;
			input_type.left = 0;
			input_type.down = 0;
			break;
		}
		case SDLK_DOWN:
		{
			status = WALK_DOWN;
			input_type.down = 1;
			input_type.up = 0;
			input_type.left = 0;
			input_type.right = 0;
			break;
		}
		}
	}
	else if (events.type == SDL_KEYUP)
	{
		switch (events.key.keysym.sym)
		{
		case SDLK_RIGHT:
		{
			input_type.right = 0;
			break;
		}

		case SDLK_LEFT:
		{
			input_type.left = 0;
			break;
		}
		case SDLK_UP:
		{
			input_type.up = 0;
			break;
		}
		case SDLK_DOWN:
		{
			input_type.down = 0;
			break;
		}
		}
	}
	// nhấn để bắn đạn 
	if (type_bullet == 15)
	{
		if (events.type == SDL_KEYDOWN)
		{
			if (events.key.keysym.sym == SDLK_KP_ENTER)
			{

				if (bullet_list_bom.size() < max_bom)
				{
					BulletObject* p_bullet = new BulletObject();
					p_bullet->set_bullet_type(type_bullet);
					p_bullet->LoadImgBullet(screen);
					// 
					p_bullet->SetRect(185 + floor((this->x_pos - 185) / 45) * 45 + 2, 60 + floor((this->y_pos - 60) / 45) * 45 + 2);
					p_bullet->set_is_move(true); // chuyển sang true tức là cho phép đạn bắn ra 
					// nhu vậy phần trên đã khởi tạo xong viên đạn 

					bullet_list_bom.push_back(p_bullet); // nạp đạn sẵn vào băng, chỉ ấn là đạn sẽ xuất hiện
					p_bullet->set_bullet_time(SDL_GetTicks());
					Mix_PlayChannel(-1, bullet_sound[0], 0);
				}
			}
		}
	}

	if (type_bullet == 11)
	{
		if (events.type == SDL_KEYDOWN)
		{
			if (events.key.keysym.sym == SDLK_KP_ENTER)
			{
				if (bullet_list_min.size() == 0)
				{
					BulletObject* p_bullet = new BulletObject();

					p_bullet->set_bullet_type(type_bullet);
					p_bullet->LoadImgBullet(screen);
					p_bullet->SetRect(185 + floor((this->x_pos - 185) / 45) * 45 + 2, 60 + floor((this->y_pos - 60) / 45) * 45 + 2);
					p_bullet->set_is_move(true); // chuyển sang true tức là cho phép đạn bắn ra 
					
					bullet_list_min.push_back(p_bullet); 

				}
				else if (bullet_list_min.size() == 1)
				{
					for (int i = 0; i < bullet_list_min.size(); i++)
					{
						BulletObject* p_bullet = bullet_list_min.at(i);
						bullet_list_min.erase(bullet_list_min.begin() + i);
						num_min--;
						if (num_min == 0)
						{
							max_bom++;
							type_bullet = 15;
						}
						int map_x; int map_y;
						map_x = (p_bullet->GetRect().x - 185) / 45;
						map_y = (p_bullet->GetRect().y - 15) / 45;
						/// 
						if (map_data.tile[map_y][map_x] == 20 || map_data.tile[map_y][map_x] == 0)
						{
							for (int k = 0; k < 4; k++)
							{
								if (map_x + dx[k] >= 0 && map_y + dy[k] > 0 && map_y + dy[k] < 14 && map_x + dx[k] <= 14)
								{
									if (!(map_data.tile[map_y + dy[k]][map_x + dx[k]] == 7 || map_data.tile[map_y + dy[k]][map_x + dx[k]] == 3))
									{
										if (map_data.tile[map_y + dy[k]][map_x + dx[k]] == 4 || map_data.tile[map_y + dy[k]][map_x + dx[k]] == 5 || map_data.tile[map_y + dy[k]][map_x + dx[k]] == 6)
										{
											map_data.tile[map_y + dy[k]][map_x + dx[k]] = Rand(9, 15);
										}
										else if (map_data.tile[map_y + dy[k]][map_x + dx[k]] >= 9 && map_data.tile[map_y + dy[k]][map_x + dx[k]] <= 15)  // tức là mìn khác bom ở chỗ sẽ nổ được cả các item
										{
											map_data.tile[map_y + dy[k]][map_x + dx[k]] = 0;
										}
									}
								}
							}
							map_data.tile[map_y][map_x] = 0;
						}

						// xử lý nổ mìn

						nomin.push_back({ p_bullet->get_nobom_doc(),p_bullet->get_nobom_ngang() });

						(*nomin.rbegin()).first.LoadImg("map1/nobom_doc.png", screen);
						(*nomin.rbegin()).second.LoadImg("map1/nobom_ngang.png", screen);

						(*nomin.rbegin()).first.SetRect(p_bullet->GetRect().x, p_bullet->GetRect().y - 45 - 2);
						(*nomin.rbegin()).second.SetRect(p_bullet->GetRect().x - 45 - 2, p_bullet->GetRect().y);

						ImpTimer ret; Delay_time_min.push_back(ret);
						(*Delay_time_min.rbegin()).start();

						if (p_bullet != NULL)
						{
							delete p_bullet;
							p_bullet = NULL;
						}
					}
				}
			}
		}
	}
	else if (type_bullet == 10)
	{
		if (events.type = SDL_KEYDOWN)
		{
			if (events.key.keysym.sym == SDLK_KP_ENTER)
			{
				if (bullet_list.size() < num_sung_dan && Delay_bullet.get_ticks() > 300)
				{
					BulletObject* p_bullet = new BulletObject();

					p_bullet->set_bullet_type(type_bullet);
					p_bullet->LoadImgBullet(screen);

					if (status == WALK_LEFT)
					{
						p_bullet->set_bullet_dir(BulletObject::DIR_LEFT);
						p_bullet->SetRect(this->rect.x, this->rect.y + height_frame * 0.5);
						//set tam ban cho vien dan ( tầm bắn của súng này là 3 ô )
						p_bullet->set_lim_dis(this->rect.x - 45 * 3);
					}
					else if (status == WALK_RIGHT)
					{
						p_bullet->set_bullet_dir(BulletObject::DIR_RIGHT);
						p_bullet->SetRect(this->rect.x + width_frame - 10, this->rect.y + height_frame * 0.5);
						//set tam ban cho vien dan
						p_bullet->set_lim_dis(this->rect.x + width_frame + 45 * 3);
					}
					else if (status == WALK_UP)
					{
						p_bullet->set_bullet_dir(BulletObject::DIR_UP);
						p_bullet->SetRect(this->rect.x + 10, this->rect.y);

						p_bullet->set_lim_dis(this->rect.y - 45 * 3);
					}
					else if (status == WALK_DOWN)
					{
						p_bullet->set_bullet_dir(BulletObject::DIR_DOWN);
						p_bullet->SetRect(this->rect.x + 10, this->rect.y + height_frame);

						p_bullet->set_lim_dis(this->rect.y + height_frame + 45 * 3);
					}

					p_bullet->set_x_val(17);   // set tốc độ cho viên đạn
					p_bullet->set_y_val(17);
					p_bullet->set_is_move(true);

					Delay_bullet.start();
					bullet_list.push_back(p_bullet);
					Mix_PlayChannel(-1, bullet_sound[2], 0);
				}
			}
		}
	}
	else if (type_bullet == 9)
	{
		if (events.type == SDL_KEYDOWN)
		{
			if (events.key.keysym.sym == SDLK_KP_ENTER)
			{
				if (bullet_list_lua.size() < num_sung_lua)
				{
					BulletObject* p_bullet = new BulletObject();
					p_bullet->set_bullet_type(type_bullet);

					if (status == WALK_RIGHT)
					{
						p_bullet->LoadImg("map1/lua_right.png", screen);
						p_bullet->SetRect(this->rect.x + width_frame, this->rect.y + 10);
						p_bullet->set_bullet_dir(BulletObject::DIR_RIGHT);
					}
					else if (status == WALK_LEFT)
					{
						p_bullet->LoadImg("map1/lua_left.png", screen);
						p_bullet->SetRect(this->rect.x - p_bullet->GetRect().w, this->rect.y + 10);
						p_bullet->set_bullet_dir(BulletObject::DIR_LEFT);
					}
					else if (status == WALK_UP)
					{
						p_bullet->LoadImg("map1/lua_up.png", screen);
						p_bullet->SetRect(this->rect.x + 10, this->rect.y - p_bullet->GetRect().h);
						p_bullet->set_bullet_dir(BulletObject::DIR_UP);
					}
					else if (status == WALK_DOWN)
					{
						p_bullet->LoadImg("map1/lua_down.png", screen);
						p_bullet->SetRect(this->rect.x + 5, this->rect.y + height_frame);
						p_bullet->set_bullet_dir(BulletObject::DIR_DOWN);
					}
					p_bullet->set_is_move(true);
					bullet_list_lua.push_back(p_bullet);
					p_bullet->set_bullet_time(SDL_GetTicks());
					Mix_PlayChannel(-1, bullet_sound[3], 0);
				}
			}
		}
	}
	else if (type_bullet == 12)
	{
		if (events.type == SDL_KEYDOWN)
		{
			if (events.key.keysym.sym == SDLK_KP_ENTER)
			{
				if (bullet_list_tenlua.size() < num_ten_lua)
				{
					BulletObject* p_bullet = new BulletObject();
					p_bullet->set_bullet_type(type_bullet);

					if (status == WALK_RIGHT)
					{
						p_bullet->LoadImg("map1/ten_lua_right.png", screen);
						p_bullet->SetRect(this->rect.x + width_frame - 10, this->rect.y + 15);
						p_bullet->set_bullet_dir(BulletObject::DIR_RIGHT);
					}
					else if (status == WALK_LEFT)
					{
						p_bullet->LoadImg("map1/ten_lua_left.png", screen);
						p_bullet->SetRect(this->rect.x - p_bullet->GetRect().w, this->rect.y + 15);
						p_bullet->set_bullet_dir(BulletObject::DIR_LEFT);
					}
					else if (status == WALK_UP)
					{
						p_bullet->LoadImg("map1/ten_lua_up.png", screen);
						p_bullet->SetRect(this->rect.x + 10, this->rect.y - p_bullet->GetRect().h);
						p_bullet->set_bullet_dir(BulletObject::DIR_UP);
					}
					else if (status == WALK_DOWN)
					{
						p_bullet->LoadImg("map1/ten_lua_down.png", screen);
						p_bullet->SetRect(this->rect.x + 10, this->rect.y + height_frame - 10);
						p_bullet->set_bullet_dir(BulletObject::DIR_DOWN);
					}

					p_bullet->set_x_val(17);   // set tốc độ cho viên đạn
					p_bullet->set_y_val(17);
					p_bullet->set_is_move(true);
					bullet_list_tenlua.push_back(p_bullet);
					Mix_PlayChannel(-1, bullet_sound[1], 0);
				}
			}
		}
	}
	else if (type_bullet == 14)
	{
		if (events.type = SDL_KEYDOWN)
		{
			if (events.key.keysym.sym == SDLK_KP_ENTER)
			{
				if (bullet_list.size() < num_sung_dien && Delay_bullet_dien.get_ticks() > 300)
				{
					BulletObject* p_bullet = new BulletObject();

					p_bullet->set_bullet_type(type_bullet);

					if (status == WALK_LEFT)
					{
						p_bullet->LoadImg("map1/lazer_ngang.png", screen);
						p_bullet->set_bullet_dir(BulletObject::DIR_LEFT);
						p_bullet->SetRect(this->rect.x, this->rect.y + height_frame * 0.5);
						//set tam ban cho vien dan ( tầm bắn của súng này là 10 ô )
						p_bullet->set_lim_dis(this->rect.x - 45 * 10);
					}
					else if (status == WALK_RIGHT)
					{
						p_bullet->LoadImg("map1/lazer_ngang.png", screen);
						p_bullet->set_bullet_dir(BulletObject::DIR_RIGHT);
						p_bullet->SetRect(this->rect.x + width_frame - 10, this->rect.y + height_frame * 0.5);
						//set tam ban cho vien dan
						p_bullet->set_lim_dis(this->rect.x + width_frame + 45 * 10);
					}
					else if (status == WALK_UP)
					{
						p_bullet->LoadImg("map1/lazer_doc.png", screen);
						p_bullet->set_bullet_dir(BulletObject::DIR_UP);
						p_bullet->SetRect(this->rect.x + 10, this->rect.y);

						p_bullet->set_lim_dis(this->rect.y - 45 * 10);
					}
					else if (status == WALK_DOWN)
					{
						p_bullet->LoadImg("map1/lazer_doc.png", screen);
						p_bullet->set_bullet_dir(BulletObject::DIR_DOWN);
						p_bullet->SetRect(this->rect.x + 10, this->rect.y + height_frame);

						p_bullet->set_lim_dis(this->rect.y + height_frame + 45 * 10);
					}

					p_bullet->set_x_val(17);   // set tốc độ cho viên đạn
					p_bullet->set_y_val(17);
					p_bullet->set_is_move(true);

					Delay_bullet_dien.start();
					bullet_list.push_back(p_bullet);
					Mix_PlayChannel(-1, bullet_sound[2], 0);
				}
			}
		}
		}


	for (int i = 0; i < bullet_list_bom.size(); i++) 
	{
		BulletObject* p_bullet = bullet_list_bom.at(i);
		int map_x; int map_y;
		map_x = (p_bullet->GetRect().x - 185) / 45;
		map_y = (p_bullet->GetRect().y - 15) / 45;
			/// 
		int x = (floor((this->x_pos - 185) / 45));
		int y = (floor((this->y_pos - 15) / 45));
		if (!(x == map_x && y == map_y)) {             // để cho sau khi đặt bom ( bom và người trùng 1 ô) thì người vẫn có thể di chuyển trong ô đó
			map_data.tile[map_y][map_x] = 8;			// đến khi nào người ra hẳn ngoài thì mới set cho ô có bom thành ô không đi được 
		}
	}
	for (int i = 0; i < bullet_list_min.size(); i++) {
		BulletObject* p_bullet = bullet_list_min.at(i);
		int map_x; int map_y;
		map_x = (p_bullet->GetRect().x - 185) / 45;
		map_y = (p_bullet->GetRect().y - 15) / 45;
		/// 
		int x = (floor((this->x_pos - 185) / 45));
		int y = (floor((this->y_pos - 15) / 45));
		if (!(x == map_x && y == map_y)) {             // để cho sau khi đặt min ( min và người trùng 1 ô) thì người vẫn có thể di chuyển trong ô đó mà không bị nổ
			map_data.tile[map_y][map_x] = 20;			// đến khi nào người ra hẳn ngoài thì mới set cho ô có mìn và khi đi vào thì bị nổ 
		}
	}
}

//------------------------------------------------------------------------------------------------
// xử lý hình ảnh đạn
void MainObject::HandleBullet_Dan(SDL_Renderer* des)
{
	for (int i = 0; i < bullet_list.size(); i++)
	{
		BulletObject* p_bullet = bullet_list.at(i);
		if (p_bullet != NULL)
		{
			if (p_bullet->get_is_move() == true)
			{
				p_bullet->HandleMove_Dan(855, 640);
				p_bullet->Render(des);
			}  
			else        // tức là khi is_move = false thì viên đạn được xóa đi
			{
				bullet_list.erase(bullet_list.begin() + i);
				if (p_bullet != NULL)
				{
					delete p_bullet;
					p_bullet = NULL;
				}

			}
		}
	}
}

// xử lý hình ảnh tên lửa 
void MainObject::HandleBullet_TenLua(SDL_Renderer* des, Map&map_data)
{
	for (int i = 0; i < bullet_list_tenlua.size(); i++)
	{
		BulletObject* p_bullet = bullet_list_tenlua.at(i);
		if (p_bullet != NULL)
		{
			if (p_bullet->get_is_move() == true)
			{
				p_bullet->HandleMove_TenLua(855, 660);
				p_bullet->Render(des);
			}
			else        // tức là khi is_move = false thì viên đạn được xóa đi
			{
				bullet_list_tenlua.erase(bullet_list_tenlua.begin() + i);
				if (p_bullet != NULL)
				{
					delete p_bullet;
					p_bullet = NULL;
				}

			}
		}
	}
}

// xử lý hình ảnh lửa
void MainObject::HandleBullet_Lua(SDL_Renderer* des)
{
	for (int i = 0; i < bullet_list_lua.size(); i++)
	{
		BulletObject* p_bullet = bullet_list_lua.at(i);
		if (p_bullet != NULL)
		{
			if (p_bullet->get_is_move() == true)
			{
				p_bullet->Render(des);
			}
			else        // tức là khi is_move = false thì viên đạn được xóa đi
			{
				bullet_list_lua.erase(bullet_list_lua.begin() + i);
				if (p_bullet != NULL)
				{
					delete p_bullet;
					p_bullet = NULL;
				}

			}
		}
	}
}

// xử lý hình ảnh bom & mìn 
void MainObject::HandleBullet(SDL_Renderer* des)
{	// Render ảnh quả bom nếu có trong list 
	for (int i = 0; i < bullet_list_bom.size(); i++)
	{
		BulletObject* p_bullet = bullet_list_bom.at(i);
		if (p_bullet != NULL)
		{
			if (p_bullet->get_is_move() == true)
			{
				p_bullet->Render(des);
			}
			else        // tức là khi is_move = false thì viên đạn được xóa đi
			{
				bullet_list_bom.erase(bullet_list_bom.begin() + i);
				if (p_bullet != NULL)
				{
					delete p_bullet;
					p_bullet = NULL;
				}

			}
		}
		
	}

	// Render ảnh mìn nếu có trong list 

	for (int i = 0; i < bullet_list_min.size(); i++)
	{
		BulletObject* p_bullet = bullet_list_min.at(i);
		if (p_bullet != NULL)
		{
			if (p_bullet->get_is_move() == true)
			{
				p_bullet->Render(des);
			}
			else        // tức là khi is_move = false thì viên đạn được xóa đi
			{
				bullet_list_min.erase(bullet_list_min.begin() + i);
				if (p_bullet != NULL)
				{
					//delete p_bullet;
					p_bullet = NULL;
				}

			}
		}
		
	}

}

//-------------------------------------------------------------------------------------------------------
int MainObject :: Rand(int l, int r)
{
	return l + rand() % (r - l + 1);
}

// hàm sinh map ngẫu nhiên kết hợp với thuật toán DFS ở main.cpp
void MainObject::Rand2(int l , int r, Map&map_data)
{
	for (int i = 1; i <= 13; i++)
	{
		for (int j = 0; j <= 14; j++)
		{
			int x = l + rand() % (r - l + 1);
			if (x == 2)	map_data.tile[i][j] = 4 + rand() % 3;           // để tăng xác suất của ô 4 , 5, 6
			else if (x == 1) map_data.tile[i][j] = 0;     //  để tăng xác suất xuất hiện của ô 0 
			else map_data.tile[i][j] = x;
		}
	}
	map_data.tile[1][0] = 0;
	map_data.tile[1][1] = 0;
	map_data.tile[2][0] = 0;
	map_data.tile[1][13] = 0;
	map_data.tile[1][14] = 0;
	map_data.tile[2][14] = 0;
	
	map_data.tile[13][0] = 0;
	map_data.tile[13][1] = 0;
	map_data.tile[12][0] = 0;
	
	map_data.tile[13][14] = 0;
	map_data.tile[13][13] = 0;
	map_data.tile[12][14] = 0;
}

//----------------------------------------------------------------------------------------------------------
void MainObject::RemoveBullet_Bom(Map& map_data, SDL_Renderer* des, Mix_Chunk* sound[2]) {
		for (int i = 0; i < bullet_list_bom.size(); i++) {
			BulletObject* p_bullet = bullet_list_bom.at(i);
			if (SDL_GetTicks() - p_bullet->get_bullet_time() >= 2000)
			{
				bullet_list_bom.erase(bullet_list_bom.begin() + i);

				int map_x; int map_y;
				map_x = (p_bullet->GetRect().x - 185) / 45;
				map_y = (p_bullet->GetRect().y - 15) / 45;
				/// 
				if (map_data.tile[map_y][map_x] == 8 || map_data.tile[map_y][map_x] == 0)
				{
					for (int k = 0; k < 4; k++)
					{
						if (map_x + dx[k] >= 0 && map_y + dy[k] > 0 && map_y + dy[k] < 14 && map_x + dx[k] <= 14)
						{
							if (!(map_data.tile[map_y + dy[k]][map_x + dx[k]] == 7 || map_data.tile[map_y + dy[k]][map_x + dx[k]] == 3))
							{
								if (map_data.tile[map_y + dy[k]][map_x + dx[k]] == 4 || map_data.tile[map_y + dy[k]][map_x + dx[k]] == 5 || map_data.tile[map_y + dy[k]][map_x + dx[k]] == 6)
								{
									map_data.tile[map_y + dy[k]][map_x + dx[k]] = Rand(9, 15);
								}
							}
						}
					}
					map_data.tile[map_y][map_x] = 0;
				}


				// xu ly no bom

				nobom.push_back({ p_bullet->get_nobom_doc(),p_bullet->get_nobom_ngang() });

				(*nobom.rbegin()).first.LoadImg("map1/nobom_doc.png", des);
				(*nobom.rbegin()).second.LoadImg("map1/nobom_ngang.png", des);

				(*nobom.rbegin()).first.SetRect(p_bullet->GetRect().x, p_bullet->GetRect().y - 45 - 2);
				(*nobom.rbegin()).second.SetRect(p_bullet->GetRect().x - 45 - 2, p_bullet->GetRect().y);

				ImpTimer ret; Delay_time_bom.push_back(ret);
				(*Delay_time_bom.rbegin()).start();

				if (p_bullet != NULL)
				{
					delete p_bullet;
					p_bullet = NULL;
				}

			}
		}
		for (int i = 0; i < nobom.size(); i++)
		{
			if (Delay_time_bom[i].get_ticks() <= 350)
			{
				nobom[i].first.Render(des);
				nobom[i].second.Render(des);
			}
			else
			{

				nobom[i].first.Free();
				nobom[i].second.Free();

				nobom.erase(nobom.begin() + i);
				Delay_time_bom.erase(Delay_time_bom.begin() + i);
			}
		}

		// cho đoạn xử lý này của mìn vào đây để nó được gọi liên tục để trong vòng while ở main
		for (int i = 0; i < nomin.size(); i++)
		{
			if (Delay_time_min[i].get_ticks() <= 350)
			{
				Mix_PlayChannel(-1, sound[0], 0);
				nomin[i].first.Render(des);
				nomin[i].second.Render(des);
			}
			else
			{

				nomin[i].first.Free();
				nomin[i].second.Free();

				nomin.erase(nomin.begin() + i);
				Delay_time_min.erase(Delay_time_min.begin() + i);
			}
		}

		// xử lý hiệu ứng nổ tên lửa
		//// cho đoạn xử lý này của mìn vào đây để nó được gọi liên tục để trong vòng while ở main

		for (int i = 0; i < no_tenlua.size(); i++)
		{
			if (Delay_time_tenlua[i].get_ticks() <= 350)
			{
				no_tenlua[i].first.Render(des);
				no_tenlua[i].second.Render(des);
			}
			else
			{

				no_tenlua[i].first.Free();
				no_tenlua[i].second.Free();

				no_tenlua.erase(no_tenlua.begin() + i);
				Delay_time_tenlua.erase(Delay_time_tenlua.begin() + i);
			}
		}
		
}

void MainObject::RemoveBullet_Lua(Map& map_data, SDL_Renderer* des)
{
	for (int i = 0; i < bullet_list_lua.size(); i++)
	{
		BulletObject* p_bullet = bullet_list_lua.at(i);
		if (p_bullet != NULL)
		{
			if (SDL_GetTicks() - p_bullet->get_bullet_time() >= 250)
			{
				if (p_bullet->get_bullet_dir() == BulletObject::DIR_RIGHT)
				{
					p_bullet->set_is_move(false);
					num_sung_lua--;
					if (num_sung_lua == 0)
					{
						max_bom = 1;
						type_bullet = 15;
					}
					SDL_Rect rect_bullet = p_bullet->GetRect();
					int map_x, map_y;
					map_x = (rect_bullet.x - 185) / 45 + 1;
					map_y = (rect_bullet.y - 60) / 45 + 1;
					SDL_Rect tile_map;
					tile_map.x = 185 + map_x * 45;
					tile_map.y = 60 + (map_y - 1) * 45;
					tile_map.w = 45;
					tile_map.h = 45;
					bool Col = SDLCommonFunc::CheckCollision(rect_bullet, tile_map);
					if (Col && (map_data.tile[map_y][map_x] == 4 || map_data.tile[map_y][map_x] == 5 || map_data.tile[map_y][map_x] == 6))
					{
						map_data.tile[map_y][map_x] = Rand(9, 15);
						
					}


				}
				else if (p_bullet->get_bullet_dir() == BulletObject::DIR_LEFT)
				{
					p_bullet->set_is_move(false);
					num_sung_lua--;
					if (num_sung_lua == 0)
					{
						max_bom = 1;
						type_bullet = 15;
					}
					SDL_Rect rect_bullet = p_bullet->GetRect();
					int map_x, map_y;

					map_x = (rect_bullet.x - 185 ) / 45;
					map_y = (rect_bullet.y - 60) / 45 + 1;

					SDL_Rect tile_map;
					tile_map.x = 185 + map_x * 45;
					tile_map.y = 60 + (map_y - 1) * 45;
					tile_map.w = 45;
					tile_map.h = 45;
					bool Col = SDLCommonFunc::CheckCollision(rect_bullet, tile_map);       
					if (Col && (map_data.tile[map_y][map_x] == 4 || map_data.tile[map_y][map_x] == 5 || map_data.tile[map_y][map_x] == 6))
					{
						map_data.tile[map_y][map_x] = Rand(9, 15);
					}

				}
				else if (p_bullet->get_bullet_dir() == BulletObject::DIR_DOWN)
				{
					p_bullet->set_is_move(false);
					num_sung_lua--;
					if (num_sung_lua == 0)
					{
						max_bom = 1;
						type_bullet = 15;
					}
					SDL_Rect rect_bullet = p_bullet->GetRect();
					int map_x, map_y;

					map_x = (rect_bullet.x - 185) / 45 ;
					map_y = (rect_bullet.y - 60) / 45 + 2;    // vì x_pos + height_frame bao h cũng không ở mép ô

					SDL_Rect tile_map;
					tile_map.x = 185 + map_x * 45;
					tile_map.y = 60 + (map_y - 1) * 45;
					tile_map.w = 45;
					tile_map.h = 45;
					bool Col = SDLCommonFunc::CheckCollision(rect_bullet, tile_map);
					if (Col && (map_data.tile[map_y][map_x] == 4 || map_data.tile[map_y][map_x] == 5 || map_data.tile[map_y][map_x] == 6))
					{
						map_data.tile[map_y][map_x] = Rand(9, 15);
					}
					
				}
				else if (p_bullet->get_bullet_dir() == BulletObject::DIR_UP)
				{
					p_bullet->set_is_move(false);
					num_sung_lua--;
					if (num_sung_lua == 0)
					{
						max_bom = 1;
						type_bullet = 15;
					}
					SDL_Rect rect_bullet = p_bullet->GetRect();
					int map_x, map_y;

					map_x = (rect_bullet.x - 185) / 45;
					map_y = (rect_bullet.y - 60) / 45 + 1;

					SDL_Rect tile_map;
					tile_map.x = 185 + map_x * 45;
					tile_map.y = 60 + (map_y - 1) * 45;
					tile_map.w = 45;
					tile_map.h = 45;
					bool Col = SDLCommonFunc::CheckCollision(rect_bullet, tile_map);
					if (Col && (map_data.tile[map_y][map_x] == 4 || map_data.tile[map_y][map_x] == 5 || map_data.tile[map_y][map_x] == 6))
					{
						map_data.tile[map_y][map_x] = Rand(9, 15);
					}

				}
			}
		}
	}
}

void MainObject::RemoveBullet_Tenlua(Map& map_data, SDL_Renderer*des , BulletObject * p_bullet , int map_y , int map_x , Mix_Chunk* sound[4])
{
	if (p_bullet->get_bullet_dir() == BulletObject::DIR_RIGHT)
	{
		for (int k = 0; k < 4; k++)
		{
			if (map_x + dx[k] - 1 >= 0 && map_y + dy[k] > 0 && map_y + dy[k] < 14 && map_x + dx[k] - 1 <= 14)
			{
				if (!(map_data.tile[map_y + dy[k]][map_x + dx[k] - 1] == 7 || map_data.tile[map_y + dy[k]][map_x + dx[k] - 1] == 3))
				{
					if (map_data.tile[map_y + dy[k]][map_x + dx[k] - 1] == 4 || map_data.tile[map_y + dy[k]][map_x + dx[k] - 1] == 5 || map_data.tile[map_y + dy[k]][map_x + dx[k] - 1] == 6)
					{
						map_data.tile[map_y + dy[k]][map_x + dx[k] - 1] = Rand(9, 15);
					}
				}
			}
		}
		Mix_FreeChunk(sound[1]);

		sound[1] = Mix_LoadWAV("Explosion+5.wav");
		Mix_PlayChannel(-1, sound[1], 0);
		no_tenlua.push_back({ p_bullet->get_nobom_doc(),p_bullet->get_nobom_ngang() });
		(*no_tenlua.rbegin()).first.LoadImg("map1/nobom_doc.png", des);
		(*no_tenlua.rbegin()).second.LoadImg("map1/nobom_ngang.png", des);

		(*no_tenlua.rbegin()).first.SetRect(185 + (map_x - 1)*45 + 2, 60 + (map_y - 2)* 45 );
		(*no_tenlua.rbegin()).second.SetRect(185 + (map_x - 2)* 45 , 60 + (map_y - 1)*45 + 2 );

		ImpTimer ret; Delay_time_tenlua.push_back(ret);
		(*Delay_time_tenlua.rbegin()).start();
	}
	else if (p_bullet->get_bullet_dir() == BulletObject::DIR_LEFT)
	{
		for (int k = 0; k < 4; k++)
		{
			if (map_x + dx[k] + 1 >= 0 && map_y + dy[k] > 0 && map_y + dy[k] < 14 && map_x + dx[k] + 1 <= 14)
			{
				if (!(map_data.tile[map_y + dy[k]][map_x + dx[k] + 1] == 7 || map_data.tile[map_y + dy[k]][map_x + dx[k] + 1] == 3))
				{
					if (map_data.tile[map_y + dy[k]][map_x + dx[k] + 1] == 4 || map_data.tile[map_y + dy[k]][map_x + dx[k] + 1] == 5 || map_data.tile[map_y + dy[k]][map_x + dx[k] + 1] == 6)
					{
						map_data.tile[map_y + dy[k]][map_x + dx[k] + 1] = Rand(9, 15);
					}
				}
			}
		}

		Mix_FreeChunk(sound[1]);
		sound[1] = Mix_LoadWAV("Explosion+5.wav");
		Mix_PlayChannel(-1, sound[1], 0);
		no_tenlua.push_back({ p_bullet->get_nobom_doc(),p_bullet->get_nobom_ngang() });
		(*no_tenlua.rbegin()).first.LoadImg("map1/nobom_doc.png", des);
		(*no_tenlua.rbegin()).second.LoadImg("map1/nobom_ngang.png", des);

		(*no_tenlua.rbegin()).first.SetRect(185 + (map_x + 1) * 45 + 2, 60 + (map_y - 2) * 45);
		(*no_tenlua.rbegin()).second.SetRect(185 + (map_x) * 45, 60 + (map_y - 1) * 45 + 2);

		ImpTimer ret; Delay_time_tenlua.push_back(ret);
		(*Delay_time_tenlua.rbegin()).start();
	}
	else if (p_bullet->get_bullet_dir() == BulletObject::DIR_UP)
	{
		for (int k = 0; k < 4; k++)
		{
			if (map_x + dx[k] >= 0 && map_y + dy[k] + 1 > 0 && map_y + dy[k] + 1 < 14 && map_x + dx[k] <= 14)
			{
				if (!(map_data.tile[map_y + dy[k] + 1][map_x + dx[k]] == 7 || map_data.tile[map_y + dy[k] + 1][map_x + dx[k]] == 3))
				{
					if (map_data.tile[map_y + dy[k] + 1][map_x + dx[k]] == 4 || map_data.tile[map_y + dy[k] + 1][map_x + dx[k] ] == 5 || map_data.tile[map_y + dy[k] + 1][map_x + dx[k]] == 6)
					{
						map_data.tile[map_y + dy[k] + 1][map_x + dx[k]] = Rand(9, 15);
					}
				}
			}
		}
		Mix_FreeChunk(sound[1]);
		sound[1] = Mix_LoadWAV("Explosion+5.wav");
		Mix_PlayChannel(-1, sound[1], 0);
		no_tenlua.push_back({ p_bullet->get_nobom_doc(),p_bullet->get_nobom_ngang() });
		(*no_tenlua.rbegin()).first.LoadImg("map1/nobom_doc.png", des);
		(*no_tenlua.rbegin()).second.LoadImg("map1/nobom_ngang.png", des);

		(*no_tenlua.rbegin()).first.SetRect(185 + (map_x) * 45 + 2, 60 + (map_y - 1) * 45);
		(*no_tenlua.rbegin()).second.SetRect(185 + (map_x - 1) * 45 , 60 + (map_y) * 45 + 2);

		ImpTimer ret; Delay_time_tenlua.push_back(ret);
		(*Delay_time_tenlua.rbegin()).start();
	}
	else if (p_bullet->get_bullet_dir() == BulletObject::DIR_DOWN)
	{
		for (int k = 0; k < 4; k++)
		{
			if (map_x + dx[k] >= 0 && map_y + dy[k] - 1 > 0 && map_y + dy[k] - 1 < 14 && map_x + dx[k] <= 14)
			{
				if (!(map_data.tile[map_y + dy[k] - 1][map_x + dx[k]] == 7 || map_data.tile[map_y + dy[k] - 1][map_x + dx[k]] == 3))
				{
					if (map_data.tile[map_y + dy[k] - 1][map_x + dx[k]] == 4 || map_data.tile[map_y + dy[k] - 1][map_x + dx[k]] == 5 || map_data.tile[map_y + dy[k] - 1][map_x + dx[k]] == 6)
					{
						map_data.tile[map_y + dy[k] - 1][map_x + dx[k]] = Rand(9, 15);
					}
				}
			}
		}
		Mix_FreeChunk(sound[1]);
		sound[1] = Mix_LoadWAV("Explosion+5.wav");
		Mix_PlayChannel(-1, sound[1], 0);
		no_tenlua.push_back({ p_bullet->get_nobom_doc(),p_bullet->get_nobom_ngang() });
		(*no_tenlua.rbegin()).first.LoadImg("map1/nobom_doc.png", des);
		(*no_tenlua.rbegin()).second.LoadImg("map1/nobom_ngang.png", des);

		(*no_tenlua.rbegin()).first.SetRect(185 + (map_x) * 45 + 2, 60 + (map_y - 3) * 45);
		(*no_tenlua.rbegin()).second.SetRect(185 + (map_x - 1) * 45, 60 + (map_y - 2) * 45 + 2);

		ImpTimer ret; Delay_time_tenlua.push_back(ret);
		(*Delay_time_tenlua.rbegin()).start();
	}
}

//--------------------------------------------------------------------------------------------------------------------------------
// hàm này gọi khi có va chạm giữa nhân vật và đạn 
void MainObject::check_around_MainObject(Map& map_data, SDL_Renderer* des, BulletObject* p_bullet, double x_pos, double y_pos)
{
	int map_x = (x_pos - 185) / 45;
	int map_y = (y_pos - 60) / 45 + 1;

	for (int k = 0; k < 4; k++)
	{
		if (map_x + dx[k] >= 0 && map_y + dy[k] > 0 && map_y + dy[k] < 14 && map_x + dx[k] <= 14)
		{
			if (map_data.tile[map_y + dy[k]][map_x + dx[k]] == 4 || map_data.tile[map_y + dy[k]][map_x + dx[k]] == 5 || map_data.tile[map_y + dy[k]][map_x + dx[k]] == 6)
			{
				map_data.tile[map_y + dy[k]][map_x + dx[k]] = Rand(9, 15);
			}
		}
	}

	no_tenlua.push_back({ p_bullet->get_nobom_doc(),p_bullet->get_nobom_ngang() });
	(*no_tenlua.rbegin()).first.LoadImg("map1/nobom_doc.png", des);
	(*no_tenlua.rbegin()).second.LoadImg("map1/nobom_ngang.png", des);

	(*no_tenlua.rbegin()).first.SetRect(185 + (map_x) * 45 + 2, 60 + (map_y - 2) * 45);
	(*no_tenlua.rbegin()).second.SetRect(185 + (map_x - 1) * 45, 60 + (map_y - 1) * 45 + 2);

	ImpTimer ret; Delay_time_tenlua.push_back(ret);
	(*Delay_time_tenlua.rbegin()).start();
}

//--------------------------------------------------------------------------------------------------------------------------
// check va chạm giữa tên lửa vs ô chứa vật phẩm
void MainObject::check_col_tenlua(Map& map_data, SDL_Renderer*des, Mix_Chunk* sound[4])
{
	for (int i = 0; i < bullet_list_tenlua.size(); i++)
	{
		BulletObject* p_bullet = bullet_list_tenlua.at(i);
		if (p_bullet != NULL)
		{
			SDL_Rect rect_bullet = p_bullet->GetRect();
			int map_x, map_y;
			map_x = (rect_bullet.x - 185) / 45;
			map_y = (rect_bullet.y - 60) / 45 + 1;
			SDL_Rect tile_map;
			tile_map.x = 185 + (map_x) * 45;
			tile_map.y = 60 + (map_y - 1) * 45;
			tile_map.w = 45;
			tile_map.h = 45;
			
			if (p_bullet->get_bullet_dir() == BulletObject::DIR_LEFT)
			{
				map_x = (rect_bullet.x - 185 + 10) / 45 ;       // +10 vì ở main, hàm Handle được gọi trước, khi đó rect.x sẽ được trừ đi 17 khiến cho lệch khỏi ô cần xét
																// do đó ta phải cộng lại 10 để lấy được rect.x của ô cần check va chạm
				tile_map.x = 185 + (map_x) * 45;
			}
			if (p_bullet->get_bullet_dir() == BulletObject::DIR_UP)
			{
				map_y = (rect_bullet.y - 60 + 10) / 45 + 1;        // + 10 cũng vì lý do trên 
				tile_map.y = 60 + (map_y - 1) * 45;
			}



			if (map_data.tile[map_y][map_x] <= 7 && map_data.tile[map_y][map_x] >= 1)
			{
				bool Col = SDLCommonFunc::CheckCollision(rect_bullet , tile_map);
				if (Col && (map_data.tile[map_y][map_x] == 2 || map_data.tile[map_y][map_x] == 3 || map_data.tile[map_y][map_x] == 7))
				{
					p_bullet->set_is_move(false);
					num_ten_lua--;
					if (num_ten_lua == 0)
					{
						max_bom = 1;
						type_bullet = 15;
					}
					RemoveBullet_Tenlua(map_data, des, p_bullet, map_y, map_x,sound);
				}
				else if (Col && !(map_data.tile[map_y][map_x] == 2 || map_data.tile[map_y][map_x] == 3 || map_data.tile[map_y][map_x] == 7))
				{
					RemoveBullet_Tenlua(map_data, des, p_bullet, map_y, map_x,sound);
					p_bullet->set_is_move(false);
					num_ten_lua--;
					if (num_ten_lua == 0)
					{
						max_bom = 1;
						type_bullet = 15;
					}
				}
				

			}
			else if (p_bullet->GetRect().x > 185 + 45 * 15 - 20)      // là khi vượt ra khỏi map 
			{
				RemoveBullet_Tenlua(map_data, des, p_bullet, map_y, map_x + 1,sound);
				p_bullet->set_is_move(false);
				num_ten_lua--;
				if (num_ten_lua == 0)
				{
					max_bom = 1;
					type_bullet = 15;
				}
			}
			else if (p_bullet->GetRect().x < 185 + 5 )            // là khi vượt ra khỏi map
			{
				RemoveBullet_Tenlua(map_data, des, p_bullet, map_y, map_x - 1,sound);
				p_bullet->set_is_move(false);
				num_ten_lua--;
				if (num_ten_lua == 0)
				{
					max_bom = 1;
					type_bullet = 15;
				}
			}

			//--------------------------------------------------------------
			else if (p_bullet->GetRect().y < 60 + 5)
			{
				RemoveBullet_Tenlua(map_data, des, p_bullet, map_y - 1, map_x, sound);
				p_bullet->set_is_move(false);
				num_ten_lua--;
				if (num_ten_lua == 0)
				{
					max_bom = 1;
					type_bullet = 15;
				}
			}
			else if (p_bullet->GetRect().y > 60 + 45*13 - 20)
			{
				RemoveBullet_Tenlua(map_data, des, p_bullet, map_y + 1, map_x, sound);
				p_bullet->set_is_move(false);
				num_ten_lua--;
				if (num_ten_lua == 0)
				{
					max_bom = 1;
					type_bullet = 15;
				}
			}
		}
	
	}

}

//  check va chạm giữa viên đạn và các ô 
void MainObject::check_col_sungdan(Map& map_data)
{
	for (int i = 0; i < bullet_list.size(); i++)
	{
		BulletObject* p_bullet = bullet_list.at(i);
		if (type_bullet == BulletObject::SUNG_DAN)
		{
			num_sung_dan--;
			if (num_sung_dan == 0)
			{
				max_bom = 1;
				type_bullet = 15;
			}
		}

		if (type_bullet == BulletObject::SUNG_DIEN)
		{
			num_sung_dien--;
			if (num_sung_dien == 0)
			{
				max_bom = 1;
				type_bullet = 15;
			}
		}
		if (p_bullet != NULL)
		{
			SDL_Rect rect_bullet = p_bullet->GetRect();
			int map_x, map_y; 
			map_x = (rect_bullet.x - 185) / 45;
			map_y = (rect_bullet.y - 60) / 45 + 1;
			SDL_Rect tile_map;
			tile_map.x = 185 + (map_x) * 45;
			tile_map.y = 60 + (map_y - 1) * 45;
			tile_map.w = 45;
			tile_map.h = 45;
			if (map_data.tile[map_y][map_x] <= 7 && map_data.tile[map_y][map_x] >= 1)
			{
				bool Col = SDLCommonFunc::CheckCollision(rect_bullet, tile_map);
				if (Col && (map_data.tile[map_y][map_x] == 2 || map_data.tile[map_y][map_x] == 3 || map_data.tile[map_y][map_x] == 7))
				{
					
					p_bullet->set_is_move(false);
					
					
				}
				else if (Col && !(map_data.tile[map_y][map_x] == 2 || map_data.tile[map_y][map_x] == 3 || map_data.tile[map_y][map_x] == 7))
				{
					map_data.tile[map_y][map_x] = Rand(9, 15);
					
					p_bullet->set_is_move(false);
					
					
				}
			}
		}
	}
}

//------------------------------------------------------------------------------

void MainObject::RemoveBullet_Col(const int& idx)
{
	int size = bullet_list.size();
	if (size > 0 && idx < size)
	{
		BulletObject* p_bullet = bullet_list.at(idx);
		num_sung_dan--;
		if (num_sung_dan == 0)
		{
			max_bom = 1;
			type_bullet = 15;
		}
		bullet_list.erase(bullet_list.begin() + idx);
		if (p_bullet)
		{
			delete p_bullet;
			p_bullet = NULL;
		}
	}
}
void MainObject::RemoveTenLua_Col(const int& idx)
{
	int size = bullet_list_tenlua.size();
	if (size > 0 && idx < size)
	{
		BulletObject* p_bullet = bullet_list_tenlua.at(idx);

		bullet_list_tenlua.erase(bullet_list_tenlua.begin() + idx);
		num_ten_lua--;
		if (num_ten_lua == 0)
		{
			max_bom = 1;
			type_bullet = 15;
		}
		if (p_bullet)
		{
			delete p_bullet;
			p_bullet = NULL;
		}
	}
}

//---------------------------------------------------------------------------------------
void MainObject::check_item_lachan(int val_1, int val_2)
{
	if ((val_1 == 13 && val_2 == 13) || (val_1 == 13 && val_2 >= 9 && val_1 != val_2 && val_2 <= 15) || (val_1 == 13 && val_2 == 0) || (val_1 == 0 && val_2 == 13))
	{
		// chú ý : ở điều kiện 2, cần có val_2 <= 15 để tránh trường hợp ô val_2 là mìn
		// vì nếu là mìn thì chỉ cần đi giữa 2 ô ( tức là chạm vào mìn ) là sẽ nổ 
		this->set_bat_tu(true);          // mặc định game: nếu 2 ô trên và dưới cùng là item thì ta chọn item trên để set cho nhân vật
		have_lachan = 1;
	}
}
void MainObject::check_item_bom(int val_1, int val_2)
{
	if ((val_1 == 15 && val_2 == 15) || (val_1 == 15 && val_2 >= 9 && val_1 != val_2 && val_2 <= 15) || (val_1 == 15 && val_2 == 0) || (val_1 == 0 && val_2 == 15))    // và phải xử lý sao cho khi ấn space nó ra bom
	{
		type_bullet = 15;
		max_bom++;
		num_sung_dan = 0;
		num_sung_lua = 0;
		num_ten_lua = 0;
		num_min = 0;
		num_sung_dien = 0;
	}
}
void MainObject::check_item_min(int val_1, int val_2)
{
	if ((val_1 == 11 && val_2 == 11) || (val_1 == 11 && val_2 >= 9 && val_1 != val_2 && val_2 <= 15) || (val_1 == 11 && val_2 == 0) || (val_1 == 0 && val_2 == 11))
	{
		num_min = 1;
		type_bullet = 11;
		max_bom = 0;
		num_sung_dan = 0;
		num_sung_lua = 0;
		num_ten_lua = 0;
		num_sung_dien = 0;
	}
}
void MainObject::check_item_sungdan(int val_1, int val_2)
{
	if ((val_1 == 10 && val_2 == 10) || (val_1 == 10 && val_2 >= 9 && val_1 != val_2 && val_2 <= 15) || (val_1 == 10 && val_2 == 0) || (val_1 == 0 && val_2 == 10))
	{
		num_sung_dan = 1;
		type_bullet = 10;
		max_bom = 0;
		num_min = 0;
		num_sung_lua = 0;
		num_ten_lua = 0;
		num_sung_dien = 0;
	}
}
void MainObject::check_item_sunglua(int val_1, int val_2)
{
	if ((val_1 == 9 && val_2 == 9) || (val_1 == 9 && val_2 >= 9 && val_1 != val_2 && val_2 <= 15) || (val_1 == 9 && val_2 == 0) || (val_1 == 0 && val_2 == 9))
	{
		num_sung_lua = 2;
		num_sung_dan = 0;
		type_bullet = 9;
		max_bom = 0;
		num_min = 0;
		num_ten_lua = 0;
		num_sung_dien = 0;
	}
}
void MainObject::check_item_tenlua(int val_1, int val_2)
{
	if ((val_1 == 12 && val_2 == 12) || (val_1 == 12 && val_2 >= 9 && val_1 != val_2 && val_2 <= 15) || (val_1 == 12 && val_2 == 0) || (val_1 == 0 && val_2 == 12))
	{
		num_sung_lua = 0;
		num_sung_dan = 0;
		type_bullet = 12;
		max_bom = 0;
		num_min = 0;
		num_ten_lua = 1;
		num_sung_dien = 0;
	}

}
void MainObject::check_item_sungdien(int val_1, int val_2)
{
	if ((val_1 == 14 && val_2 == 14) || (val_1 == 14 && val_2 >= 9 && val_1 != val_2 && val_2 <= 15) || (val_1 == 14 && val_2 == 0) || (val_1 == 0 && val_2 == 14))
	{
		num_sung_lua = 0;
		num_sung_dan = 0;
		type_bullet = 14;
		max_bom = 0;
		num_min = 0;
		num_ten_lua = 0;
		num_sung_dien = 1;
	}

}

//-----------------------------------------------------------------------
void MainObject :: init_sunglua(SDL_Renderer* screen)
{
	sung_lua.LoadImg("map1/9_.png", screen);
	
}
void MainObject :: show_sunglua(SDL_Renderer* screen,double x, double y)

{	sung_lua.SetRect(x, y);
	sung_lua.Render(screen);
}

void MainObject::init_tenlua(SDL_Renderer* screen)
{
	ten_lua.LoadImg("map1/icon_ten_lua.png", screen);

}
void MainObject::show_tenlua(SDL_Renderer* screen, double x, double y)

{
	ten_lua.SetRect(x, y);
	ten_lua.Render(screen);
}

void MainObject::init_min_(SDL_Renderer* screen)
{
	min_.LoadImg("map1/min_icon.png", screen);

}
void MainObject::show_min_(SDL_Renderer* screen, double x, double y)

{
	min_.SetRect(x, y);
	min_.Render(screen);
}

void MainObject::init_sungdan(SDL_Renderer* screen)
{
	sung_dan.LoadImg("map1/10_.png", screen);

}
void MainObject::show_sungdan(SDL_Renderer* screen, double x, double y)

{
	sung_dan.SetRect(x, y);
	sung_dan.Render(screen);
}

void MainObject::init_sungdien(SDL_Renderer* screen)
{
	sung_dien.LoadImg("map1/sung_dien.png", screen);

}
void MainObject::show_sungdien(SDL_Renderer* screen, double x, double y)

{
	sung_dien.SetRect(x, y);
	sung_dien.Render(screen);
}

void MainObject::init_la_chan(SDL_Renderer* screen, double x, double y)
{
	lachan.LoadImg("map1/lachan.png", screen);
	lachan.SetRect(x, y);
}
void MainObject::show_la_chan(SDL_Renderer* screen)
{
	lachan.Render(screen);
}


//---------------------------------------------------------------
// xử lý va chạm và di chuyển 

void MainObject::DoPlayer(Map& map_data,SDL_Renderer*des) {
	x_val = 0;
	y_val = 0;
	if (input_type.left == 1) {
		x_val -= PLAYER_SPEED;
	}
	else if (input_type.right == 1) {
		x_val += PLAYER_SPEED;
	}
	if (input_type.down == 1) {
		y_val += PLAYER_SPEED;
	}
	else if (input_type.up == 1) {
		y_val -= PLAYER_SPEED;
	}
	CheckToMap(map_data,des);

}

void MainObject::CheckToMap(Map& map_data, SDL_Renderer* des) {
	int map_x1, map_x2, map_y1, map_y2;
	int val_1, val_2;
	map_x1 = (x_pos + x_val - 185) / TILE_SIZE;
	map_x2 = (x_pos + x_val + width_frame - 185 - 1) / TILE_SIZE;
	map_y1 = (y_pos - 15) / TILE_SIZE;
	map_y2 = (y_pos + height_frame - 15 - 1) / TILE_SIZE;
	if (map_x1 >= 0 && map_x2 < MAX_MAP_X && map_y1 >= 0 && map_y2 < MAX_MAP_Y)
	{
		if (x_val > 0) {
			// 15 la toa do y de set_rect cho cac o vuong dòng 0 
			val_1 = map_data.tile[map_y1][map_x2];
			val_2 = map_data.tile[map_y2][map_x2];
			check_item_lachan(val_1, val_2);
			check_item_bom(val_1, val_2);
			check_item_min(val_1, val_2);
			check_item_sungdan(val_1, val_2);
			check_item_sunglua(val_1, val_2);
			check_item_tenlua(val_1, val_2);
			check_item_sungdien(val_1, val_2);


			if (9 <= val_1 && 9 <= val_2 && val_1 <= 15 && val_2 <= 15)            // dấu && chứ không phải || ( vì nếu là || thì ví dụ ô [1][2] là ô item, ô [2][2] là ô không phải item
				// nếu ta đi giữa dòng 1 và dòng 2 thì cả 2 ô đều mất trong khi chỉ có ô [1][2] mới có thể mất đi 
			{
				map_data.tile[map_y1][map_x2] = 0;
				map_data.tile[map_y2][map_x2] = 0;
			}
			else if (val_1 >= 9 && val_2 == 0 && val_1 <= 15)
			{
				map_data.tile[map_y1][map_x2] = 0;
			}
			else if (val_1 == 0 && val_2 >= 9 && val_2 <= 15)
			{
				map_data.tile[map_y2][map_x2] = 0;
			}

			if (map_data.tile[map_y1][map_x2] != BLANK_TILE || map_data.tile[map_y2][map_x2] != BLANK_TILE) {
				x_pos = 185 + TILE_SIZE * (map_x2)-width_frame - 1;
				x_val = 0;
			}
		}
		else if (x_val < 0) {

			val_1 = map_data.tile[map_y1][map_x1];
			val_2 = map_data.tile[map_y2][map_x1];
			check_item_lachan(val_1, val_2);
			check_item_bom(val_1, val_2);
			check_item_min(val_1, val_2);
			check_item_sungdan(val_1, val_2);
			check_item_sunglua(val_1, val_2);
			check_item_tenlua(val_1, val_2);
			check_item_sungdien(val_1, val_2);
			if (9 <= val_1 && 9 <= val_2 && val_1 <= 15 && val_2 <= 15)
			{
				map_data.tile[map_y1][map_x1] = 0;
				map_data.tile[map_y2][map_x1] = 0;
			}
			else if (val_1 >= 9 && val_2 == 0 && val_1 <= 15)
			{
				map_data.tile[map_y1][map_x1] = 0;
			}
			else if (val_1 == 0 && val_2 >= 9 && val_2 <= 15)
			{
				map_data.tile[map_y2][map_x1] = 0;
			}

			if (map_data.tile[map_y1][map_x1] != BLANK_TILE || map_data.tile[map_y2][map_x1] != BLANK_TILE) {
				x_pos = 185 + (map_x1 + 1) * TILE_SIZE;
				x_val = 0;
			}
		}
	}
	map_x1 = (x_pos - 185) / TILE_SIZE;
	map_x2 = (x_pos + width_frame - 185 - 1) / TILE_SIZE;
	map_y1 = (y_pos + y_val - 15) / TILE_SIZE;
	map_y2 = (y_pos + y_val + height_frame - 15 - 1) / TILE_SIZE;
	if (map_x1 >= 0 && map_x2 < MAX_MAP_X && map_y1 >= 0 && map_y2 < MAX_MAP_Y) {
		if (y_val > 0)
		{
			val_1 = map_data.tile[map_y2][map_x1];
			val_2 = map_data.tile[map_y2][map_x2];
			check_item_lachan(val_1, val_2);
			check_item_bom(val_1, val_2);
			check_item_min(val_1, val_2);
			check_item_sungdan(val_1, val_2);
			check_item_sunglua(val_1, val_2);
			check_item_tenlua(val_1, val_2);
			check_item_sungdien(val_1, val_2);
			if (9 <= val_1 && 9 <= val_2 && val_1 <= 15 && val_2 <= 15)            // dấu && chứ không phải || ( vì nếu là || thì ví dụ ô [1][2] là ô item, ô [2][2] là ô không phải item
				// nếu ta đi giữa dòng 1 và dòng 2 thì cả 2 ô đều mất trong khi chỉ có ô [1][2] mới có thể mất đi 
			{
				map_data.tile[map_y2][map_x1] = 0;
				map_data.tile[map_y2][map_x2] = 0;
			}
			else if (val_1 >= 9 && val_2 == 0 && val_1 <= 15)
			{
				map_data.tile[map_y2][map_x1] = 0;
			}
			else if (val_1 == 0 && val_2 >= 9 && val_2 <= 15)
			{
				map_data.tile[map_y2][map_x2] = 0;
			}

			if (map_data.tile[map_y2][map_x1] != BLANK_TILE || map_data.tile[map_y2][map_x2] != BLANK_TILE) {
				y_pos = 15 + map_y2 * TILE_SIZE - height_frame - 1;
				y_val = 0;
			}
		}

		else if (y_val < 0)
		{
			val_1 = map_data.tile[map_y1][map_x1];
			val_2 = map_data.tile[map_y1][map_x2];
			check_item_lachan(val_1, val_2);
			check_item_bom(val_1, val_2);
			check_item_min(val_1, val_2);
			check_item_sungdan(val_1, val_2);
			check_item_sunglua(val_1, val_2);
			check_item_tenlua(val_1, val_2);
			check_item_sungdien(val_1, val_2);
			if (9 <= val_1 && 9 <= val_2 && val_1 <= 15 && val_2 <= 15)            // dấu && chứ không phải || ( vì nếu là || thì ví dụ ô [1][2] là ô item, ô [2][2] là ô không phải item
				// nếu ta đi giữa dòng 1 và dòng 2 thì cả 2 ô đều mất trong khi chỉ có ô [1][2] mới có thể mất đi 
			{
				map_data.tile[map_y1][map_x1] = 0;
				map_data.tile[map_y1][map_x2] = 0;
			}
			else if (val_1 >= 9 && val_2 == 0 && val_1 <= 15)
			{
				map_data.tile[map_y1][map_x1] = 0;
			}
			else if (val_1 == 0 && val_2 >= 9 && val_2 <= 15)
			{
				map_data.tile[map_y1][map_x2] = 0;
			}

			if (map_data.tile[map_y1][map_x1] != BLANK_TILE || map_data.tile[map_y1][map_x2] != BLANK_TILE)
			{
				y_pos = (map_y1 + 1) * TILE_SIZE + 15;
				y_val = 0;
			}
		}
	}

	x_pos += x_val;
	y_pos += y_val;
	if (x_pos < 185) {
		x_pos = 185;
	}
	else if (x_pos + width_frame > 185 + TILE_SIZE * (MAX_MAP_X)) {
		x_pos = 185 + TILE_SIZE * MAX_MAP_X - width_frame - 1;
	}

	//----------------------------
	if (num_sung_lua > 0)
	{
		show_sunglua(des, x_pos + 5, y_pos - 20);
	}

	if (num_ten_lua > 0)
	{
		show_tenlua(des, x_pos + 5, y_pos - 20);
	}

	if (num_min > 0)
	{
		show_min_(des, x_pos + 5, y_pos - 20);
	}

	if (num_sung_dan > 0)
	{
		show_sungdan(des, x_pos + 5, y_pos - 20);
	}
	if (num_sung_dien > 0)
	{
		show_sungdien(des, x_pos + 5, y_pos - 20);
	}
}

