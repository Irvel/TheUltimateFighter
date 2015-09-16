#ifndef Carlos
#define Carlos
//////////////////////////////////////////////////////////////////////////////
//                              Functions                                   //
//////////////////////////////////////////////////////////////////////////////


void jump(sprite &sSprite)
{
	if (sSprite.bIsJumping)
	{
		if (sSprite.iRow >= (sSprite.iInitPlace - 30) && sSprite.bIsFalling == false)
		{
			sSprite.iCurrentAnimation = 0;
			print(sSprite);
			sSprite.iRow-=3;
			backUp(sSprite);
			sSprite.iCurrentAnimation = 3;
			if(sSprite.bIsToTheRight)
				horizontalFlip(sSprite);
			else
				print(sSprite);
			delay(40);
		}
		else if (sSprite.iRow < sSprite.iInitPlace)
		{
			sSprite.bIsFalling = true;
			sSprite.iCurrentAnimation = 0;
			print(sSprite);
			sSprite.iRow+=3;
			backUp(sSprite);
			sSprite.iCurrentAnimation = 3;
			if(sSprite.bIsToTheRight)
				horizontalFlip(sSprite);
			else
				print(sSprite);
			delay(40);
		}
		else{
			sSprite.bIsJumping = false;
			sSprite.bIsFalling = false;
		}
	}
	else{
		if (sSprite.iRow+1 < sSprite.iInitPlace){
			sSprite.bIsFalling = true;
			sSprite.iCurrentAnimation = 0;
			print(sSprite);
			sSprite.iRow+=3;
			backUp(sSprite);
			sSprite.iCurrentAnimation = 3;
			if(sSprite.bIsToTheRight)
				horizontalFlip(sSprite);
			else
				print(sSprite);
			delay(40);
		}
		else{
			sSprite.bIsFalling = false;
		}
	}
}
#endif