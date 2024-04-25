#include "game_map.h"
#include "BaseObject.h"
#include "CommonFunc.h"
#include "MainObject.h"
#include "ImpTimer.h"
#include "TextObject.h"
Uint32 val;
BaseObject g_background;
TTF_Font *font_time = NULL;

int B;           
bool Init() {
	B = SDL_GetTicks();             // là thời gian khi bắt đầu vào menu
	bool success = 1;
	int ret = SDL_Init(SDL_INIT_VIDEO);
	if (ret < 0) return 0;
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
	g_window = SDL_CreateWindow("Bomber Man Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (g_window == NULL) success = 0;
	else {
		g_screen = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);
		if (g_screen == NULL) success = 0;
		else {
			SDL_SetRenderDrawColor(g_screen, COLOR_R, COLOR_G, COLOR_B, 255);
			int imgFlag = IMG_INIT_PNG;
			if (!(IMG_Init(imgFlag) && imgFlag)) {
				success = 0;
			}
		}
		if (TTF_Init() == -1)
		{
			success = false;
		}
		font_time = TTF_OpenFont("font/dlxfont_.ttf", 12);
		if (font_time == NULL)
		{
			success = false;
		}
	}

	if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
	{
		success = false;
	}
	g_sound_bullet[0] = Mix_LoadWAV("Ticking+Bomb.wav");  // âm thanh cho quả bom thường sau khi đặt
	g_sound_bullet[1] = Mix_LoadWAV("Bomb+4.wav");     // âm thanh cho tên lửa
	g_sound_bullet[2] = Mix_LoadWAV("Fire1.wav");    // âm thanh cho súng đạn
	g_sound_bullet[3] = Mix_LoadWAV("Fireball+3.wav");
	g_sound_exp[0] = Mix_LoadWAV("Explosion+5.wav");  // âm thanh cho vụ nổ mìn

	return success;
}
bool LoadBackground() {
	bool ret = g_background.LoadImg("map1/vien.png", g_screen);
	if (ret == 0) {
		return 0;
	}
	return 1;

}
void close() {
	SDL_DestroyRenderer(g_screen);
	g_screen = NULL;
	SDL_DestroyWindow(g_window);
	g_window = NULL;
	IMG_Quit();
	SDL_Quit();
}



int Menu() {
	BaseObject p_menu,p_nut[5];
	p_menu.LoadImg("map1/menu_game.png", g_screen);
	p_nut[0].LoadImg("map1/Start.png", g_screen);
	p_nut[1].LoadImg("map1/guide.png", g_screen);
	p_nut[2].LoadImg("map1/exit.png", g_screen);       // nút game khác là nút thoát chương trình


	int Kt = -1;

	do{                                      // kt = -1 thì hiện lên menu chính
		p_menu.Render(g_screen);
		p_nut[0].SetRect(640, 320);
		p_nut[0].Render(g_screen);

		p_nut[1].SetRect(640, 380);
		p_nut[1].Render(g_screen);

		p_nut[2].SetRect(640, 440);
		p_nut[2].Render(g_screen); 
		while (SDL_PollEvent(&g_event) != 0) 
		{
			if (g_event.type == SDL_QUIT) return -1;         // return -1 là thoát chương trình 
					
			if (g_event.type == SDL_MOUSEBUTTONDOWN) 
			{
				int mouseX, mouseY;
				const Uint8* state = SDL_GetKeyboardState(NULL);
				SDL_GetMouseState(&mouseX, &mouseY);           // lấy tọa độ chuột 
				for (int i = 0; i <= 2; i++) 
				{
					if (SDLCommonFunc::CheckToado(p_nut[i].GetRect(), mouseX, mouseY)) Kt = i;       // cập nhật cửa sổ menu
				}
			}
		}
		if (Kt == 1)       // Kt bằng 1 thì chui vào phần hướng dẫn
		{
			BaseObject p_huongdan;
			SDL_Rect Rect = { 350,610,190,60 };           // rect của nút back trong phần hướng dẫn
			p_huongdan.LoadImg("map1/huongdan.png", g_screen);
			p_huongdan.Render(g_screen);
			do 
			{
				while (SDL_PollEvent(&g_event) != 0) 
				{
					if (g_event.type == SDL_QUIT) return -1;

					if (g_event.type == SDL_MOUSEBUTTONDOWN) 
					{
						int mouseX, mouseY;
						const Uint8* state = SDL_GetKeyboardState(NULL);
						SDL_GetMouseState(&mouseX, &mouseY);
						if (SDLCommonFunc::CheckToado(Rect, mouseX, mouseY)) Kt = -1;    // để thoát phần hướng dẫn ra ngoài menu chính
					}
				}
				SDL_RenderPresent(g_screen);
			} while (Kt == 1);
		}

		SDL_RenderPresent(g_screen);
	} while (Kt < 0);

	return Kt;
}

