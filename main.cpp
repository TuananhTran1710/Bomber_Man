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
		font_time = TTF_OpenFont("font/dlxfont_.ttf", 15);
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
	//


	bool quit = 0;
	int num_die = 0; // lưu số mạng của nhân vật

	//Time Text ;
	TextObject time_game;
	time_game.SetColor(TextObject::WHITE_TEXT);
	
	//
	TextObject mark_game;
	mark_game.SetColor(TextObject::WHITE_TEXT);
	UINT mark_value = 0;

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
		
		std::vector <std::pair<NoBom, NoBom>> nobom_list1 = p_player1.get_no_bom_list();
		std::vector <std::pair<NoBom, NoBom>> nobom_list2 = p_player2.get_no_bom_list();
		for (int r = 0; r < nobom_list1.size(); r++)
		{
			std::pair<NoBom, NoBom> no_bom = nobom_list1.at(r);
			 
			NoBom doc1 = nobom_list1.at(r).first;
			NoBom ngang1 = nobom_list1.at(r).second; 
			
			SDL_Rect tRect;
			tRect.x = p_player1.GetRect().x;
			tRect.y = p_player1.GetRect().y;
			tRect.w = p_player1.get_width_frame();
			tRect.h = p_player1.get_height_frame();
				
			SDL_Rect bRect_doc1 = doc1.GetRect();
			SDL_Rect bRect_ngang1 = ngang1.GetRect();

			bool bCol_doc1 = SDLCommonFunc::CheckCollision(bRect_doc1, tRect);
			bool bCol_ngang1 = SDLCommonFunc::CheckCollision(bRect_ngang1, tRect);
			SDL_RenderPresent(g_screen);
			if (bCol_doc1 || bCol_ngang1)
			{
				num_die++;
				if (num_die <= 3)
				{
					p_player1.set_pos2(185, 60);
					p_player1.Render(g_screen);
					SDL_RenderPresent(g_screen);
					nobom_list1.erase(nobom_list1.begin() + r);
					continue;
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

		//Show game time;
		time_game.SetColor(TextObject::WHITE_TEXT);
		std::string str_time = "Time: ";
		Uint32 time_val = SDL_GetTicks() / 1000;
		Uint32 val_time = 180 - time_val;
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
			time_game.RenderText(g_screen, SCREEN_WIDTH - 200, 15);
		}

		time_game.Free();  // giải phóng cho đỡ tốn bộ nhớ


		//
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