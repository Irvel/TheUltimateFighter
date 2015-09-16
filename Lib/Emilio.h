#ifndef Emilio
#define Emilio
//////////////////////////////////////////////////////////////////////////////
//                              Functions                                   //
//////////////////////////////////////////////////////////////////////////////

void attack1(sprite &sSprite)
{
if(sSprite.bIsToTheRight == true)
 {
	sSprite.iCurrentAnimation=0;
	print(sSprite);
	sSprite.iWidth=41;
	sSprite.iRow=sSprite.iRow-2;
	sSprite.iColumn= sSprite.iColumn-5;
	backUp(sSprite);
	sSprite.iCurrentAnimation=1;
	horizontalFlip(sSprite);
	delay(100);
	sSprite.iCurrentAnimation=0;
	print(sSprite);
	sSprite.iCurrentAnimation=2;
	sSprite.iWidth=25;
	sSprite.iRow=sSprite.iRow+2;
	sSprite.iColumn=sSprite.iColumn+5;
	backUp(sSprite);
	horizontalFlip(sSprite);
	}
else{
	sSprite.iCurrentAnimation=0;
	print(sSprite);
	sSprite.iWidth=41;
	sSprite.iRow=sSprite.iRow-2;
	sSprite.iColumn= sSprite.iColumn-5;
	backUp(sSprite);
	sSprite.iCurrentAnimation=1;
	print(sSprite);
	delay(60);
	sSprite.iCurrentAnimation=0;
	print(sSprite);
	sSprite.iCurrentAnimation=2;
	sSprite.iWidth=25;
	sSprite.iRow=sSprite.iRow+2;
	sSprite.iColumn=sSprite.iColumn+5;
	backUp(sSprite);
	print(sSprite);

	}
}

void attack2(sprite &sSprite)
{
if(sSprite.bIsToTheRight == true)
 {
	sSprite.iCurrentAnimation=0;
	print(sSprite);
	sSprite.iWidth=30;
	backUp(sSprite);
	sSprite.iCurrentAnimation=1;
	horizontalFlip(sSprite);
	delay(100);
	sSprite.iCurrentAnimation=0;
	print(sSprite);
	sSprite.iCurrentAnimation=2;
	sSprite.iWidth=25;
	horizontalFlip(sSprite);
	}
else{
	sSprite.iCurrentAnimation=0;
	print(sSprite);
	sSprite.iWidth=30;
	backUp(sSprite);
	sSprite.iCurrentAnimation=1;
	print(sSprite);
	delay(100);
	sSprite.iCurrentAnimation=0;
	print(sSprite);
	sSprite.iCurrentAnimation=2;
	sSprite.iWidth=25;
	print(sSprite);

	}
}


#endif