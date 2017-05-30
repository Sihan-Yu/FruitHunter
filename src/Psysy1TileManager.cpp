#include "header.h"
#include "templates.h"
#include "JPGImage.h"


#include "BaseEngine.h"
#include "Psysy1Engine.h"
#include "Psysy1TileManager.h"


Psysy1TileManager::Psysy1TileManager(void)
	: TileManager(30,30)
{
	// Load the image file into an image object - at the normal size
	im2.LoadImage("heart.png");
	// Create a second image from the first, by halving the size
	im.ResizeFrom(&im2, 30, 30, true);
}


Psysy1TileManager::~Psysy1TileManager(void)
{
}

void Psysy1TileManager::DrawTileAt(
	BaseEngine* pEngine,
	SDL_Surface* pSurface,
	int iMapX, int iMapY,
	int iStartPositionScreenX, int iStartPositionScreenY) const
{
	// Base class implementation just draws some grey tiles
	im.RenderImageWithMask(pEngine->GetBackground(),
		0, 0,
		iStartPositionScreenX + GetTileWidth() - 1,
		iStartPositionScreenY + GetTileHeight() - 1,
		im.GetWidth(), im.GetHeight());
}