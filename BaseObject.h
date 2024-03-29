#ifndef BASE_OBJECT_H_
#define BASE_OBJECT_H_

#include "CommonFunc.h"

class BaseObject
{
public:
	BaseObject();
	~BaseObject();
	void SetRect(const int& x, const int& y) {
		rect.x = x;
		rect.y = y;
	}
	SDL_Rect GetRect() { return rect; }
	SDL_Texture* GetObject() { return p_object; }
	virtual bool LoadImg(std::string path, SDL_Renderer* screen);
	void Render(SDL_Renderer* des, const SDL_Rect* clip = NULL);
	void Free();

protected:
	SDL_Texture* p_object;
	SDL_Rect rect;
};


#endif