#include "header.h"
#include "templates.h"

#include "Psysy1Fruit.h"
#include "Psysy1Basket.h"
#include "Psysy1Engine.h"
#include "Psysy1Item.h"
#include "JPGImage.h"


Psysy1Fruit::Psysy1Fruit(Psysy1Engine* pEngine, char* fileName)
	: Psysy1Item(pEngine, fileName)
{
	// The ball coordinate will be the centre of the ball.
	m_iStartDrawPosX = 0;
	m_iStartDrawPosY = 0;

	// Record the ball size as both height and width
	m_iDrawWidth = 60;
	m_iDrawHeight = 60;

	xImage = 0, yImage = 0;
	explosionIm.LoadImage("explosion.png");
	explosionIm2.ResizeFrom(&explosionIm, 540, 540, true);

	fruitIm.LoadImage(fileName);
	fruitIm2.ResizeFrom(&fruitIm, 60, 60, true);

	scored = false;
	scoreAdded = false;
	boomed = false;

	SetVisible(true);
}

void Psysy1Fruit::Draw()
{
	if (!IsVisible())
		return;

	// if the movement do not finish
	if (m_iCurrentScreenY < 700){
		fruitIm2.RenderImageWithMask(m_pMainEngine->GetForeground(),
			0, 0,
			m_iCurrentScreenX,
			m_iCurrentScreenY,
			fruitIm2.GetWidth(), fruitIm2.GetHeight());
	}
	// if not scored then display the explosion effect
	else if (!scored){
		if (yImage == 9)
		{
			xImage = 0;
			yImage = 0;
			
		}
		if (!boomed)
			explosionEffect();// just explode once
	}
	
	// Store the position at which the object was last drawn
	StoreLastScreenPositionForUndraw();
}


void Psysy1Fruit::DoUpdate(int iCurrentTime)
{
	// If movement has finished 
	if (m_oMovement.HasMovementFinished(iCurrentTime))
	{
		// initialise variables
		scored = false;
		scoreAdded = false;
		boomed = false;
		int dropPosition = rand() % 541;

		// change the drop speed
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
			this->SetMovement(iCurrentTime, iCurrentTime + 5400, iCurrentTime, dropPosition, 0, dropPosition, 721);
			break;
		}
		
	}

	// If it is in momvment
	if (!m_oMovement.HasMovementFinished(iCurrentTime))
	{
		m_oMovement.Calculate(iCurrentTime);
		if (m_oMovement.GetY() == 0)
			SetVisible(false);
		else{
			SetVisible(true);
			m_iCurrentScreenX = m_oMovement.GetX();
			m_iCurrentScreenY = m_oMovement.GetY();
			if (m_oMovement.GetY() == 700)
			{
				DisplayableObject* basket = m_pMainEngine->GetDisplayableObject(0);
				int basket_position = basket->GetXCentre();

				// if there is a collision
				if (m_iCurrentScreenX > (basket_position - 90) && m_iCurrentScreenX < (basket_position + 30))
				{
					scored = true;
				}

				if (scored && !scoreAdded){
					AddScore();
					
					// change the game level according to how many fruits have been caught
					switch (Psysy1Engine::fruitNum)
					{
					case 20:
						Psysy1Engine::level = 2;
						break;
					case 40:
						Psysy1Engine::level = 3;
						break;
					case 60:
						Psysy1Engine::level = 4;
						break;
					}

					//record the fact that the score has been added
					scoreAdded = true;
				}
				else if (!scored && !scoreAdded)
				{
					Psysy1Engine::remainingLives--;
					scoreAdded = true;
				}

			}
		}
	}
	// Ensure that the object gets redrawn on the display, if something changed
	RedrawObjects();
}

void Psysy1Fruit::explosionEffect(){
	
	if (yImage <9)
	{
		if (xImage<9){
			explosionIm2.RenderImageWithMask(m_pMainEngine->GetForeground(),
				xImage * 60, yImage * 60,
				m_iCurrentScreenX,
				m_iCurrentScreenY,
				60, 60);
			if (xImage == 8 )
				xImage = 0;
			
			else if (m_pMainEngine->GetTime() % 2 == 0)//every 2 ticks update
				xImage++;
		}
		if (xImage == 0 )
			yImage++;
	}
	if (yImage == 9)
	{
		boomed = true;
	}
	
}
