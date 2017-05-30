#include "header.h"
#include "templates.h"

#include "Psysy1Basket.h"
#include "Psysy1Engine.h"
#include "Psysy1Item.h"
#include "Psysy1Treasure.h"
#include "JPGImage.h"


Psysy1Treasure::Psysy1Treasure(Psysy1Engine* pEngine, char* fileName)
	: Psysy1Item(pEngine, fileName)
{
	// The ball coordinate will be the centre of the ball.
	m_iStartDrawPosX = 0;
	m_iStartDrawPosY = 0;

	// Record the ball size as both height and width
	m_iDrawWidth = 50;
	m_iDrawHeight = 50;

	fruitIm.LoadImage(fileName);
	fruitIm2.ResizeFrom(&fruitIm, 50, 50, true);

	scored = false;
	scoreAdded = false;

	SetVisible(true);
}


void Psysy1Treasure::DoUpdate(int iCurrentTime)
{
	// If movement has finished 
	if (m_oMovement.HasMovementFinished(iCurrentTime))
	{
		scored = false;
		scoreAdded = false;
		int dropPosition = rand() % 551;

		// increase the speed if the game level up
		switch (Psysy1Engine::level)
		{
		case 1:
			this->SetMovement(iCurrentTime, iCurrentTime + 8400, iCurrentTime, dropPosition, 0, dropPosition, 721);
			break;
		case 2:
			this->SetMovement(iCurrentTime, iCurrentTime + 7000, iCurrentTime, dropPosition, 0, dropPosition, 721);
			break;
		case 3:
			this->SetMovement(iCurrentTime, iCurrentTime + 5600, iCurrentTime, dropPosition, 0, dropPosition, 721);
			break;
		case 4:
			this->SetMovement(iCurrentTime, iCurrentTime + 4200, iCurrentTime, dropPosition, 0, dropPosition, 721);
			break;
		}

	}

	// If it is in momvment
	if (!m_oMovement.HasMovementFinished(iCurrentTime))
	{
		m_oMovement.Calculate(iCurrentTime);
		if (m_oMovement.GetY() == 0){
			SetVisible(false);
		}
		else{
			SetVisible(true);
			m_iCurrentScreenX = m_oMovement.GetX();
			m_iCurrentScreenY = m_oMovement.GetY();
			if (m_oMovement.GetY() == 700) // if movement is over
			{
				DisplayableObject* basket = m_pMainEngine->GetDisplayableObject(0);
				int basket_position = basket->GetXCentre();// get the current basket position

				if (m_iCurrentScreenX > (basket_position - 80) && m_iCurrentScreenX < (basket_position + 20))
				{
					scored = true;
				}

				if (scored && !scoreAdded){

					AddScore();

					//record the fact that the score has been added
					scoreAdded = true;
				}
				else if (!scored && !scoreAdded)
				{
					scoreAdded = true;
				}

			}
		}
	}
	// Ensure that the object gets redrawn on the display, if something changed
	RedrawObjects();
}


void Psysy1Treasure::AddScore()
{
	// add 300 points
	Psysy1Engine::score = Psysy1Engine::score + 300;
}