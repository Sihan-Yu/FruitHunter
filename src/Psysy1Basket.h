#pragma once
#include "displayableobject.h"
#include "JPGImage.h"

class Psysy1Engine;


class Psysy1Basket :
	public DisplayableObject
{
public:

	Psysy1Basket(Psysy1Engine* pEngine);
	~Psysy1Basket(void);

	void Draw();
	void DoUpdate(int iCurrentTime);

private:
	Psysy1Engine* m_pMainEngine;

	ImageData basketIm, basketIm2;
};
