#include"game_map.h"


void GameMap::LoadMap(std::string path) {
	std::ifstream in;
	in.open(path.c_str());
	for (int i = 0; i < MAX_MAP_Y; i++) {
		for (int j = 0; j < MAX_MAP_X; j++) {
			in >> game_map.tile[i][j];
		}
	}
	in.close();
}

void GameMap::LoadTiles(SDL_Renderer* screen) {
	char file_img[30];
	FILE* fp = NULL;
	for (int i = 0; i < MAX_TILE; i++) {
		sprintf_s(file_img, "map1/%d.png", i);
		fopen_s(&fp, file_img, "rb");
		if (fp == NULL) {
			continue;
		}
		fclose(fp);
		tile_mat[i].LoadImg(file_img, screen);
	}
}

void GameMap::DrawMap(SDL_Renderer* screen) {


	int x1 = 185, x2 = 852, y1 = 15, y2 = 690;

	int map_x = 0, map_y = 0;

	for (int i = y1; i < y2; i += TILE_SIZE) {

		map_x = 0;

		for (int j = x1; j < x2; j += TILE_SIZE) {
			int val = game_map.tile[map_y][map_x];

			if (val >= 0) {
				tile_mat[val].SetRect(j, i);
				tile_mat[val].Render(screen);
			}
			map_x++;
		}
		map_y++;
	}
}