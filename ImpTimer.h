#ifndef IMP_TIMER_H_
#define IMG_TIMER_H_

class ImpTimer
{
public:
	ImpTimer();
	~ImpTimer();
	// chu y : g?c th?i gian l� l�c SDL ???c kh?i t?o  
	void start();   // h�m n�y ?? c?p nh?t start_tick trong m?i v�ng while ? main.cpp
	void stop();
	void paused();   // h�m n�y ?? c?p nh?t paused_tick
	void unpaused();

	int get_ticks();

	bool is_started();
	bool is_paused();
private:
	int start_tick;  // luu thoi gian tu luc SDL bat dau dc khoi tao
	int paused_tick;  // thoi diem pause lai  

	bool is_pause;
	bool is_start;
};

#endif