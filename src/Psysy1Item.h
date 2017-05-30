#pragma once
#include "displayableobject.h"
#include "MovementPosition.h"
#include "JPGImage.h"

class Psysy1Engine;


class Psysy1Item :
	public DisplayableObject
{
public:
	Psysy1Item(Psysy1Engine* pEngine, char* fileName);
	~Psysy1Item(void);

	void Draw();
	void SetMovement(int iStartTime, int iEndTime, int iCurrentTime,
		int iStartX, int iStartY, int iEndX, int iEndY);
	void DoUpdate(int iCurrentTime);
	void AddScore();

protected:
	/** Movement position calculator - give it start and end position and times
	and it works out current position for the current time. */
	MovementPosition m_oMovement;
	Psysy1Engine* m_pMainEngine;
	bool scored;
	bool scoreAdded;
	ImageData fruitIm, fruitIm2;
};