#include "BaseObject.h"

BaseObject::BaseObject() {
	p_object = NULL;
	rect.x = 0;
	rect.y = 0;
	rect.w = 0;
	rect.h = 0;
}

BaseObject :: ~BaseObject() {
	Free();
}

bool BaseObject::LoadImg(std::string path, SDL_Renderer* screen) {
	Free();
	SDL_Texture* new_texture = NULL;
	SDL_Surface* surface = IMG_Load(path.c_str());
	if (surface != NULL) {
		SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, COLOR_KEY_R, COLOR_KEY_G, COLOR_KEY_B));
		new_texture = SDL_CreateTextureFromSurface(screen, surface);
		if (new_texture != NULL) {
			rect.w = surface->w;
			rect.h = surface->h;
		}
		SDL_FreeSurface(surface);

	}
	p_object = new_texture;
	return p_object != NULL;
}

void BaseObject::Render(SDL_Renderer* des, const SDL_Rect* clip) {
	SDL_Rect renderquad = { rect.x, rect.y ,rect.w ,rect.h };
	SDL_RenderCopy(des, p_object, clip, &renderquad);
}

void BaseObject::Free() {
	if (p_object != NULL) {
		SDL_DestroyTexture(p_object);
		p_object = NULL;
		rect.w = 0;
		rect.h = 0;
	}
}