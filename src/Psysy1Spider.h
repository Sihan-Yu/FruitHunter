#pragma once
#include "displayableobject.h"
#include "MovementPosition.h"
#include "JPGImage.h"

class Psysy1Engine;


class Psysy1Spider :
	public DisplayableObject
{
public:
	Psysy1Spider(Psysy1Engine* pEngine);
	~Psysy1Spider(void);

	void Draw();
	void DoUpdate(int iCurrentTime);
	bool IfDead();
	
	static int spiderLives;

private:
	int xSpeed;
	Psysy1Engine* m_pMainEngine;
	bool scored;
	bool scoreAdded;
	bool moveFinished;
	ImageData spiderIm, spiderIm2;
	int endtime;
};