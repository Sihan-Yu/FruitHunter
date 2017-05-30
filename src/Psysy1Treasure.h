#pragma once
#include "displayableobject.h"
#include "MovementPosition.h"
#include "JPGImage.h"
#include "Psysy1Item.h"

class Psysy1Engine;


class Psysy1Treasure :
	public Psysy1Item
{
public:
	Psysy1Treasure(Psysy1Engine* pEngine, char* fileName);
	void DoUpdate(int iCurrentTime);
	void AddScore();
};