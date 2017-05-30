#include "header.h"
#include "templates.h"

#include "Psysy1Candy.h"
#include "Psysy1Basket.h"
#include "Psysy1Spider.h"
#include "Psysy1Engine.h"
#include "JPGImage.h"


Psysy1Candy::Psysy1Candy(Psysy1Engine* pEngine)
	: DisplayableObject(pEngine)
	, m_pMainEngine(pEngine)
{
	// The ball coordinate will be the centre of the ball.
	m_iStartDrawPosX = 0;
	m_iStartDrawPosY = 0;

	// Record the ball size as both height and width
	m_iDrawWidth = 40;
	m_iDrawHeight = 40;

	DisplayableObject* basket = m_pMainEngine->GetDisplayableObject(0);
	// fire candy at specific coordinates
	m_iCurrentScreenX = m_iPreviousScreenX = basket->GetXCentre() - 10;
	m_iCurrentScreenY = m_iPreviousScreenY = basket->GetYCentre() - 30;

	CandyIm.LoadImage("candy.png");
	CandyIm2.ResizeFrom(&CandyIm, 40, 40, true);

	SetVisible(true);
}

Psysy1Candy::~Psysy1Candy(void)
{
}

void Psysy1Candy::Draw()
{
	// Do not draw if it should not be visible
	if (!IsVisible())
		return;

	CandyIm2.RenderImageWithMask(m_pMainEngine->GetForeground(),
		0, 0,
		m_iCurrentScreenX,
		m_iCurrentScreenY,
		CandyIm2.GetWidth(), CandyIm2.GetHeight());

	// Store the position at which the object was last drawn
	StoreLastScreenPositionForUndraw();
}

void Psysy1Candy::DoUpdate(int iCurrentTime)
{
	// Change position if player presses a key
	if (m_iCurrentScreenY > 0)
		m_iCurrentScreenY--;
	if (m_iCurrentScreenY <= 0)
	{
		m_iCurrentScreenX = -100;
		m_iCurrentScreenY = -100;
		SetVisible(false);
	}
	
	// get current spider coordinate
	DisplayableObject* spider = m_pMainEngine->GetDisplayableObject(8);
	int spiderX = spider->GetXCentre();
	int spiderY = spider->GetYCentre();
	
	// if there is a collision
	if (m_iCurrentScreenX >= (spiderX - 60) && m_iCurrentScreenX <= (spiderX + 20) && m_iCurrentScreenY >= (spiderY - 30) && m_iCurrentScreenY <= (spiderY) && !dynamic_cast<Psysy1Spider*>(spider)->IfDead())
	{
		m_iCurrentScreenY = -100;
		Psysy1Spider::spiderLives--;
		SetVisible(false);
	}
	
	// Ensure that the object gets redrawn on the display, if something changed
	RedrawObjects();
}