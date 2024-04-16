#include "BulletObject.h"

BulletObject::BulletObject() {
	bullet_time = 0;
	is_move = false;
	bullet_type = BOM;
}




void BulletObject::LoadImgBullet(SDL_Renderer* des)
{
	if (bullet_type == MIN)
	{
		LoadImg("map1/min.png", des);
	}
	else
	{
		LoadImg("map1/bom.png", des);
	}
}

