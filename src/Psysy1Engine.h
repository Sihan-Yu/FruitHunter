#pragma once
#include "BaseEngine.h"
#include "TileManager.h"
#include "Psysy1TileManager.h"
#include "JPGImage.h"
#include <list>

class Psysy1Fruit;
class Psysy1Treasure;
class Psysy1Spider;
class Psysy1Candy;


class Psysy1Engine :
	public BaseEngine
{

public:
	Psysy1Engine();
	~Psysy1Engine();
	virtual void SetupBackgroundBuffer();
	virtual void scrollingBackground();
	virtual int InitialiseObjects();
	virtual void DrawStringsOnTop();
	virtual void UnDrawStrings();
	virtual void GameAction();
	virtual void UndrawObjects();
	virtual void DrawObjects();
	virtual void MouseDown(int iButton, int iX, int iY);
	virtual void KeyDown(int iKeyCode);
	virtual void StoreScore();
	virtual void GetScore();

public:
	// State number
	enum State { stateInit, stateHelp, stateMain, statePaused, stateOver };
	static int remainingLives;
	static int score;
	static int level;
	static int fruitNum;

private:
	int m_iPauseStarted;
	// game start time
	int imCoordinate;
	int m_iStartTime;
	ImageData imBackground, imBuffer, imInitBackground, imStartButton, imPlayAgainButton, imPaused, imContinue, imOver, imInstruction, imBack;
	Psysy1Fruit* fruit[6];
	Psysy1Treasure* treasure;
	Psysy1Spider* spider;
	Psysy1Candy* candy;
	State m_state;
	bool scoreStored;
	std::list<int> scoreTable;
	Psysy1TileManager m_oTiles;
};

