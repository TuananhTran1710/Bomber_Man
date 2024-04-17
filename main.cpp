#include "game_map.h"
#include "BaseObject.h"
#include "CommonFunc.h"
#include "MainObject.h"
#include "ImpTimer.h"
#include "TextObject.h"


BaseObject g_background;
TTF_Font *font_time = NULL;
bool Init() {
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

int main(int argv, char* arg[]) {

	ImpTimer fps_timer;
	if (!Init()) return -1;
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

	// xu ly hinh anh la chan
	p_player1.init_lachan(g_screen, 105 ,80);
	p_player2.init_lachan(g_screen, 107, 210);
	// xu ly hinh anh min
	p_player1.init_min(g_screen, 105, 103);
	p_player2.init_min(g_screen, 105, 222);

	// xử lý hình ảnh súng đạn
	p_player1.init_sung_dan(g_screen, 105, 103);
	p_player2.init_sung_dan(g_screen, 105, 222);

	bool quit = 0;

	//Time Text ;
	TextObject time_game;
	time_game.SetColor(TextObject::WHITE_TEXT);

	// xử lý text sinh mạng và số bom hiện có
	TextObject life1, life2,num_bom1, num_bom2;
	life1.SetColor(TextObject::BLACK_TEXT);
	life2.SetColor(TextObject::BLACK_TEXT);
	num_bom1.SetColor(TextObject::BLACK_TEXT);
	num_bom2.SetColor(TextObject::BLACK_TEXT);

	// xử lý text kill 
	TextObject kill_1, kill_2;
	kill_1.SetColor(TextObject::BLACK_TEXT);
	kill_2.SetColor(TextObject::BLACK_TEXT);


	ImpTimer time_bat_tu1;  //xu ly thoi gian bất tử cho nhan vat 
	ImpTimer time_bat_tu2;   

	srand((int)time(0));

	while (!quit)
	{
		
		Map map_data = map.getMap();

		fps_timer.start();
		while (SDL_PollEvent(&g_event) != 0) {
			if (g_event.type == SDL_QUIT) {
				quit = 1;
			}
			p_player1.HandleInputAction1(g_event, g_screen, map_data);
			p_player2.HandleInputAction2(g_event, g_screen, map_data);

		}

		SDL_SetRenderDrawColor(g_screen, COLOR_R, COLOR_G, COLOR_B, 255);
		SDL_RenderClear(g_screen);
		g_background.Render(g_screen, NULL);

		map.DrawMap(g_screen);

		p_player1.DoPlayer(map_data,g_screen);    // xử lý di chuyển và va chạm
		p_player2.DoPlayer(map_data,g_screen);    // xử lý di chuyển và va chạm

		// xu ly hinh anh la chan ở bảng tồng hợp 
		if (p_player1.get_have_lachan()) p_player1.show_la_chan(g_screen);
		if (p_player2.get_have_lachan()) p_player2.show_la_chan(g_screen);
		// set bất tử sau khi ăn lá chắn
		if (p_player1.get_have_lachan()) p_player1.set_bat_tu(true);
		if (p_player2.get_have_lachan()) p_player2.set_bat_tu(true);
		//

		// xu ly hinh anh mìn ở bàng tổng hợp
		if (p_player1.get_num_min()) p_player1.show_min(g_screen);
		if (p_player2.get_num_min()) p_player2.show_min(g_screen);

		// xử lý hình ảnh súng đạn ở bảng tổng hợp
		if (p_player1.get_num_sung_dan()) p_player1.show_sung_dan(g_screen);
		if (p_player2.get_num_sung_dan()) p_player2.show_sung_dan(g_screen);

		p_player1.HandleBullet_Dan(g_screen); // xu ly dan
		p_player2.HandleBullet_Dan(g_screen);


		p_player1.HandleBullet(g_screen);  // xử lý bom & min 
		p_player2.HandleBullet(g_screen);  // xử lý bom & min
		 
		p_player1.RemoveBullet_Bom(map_data,g_screen);
		p_player2.RemoveBullet_Bom(map_data,g_screen);


		map.SetMap(map_data);      // cap nhat game map vi ta co cau lenh khai bao Map map_data = map.getmap() o dong 71

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
			if (i < nobom_list2.size()) no2.push_back( nobom_list2[i] );
			else no2.push_back(nomin_list2[ i - nobom_list2.size() ]);
		}

		// xử lý va chạm giữa nhân vật 1 và nổ bom && nổ mìn 

		for (int r = 0; r < no1.size(); r++){

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
					if ( (r >= nobom_list_1.size() && r < nobom_list1.size() ) || (r >= nobom_list1.size() + nomin_list_1.size() && r < no1.size()) )    // tức là bom (mìn) của 2 đã giết 1 
					{
						p_player2.Increase_num_kill();    
						if (p_player2.get_num_kill() == 3)
						{
							if (MessageBox(NULL, L"P2 Win", L"Info", MB_OK | MB_ICONSTOP) == IDOK)
							{
								no1.erase(no1.begin() + r);
								close();
								SDL_Quit();
								return 0;
							}
						}
					}
					p_player1.Decrease_num_life();

					p_player1.set_pos2(185, 60);

					time_bat_tu1.start();   //

					p_player1.set_bat_tu(true);
					//continue;	
				}
			}
			if ((bCol_doc || bCol_ngang) && p_player1.get_have_lachan()) {
				p_player1.set_have_lachan(0);
				p_player1.set_bat_tu(true);
				time_bat_tu1.start();    // sau khi mất lá chắn, cho bất tử trong 2s sau đó
			}


		}
		if (time_bat_tu1.get_ticks() >= 2000) 
		{ 
			p_player1.set_bat_tu(false); 
		}	
	

		// xử lý va chạm giữa đạn của 2 với nhân vật 1 
		p_player1.check_col_sungdan(map_data);
		map.SetMap(map_data);

		// xử lý chỉ số kill cho nhân vật 2 
		std::string str_kill_2 = std::to_string(p_player2.get_num_kill());
		str_kill_2 += "/3";
		kill_2.SetText(str_kill_2);
		kill_2.LoadFromRenderText(font_time, g_screen);
		kill_2.RenderText(g_screen, 60, 243);


		// xử lý text chỉ số sinh mang cho nhân vật 1
		std::string str_life1 = std:: to_string(p_player1.get_num_life());
		life1.SetText(str_life1);
		life1.LoadFromRenderText(font_time, g_screen);
		life1.RenderText(g_screen, 135, 39);

		// xu ly text chi so bom cho nhan vat 1 
		std::string str_num_bom1 = std::to_string(p_player1.get_max_bom());
		num_bom1.SetText(str_num_bom1);
		num_bom1.LoadFromRenderText(font_time, g_screen);
		num_bom1.RenderText(g_screen, 135, 60);


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
					if ( ! ( (r >= nobom_list_1.size() && r < nobom_list1.size()) || (r >= nobom_list1.size() + nomin_list_1.size() && r < no1.size() ) ) )    // tức là bom (mìn) của 1 đã giết 2
					{
						p_player1.Increase_num_kill();					
						if (p_player1.get_num_kill() == 3)
						{
							if (MessageBox(NULL, L"P1 Win", L"Info", MB_OK | MB_ICONSTOP) == IDOK)
							{
								no2.erase(no2.begin() + r);
								close();
								SDL_Quit();
								return 0;
							}
						}
					}
					p_player2.Decrease_num_life();

					p_player2.set_pos2(185 + 45 * 14, 60);

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
		if (time_bat_tu2.get_ticks() >= 2000)
		{
			p_player2.set_bat_tu(false);
		}

		// xử lý chỉ số kill cho nhân vật 2
		std::string str_kill_1 = std::to_string(p_player1.get_num_kill());
		str_kill_1 += "/3";
		kill_1.SetText(str_kill_1);
		kill_1.LoadFromRenderText(font_time, g_screen);
		kill_1.RenderText(g_screen, 58, 122);

		// xử lý text sinh mạng cho nhân vật 2 
		std::string str_life2 = std::to_string(p_player2.get_num_life());
		life2.SetText(str_life2);
		life2.LoadFromRenderText(font_time, g_screen);
		life2.RenderText(g_screen, 135, 163);

		//xử lý text so bom cho nhân vật 2
		std::string str_num_bom2 = std::to_string(p_player2.get_max_bom());
		num_bom2.SetText(str_num_bom2);
		num_bom2.LoadFromRenderText(font_time, g_screen);
		num_bom2.RenderText(g_screen, 135, 187);

		//Show game time (xử lý text)
		time_game.SetColor(TextObject::WHITE_TEXT);
		std::string str_time = "Time: ";
		Uint32 time_val = SDL_GetTicks() / 1000;
		Uint32 val_time = 300 - time_val;
		if (val_time <= 0)       
		{
			if (p_player1.get_num_kill() > p_player2.get_num_kill())
			{
				if (MessageBox(NULL, L"P1 Win", L"Info", MB_OK | MB_ICONSTOP) == IDOK)
				{
					quit = true;
					break;
				}
			}
			else if (p_player1.get_num_kill() < p_player2.get_num_kill())
			{
				if (MessageBox(NULL, L"P2 Win", L"Info", MB_OK | MB_ICONSTOP) == IDOK)
				{
					quit = true;
					break;
				}
			}
			else
			{
				if (MessageBox(NULL, L"Equal", L"Info", MB_OK | MB_ICONSTOP) == IDOK)
				{
					quit = true;
					break;
				}
			}
			
		}
		else
		{
			std::string str_val = std::to_string(val_time);
			str_time += str_val;
			time_game.SetText(str_time);
			time_game.LoadFromRenderText(font_time, g_screen);
			time_game.RenderText(g_screen, 35, 550);       // set vi tri hien thi text
		}

		time_game.Free();  // giải phóng cho đỡ tốn bộ nhớ
		life1.Free();
		life2.Free();
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

	close();

	return 0;
}