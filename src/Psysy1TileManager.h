#pragma once
#include "TileManager.h"
#include "JPGImage.h"

class Psysy1TileManager :
	public TileManager
{

public:
	Psysy1TileManager();
	~Psysy1TileManager();
	virtual void DrawTileAt(
		BaseEngine* pEngine,
		SDL_Surface* pSurface,
		int iMapX, int iMapY,
		int iStartPositionScreenX, int iStartPositionScreenY)const;

private:
	ImageData im, im2;
};

