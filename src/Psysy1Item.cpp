#include "header.h"
#include "templates.h"

#include "Psysy1Item.h"
#include "Psysy1Basket.h"
#include "Psysy1Engine.h"
#include "JPGImage.h"


Psysy1Item::Psysy1Item(Psysy1Engine* pEngine, char* fileName)
	: DisplayableObject(pEngine)
	, m_pMainEngine(pEngine)
{
	// The ball coordinate will be the centre of the ball.
	m_iStartDrawPosX = 0;
	m_iStartDrawPosY = 0;

	// Record the ball size as both height and width
	m_iDrawWidth = 60;
	m_iDrawHeight = 60;

	fruitIm.LoadImage(fileName);
	fruitIm2.ResizeFrom(&fruitIm, 60, 60, true);

	scored = false;
	scoreAdded = false;

	SetVisible(true);
}

Psysy1Item::~Psysy1Item(void)
{
}

void Psysy1Item::Draw()
{
	if (!IsVisible())
		return;

	if (m_iCurrentScreenY < 700){
		fruitIm2.RenderImageWithMask(m_pMainEngine->GetForeground(),
			0, 0,
			m_iCurrentScreenX,
			m_iCurrentScreenY,
			fruitIm2.GetWidth(), fruitIm2.GetHeight());
	}

	// Store the position at which the object was last drawn
	StoreLastScreenPositionForUndraw();
}

// Allows a caller to specify where the object will move from and to and when
void Psysy1Item::SetMovement(int iStartTime, int iEndTime, int iCurrentTime,
	int iStartX, int iStartY, int iEndX, int iEndY)
{
	m_oMovement.Setup(iStartX, iStartY, iEndX, iEndY, iStartTime, iEndTime);
	m_oMovement.Calculate(iCurrentTime);
	m_iCurrentScreenX = m_oMovement.GetX();
	m_iCurrentScreenY = m_oMovement.GetY();
}

void Psysy1Item::DoUpdate(int iCurrentTime)
{
	// Ensure that the object gets redrawn on the display, if something changed
	RedrawObjects();
}


void Psysy1Item::AddScore()
{
	Psysy1Engine::score = Psysy1Engine::score + 100;
	Psysy1Engine::fruitNum++;
}