#pragma once
#include "displayableobject.h"
#include "MovementPosition.h"
#include "JPGImage.h"
#include "Psysy1Item.h"

class Psysy1Engine;


class Psysy1Fruit :
	public Psysy1Item
{
public:
	Psysy1Fruit(Psysy1Engine* pEngine, char* fileName);

	void Draw();
	void DoUpdate(int iCurrentTime);
	void explosionEffect();

private:
	ImageData explosionIm, explosionIm2;
	int xImage , yImage ;
	bool boomed;
};