#include "header.h"
#include "templates.h"

#include "Psysy1MovingObject.h"
#include "Psysy1Engine.h"


Psysy1MovingObject::Psysy1MovingObject(Psysy1Engine* pEngine)
	: DisplayableObject(pEngine)
	, m_pMainEngine(pEngine)
{
	// The ball coordinate will be the centre of the ball
	// Because we start drawing half the size to the top-left.
	m_iStartDrawPosX = -50;
	m_iStartDrawPosY = -50;

	// Record the ball size as both height and width
	m_iDrawWidth = 100;
	m_iDrawHeight = 100;

	// Just put it somewhere initially
	m_iPreviousScreenX = m_iCurrentScreenX = 50 + rand() % 700;
	m_iPreviousScreenY = m_iCurrentScreenY = 50 + rand() % 500;

	m_iColour = GetEngine()->GetColour(rand() % 41);

	// And make it visible
	SetVisible(true);
}


Psysy1MovingObject::~Psysy1MovingObject()
{
}


void Psysy1MovingObject::Draw()
{
	// Do not draw if it should not be visible
	if (!IsVisible())
		return;

	m_pMainEngine->DrawScreenOval(
		m_iCurrentScreenX - 50,
		m_iCurrentScreenY - 50,
		m_iCurrentScreenX + 49,
		m_iCurrentScreenY + 49,
		m_iColour /*rand() % 0xffffff*/);

	// Store the position at which the object was last drawn
	// You MUST do this to ensure that the screen is updated when only drawing movable objects
	// This tells the system where to 'undraw' the object from
	StoreLastScreenPositionForUndraw();
}


// Allows a caller to specify where the object will move from and to and when
void Psysy1MovingObject::SetMovement(int iStartTime, int iEndTime, int iCurrentTime,
	int iStartX, int iStartY, int iEndX, int iEndY)
{
	m_oMovement.Setup(iStartX, iStartY, iEndX, iEndY, iStartTime, iEndTime);
	m_oMovement.Calculate(iCurrentTime);
	m_iCurrentScreenX = m_oMovement.GetX();
	m_iCurrentScreenY = m_oMovement.GetY();
}

/**
Handle the update action, moving the object and/or handling any game logic
*/
void Psysy1MovingObject::DoUpdate(int iCurrentTime)
{
	// Work out current position
	m_oMovement.Calculate(iCurrentTime);
	m_iCurrentScreenX = m_oMovement.GetX();
	m_iCurrentScreenY = m_oMovement.GetY();

	// If movement has finished then request instructions
	if (m_oMovement.HasMovementFinished(iCurrentTime))
	{
		m_oMovement.Reverse();
		m_oMovement.Calculate(iCurrentTime);
		m_iCurrentScreenX = m_oMovement.GetX();
		m_iCurrentScreenY = m_oMovement.GetY();
	}

	if (m_pTileManager->IsValidTilePosition(m_iCurrentScreenX, m_iCurrentScreenY))
	{
		int iTileX = m_pTileManager->GetTileXForPositionOnScreen(m_iCurrentScreenX);
		int iTileY = m_pTileManager->GetTileYForPositionOnScreen(m_iCurrentScreenY);
		int iCurrentTile = m_pTileManager->GetValue(iTileX, iTileY);
		m_pTileManager->UpdateTile(GetEngine(), iTileX, iTileY, iCurrentTile + 1);
	}

	// Ensure that the object gets redrawn on the display, if something changed
	RedrawObjects();
}