int Over(SDL_Rect rect1, SDL_Rect rect2)
{
	while (SDL_PollEvent(&g_event) != 0) {
		if (g_event.type == SDL_QUIT) return 0;

		if (g_event.type == SDL_MOUSEBUTTONDOWN) 
		{
			int mouseX, mouseY;
			const Uint8* state = SDL_GetKeyboardState(NULL);
			SDL_GetMouseState(&mouseX, &mouseY);
			
			if (SDLCommonFunc::CheckToado(rect1, mouseX, mouseY)) return 1;     // là khi ấn vào nút quay về menu ở bảng tổng kết 
			if (SDLCommonFunc::CheckToado(rect2, mouseX, mouseY)) return 2;		// là khi ấn vào nút thoát (game khác) ở bảng tồng kết	
		}
	}
	return -1;             
}

int dx1[4] = { -1,0,0,1 };
int dy1[4] = { 0,1,-1,0 };
char a[100][100];
bool visited[100][100];

void dfs(int i, int j)
{
	visited[i][j] = true;
	for (int k = 0; k < 4; k++)
	{
		int i1 = i + dx1[k];
		int j1 = j + dy1[k];
		if (i1 >= 1 && i1 <= 13 && j1 >= 0 && j1 <= 14 && a[i1][j1] == 'x' && visited[i1][j1] == false)
		{
			dfs(i1, j1);
		}
	}
}



