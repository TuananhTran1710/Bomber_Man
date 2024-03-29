#include "game_map.h"
#include "BaseObject.h"
#include "CommonFunc.h"
#include "MainObject.h"
#include "ImpTimer.h"

BaseObject g_background;
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
	MainObject p_player;
	p_player.LoadImg("map1/right.png", g_screen);  // mac dinh cho ban dau nhan vat quay ve ben phai 
	p_player.set_clips();
	//


	bool quit = 0;
	Map map_data = map.getMap();

	while (!quit)
	{

		fps_timer.start();

		while (SDL_PollEvent(&g_event) != 0) {
			if (g_event.type == SDL_QUIT) {
				quit = 1;
			}
			p_player.HandleInputAction(g_event, g_screen, map_data);
			map.SetMap(map_data);
		}

		SDL_SetRenderDrawColor(g_screen, COLOR_R, COLOR_G, COLOR_B, 255);
		SDL_RenderClear(g_screen);
		g_background.Render(g_screen, NULL);

		// xu ly map 
		map_data = map.getMap();
		map.DrawMap(g_screen);


		p_player.DoPlayer(map_data);    // xử lý di chuyển và va chạm
		p_player.HandleBullet(g_screen);  // xử lý đạn 
		p_player.RemoveBullet(map_data);
		map.SetMap(map_data);

		p_player.Show(g_screen); // bản chất hàm này mỗi lần chỉ load 1 frame, nhưng vì chương trình chạy nhanh quá nên không thể nhìn rõ từng frame 
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