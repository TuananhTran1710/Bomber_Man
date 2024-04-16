#include "MainObject.h"
#include "ImpTimer.h"
std::vector< ImpTimer> Delay_time_bom;
std::vector< ImpTimer> Delay_time_min;

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
	max_bom = 2;
	bat_tu = false;
	num_life = 2;
	num_kill = 0;
	have_lachan = 0;
	type_bullet = 15;

	num_sung_dan=0;
	num_sung_lua=0;
	num_ten_lua=0;
	num_min=0;
	num_sung_dien=0;

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


// xu ly dan
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
					if (status == WALK_LEFT) {

						p_bullet->SetRect(185 + floor((this->x_pos - 185) / 45) * 45 + 2, 60 + floor((this->y_pos - 60) / 45) * 45 + 2); // rect.x , rect.y la vi tri set anh cua nhan vat 

					}

					else if (status == WALK_RIGHT)
					{

						p_bullet->SetRect(185 + floor((this->x_pos - 185) / 45) * 45 + 2, 60 + floor((this->y_pos - 60) / 45) * 45 + 2);


					}
					else if (status == WALK_UP)
					{

						p_bullet->SetRect(185 + floor((this->x_pos - 185) / 45) * 45 + 2, 60 + floor((this->y_pos - 60) / 45) * 45 + 2);


					}
					else if (status == WALK_DOWN)
					{
						p_bullet->SetRect(185 + floor((this->x_pos - 185) / 45) * 45 + 2, 60 + floor((this->y_pos - 60) / 45) * 45 + 2);


					}

					p_bullet->set_is_move(true); // chuyển sang true tức là cho phép đạn bắn ra 
					// nhu vậy phần trên đã khởi tạo xong viên đạn 

					bullet_list_bom.push_back(p_bullet); // nạp đạn sẵn vào băng, chỉ ấn là đạn sẽ xuất hiện
					p_bullet->set_bullet_time(SDL_GetTicks());

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
				if (bullet_list_min.size() < num_min)
				{
					BulletObject* p_bullet = new BulletObject();

					p_bullet->set_bullet_type(type_bullet);
					p_bullet->LoadImgBullet(screen);

					if (status == WALK_LEFT) {

						p_bullet->SetRect(185 + floor((this->x_pos - 185) / 45) * 45 + 2, 60 + floor((this->y_pos - 60) / 45) * 45 + 2);

					}

					else if (status == WALK_RIGHT)
					{
						p_bullet->SetRect(185 + floor((this->x_pos - 185) / 45) * 45 + 2, 60 + floor((this->y_pos - 60) / 45) * 45 + 2);

					}
					else if (status == WALK_UP)
					{

						p_bullet->SetRect(185 + floor((this->x_pos - 185) / 45) * 45 + 2, 60 + floor((this->y_pos - 60) / 45) * 45 + 2);


					}
					else if (status == WALK_DOWN)
					{
						p_bullet->SetRect(185 + floor((this->x_pos - 185) / 45) * 45 + 2, 60 + floor((this->y_pos - 60) / 45) * 45 + 2);
					}

					p_bullet->set_is_move(true); // chuyển sang true tức là cho phép đạn bắn ra 
					// nhu vậy phần trên đã khởi tạo xong viên đạn 

					bullet_list_min.push_back(p_bullet); // nạp đạn sẵn vào băng, chỉ ấn là đạn sẽ xuất hiện

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


// chưa xử lý thằng 2 
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
					if (status == WALK_LEFT) {

						p_bullet->SetRect(185 + floor((this->x_pos - 185) / 45) * 45 + 2, 60 + floor((this->y_pos - 60) / 45) * 45 + 2); // rect.x , rect.y la vi tri set anh cua nhan vat 


					}

					else if (status == WALK_RIGHT)
					{

						p_bullet->SetRect(185 + floor((this->x_pos - 185) / 45) * 45 + 2, 60 + floor((this->y_pos - 60) / 45) * 45 + 2);


					}
					else if (status == WALK_UP)
					{

						p_bullet->SetRect(185 + floor((this->x_pos - 185) / 45) * 45 + 2, 60 + floor((this->y_pos - 60) / 45) * 45 + 2);

					}
					else if (status == WALK_DOWN)
					{
						p_bullet->SetRect(185 + floor((this->x_pos - 185) / 45) * 45 + 2, 60 + floor((this->y_pos - 60) / 45) * 45 + 2);

					}
					p_bullet->set_is_move(true); // chuyển sang true tức là cho phép đạn bắn ra 
					// nhu vậy phần trên đã khởi tạo xong viên đạn 

					bullet_list_bom.push_back(p_bullet); // nạp đạn sẵn vào băng, chỉ ấn là đạn sẽ xuất hiện
					p_bullet->set_bullet_time(SDL_GetTicks());

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
				if (bullet_list_min.size() < num_min)
				{
					BulletObject* p_bullet = new BulletObject();

					p_bullet->set_bullet_type(type_bullet);
					p_bullet->LoadImgBullet(screen);

					if (status == WALK_LEFT) {

						p_bullet->SetRect(185 + floor((this->x_pos - 185) / 45) * 45 + 2, 60 + floor((this->y_pos - 60) / 45) * 45 + 2);

					}

					else if (status == WALK_RIGHT)
					{
						p_bullet->SetRect(185 + floor((this->x_pos - 185) / 45) * 45 + 2, 60 + floor((this->y_pos - 60) / 45) * 45 + 2);

					}
					else if (status == WALK_UP)
					{

						p_bullet->SetRect(185 + floor((this->x_pos - 185) / 45) * 45 + 2, 60 + floor((this->y_pos - 60) / 45) * 45 + 2);


					}
					else if (status == WALK_DOWN)
					{
						p_bullet->SetRect(185 + floor((this->x_pos - 185) / 45) * 45 + 2, 60 + floor((this->y_pos - 60) / 45) * 45 + 2);
					}

					p_bullet->set_is_move(true); // chuyển sang true tức là cho phép đạn bắn ra 
					// nhu vậy phần trên đã khởi tạo xong viên đạn 

					bullet_list_min.push_back(p_bullet); // nạp đạn sẵn vào băng, chỉ ấn là đạn sẽ xuất hiện

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


// xử lý hình ảnh đạn 
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
		}
	}

}

