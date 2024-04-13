#include "MainObject.h"
#include "ImpTimer.h"
std::vector< ImpTimer> Delay_time;

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
	max_bom = 1;
	bat_tu = false;
	num_life = 2;
	mark = 0; 
}
MainObject :: ~MainObject() {

}

void MainObject::set_pos2(float x, float y)
{
	x_pos = x;
	y_pos = y;
}
				

bool MainObject::LoadImg(std::string path, SDL_Renderer* screen) {
	bool ret = BaseObject::LoadImg(path, screen);
	if (ret == true) {
		width_frame = rect.w / 8;
		height_frame = rect.h;    // chu y : height_frame = 45 , width_frame = 40 ; 
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

	//
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

	//
	if (input_type.left == 1 || input_type.right == 1) {
		frame++;
	}
	else {
		frame = 0;
	}

	if (frame >= 8){
		frame = 0;
		}

	rect.x = x_pos;  // day la vi tri tren man hinh ma hien thi nhan vat len
		rect.y = y_pos;

		SDL_Rect* current_clip = &frame_clip[frame];

		SDL_Rect renderQuad = { rect.x ,rect.y , width_frame,height_frame };
		SDL_RenderCopy(des, p_object, current_clip, &renderQuad);
}



void MainObject::Show2(SDL_Renderer* des) {

	//
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

	//
	if (input_type.left == 1 || input_type.right == 1) {
		frame++;
	}
	else {
		frame = 0;
	}

	if (frame >= 8) {
		frame = 0;
	}

	rect.x = x_pos;  // day la vi tri tren man hinh ma hien thi nhan vat len
	rect.y = y_pos;

	SDL_Rect* current_clip = &frame_clip[frame];

	SDL_Rect renderQuad = { rect.x ,rect.y , width_frame,height_frame };
	SDL_RenderCopy(des, p_object, current_clip, &renderQuad);
}


void MainObject::HandleInputAction1(SDL_Event events, SDL_Renderer* screen, Map& map_data) {
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
	if (events.type == SDL_KEYDOWN)
	{
		if (events.key.keysym.sym == SDLK_SPACE)
		{

			if (bullet_list.size() < max_bom)
			{
				BulletObject* p_bullet = new BulletObject();

				// 
				if (status == WALK_LEFT) {

					p_bullet->SetRect(185 + floor((this->x_pos - 185) / 45) * 45 + 2, 60 + floor((this->y_pos - 60) / 45) * 45 + 2); // rect.x , rect.y la vi tri set anh cua nhan vat 

					p_bullet->LoadImg("map1/bom.png", screen);

				}

				else if (status == WALK_RIGHT)
				{

					p_bullet->SetRect(185 + floor((this->x_pos - 185) / 45) * 45 + 2, 60 + floor((this->y_pos - 60) / 45) * 45 + 2);
					p_bullet->LoadImg("map1/bom.png", screen);

				}
				else if (status == WALK_UP)
				{

					p_bullet->SetRect(185 + floor((this->x_pos - 185) / 45) * 45 + 2, 60 + floor((this->y_pos - 60) / 45) * 45 + 2);
					p_bullet->LoadImg("map1/bom.png", screen);

				}
				else if (status == WALK_DOWN)
				{
					p_bullet->SetRect(185 + floor((this->x_pos - 185) / 45) * 45 + 2, 60 + floor((this->y_pos - 60) / 45) * 45 + 2);
					p_bullet->LoadImg("map1/bom.png", screen);

				}

				p_bullet->set_is_move(true); // chuyển sang true tức là cho phép đạn bắn ra 
				// nhu vậy phần trên đã khởi tạo xong viên đạn 

				bullet_list.push_back(p_bullet); // nạp đạn sẵn vào băng, chỉ ấn là đạn sẽ xuất hiện
				p_bullet->set_bullet_time(SDL_GetTicks());
				
			}
		}
	}

	for (int i = 0; i < bullet_list.size(); i++) {
		BulletObject* p_bullet = bullet_list.at(i);
		int map_x; int map_y;
		map_x = (p_bullet->GetRect().x - 185) / 45;
		map_y = (p_bullet->GetRect().y - 15) / 45;
		/// 
		int x = ( floor( (this->x_pos - 185) / 45 ) );
		int y = ( floor( (this->y_pos - 15) / 45 ) );
		if ( ! (x == map_x && y == map_y) ) {             // để cho sau khi đặt bom ( bom và người trùng 1 ô) thì người vẫn có thể di chuyển trong ô đó
			map_data.tile[map_y][map_x] = 8;			// đến khi nào người ra hẳn ngoài thì mới set cho ô có bom thành ô không đi được 
		} 
	}	
	
}

void MainObject::HandleInputAction2(SDL_Event events, SDL_Renderer* screen, Map& map_data) {
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
	if (events.type == SDL_KEYDOWN)
	{
		if (events.key.keysym.sym == SDLK_KP_ENTER)
		{

			if (bullet_list.size() < max_bom)
			{
				BulletObject* p_bullet = new BulletObject();

				// 
				if (status == WALK_LEFT) {

					p_bullet->SetRect(185 + floor((this->x_pos - 185) / 45) * 45 + 2, 60 + floor((this->y_pos - 60) / 45) * 45 + 2); // rect.x , rect.y la vi tri set anh cua nhan vat 

					p_bullet->LoadImg("map1/bom.png", screen);

				}

				else if (status == WALK_RIGHT)
				{

					p_bullet->SetRect(185 + floor((this->x_pos - 185) / 45) * 45 + 2, 60 + floor((this->y_pos - 60) / 45) * 45 + 2);
					p_bullet->LoadImg("map1/bom.png", screen);

				}
				else if (status == WALK_UP)
				{

					p_bullet->SetRect(185 + floor((this->x_pos - 185) / 45) * 45 + 2, 60 + floor((this->y_pos - 60) / 45) * 45 + 2);
					p_bullet->LoadImg("map1/bom.png", screen);

				}
				else if (status == WALK_DOWN)
				{
					p_bullet->SetRect(185 + floor((this->x_pos - 185) / 45) * 45 + 2, 60 + floor((this->y_pos - 60) / 45) * 45 + 2);
					p_bullet->LoadImg("map1/bom.png", screen);

				}

				p_bullet->set_is_move(true); // chuyển sang true tức là cho phép đạn bắn ra 
				// nhu vậy phần trên đã khởi tạo xong viên đạn 

				bullet_list.push_back(p_bullet); // nạp đạn sẵn vào băng, chỉ ấn là đạn sẽ xuất hiện
				p_bullet->set_bullet_time(SDL_GetTicks());

			}
		}
	}

	for (int i = 0; i < bullet_list.size(); i++) {
		BulletObject* p_bullet = bullet_list.at(i);
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

}


// xử lý đạn 
void MainObject::HandleBullet(SDL_Renderer* des)
{
	for (int i = 0; i < bullet_list.size(); i++)
	{
		BulletObject* p_bullet = bullet_list.at(i);
		if (p_bullet != NULL)
		{
			if (p_bullet->get_is_move() == true)
			{
				p_bullet->Render(des);
			}
		}

	}
}


int dx[5] = { 0,1,-1,0,0 };
int dy[5] = { 0,0,0,-1,1 };


void MainObject::RemoveBullet(Map& map_data, SDL_Renderer* des ) {
	for (int i = 0; i < bullet_list.size(); i++) {
		BulletObject* p_bullet = bullet_list.at(i);
		if (SDL_GetTicks() - p_bullet->get_bullet_time() >= 3000)
		{
			bullet_list.erase(bullet_list.begin() + i);

			int map_x; int map_y;
			map_x = (p_bullet->GetRect().x - 185) / 45;
			map_y = (p_bullet->GetRect().y -  15) / 45 ;
			/// 
			int cnt = 0; // biến tính số ô bị phá hủy để suy ra điểm số nhân vật nhận được
			if (map_data.tile[map_y][map_x] == 8)  
			{
				for (int k = 0; k < 5; k++) 
				{
					if (map_x + dx[k] >= 0 && map_y + dy[k] > 0 && map_y + dy[k] < 14)
					{
						if (!(map_data.tile[map_y + dy[k]][map_x + dx[k]] == 7 || map_data.tile[map_y + dy[k]][map_x + dx[k]] == 3))
						{
							if (map_data.tile[map_y + dy[k]][map_x + dx[k]] == 4 || map_data.tile[map_y + dy[k]][map_x + dx[k]] == 5 || map_data.tile[map_y + dy[k]][map_x + dx[k]] == 6)
							{
								cnt++;
							}
							map_data.tile[map_y + dy[k]][map_x + dx[k]] = 0;
						}
					}
				}
			}

			else if(map_data.tile[map_y][map_x] == 0)    // là khi đặt bom xong vẫn không di chuyển, người và bom cùng 1 ô 
			{
				for (int k = 0; k < 5; k++)
				{
					if (map_x + dx[k] >= 0 && map_y + dy[k] > 0 && map_y + dy[k] < 14)
					{
						if (!(map_data.tile[map_y + dy[k]][map_x + dx[k]] == 7 || map_data.tile[map_y + dy[k]][map_x + dx[k]] == 3))
						{
							if (map_data.tile[map_y + dy[k]][map_x + dx[k]] == 4 || map_data.tile[map_y + dy[k]][map_x + dx[k]] == 5 || map_data.tile[map_y + dy[k]][map_x + dx[k]] == 6)
							{
								cnt++;
							}
							map_data.tile[map_y + dy[k]][map_x + dx[k]] = 0;
						}
					}
				}
			}
			mark += cnt * 10;   // mỗi ô phá hủy được cộng thêm 10 điểm

			// xu ly no bom
						
			nobom.push_back({ p_bullet->get_nobom_doc(),p_bullet->get_nobom_ngang() });

			(*nobom.rbegin()).first.LoadImg("map1/nobom_doc.png", des);
			(*nobom.rbegin()).second.LoadImg("map1/nobom_ngang.png", des);

			(*nobom.rbegin()).first.SetRect(p_bullet->GetRect().x, p_bullet->GetRect().y - 45 - 2);
			(*nobom.rbegin()).second.SetRect(p_bullet->GetRect().x - 45 - 2 , p_bullet->GetRect().y);

			ImpTimer ret; Delay_time.push_back(ret);
			(*Delay_time.rbegin()).start();
			
			if (p_bullet != NULL)
			{
					delete p_bullet;
					p_bullet = NULL;
			}

		}
	}


	for (int i = 0; i < nobom.size(); i++)
	{
		if (Delay_time[i].get_ticks() <= 400)
		{
			nobom[i].first.Render(des);
			nobom[i].second.Render(des);
		}
		else
		{
			
			nobom[i].first.Free();
			nobom[i].second.Free();

			nobom.erase(nobom.begin() + i);
			Delay_time.erase(Delay_time.begin() + i);
		}
	}
}





// xử lý va chạm và di chuyển 

void MainObject::DoPlayer(Map& map_data) {
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
	CheckToMap(map_data);

}


void MainObject::CheckToMap(Map& map_data) {
	int map_x1, map_x2, map_y1, map_y2;
	map_x1 = (x_pos + x_val - 185) / TILE_SIZE;
	map_x2 = (x_pos + x_val + width_frame - 185 - 1) / TILE_SIZE;
	map_y1 = (y_pos - 15) / TILE_SIZE;
	map_y2 = (y_pos + height_frame - 15 - 1) / TILE_SIZE;
	if (map_x1 >= 0 && map_x2 < MAX_MAP_X && map_y1 >= 0 && map_y2 < MAX_MAP_Y)
	{
		if (x_val > 0) {
			// 15 la toa do y de set_rect cho cac o vuong dòng 0 
			if (map_data.tile[map_y1][map_x2] != BLANK_TILE || map_data.tile[map_y2][map_x2] != BLANK_TILE) {
				x_pos = 185 + TILE_SIZE * (map_x2)-width_frame - 1;
				x_val = 0;
			}
		}
		else if (x_val < 0) {

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
		if (y_val > 0) {
			if (map_data.tile[map_y2][map_x1] != BLANK_TILE || map_data.tile[map_y2][map_x2] != BLANK_TILE) {
				y_pos = 15 + map_y2 * TILE_SIZE - height_frame - 1;
				y_val = 0;
			}
		}

		else if (y_val < 0)
		{
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
}