int Playgame()
{
	ImpTimer fps_timer;
	//if (!Init()) return -1;
	if (!LoadBackground()) return -1;
	g_background.Render(g_screen);

	// xu ly map 
	GameMap map;
	map.LoadMap("map1/map01.txt");
	map.LoadTiles(g_screen);
	//


	// xu ly nhan vat 
	MainObject p_player1, p_player2;

	p_player2.set_pos2(185 + 45 * 14, 60);

	p_player1.LoadImg("map1/right.png", g_screen);  // mac dinh cho ban dau nhan vat quay ve ben phai 
	p_player2.LoadImg("map1/left2.png", g_screen);

	p_player1.set_clips();
	p_player2.set_clips();

	// xu ly hinh anh min
	p_player1.init_min_(g_screen);
	p_player2.init_min_(g_screen);

	 //xử lý hình ảnh súng đạn
	p_player1.init_sungdan(g_screen);
	p_player2.init_sungdan(g_screen);

	p_player1.init_sungdien(g_screen);
	p_player2.init_sungdien(g_screen);
	 //xử lý hình ảnh súng lửa
	p_player1.init_sunglua(g_screen);
	p_player2.init_sunglua(g_screen);

	p_player1.init_tenlua(g_screen);
	p_player2.init_tenlua(g_screen);
	//--------------------------------------------------
	p_player1.init_la_chan(g_screen, 115, 160);
	p_player2.init_la_chan(g_screen, 115, 430);


	bool quit = 0;

	//Time Text ;
	TextObject time_game;
	time_game.SetColor(TextObject::WHITE_TEXT);

	// xử lý text số bom hiện có
	TextObject num_bom1, num_bom2;

	num_bom1.SetColor(TextObject::BLACK_TEXT);
	num_bom2.SetColor(TextObject::BLACK_TEXT);

	// xử lý text kill 
	TextObject kill_1, kill_2;
	kill_1.SetColor(TextObject::BLACK_TEXT);
	kill_2.SetColor(TextObject::BLACK_TEXT);


	ImpTimer time_bat_tu1;  //xu ly thoi gian bất tử cho nhan vat 
	ImpTimer time_bat_tu2;

	srand((int)time(0));

	Map map_data = map.getMap();

	int cnt = 0;      // đếm số thành phần liên thông của đồ thị
	while (cnt != 1)
	{
		p_player1.Rand2 (0, 7, map_data);
		memset(visited, false, sizeof(visited));
		cnt = 0;

		for (int i = 1; i <= 13; i++)
		{
			for (int j = 0; j <= 14; j++)
			{
				if (map_data.tile[i][j] != 3 && map_data.tile[i][j] != 7)
				{
					a[i][j] = 'x';
				}
				else a[i][j] = 'o';
			}
		}
		for (int i = 1; i <= 13; i++)
		{
			for (int j = 0; j <= 14; j++)
			{
				if (a[i][j] == 'x' && visited[i][j] == false)
				{
					dfs(i, j);
					cnt++;
				}
			}
		}
	}

	int denta_time = SDL_GetTicks() - B;            // khi bắt đầu ấn vào chơi

	map.SetMap(map_data);

	while (!quit)
	{

		Map map_data = map.getMap();


		fps_timer.start();
		while (SDL_PollEvent(&g_event) != 0) {
			if (g_event.type == SDL_QUIT) {
				quit = 1;
			}
			p_player1.HandleInputAction1(g_event, g_screen, map_data, g_sound_bullet);
			p_player2.HandleInputAction2(g_event, g_screen, map_data, g_sound_bullet);

		}

		SDL_SetRenderDrawColor(g_screen, COLOR_R, COLOR_G, COLOR_B, 255);
		SDL_RenderClear(g_screen);
		g_background.Render(g_screen, NULL);

		map.DrawMap(g_screen);

		p_player1.DoPlayer(map_data, g_screen);    // xử lý di chuyển và va chạm
		p_player2.DoPlayer(map_data, g_screen);    // xử lý di chuyển và va chạm

		// set bất tử sau khi ăn lá chắn
		if (p_player1.get_have_lachan()) p_player1.set_bat_tu(true);
		if (p_player2.get_have_lachan()) p_player2.set_bat_tu(true);
		//

	
		
		//---------------------------------
		if (p_player1.get_have_lachan()) p_player1.show_la_chan(g_screen);
		if (p_player2.get_have_lachan()) p_player2.show_la_chan(g_screen);

		p_player1.HandleBullet_Dan(g_screen); // xu ly dan
		p_player2.HandleBullet_Dan(g_screen);


		p_player1.HandleBullet(g_screen);  // xử lý bom & min 
		p_player2.HandleBullet(g_screen);  // xử lý bom & min


		p_player1.HandleBullet_Lua(g_screen); // xử lý lửa
		p_player2.HandleBullet_Lua(g_screen);

		p_player1.HandleBullet_TenLua(g_screen, map_data); // xử lý tên lửa
		p_player2.HandleBullet_TenLua(g_screen, map_data);

		p_player1.RemoveBullet_Bom(map_data, g_screen, g_sound_exp);
		p_player2.RemoveBullet_Bom(map_data, g_screen, g_sound_exp);

		//  xử lý súng lửa
		p_player1.RemoveBullet_Lua(map_data, g_screen);
		p_player2.RemoveBullet_Lua(map_data, g_screen);

		// xử lý va chạm giữa ô chứa vật phẩm và súng đạn
		p_player1.check_col_sungdan(map_data);
		p_player2.check_col_sungdan(map_data);

		//xử lý va chạm giữa ô chứa vật phẩm và tên lửa
		p_player1.check_col_tenlua(map_data, g_screen, g_sound_bullet);
		p_player2.check_col_tenlua(map_data, g_screen, g_sound_bullet);


		map.SetMap(map_data);
		// cap nhat game map vi ta co cau lenh khai bao Map map_data = map.getmap() o dong 71

		p_player1.Show1(g_screen); // bản chất hàm này mỗi lần chỉ load 1 frame, nhưng vì chương trình chạy nhanh quá nên không thể nhìn rõ từng frame 
		p_player2.Show2(g_screen);

		// xu ly va cham giua nguoi va bom
		std::vector <std::pair<NoBom, NoBom>> nobom_list_1 = p_player1.get_no_bom_list();
		std::vector <std::pair<NoBom, NoBom>> nobom_list_2 = p_player2.get_no_bom_list();
		std::vector <std::pair<NoBom, NoBom>> nobom_list1, nobom_list2;


		for (int i = 0; i < nobom_list_1.size(); i++)
		{
			nobom_list1.push_back(nobom_list_1[i]);
			nobom_list2.push_back(nobom_list_1[i]);
		}
		for (int i = 0; i < nobom_list_2.size(); i++)
		{
			nobom_list1.push_back(nobom_list_2[i]);
			nobom_list2.push_back(nobom_list_2[i]);
		}




		// xu ly va cham giữa người - mìn
		std::vector <std::pair<NoBom, NoBom>> nomin_list_1 = p_player1.get_no_min_list();
		std::vector <std::pair<NoBom, NoBom>> nomin_list_2 = p_player2.get_no_min_list();
		std::vector <std::pair<NoBom, NoBom>> nomin_list1, nomin_list2;
		std::vector < std::pair<NoBom, NoBom>> no1, no2;

		for (int i = 0; i < nomin_list_1.size(); i++)
		{
			nomin_list1.push_back(nomin_list_1[i]);
			nomin_list2.push_back(nomin_list_1[i]);
		}
		for (int i = 0; i < nomin_list_2.size(); i++)
		{
			nomin_list1.push_back(nomin_list_2[i]);
			nomin_list2.push_back(nomin_list_2[i]);
		}

		// lấy ra list nổ chung gồm cả nổ bom và mìn để xử lý cho tiện
		for (int i = 0; i < nomin_list1.size() + nobom_list1.size(); i++)
		{
			if (i < nobom_list1.size()) no1.push_back(nobom_list1[i]);
			else no1.push_back(nomin_list1[i - nobom_list1.size()]);
		}

		for (int i = 0; i < nomin_list2.size() + nobom_list2.size(); i++)
		{
			if (i < nobom_list2.size()) no2.push_back(nobom_list2[i]);
			else no2.push_back(nomin_list2[i - nobom_list2.size()]);
		}


		// xử lý va chạm giữa nhân vật 1 và nổ bom && nổ mìn 

		for (int r = 0; r < no1.size(); r++) {

			std::pair<NoBom, NoBom> no_bom = no1.at(r);

			NoBom doc = no1.at(r).first;
			NoBom ngang = no1.at(r).second;

			SDL_Rect tRect;

			tRect.x = p_player1.GetRect().x;
			tRect.y = p_player1.GetRect().y;
			tRect.w = p_player1.get_width_frame();
			tRect.h = p_player1.get_height_frame();



			SDL_Rect bRect_doc = doc.GetRect();
			SDL_Rect bRect_ngang = ngang.GetRect();

			bool bCol_doc = SDLCommonFunc::CheckCollision(bRect_doc, tRect);
			bool bCol_ngang = SDLCommonFunc::CheckCollision(bRect_ngang, tRect);
			//SDL_RenderPresent(g_screen);

			if (p_player1.get_bat_tu() == false)
			{
				if (bCol_doc || bCol_ngang)
				{
					if ((r >= nobom_list_1.size() && r < nobom_list1.size()) || (r >= nobom_list1.size() + nomin_list_1.size() && r < no1.size()))    // tức là bom (mìn) của 2 đã giết 1 
					{
						p_player2.Increase_num_kill();
					}


					p_player1.Decrease_num_life();

					time_bat_tu1.start();   //

					p_player1.set_bat_tu(true);


				}
			}
			if ((bCol_doc || bCol_ngang) && p_player1.get_have_lachan())
			{
				p_player1.set_have_lachan(0);
				p_player1.set_bat_tu(true);
				time_bat_tu1.start();    // sau khi mất lá chắn, cho bất tử trong 2s sau đó
			}


		}


		// xử lý va chạm giữa đạn của 2 với nhân vật 1 
		std::vector<BulletObject*> list_dan2 = p_player2.get_bullet_list();

		for (int i = 0; i < list_dan2.size(); i++)
		{
			BulletObject* p_bullet = list_dan2.at(i);
			if (p_bullet != NULL)
			{
				SDL_Rect tRect;

				tRect.x = p_player1.GetRect().x;
				tRect.y = p_player1.GetRect().y;
				tRect.w = p_player1.get_width_frame();
				tRect.h = p_player1.get_height_frame();

				bool Col = SDLCommonFunc::CheckCollision(p_bullet->GetRect(), tRect);



				if (p_player1.get_bat_tu() == false)
				{
					if (Col)
					{
						p_player2.RemoveBullet_Col(i);
						p_player2.Increase_num_kill();


						p_player1.Decrease_num_life();



						time_bat_tu1.start();   //

						p_player1.set_bat_tu(true);
						//continue;	
					}
				}
				if (Col && p_player1.get_have_lachan())
				{
					p_player2.RemoveBullet_Col(i);
					p_player1.set_have_lachan(0);
					p_player1.set_bat_tu(true);
					time_bat_tu1.start();    // sau khi mất lá chắn, cho bất tử trong 2s sau đó
				}
			}
		}

		// xử lý va chạm giữa lửa của 2 với nhân vật 1 
		std::vector <BulletObject*> list_lua2 = p_player2.get_bullet_list_lua();
		for (int i = 0; i < list_lua2.size(); i++)
		{
			BulletObject* p_bullet = list_lua2.at(i);
			if (p_bullet != NULL)
			{
				SDL_Rect tRect;

				tRect.x = p_player1.GetRect().x;
				tRect.y = p_player1.GetRect().y;
				tRect.w = p_player1.get_width_frame();
				tRect.h = p_player1.get_height_frame();

				bool Col = SDLCommonFunc::CheckCollision(p_bullet->GetRect(), tRect);



				if (p_player1.get_bat_tu() == false)
				{
					if (Col)
					{
						p_player2.RemoveBullet_Col(i);

						p_player2.Increase_num_kill();


						p_player1.Decrease_num_life();



						time_bat_tu1.start();

						p_player1.set_bat_tu(true);

					}
				}
				if (Col && p_player1.get_have_lachan())
				{
					p_player2.RemoveBullet_Col(i);
					p_player1.set_have_lachan(0);
					p_player1.set_bat_tu(true);
					time_bat_tu1.start();    // sau khi mất lá chắn, cho bất tử trong 2s sau đó
				}
			}
		}

		// xử lý va chạm TÊN LỬA - nhân vật 1;
		std::vector <std::pair<NoBom, NoBom>> no_tenlua_list_1 = p_player1.get_no_tenlua_list();
		std::vector <std::pair<NoBom, NoBom>> no_tenlua_list_2 = p_player2.get_no_tenlua_list();
		std::vector < std::pair<NoBom, NoBom>> no_tenlua1, no_tenlua2;

		for (int i = 0; i < no_tenlua_list_1.size(); i++)
		{
			no_tenlua1.push_back(no_tenlua_list_1[i]);
			no_tenlua2.push_back(no_tenlua_list_1[i]);
		}
		for (int i = 0; i < no_tenlua_list_2.size(); i++)
		{
			no_tenlua1.push_back(no_tenlua_list_2[i]);
			no_tenlua2.push_back(no_tenlua_list_2[i]);
		}


		std::vector<BulletObject*> list_tenlua2 = p_player2.get_bullet_list_tenlua();
		// đây là khi đạn tên lửa trúng nhân vật
		for (int i = 0; i < list_tenlua2.size(); i++)
		{
			BulletObject* p_bullet = list_tenlua2.at(i);
			if (p_bullet != NULL)
			{
				SDL_Rect tRect;

				tRect.x = p_player1.GetRect().x;
				tRect.y = p_player1.GetRect().y;
				tRect.w = p_player1.get_width_frame();
				tRect.h = p_player1.get_height_frame();

				bool Col = SDLCommonFunc::CheckCollision(p_bullet->GetRect(), tRect);
				if (p_player1.get_bat_tu() == false)
				{
					if (Col)
					{
						Mix_FreeChunk(g_sound_bullet[1]);
						g_sound_bullet[1] = Mix_LoadWAV("Explosion+5.wav");
						Mix_PlayChannel(-1, g_sound_bullet[1], 0);
						p_player1.check_around_MainObject(map_data, g_screen, p_bullet, tRect.x, tRect.y);
						map.SetMap(map_data);
						p_player2.RemoveTenLua_Col(i);

						p_player2.Increase_num_kill();


						p_player1.Decrease_num_life();



						time_bat_tu1.start();   //

						p_player1.set_bat_tu(true);
						//continue;	
					}
				}
				if (Col && p_player1.get_have_lachan())
				{
					Mix_FreeChunk(g_sound_bullet[1]);
					g_sound_bullet[1] = Mix_LoadWAV("Explosion+5.wav");
					Mix_PlayChannel(-1, g_sound_bullet[1], 0);
					p_player2.RemoveTenLua_Col(i);
					p_player1.set_have_lachan(0);
					p_player1.set_bat_tu(true);
					time_bat_tu1.start();    // sau khi mất lá chắn, cho bất tử trong 2s sau đó
				}
			}
		}
		// đây là khi đạn tên lửa không trúng nhân vật nhưng hiệu ứng nổ lại trúng
		for (int r = 0; r < no_tenlua1.size(); r++) {

			std::pair<NoBom, NoBom> no_bom = no_tenlua1.at(r);

			NoBom doc = no_tenlua1.at(r).first;
			NoBom ngang = no_tenlua1.at(r).second;

			SDL_Rect tRect;

			tRect.x = p_player1.GetRect().x;
			tRect.y = p_player1.GetRect().y;
			tRect.w = p_player1.get_width_frame();
			tRect.h = p_player1.get_height_frame();



			SDL_Rect bRect_doc = doc.GetRect();
			SDL_Rect bRect_ngang = ngang.GetRect();

			bool bCol_doc = SDLCommonFunc::CheckCollision(bRect_doc, tRect);
			bool bCol_ngang = SDLCommonFunc::CheckCollision(bRect_ngang, tRect);

			if (p_player1.get_bat_tu() == false)
			{
				if (bCol_doc || bCol_ngang)
				{
					if (r >= no_tenlua_list_1.size())    // tức là tên lửa của 2 đã giết 1 
					{
						p_player2.Increase_num_kill();

					}
					p_player1.Decrease_num_life();



					time_bat_tu1.start();   //

					p_player1.set_bat_tu(true);
					//continue;	
				}
			}
			if ((bCol_doc || bCol_ngang) && p_player1.get_have_lachan())
			{
				p_player1.set_have_lachan(0);
				p_player1.set_bat_tu(true);
				time_bat_tu1.start();    // sau khi mất lá chắn, cho bất tử trong 2s sau đó
			}
		}

		if (time_bat_tu1.get_ticks() >= 2000)
		{
			p_player1.set_bat_tu(false);
		}
		// xử lý chỉ số kill cho nhân vật 2 
		std::string str_kill_2 =  std::to_string(p_player2.get_num_kill());
		str_kill_2 += "/7";
		kill_2.SetText(str_kill_2);
		kill_2.LoadFromRenderText(font_time, g_screen);
		kill_2.RenderText(g_screen, 40, 485);


		// xu ly text chi so bom cho nhan vat 1 
		std::string str_num_bom1 = ":" + std::to_string(p_player1.get_max_bom());
		num_bom1.SetText(str_num_bom1);
		num_bom1.LoadFromRenderText(font_time, g_screen);
		num_bom1.RenderText(g_screen, 57, 170);


		// xử lý va chạm giữa nhân vật 2 và nổ bom & mìn
		for (int r = 0; r < no2.size(); r++)
		{

			std::pair<NoBom, NoBom> no_bom = no2.at(r);

			NoBom doc = no2.at(r).first;
			NoBom ngang = no2.at(r).second;

			SDL_Rect tRect;

			tRect.x = p_player2.GetRect().x;
			tRect.y = p_player2.GetRect().y;
			tRect.w = p_player2.get_width_frame();
			tRect.h = p_player2.get_height_frame();



			SDL_Rect bRect_doc = doc.GetRect();
			SDL_Rect bRect_ngang = ngang.GetRect();

			bool bCol_doc = SDLCommonFunc::CheckCollision(bRect_doc, tRect);
			bool bCol_ngang = SDLCommonFunc::CheckCollision(bRect_ngang, tRect);
			//SDL_RenderPresent(g_screen);
			if (p_player2.get_bat_tu() == false)
			{
				if (bCol_doc || bCol_ngang)
				{
					if (!((r >= nobom_list_1.size() && r < nobom_list1.size()) || (r >= nobom_list1.size() + nomin_list_1.size() && r < no1.size())))    // tức là bom (mìn) của 1 đã giết 2
					{
						p_player1.Increase_num_kill();

					}
					p_player2.Decrease_num_life();



					time_bat_tu2.start();   //

					p_player2.set_bat_tu(true);
					//continue;	
				}
			}
			if ((bCol_doc || bCol_ngang) && p_player2.get_have_lachan()) {
				p_player2.set_have_lachan(0);
				p_player2.set_bat_tu(true);
				time_bat_tu2.start();    // sau khi mất lá chắn, cho bất tử trong 2s sau đó
			}


		}

		// xử lý va chạm giữa đạn của 1 với nhân vật 2 
		std::vector<BulletObject*> list_dan1 = p_player1.get_bullet_list();
		for (int i = 0; i < list_dan1.size(); i++)
		{
			BulletObject* p_bullet = list_dan1.at(i);
			if (p_bullet != NULL)
			{
				SDL_Rect tRect;

				tRect.x = p_player2.GetRect().x;
				tRect.y = p_player2.GetRect().y;
				tRect.w = p_player2.get_width_frame();
				tRect.h = p_player2.get_height_frame();

				bool Col = SDLCommonFunc::CheckCollision(p_bullet->GetRect(), tRect);



				if (p_player2.get_bat_tu() == false)
				{
					if (Col)
					{
						p_player1.RemoveBullet_Col(i);

						p_player1.Increase_num_kill();


						p_player2.Decrease_num_life();



						time_bat_tu2.start();   //

						p_player2.set_bat_tu(true);
						//continue;	
					}
				}
				if (Col && p_player2.get_have_lachan())
				{
					p_player1.RemoveBullet_Col(i);
					p_player2.set_have_lachan(0);
					p_player2.set_bat_tu(true);
					time_bat_tu2.start();    // sau khi mất lá chắn, cho bất tử trong 2s sau đó
				}
			}
		}

		// xử lý va chạm giữa lửa của 1 với nhân vật 2 
		std::vector <BulletObject*> list_lua1 = p_player1.get_bullet_list_lua();
		for (int i = 0; i < list_lua1.size(); i++)
		{
			BulletObject* p_bullet = list_lua1.at(i);
			if (p_bullet != NULL)
			{
				SDL_Rect tRect;

				tRect.x = p_player2.GetRect().x;
				tRect.y = p_player2.GetRect().y;
				tRect.w = p_player2.get_width_frame();
				tRect.h = p_player2.get_height_frame();

				bool Col = SDLCommonFunc::CheckCollision(p_bullet->GetRect(), tRect);



				if (p_player2.get_bat_tu() == false)
				{
					if (Col)
					{
						p_player1.RemoveBullet_Col(i);

						p_player1.Increase_num_kill();



						p_player2.Decrease_num_life();


						time_bat_tu2.start();

						p_player2.set_bat_tu(true);

					}
				}
				if (Col && p_player2.get_have_lachan())
				{
					p_player1.RemoveBullet_Col(i);
					p_player2.set_have_lachan(0);
					p_player2.set_bat_tu(true);
					time_bat_tu2.start();    // sau khi mất lá chắn, cho bất tử trong 2s sau đó
				}
			}
		}


		// xử lý va chạm tên lửa - nhân vật 2 

		std::vector<BulletObject*> list_tenlua1 = p_player1.get_bullet_list_tenlua();

		for (int i = 0; i < list_tenlua1.size(); i++)
		{
			BulletObject* p_bullet = list_tenlua1.at(i);
			if (p_bullet != NULL)
			{
				SDL_Rect tRect;

				tRect.x = p_player2.GetRect().x;
				tRect.y = p_player2.GetRect().y;
				tRect.w = p_player2.get_width_frame();
				tRect.h = p_player2.get_height_frame();

				bool Col = SDLCommonFunc::CheckCollision(p_bullet->GetRect(), tRect);
				if (p_player1.get_bat_tu() == false)
				{
					if (Col)
					{
						Mix_FreeChunk(g_sound_bullet[1]);
						g_sound_bullet[1] = Mix_LoadWAV("Explosion+5.wav");
						Mix_PlayChannel(-1, g_sound_bullet[1], 0);
						p_player2.check_around_MainObject(map_data, g_screen, p_bullet, tRect.x, tRect.y);
						map.SetMap(map_data);
						p_player1.RemoveTenLua_Col(i);

						p_player1.Increase_num_kill();


						p_player2.Decrease_num_life();


						time_bat_tu2.start();   //

						p_player2.set_bat_tu(true);
						//continue;	
					}
				}
				if (Col && p_player2.get_have_lachan())
				{
					Mix_FreeChunk(g_sound_bullet[1]);
					g_sound_bullet[1] = Mix_LoadWAV("Explosion+5.wav");
					Mix_PlayChannel(-1, g_sound_bullet[1], 0);
					p_player1.RemoveTenLua_Col(i);
					p_player2.set_have_lachan(0);
					p_player2.set_bat_tu(true);
					time_bat_tu2.start();    // sau khi mất lá chắn, cho bất tử trong 2s sau đó
				}
			}
		}

		for (int r = 0; r < no_tenlua2.size(); r++) {

			std::pair<NoBom, NoBom> no_bom = no_tenlua2.at(r);

			NoBom doc = no_tenlua2.at(r).first;
			NoBom ngang = no_tenlua2.at(r).second;

			SDL_Rect tRect;

			tRect.x = p_player2.GetRect().x;
			tRect.y = p_player2.GetRect().y;
			tRect.w = p_player2.get_width_frame();
			tRect.h = p_player2.get_height_frame();



			SDL_Rect bRect_doc = doc.GetRect();
			SDL_Rect bRect_ngang = ngang.GetRect();

			bool bCol_doc = SDLCommonFunc::CheckCollision(bRect_doc, tRect);
			bool bCol_ngang = SDLCommonFunc::CheckCollision(bRect_ngang, tRect);

			if (p_player2.get_bat_tu() == false)
			{
				if (bCol_doc || bCol_ngang)
				{
					if (r < no_tenlua_list_1.size())    // tức là tên lửa của 2 đã giết 1 
					{
						p_player1.Increase_num_kill();
					}
					p_player2.Decrease_num_life();



					time_bat_tu2.start();   //

					p_player2.set_bat_tu(true);
					//continue;	
				}
			}
			if ((bCol_doc || bCol_ngang) && p_player2.get_have_lachan())
			{
				p_player2.set_have_lachan(0);
				p_player2.set_bat_tu(true);
				time_bat_tu2.start();    // sau khi mất lá chắn, cho bất tử trong 2s sau đó
			}



		}

		if (time_bat_tu2.get_ticks() >= 2000)
		{
			p_player2.set_bat_tu(false);
		}

		// xử lý chỉ số kill cho nhân vật 1
		std::string str_kill_1 = std::to_string(p_player1.get_num_kill());
		str_kill_1 += "/7";
		kill_1.SetText(str_kill_1);
		kill_1.LoadFromRenderText(font_time, g_screen);
		kill_1.RenderText(g_screen, 40, 208);


		//xử lý text so bom cho nhân vật 2
		std::string str_num_bom2 = ":" + std::to_string(p_player2.get_max_bom());
		num_bom2.SetText(str_num_bom2);
		num_bom2.LoadFromRenderText(font_time, g_screen);
		num_bom2.RenderText(g_screen, 57, 445);
		//---------------------------------------------------------------------
		//Show game time (xử lý text)
		time_game.SetColor(TextObject::WHITE_TEXT);
		std::string str_time = "Time: ";
		Uint32 time_val = SDL_GetTicks() / 1000;               // chia 1000 để ra đơn vị ms 
		Uint32 val_time = denta_time / 1000 + 300 - time_val;


		//------------------------------------------------------------------------
		std::string str_val = std::to_string(val_time);
		str_time += str_val;
		time_game.SetText(str_time);
		time_game.LoadFromRenderText(font_time, g_screen);
		time_game.RenderText(g_screen, 35, 550);       // set vi tri hien thi text

		//--------------------------------------- xử lý game over------------------------------------------------

		if (p_player1.get_num_kill() >= MAX_KILL || p_player2.get_num_kill() >= MAX_KILL || val_time <= 0)
		{
			BaseObject p_over;
			int Kt_Over = -1;
			SDL_Rect Rect_1 = { 340,475,165,35 };                // là rect của nút menu ở table xuất hiện sau khi game kết thúc
			SDL_Rect Rect_2 = { 525,475,165,35 };				// là rect của nút "game khác " (thoát) ở bảng table	
			if (p_player1.get_num_kill() >= MAX_KILL || (val_time <= 0 && p_player1.get_num_kill() > p_player2.get_num_kill()) ) 
			{
				p_over.LoadImg("map1/table2.png", g_screen);
				p_over.SetRect(227, 150);
				do 
				{
					p_over.Render(g_screen);
					Kt_Over = Over(Rect_1, Rect_2);
					SDL_RenderPresent(g_screen);
				} while (Kt_Over == -1);

			}
			else if (p_player2.get_num_kill() >= MAX_KILL || (val_time <= 0 && p_player2.get_num_kill() > p_player1.get_num_kill()))
			{
				p_over.LoadImg("map1/table1.png", g_screen);
				p_over.SetRect(227, 150);
				do 
				{
					p_over.Render(g_screen);
					Kt_Over = Over(Rect_1, Rect_2);
					SDL_RenderPresent(g_screen);
				} while (Kt_Over == -1);
			}
			else
			{
				p_over.LoadImg("map1/table3.png", g_screen);
				p_over.SetRect(227, 150);
				do 
				{
					p_over.Render(g_screen);
					Kt_Over = Over(Rect_1, Rect_2);
					SDL_RenderPresent(g_screen);
				} while (Kt_Over == -1);
			}
			if (Kt_Over == 2 || Kt_Over == 0)    // = 0 là đã ấn vào QUIT
			{
				p_player1.RemoveBullet_Bom(map_data, g_screen, g_sound_exp);
				p_player2.RemoveBullet_Bom(map_data, g_screen, g_sound_exp);
				map.SetMap(map_data);
				return -1;         // thoát chương trình
			}
			else
			{
				p_player1.RemoveBullet_Bom(map_data, g_screen, g_sound_exp);
				p_player2.RemoveBullet_Bom(map_data, g_screen, g_sound_exp);
				map.SetMap(map_data);
				return 0;      // tức là Kt_Over = 1 (ấn trở lại menu)
			}
		}
		time_game.Free();  // giải phóng cho đỡ tốn bộ nhớ
		num_bom1.Free();
		num_bom2.Free();
		kill_1.Free();
		kill_2.Free();
		SDL_RenderPresent(g_screen);


		// xử lý thời gian 
		int real_imp_time = fps_timer.get_ticks();
		int time_one_frame = 1000 / FRAME_PER_SECOND;  //ms
		if (real_imp_time < time_one_frame)
		{
			int delay_time = time_one_frame - real_imp_time;
			if (delay_time >= 0) {
				SDL_Delay(delay_time);
			}
		}
	}

	std::this_thread::sleep_for
	(std::chrono::milliseconds(500));
}



int main(int argv, char* arg[]){
	Init();
	int Kt = -1;
	//int time1 = 0;
	
	do
	{
		Kt = Menu();
		
		if (Kt == 0) 
		{

			Kt = Playgame(); 
		
		}
	} while (Kt == 0);
	close();
	return 0;
}