int dx[4] = { 1,-1,0,0 };
int dy[4] = { 0,0,-1,1 };

int Rand(int l, int r)
{
	return l + rand() % (r - l + 1);
}

void MainObject::RemoveBullet_Bom(Map& map_data, SDL_Renderer* des) {
		for (int i = 0; i < bullet_list_bom.size(); i++) {
			BulletObject* p_bullet = bullet_list_bom.at(i);
			if (SDL_GetTicks() - p_bullet->get_bullet_time() >= 2500)
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
}


void MainObject :: RemoveBullet_Min(Map& map_data, SDL_Renderer* des)
{
	for (int i = 0; i < bullet_list_min.size(); i++)
	{
		BulletObject* p_bullet = bullet_list_min.at(i);
		bullet_list_min.erase(bullet_list_min.begin() + i);

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

		(*nomin.rbegin()).first.LoadImg("map1/nobom_doc.png", des);
		(*nomin.rbegin()).second.LoadImg("map1/nobom_ngang.png", des);

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



// xu ly hinh anh la chan
void MainObject::init_lachan(SDL_Renderer* des, double x , double y)
{
	lachan.LoadImg("map1/lachan.png", des);
	lachan.SetRect(x, y);
}

void MainObject::show_la_chan(SDL_Renderer* des)
{
	for (int i = 1; i <= this->get_have_lachan();i++)
	{
		lachan.Render(des);
	}
}

// check va set tinh nang cho item la chan
void MainObject::check_item_lachan(int val_1, int val_2)
{
	if ( (val_1 == 13 && val_2 == 13) || (val_1 == 13 && val_2 >= 9 && val_1 != val_2 && val_2 <=15) || (val_1 == 13 && val_2 == 0) || (val_1 == 0 && val_2 == 13) )
	{
		// chú ý : ở điều kiện 2, cần có val_2 <= 15 để tránh trường hợp ô val_2 là mìn
		// vì nếu là mìn thì chỉ cần đi giữa 2 ô ( tức là chạm vào mìn ) là sẽ nổ 
		this->set_bat_tu(true);          // mặc định game: nếu 2 ô trên và dưới cùng là item thì ta chọn item trên để set cho nhân vật
		have_lachan = 1;
	}
}


// check và set tinh nang cho item bom 
void MainObject :: check_item_bom(int val_1, int val_2)
{
	if ( (val_1 == 15 && val_2 == 15 ) || (val_1 == 15 && val_2 >= 9 && val_1 != val_2 && val_2 <= 15) || (val_1 == 15 && val_2 == 0) || (val_1 == 0 && val_2 == 15))    // và phải xử lý sao cho khi ấn space nó ra bom
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


void MainObject::init_min(SDL_Renderer* screen, double x , double y)
{
	min_.LoadImg("map1/min_icon.png", screen);
	min_.SetRect(x, y);
}

void MainObject::show_min(SDL_Renderer* screen)
{
	for (int i = 1; i <= num_min; i++)
	{
		min_.Render(screen);
	}
}
// check và set tinh nang cho mìn
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

void MainObject::check_col_min(int val_1, int val_2, Map& map_data, SDL_Renderer* des)
{
	if ( (val_1 == 20 && val_2 == 20) || (val_1 == 20 && val_2 == 0) || (val_1 == 0 && val_2 == 20) || (val_1 == 20 && val_2 >= 9) || (val_1 >= 9 && val_2 == 20) )
 	{
		RemoveBullet_Min(map_data, des);  // phải truyền vào đây g_screen
	}
}


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

void MainObject::CheckToMap(Map& map_data , SDL_Renderer *des) {
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
			
			// check xem nhân vật có đi vào mìn không 
			check_col_min(val_1, val_2, map_data, des);

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

			if ( map_data.tile[map_y1][map_x2] != BLANK_TILE || map_data.tile[map_y2][map_x2] != BLANK_TILE) {
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

			check_col_min(val_1, val_2, map_data, des);
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

			check_col_min(val_1, val_2, map_data, des);
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

			check_col_min(val_1, val_2, map_data, des);
			if (9 <= val_1 && 9 <= val_2 && val_1 <= 15 && val_2 <= 15 )            // dấu && chứ không phải || ( vì nếu là || thì ví dụ ô [1][2] là ô item, ô [2][2] là ô không phải item
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
}

