#include "ImpTimer.h"
#include "CommonFunc.h"

ImpTimer::ImpTimer() {
	start_tick = 0;
	paused_tick = 0;
	is_pause = false;
	is_start = false;
}

ImpTimer :: ~ImpTimer() {

}

void ImpTimer::start() {  //  lay thoi diem chuong trinh 
	is_start = true;
	is_pause = false;
	start_tick = SDL_GetTicks(); // SDL_Gettick trả về thoi diem tu luc SDL dc khoi tao
	// => start_tick lien tuc duoc cap nhap sau moi vòng while 

}                                                  


void ImpTimer::stop() {     // ??
	is_pause = 0;
	is_start = 0;
}

void ImpTimer::paused() {
	if (is_start == 1 && is_pause == 0) {
		is_pause = 1;
		paused_tick = SDL_GetTicks() - start_tick; // lấy thời điểm dừng
	}
}

void ImpTimer::unpaused() {
	if (is_pause == 1) {
		is_pause = 0;
		start_tick = SDL_GetTicks() - paused_tick;
		paused_tick = 0;
	}
}

int ImpTimer::get_ticks()
{
	if (is_start == true) {
		if (is_pause == true) {
			return paused_tick;
		}
		else {
			return SDL_GetTicks() - start_tick;
		}
	}
	return 0;
}


bool ImpTimer::is_started() {
	return is_start;
}

bool ImpTimer::is_paused() {
	return is_pause;
}