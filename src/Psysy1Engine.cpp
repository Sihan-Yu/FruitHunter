#include "header.h"
#include "templates.h"
#include "JPGImage.h"

#include "BaseEngine.h"
#include "Psysy1Engine.h"
#include "Psysy1Basket.h"
#include "Psysy1Item.h"
#include "Psysy1Fruit.h"
#include "Psysy1Treasure.h"
#include "Psysy1Spider.h"
#include "Psysy1Candy.h"
#include <sstream>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

#define NUMBER_OF_LIVES 5

int Psysy1Engine::remainingLives = NUMBER_OF_LIVES;
int Psysy1Engine::score = 0;
int Psysy1Engine::level = 1;
int Psysy1Engine::fruitNum = 0;

Psysy1Engine::Psysy1Engine()
	: BaseEngine(50)
	, m_state(stateInit)
{
	imCoordinate = 0;
	// Load all the image files into image objects, and resize to specific size
	imBuffer.LoadImage("initBackground.png");
	imInitBackground.ResizeFrom(&imBuffer, 600, 800, true);
	imBuffer.LoadImage("background.png");
	imBackground.ResizeFrom(&imBuffer, 600, 3300, true);
	imBuffer.LoadImage("startButton.png");
	imStartButton.ResizeFrom(&imBuffer, 200, 100, true);
	imBuffer.LoadImage("back.png");
	imBack.ResizeFrom(&imBuffer, 70, 70, true);
	imBuffer.LoadImage("instruction.png");
	imInstruction.ResizeFrom(&imBuffer, 60, 60, true);
	imBuffer.LoadImage("playAgainButton.png");
	imPlayAgainButton.ResizeFrom(&imBuffer, 200, 100, true);
	imBuffer.LoadImage("pause.png");
	imPaused.ResizeFrom(&imBuffer, 70, 70, true);
	imBuffer.LoadImage("continue.png");
	imContinue.ResizeFrom(&imBuffer, 300, 100, true);
	imBuffer.LoadImage("game_over.png");
	imOver.ResizeFrom(&imBuffer, 400, 100, true);
}


Psysy1Engine::~Psysy1Engine()
{
}


void Psysy1Engine::SetupBackgroundBuffer()
{
	switch (m_state)
	{
	case stateInit: 
		FillBackground(0x808080);
		// initial background
		imInitBackground.RenderImageWithMask(this->GetBackground(),
			0, 0,
			0, 0,
			imInitBackground.GetWidth(), imInitBackground.GetHeight());
		// start button
		imStartButton.RenderImageWithMask(this->GetBackground(),
			0, 0,
			200, 500,
			imStartButton.GetWidth(), imStartButton.GetHeight());
		// help button
		imInstruction.RenderImageWithMask(this->GetBackground(),
			0, 0,
			500, 60,
			imInstruction.GetWidth(), imInstruction.GetHeight());
		// game name
		DrawBackgroundString(50, 170, "FRUIT HUNTER", 0x800080,
			GetFont("game.otf", 90));
		return;
	case stateHelp:
		FillBackground(0x808080);
		// initial background
		imInitBackground.RenderImageWithMask(this->GetBackground(),
			0, 0,
			0, 0,
			imInitBackground.GetWidth(), imInitBackground.GetHeight());
		// back button
		imBack.RenderImageWithMask(this->GetBackground(),
			0, 0,
			70, 60,
			imBack.GetWidth(), imBack.GetHeight());
		// game instructions
		DrawBackgroundString(80, 200, "Your task is to catch all the fruits", 0x000000,
			GetFont("Cornerstone Regular.ttf", 20));
		DrawBackgroundString(80, 250, "And defend the annoying spiders ", 0x000000,
			GetFont("Cornerstone Regular.ttf", 20));
		DrawBackgroundString(80, 300, "by shooting them or avoiding them", 0x000000,
			GetFont("Cornerstone Regular.ttf", 20));
		return;
	case stateMain:
		FillBackground(0x808080);
		scrollingBackground();// call the function to make the background scroll
		// using tile manager to display current remaining lives
		m_oTiles.SetBaseTilesPositionOnScreen(130, 70);
		m_oTiles.DrawAllTiles(this,
			this->GetBackground(),
			0, 0, remainingLives-1, 0);
		// pause button
		imPaused.RenderImageWithMask(this->GetBackground(),
			0, 0,
			480, 60,
			imPaused.GetWidth(), imPaused.GetHeight());
		break; 
	case statePaused:
		FillBackground(0x808080);
		scrollingBackground();// call the function to make the background scroll
		// continue button
		imContinue.RenderImageWithMask(this->GetBackground(),
			0, 0,
			150, 500,
			imContinue.GetWidth(), imContinue.GetHeight());
		// game paused text
		DrawBackgroundString(60, 100, "Game Paused", 0x000000,
			GetFont("game.otf", 80));
		break;
	case stateOver: 
		FillBackground(0x808080);
		// game over image
		imOver.RenderImageWithMask(this->GetBackground(),
			0, 0,
			100, 100,
			imOver.GetWidth(), imOver.GetHeight());
		// restart button
		imPlayAgainButton.RenderImageWithMask(this->GetBackground(),
			0, 0,
			200, 600,
			imPlayAgainButton.GetWidth(), imPlayAgainButton.GetHeight());
		return;
	} // End switch

}


