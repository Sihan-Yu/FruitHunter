#include "header.h"
#include "templates.h"

#include "Psysy1Spider.h"
#include "Psysy1Basket.h"
#include "Psysy1Engine.h"
#include "JPGImage.h"

int Psysy1Spider::spiderLives = 3;

Psysy1Spider::Psysy1Spider(Psysy1Engine* pEngine)
	: DisplayableObject(pEngine)
	, m_pMainEngine(pEngine)
{
	// The ball coordinate will be the centre of the ball.
	m_iStartDrawPosX = 0;
	m_iStartDrawPosY = 0;

	// Record the ball size as both height and width
	m_iDrawWidth = 80;
	m_iDrawHeight = 80;

	m_iCurrentScreenX = rand() % 521;
	m_iCurrentScreenY = 0;

	spiderIm.LoadImage("spider.png");
	spiderIm2.ResizeFrom(&spiderIm, 80, 80, true);

	scored = false;
	scoreAdded = false;
	moveFinished = false;

	xSpeed = 1;

	SetVisible(true);
}

Psysy1Spider::~Psysy1Spider(void)
{
}

void Psysy1Spider::Draw()
{
	if (!IsVisible())
		return;

	spiderIm2.RenderImageWithMask(m_pMainEngine->GetForeground(),
		0, 0,
		m_iCurrentScreenX,
		m_iCurrentScreenY,
		spiderIm2.GetWidth(), spiderIm2.GetHeight());

	// Store the position at which the object was last drawn
	StoreLastScreenPositionForUndraw();
}


void Psysy1Spider::DoUpdate(int iCurrentTime)
{
	// if movement finish then set visible false
	if (moveFinished)
		SetVisible(false);
	else
		SetVisible(true);


	if (spiderLives <= 0)
	{
		moveFinished = true;
	}
		
		
	// get current basket position
	DisplayableObject* basket = m_pMainEngine->GetDisplayableObject(0);
	int basket_position = basket->GetXCentre();

	// AI to decide the spider's moving derection
	if ((m_pMainEngine->GetTime() % 3) == 0 && !moveFinished && m_iCurrentScreenY < 350)
		m_iCurrentScreenY+=1;
	if ((m_pMainEngine->GetTime() % 3) == 0 && !moveFinished && m_iCurrentScreenY >= 350)
		m_iCurrentScreenY+=2;
	if (m_iCurrentScreenX < basket_position - 40 && !moveFinished)
		m_iCurrentScreenX++;
	else if (m_iCurrentScreenX > basket_position - 40 && !moveFinished)
		m_iCurrentScreenX--;
	
	// if movement has finished
	if (m_iCurrentScreenY == 700)
	{
		moveFinished = true;
		endtime = iCurrentTime;

		if (m_iCurrentScreenX > (basket_position - 90) && m_iCurrentScreenX < (basket_position + 30) && iCurrentTime == endtime)
			scored = true;

		if (scored && !scoreAdded)
		{
			Psysy1Engine::remainingLives = Psysy1Engine::remainingLives - 1;
			//record the fact that the score has been added
			scoreAdded = true;
		}
	}

	if (moveFinished)
	{
		// randomly set the spider (0-6seconds)
		if (iCurrentTime % 6000 == 0)
		{
			// initialise all variables
			spiderLives = 3;
			m_iCurrentScreenY = 0;
			m_iCurrentScreenX = rand() % 521;
			scored = false;
			scoreAdded = false;
			moveFinished = false;
		}
		
	}
	// Ensure that the object gets redrawn on the display, if something changed
	RedrawObjects();
}


bool Psysy1Spider::IfDead()
{
	return moveFinished;
}