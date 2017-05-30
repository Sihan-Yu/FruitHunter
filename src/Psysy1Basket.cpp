#include "header.h"

#include "Psysy1Basket.h"
#include "Psysy1Engine.h"
#include "JPGImage.h"

Psysy1Basket::Psysy1Basket(Psysy1Engine* pEngine)
	: DisplayableObject(pEngine)
	, m_pMainEngine(pEngine)
{
	// The ball coordinate will be the centre of the ball
	// Because we start drawing half the size to the top-left.
    m_iStartDrawPosX = 0;
	m_iStartDrawPosY = 0;

	// Record the ball size as both height and width
	m_iDrawWidth = 100;
	m_iDrawHeight = 80;

	// Out item at specific coordinates
	m_iCurrentScreenX = m_iPreviousScreenX = 250;
	m_iCurrentScreenY = m_iPreviousScreenY = 720;

	basketIm.LoadImage("basket.png");
	basketIm2.ResizeFrom(&basketIm, 100, 80,true);

	// And make it visible
	SetVisible(true);
}

Psysy1Basket::~Psysy1Basket(void)
{
}

void Psysy1Basket::Draw()
{
	// Do not draw if it should not be visible
	if (!IsVisible())
		return;

	basketIm2.RenderImageWithMask(m_pMainEngine->GetForeground(),
		0,0,
		m_iCurrentScreenX,
		m_iCurrentScreenY,
		basketIm2.GetWidth(), basketIm2.GetHeight());

	char text[100];
	sprintf(text, "%d", Psysy1Engine::fruitNum);
	m_pMainEngine->DrawScreenString(m_iCurrentScreenX + 40, m_iCurrentScreenY + 35, text, 0x008000);

	// Store the position at which the object was last drawn
	StoreLastScreenPositionForUndraw();
}

void Psysy1Basket::DoUpdate(int iCurrentTime)
{
	// Change position if player presses a key
	if (GetEngine()->IsKeyPressed(SDLK_LEFT))
		m_iCurrentScreenX -= 3;
	if (GetEngine()->IsKeyPressed(SDLK_RIGHT))
		m_iCurrentScreenX += 3;

	if (m_iCurrentScreenX < 0)
		m_iCurrentScreenX = 0;
	if (m_iCurrentScreenX >= GetEngine()->GetScreenWidth() - 100)
		m_iCurrentScreenX = GetEngine()->GetScreenWidth() - 100;

	// Ensure that the object gets redrawn on the display, if something changed
	RedrawObjects();
}
