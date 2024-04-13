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

	//
	TextObject mark_game1, mark_game2;
	mark_game1.SetColor(TextObject::WHITE_TEXT);
	mark_game2.SetColor(TextObject::WHITE_TEXT);

	ImpTimer time_bat_tu1;  //xu ly thoi gian bất tử cho nhan vat 
	ImpTimer time_bat_tu2;   

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

		p_player1.DoPlayer(map_data);    // xử lý di chuyển và va chạm
		p_player2.DoPlayer(map_data);    // xử lý di chuyển và va chạm

		p_player1.HandleBullet(g_screen);  // xử lý đạn 
		p_player2.HandleBullet(g_screen);  // xử lý đạn 

		p_player1.RemoveBullet(map_data,g_screen);
		p_player2.RemoveBullet(map_data,g_screen);

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

		// xử lý va cham bom-nguoi cho nhân vật 1 
		for (int r = 0; r < nobom_list1.size(); r++)
		{
				
				std::pair<NoBom, NoBom> no_bom = nobom_list1.at(r);

				NoBom doc = nobom_list1.at(r).first;
				NoBom ngang = nobom_list1.at(r).second;

				SDL_Rect tRect;

				tRect.x = p_player1.GetRect().x;
				tRect.y = p_player1.GetRect().y;
				tRect.w = p_player1.get_width_frame();
				tRect.h = p_player1.get_height_frame();



				SDL_Rect bRect_doc = doc.GetRect();
				SDL_Rect bRect_ngang = ngang.GetRect();

				bool bCol_doc = SDLCommonFunc::CheckCollision(bRect_doc, tRect);
				bool bCol_ngang = SDLCommonFunc::CheckCollision(bRect_ngang, tRect);

				SDL_RenderPresent(g_screen);
				if (p_player1.get_bat_tu() == false)
				{
					if (bCol_doc || bCol_ngang)
					{
						p_player1.Decrease_num_life();
						if ( p_player1.get_num_life() >= 1)
						{
							p_player1.set_pos2(185, 60);

							time_bat_tu1.start();   //

							p_player1.set_bat_tu(true);
							
							nobom_list1.erase(nobom_list1.begin() + r);

							//continue;
						}
						else
						{
							if (MessageBox(NULL, L"Game Over", L"Info", MB_OK | MB_ICONSTOP) == IDOK)
							{
								nobom_list1.erase(nobom_list1.begin() + r);
								close();
								SDL_Quit();
								return 0;
							}
						}
					}
				}

				if (time_bat_tu1.get_ticks() >= 3000)
				{
					p_player1.set_bat_tu(false);
				}	
		}
		if (time_bat_tu1.get_ticks() >= 3000) 
		{ 
			p_player1.set_bat_tu(false); 
		}	

		//xử lý chỉ số điểm cho nhân vật 1 
		std::string  val_str_mark1 = std::to_string(p_player1.get_mark());
		mark_game1.SetText(val_str_mark1);
		mark_game1.LoadFromRenderText(font_time, g_screen);
		mark_game1.RenderText(g_screen, 40, 122);

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


		// xử lý va cham bom-nguoi cho nhân vật 2
		for (int r = 0; r < nobom_list2.size(); r++)
		{

			std::pair<NoBom, NoBom> no_bom = nobom_list2.at(r);

			NoBom doc = nobom_list2.at(r).first;
			NoBom ngang = nobom_list2.at(r).second;

			SDL_Rect tRect;

			tRect.x = p_player2.GetRect().x;
			tRect.y = p_player2.GetRect().y;
			tRect.w = p_player2.get_width_frame();
			tRect.h = p_player2.get_height_frame();



			SDL_Rect bRect_doc = doc.GetRect();
			SDL_Rect bRect_ngang = ngang.GetRect();

			bool bCol_doc = SDLCommonFunc::CheckCollision(bRect_doc, tRect);
			bool bCol_ngang = SDLCommonFunc::CheckCollision(bRect_ngang, tRect);

			SDL_RenderPresent(g_screen);

			if (p_player2.get_bat_tu() == false)
			{
				if (bCol_doc || bCol_ngang)
				{
					p_player2.Decrease_num_life();
					if (p_player2.get_num_life() >= 1)
					{
						p_player2.set_pos2(185 + 14 * 45, 60);
						p_player2.set_bat_tu(true);
						time_bat_tu2.start();
						nobom_list2.erase(nobom_list2.begin() + r);

						//continue;
					}
					else
					{
						if (MessageBox(NULL, L"Game Over", L"Info", MB_OK | MB_ICONSTOP) == IDOK)
						{
							nobom_list2.erase(nobom_list2.begin() + r);
							close();
							SDL_Quit();
							return 0;
						}
					}
				}
			}
			if (time_bat_tu2.get_ticks() >= 3000)
			{
				p_player2.set_bat_tu(false);
			}
		}
		if (time_bat_tu2.get_ticks() >= 3000)
		{
			p_player2.set_bat_tu(false);
		}

		//xử lý chỉ số điểm cho nhân vật 2 
		std::string  val_str_mark2 = std::to_string(p_player2.get_mark());
		mark_game2.SetText(val_str_mark2);
		mark_game2.LoadFromRenderText(font_time, g_screen);
		mark_game2.RenderText(g_screen, 40, 242);

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
		if (val_time <= 0)        // tuc la het gio nhưng nhan vật vẫn còn mạng
		{
			if (MessageBox(NULL, L"Game Over", L"Info", MB_OK | MB_ICONSTOP) == IDOK)
			{
				quit = true;
				break;
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
		mark_game1.Free();
		mark_game2.Free();
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