void Psysy1Engine::scrollingBackground()
{
	// change the scrolling speed accroding to current game level
	switch (level)
	{
	case 1:
		if (GetModifiedTime() % 10 == 0)
			imCoordinate++;
		break;
	case 2:
		if (GetModifiedTime() % 7 == 0)
			imCoordinate++;
		break;
	case 3:
		if (GetModifiedTime() % 5 == 0)
			imCoordinate++;
		break;
	case 4:
		if (GetModifiedTime() % 3 == 0)
			imCoordinate++;
		break;
	}

	// let the background image scroll smoothly
	if (imCoordinate == 3300)
		imCoordinate = 0;
	else if (imCoordinate < 2500)
	{
		imBackground.RenderImageWithMask(this->GetBackground(),
			0, imCoordinate,
			0, 0,
			600, 800);
	}
	else if (imCoordinate >= 2500)
	{
		imBackground.RenderImageWithMask(this->GetBackground(),
			0, imCoordinate, // source 
			0, 0,			 // screen
			600, 3300 - imCoordinate);//size
		imBackground.RenderImageWithMask(this->GetBackground(),
			0, 0,
			0, 3300 - imCoordinate,
			600, imCoordinate - 2500);
	}
	
}


int Psysy1Engine::InitialiseObjects()
{
	// Reset variables for the next game
	remainingLives = NUMBER_OF_LIVES;
	score = 0;
	level = 1;
	fruitNum = 0;
	imCoordinate = 0;
	scoreStored = false;
	scoreTable.clear();
	SetTimeOffset(0);

	// Record the fact that we are about to change the array - so it doesn't get used elsewhere without reloading it
	DrawableObjectsChanged();

	// Destroy any existing objects
	DestroyOldObjects();

	// initialise all the item object
	fruit[0] = new Psysy1Fruit(this, "0.png");
	fruit[1] = new Psysy1Fruit(this, "1.png");
	fruit[2] = new Psysy1Fruit(this, "2.png");
	fruit[3] = new Psysy1Fruit(this, "3.png");
	fruit[4] = new Psysy1Fruit(this, "4.png");
	fruit[5] = new Psysy1Fruit(this, "5.png");
	treasure = new Psysy1Treasure(this, "6.png");
	spider = new Psysy1Spider(this);

	return 0;
}


void Psysy1Engine::UnDrawStrings()
{
	// Clear the top of the screen, since we about to draw text on it.
	CopyBackgroundPixels(0, 0, GetScreenWidth(), 800);
}


void Psysy1Engine::DrawStringsOnTop()
{
	// draw different text according to the game state
	switch (m_state)
	{
	case stateMain:
		char text[100];
		sprintf(text, "LEVEL %d", level);
		DrawScreenString(50, 40, text, 0x000000, NULL);
		DrawScreenString(50, 100, "LIVES:", 0x000000, NULL);
		sprintf(text, "SCORE: %d", score);
		DrawScreenString(50, 160, text, 0x000000, NULL);
		break;
	case stateOver:
		char final_text[100];
		sprintf(final_text, "Your Score: %d", score);
		DrawScreenString(150, 200, final_text, 0xffffff,
			GetFont("Cornerstone Regular.ttf", 30));
		DrawScreenRectangle(140, 280, 460, 580, 0xB0B0B0);
		DrawScreenString(175, 300, "Top ten score", 0xffffff,
			GetFont("Cornerstone Regular.ttf", 30));
		GetScore();
		for (int i = 0; i < 10; i++)
		{
			if (!scoreTable.empty())
			{
				sprintf(final_text, "%d.  %d", i+1, scoreTable.back());
				scoreTable.pop_back();
			}
			else
				sprintf(final_text, "%d. no data", i+1);

			DrawScreenString(270, 350 + 22 * i, final_text, 0xffffff,
				GetFont("game.otf", 17));
		}
		break;
	}
	
}


void Psysy1Engine::GameAction()
{
	if (!IsTimeToAct()) 
		return;
	// Don't act for another 1 tick - this is a difference from the base class
	SetTimeToAct(1);

	// after all item have been droped
	if (remainingLives <= 0)
	{
		// Destroy any existing objects
		DestroyOldObjects();
		if (!scoreStored)
		{
			StoreScore();
			scoreStored = true;
		}
		m_state = stateOver;// set state to over
		SetupBackgroundBuffer();
		Redraw(true);
	}

	switch (m_state)
	{
	case stateInit:
	case stateHelp:
	case stateOver:
		break;
	case statePaused:
		break;
	case stateMain:
		SetupBackgroundBuffer(); // background needs to scroll
		UpdateAllObjects(GetModifiedTime());
		break;
	}

}


