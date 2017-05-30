#pragma once
#include "displayableobject.h"
#include "MovementPosition.h"
#include "JPGImage.h"

class Psysy1Engine;


class Psysy1Candy :
	public DisplayableObject
{
public:
	Psysy1Candy(Psysy1Engine* pEngine);
	~Psysy1Candy(void);

	void Draw();
	void DoUpdate(int iCurrentTime);
	bool IfCollision();

private:
	Psysy1Engine* m_pMainEngine;
	ImageData CandyIm, CandyIm2;
	bool hit;
};