void Psysy1Engine::MouseDown(int iButton, int iX, int iY)
{
	if (iButton == SDL_BUTTON_LEFT)
	{
		switch (m_state)
		{
		case stateInit:
			if (iX > 200 && iX < 400 && iY>500 && iY < 600)
			{
				// Go to state main
				m_state = stateMain;
				// record the start time
				m_iStartTime = GetTime();
				// Force redraw of background
				SetupBackgroundBuffer();
				// create the basket object
				StoreObjectInArray(0, new Psysy1Basket(this));
				// The LAST entry has to be NULL
				StoreObjectInArray(1, NULL);
				// fruit and diamond are both moving object, set the start time and position
				// and end time and position
				int dropPosition;

				for (int i = 0; i < 6; i++){
					dropPosition = rand() % 541;
					fruit[i]->SetMovement(m_iStartTime + 1200 * i, m_iStartTime + 1200 * i + 8400, m_iStartTime + 1200 * i, dropPosition, 0, dropPosition, 721);
					StoreObjectInArray(i + 1, fruit[i]);
				}

				dropPosition = rand() % 551;
				treasure->SetMovement(m_iStartTime + 1200 * 6, m_iStartTime + 1200 * 6 + 8400, m_iStartTime + 1200 * 6, dropPosition, 0, dropPosition, 721);
				StoreObjectInArray(7, treasure);

			    StoreObjectInArray(8, spider);
				// Redraw the whole screen now
				Redraw(true);
			}
			else if (iX > 500 && iX < 570 && iY > 60 && iY < 130)
			{
				// Go to state help
				m_state = stateHelp;
				SetupBackgroundBuffer();
				Redraw(true);
			}
			break;
		case stateHelp:
			if (iX > 70 && iX < 140 && iY > 60 && iY < 130)
			{
				// Go to state init
				m_state = stateInit;
				SetupBackgroundBuffer();
				Redraw(true);
			}
			break;
		case stateMain:
			if (iX > 480 && iX < 550 && iY> 60 && iY < 130)
			{
				// Go to state paused
				m_state = statePaused;
				m_iPauseStarted = GetTime();
				// Force redraw of background
				SetupBackgroundBuffer();
				// Redraw the whole screen now
				Redraw(true);
				break;
			}
			else
			{
				candy = new Psysy1Candy(this);
				StoreObjectInArray(9, candy);
			}
		case statePaused:
			if (iX > 150 && iX < 450 && iY>500 && iY < 600)
			{
				// Go to state main
				m_state = stateMain;
				IncreaseTimeOffset(m_iPauseStarted - GetTime());
				// Force redraw of background
				SetupBackgroundBuffer();
				// Redraw the whole screen now
				Redraw(true);
				break;
			}
		case stateOver:
			if (iX > 200 && iX < 400 && iY > 600 && iY < 700)
			{
				// go to initial state
				m_state = stateInit;
				// Create the moving objects
				InitialiseObjects();
				// Set up the initial background
				SetupBackgroundBuffer();
				Redraw(true);
				break;
			}
		}
	}
}


void Psysy1Engine::KeyDown(int iKeyCode)
{
	// NEW SWITCH on current state
	switch (iKeyCode)
	{
	case SDLK_ESCAPE: // End program when escape is pressed
		SetExitWithCode(0);
		break;
	case SDLK_SPACE:
		if (m_state == stateOver)
		{
			m_state = stateInit;
			// Create the moving objects
			InitialiseObjects();
			// Set up the initial background
			SetupBackgroundBuffer();
			Redraw(true);
			break;
		}
	}
}


void Psysy1Engine::UndrawObjects()
{
	if (m_state != stateInit) // Not in initialise state
		BaseEngine::UndrawObjects();
}


void Psysy1Engine::DrawObjects()
{
	if (m_state != stateInit) // Not in initialise state
		BaseEngine::DrawObjects();
}


void Psysy1Engine::StoreScore()
{
	// write score to the final of the file
	ofstream scoresFile("highscores.txt", ios::app);
	if (scoresFile.is_open())
	{
		scoresFile << score << endl;
		scoresFile.close();//close the file
	}
	else 
		cout << "Unable to open file";
}


void Psysy1Engine::GetScore()
{	
	// get all the scores with ascending order
	ifstream scoresFile("highscores.txt");
	char buffer[10];
	
	if (scoresFile.is_open())
	{
		while (!scoresFile.eof())
		{
			// store score to the list
			int num;
			scoresFile.getline(buffer,10);
			stringstream(buffer) >> num;
			scoreTable.push_back(num);
		}
		scoreTable.pop_back();// pop the last item because it appears twice
		scoresFile.close();//close the file
	}
	else
		cout << "Unable to open file";

	// sort the score table
	scoreTable.sort();
}