#ifndef Diego
#define Diego
//////////////////////////////////////////////////////////////////////////////
//                              Libraries                                   //
//////////////////////////////////////////////////////////////////////////////

	#include <dos.h>
	#include <conio.h>
	#include <fstream.h>
	#include <iostream.h>
	#include <string.h>
	#include <stdlib.h>



//////////////////////////////////////////////////////////////////////////////
//                              Functions                                   //
//////////////////////////////////////////////////////////////////////////////

//Allowing bool variables on the program
typedef enum {false=0, true} bool;

	struct sprite
	{
		unsigned short int iPixels[200][50];
		int iHeight;
		int iWidth;
		int iTransparentColor;
		int iNumberOfAnimations;
		int iCurrentAnimation;
		int iMovingAnimation;
		int iRow;
		int iColumn;
		int iHealth;
		int iInitPlace;
		bool bIsFalling;
		bool bIsASprite;
		bool bIsOnScreen;
		bool bIsToTheRight;
		bool bIsJumping;
		bool bIsAttacking;
	};

	void initSprite(sprite &sSprite, char cSprite[10], int iNumberOfAnimations, int iTransparentColor)
	{
		//Initializing Default propierties.
		sSprite.iCurrentAnimation = 2;
		sSprite.iInitPlace = 124;
		sSprite.iHealth = 10;
		sSprite.iMovingAnimation = 4;
		sSprite.bIsASprite = true;
		sSprite.bIsOnScreen = true;
		sSprite.bIsToTheRight = false;
		sSprite.bIsJumping = false;
		sSprite.bIsAttacking = false;
		sSprite.bIsFalling = false;
		sSprite.iTransparentColor = iTransparentColor;
		sSprite.iNumberOfAnimations = iNumberOfAnimations;
		//Initializing all the array with the transparent color for painting different width sprites.
		char cConcatenate[45];
		for(int iInitCounter=0; iInitCounter<45; iInitCounter++)
				cConcatenate[iInitCounter] = 0;
		char cStatus[1] = {0};
		fstream sprites;
			strcat(cConcatenate,"TUF_GAME/Content/Sprites/");
			strcat(cConcatenate,cSprite);
			strcat(cConcatenate,"/");
			strcat(cConcatenate,cSprite);
			strcat(cConcatenate,"1.DEF");
			sprites.open(cConcatenate, ios::in);
				sprites >> sSprite.iHeight;
				sSprite.iHeight++;
				sprites >> sSprite.iHeight;
				sSprite.iHeight++;
			sprites.close();
			for (int iPixelRow=0; iPixelRow < (sSprite.iHeight)*(sSprite.iNumberOfAnimations+1); iPixelRow++)
				for (int iPixelCol=0; iPixelCol < 50; iPixelCol++)
					sSprite.iPixels[iPixelRow][iPixelCol] = iTransparentColor;
			for(int iErraseCounter=0; iErraseCounter<45; iErraseCounter++)
				cConcatenate[iErraseCounter] = 0;
			cStatus[0] = 0;
		//Initializing Height, Width and Pixels Array.
		for(int iCurrentStatus = 1;	iCurrentStatus <= iNumberOfAnimations; iCurrentStatus++)
		{
			itoa(iCurrentStatus,cStatus,10);
			strcat(cConcatenate,"TUF_GAME/Content/Sprites/");
			strcat(cConcatenate,cSprite);
			strcat(cConcatenate,"/");
			strcat(cConcatenate,cSprite);
			strcat(cConcatenate,cStatus);
			strcat(cConcatenate,".DEF");
			sprites.open(cConcatenate, ios::in);
				sprites >> sSprite.iWidth;
				sSprite.iWidth++;
				sprites >> sSprite.iHeight;
				sSprite.iHeight++;
				for (int iPixelRow=0; iPixelRow < sSprite.iHeight; iPixelRow++)
					for (int iPixelCol=0; iPixelCol< sSprite.iWidth; iPixelCol++)
						sprites >> sSprite.iPixels[iPixelRow+(iCurrentStatus*sSprite.iHeight)][iPixelCol];
			sprites.close();
			for(int iErraseCounter=0; iErraseCounter<45; iErraseCounter++)
				cConcatenate[iErraseCounter] = 0;
			cStatus[0] = 0;
		} 
	}

	void mcga()
	{
	  REGS sIn,sOut;
	  sIn.h.ah=0;
	  sIn.h.al=19;
	  int86(0x10,&sIn,&sOut);
	}

	void paintPixel(int iRow, int iColumn, unsigned short int iColor)
	{
	   char far *ptr = (char far *)0xA0000000;
	   ptr += 320*iRow + iColumn;
	   *ptr = iColor;
	}

	unsigned short int retrievePixel(int iRow, int iColumn)
	{
	  char far *pxPtr = (char far*)0xA0000000;
	  pxPtr += iRow*320 + iColumn;
	  return *pxPtr;
	}

	void backUp (sprite &sSprite)
	{
		for (int iRowCounter=0; iRowCounter<sSprite.iHeight; iRowCounter++)
      		for (int iColumnCounter=0; iColumnCounter<sSprite.iWidth; iColumnCounter++)
	  			sSprite.iPixels[iRowCounter][iColumnCounter] = retrievePixel(sSprite.iRow+iRowCounter,sSprite.iColumn+iColumnCounter);
	}

	enum
	{
	  keyEsc     = 27,
	  enter      = 13,
	  spaceBar   = 32,
	  arrowUp    = 256 + 72,
	  arrowDown  = 256 + 80,
	  arrowLeft  = 256 + 75,
	  arrowRight = 256 + 77,
	  letter_A   = 65,
	  letter_a   = 97,
	  letter_D   = 68,
	  letter_d   = 100,
	  letter_S   = 83,
	  letter_s   = 115,
	  letter_W   = 87,
	  letter_w   = 119,
	  letter_F   = 70,
	  letter_f   = 102
	};

	int getInput()
	{
	  int iChar = getch();
	  if (iChar == 0 || iChar == 224)
	     iChar = 256 + getch();
	 return iChar;
	}

	void print (sprite sSprite)
	{
		for (int iPixelRow=0; iPixelRow <sSprite.iHeight; iPixelRow++)
			for (int iPixelCol=0; iPixelCol<sSprite.iWidth; iPixelCol++)
			    if(sSprite.iPixels[iPixelRow+sSprite.iCurrentAnimation*sSprite.iHeight][iPixelCol] != sSprite.iTransparentColor)
		      		paintPixel(sSprite.iRow+iPixelRow,sSprite.iColumn+iPixelCol,sSprite.iPixels[iPixelRow+sSprite.iCurrentAnimation*sSprite.iHeight][iPixelCol]);
	}

	void print2X (sprite sSprite)
	{
		for (int iPixelRow=0, iRow=0; iPixelRow < (sSprite.iHeight/2); iPixelRow++,iRow+=2)
			for (int iPixelCol=0, iCol=0; iPixelCol < sSprite.iWidth; iPixelCol++,iCol+=2)
			    if(sSprite.iPixels[iPixelRow+sSprite.iCurrentAnimation*sSprite.iHeight][iPixelCol] == sSprite.iTransparentColor)
			    {
			    	paintPixel(sSprite.iRow+iRow,sSprite.iColumn+iCol,0);
				    paintPixel(sSprite.iRow+iRow,sSprite.iColumn+iCol+1,0);
				    paintPixel(sSprite.iRow+iRow+1,sSprite.iColumn+iCol,0);
				    paintPixel(sSprite.iRow+iRow+1,sSprite.iColumn+iCol+1,0);
			    }
		      	else
		      	{
		      		paintPixel(sSprite.iRow+iRow,sSprite.iColumn+iCol,sSprite.iPixels[iPixelRow+sSprite.iCurrentAnimation*sSprite.iHeight][iPixelCol]);
			      	paintPixel(sSprite.iRow+iRow,sSprite.iColumn+iCol+1,sSprite.iPixels[iPixelRow+sSprite.iCurrentAnimation*sSprite.iHeight][iPixelCol]);
			      	paintPixel(sSprite.iRow+iRow+1,sSprite.iColumn+iCol,sSprite.iPixels[iPixelRow+sSprite.iCurrentAnimation*sSprite.iHeight][iPixelCol]);
			      	paintPixel(sSprite.iRow+iRow+1,sSprite.iColumn+iCol+1,sSprite.iPixels[iPixelRow+sSprite.iCurrentAnimation*sSprite.iHeight][iPixelCol]);
		      	}
	}

	void horizontalFlip2X (sprite sSprite)
	{
		for (int iPixelRow=0, iRow=0; iPixelRow < (sSprite.iHeight/2); iPixelRow++,iRow+=2)
			for (int iPixelCol=0, iCol=0; iPixelCol < sSprite.iWidth; iPixelCol++,iCol+=2)
			    if(sSprite.iPixels[iPixelRow+sSprite.iCurrentAnimation*sSprite.iHeight][iPixelCol] == sSprite.iTransparentColor)
			    {
					paintPixel(sSprite.iRow+iRow,sSprite.iColumn+sSprite.iWidth-iCol,0);
					paintPixel(sSprite.iRow+iRow,sSprite.iColumn+sSprite.iWidth-iCol+1,0);
					paintPixel(sSprite.iRow+iRow+1,sSprite.iColumn+sSprite.iWidth-iCol,0);
					paintPixel(sSprite.iRow+iRow+1,sSprite.iColumn+sSprite.iWidth-iCol+1,0);
			    }
		      	else
		      	{
					paintPixel(sSprite.iRow+iRow,sSprite.iColumn+sSprite.iWidth-iCol,sSprite.iPixels[iPixelRow+sSprite.iCurrentAnimation*sSprite.iHeight][iPixelCol]);
					paintPixel(sSprite.iRow+iRow,sSprite.iColumn+sSprite.iWidth-iCol+1,sSprite.iPixels[iPixelRow+sSprite.iCurrentAnimation*sSprite.iHeight][iPixelCol]);
					paintPixel(sSprite.iRow+iRow+1,sSprite.iColumn+sSprite.iWidth-iCol,sSprite.iPixels[iPixelRow+sSprite.iCurrentAnimation*sSprite.iHeight][iPixelCol]);
					paintPixel(sSprite.iRow+iRow+1,sSprite.iColumn+sSprite.iWidth-iCol+1,sSprite.iPixels[iPixelRow+sSprite.iCurrentAnimation*sSprite.iHeight][iPixelCol]);
		      	}
	}

	void verticalFlip (sprite sSprite)
	{
		for (int iPixelRow=0; iPixelRow<sSprite.iHeight; iPixelRow++)
			for (int iPixelCol=0; iPixelCol<sSprite.iWidth; iPixelCol++)
			    if(sSprite.iPixels[iPixelRow+sSprite.iCurrentAnimation*sSprite.iHeight][iPixelCol] != sSprite.iTransparentColor)
		      		paintPixel(sSprite.iRow+sSprite.iHeight-iPixelRow,sSprite.iColumn+iPixelCol,sSprite.iPixels[iPixelRow+sSprite.iCurrentAnimation*sSprite.iHeight][iPixelCol]);
	}

	void horizontalFlip (sprite sSprite)
	{
		for (int iPixelRow=0; iPixelRow<sSprite.iHeight; iPixelRow++)
			for (int iPixelCol=0; iPixelCol<sSprite.iWidth; iPixelCol++)
			    if(sSprite.iPixels[iPixelRow+sSprite.iCurrentAnimation*sSprite.iHeight][iPixelCol] != sSprite.iTransparentColor)
			      		paintPixel(sSprite.iRow+iPixelRow,sSprite.iColumn+sSprite.iWidth-iPixelCol,sSprite.iPixels[iPixelRow+sSprite.iCurrentAnimation*sSprite.iHeight][iPixelCol]);
	}

	void rotate90Clockwise (sprite sSprite)
	{
		for (int iPixelRow=0; iPixelRow<sSprite.iHeight; iPixelRow++)
			for (int iPixelCol=0; iPixelCol<sSprite.iWidth; iPixelCol++)
			    if(sSprite.iPixels[iPixelRow+sSprite.iCurrentAnimation*sSprite.iHeight][iPixelCol] != sSprite.iTransparentColor)
		      		paintPixel(sSprite.iRow+iPixelCol,sSprite.iColumn+sSprite.iHeight-iPixelRow,sSprite.iPixels[iPixelRow+sSprite.iCurrentAnimation*sSprite.iHeight][iPixelCol]);
	}

	void rotate90CounterClockwise (sprite sSprite)
	{
		for (int iPixelRow=0; iPixelRow<sSprite.iHeight; iPixelRow++)
			for (int iPixelCol=0; iPixelCol<sSprite.iWidth; iPixelCol++)
			    if(sSprite.iPixels[iPixelRow+sSprite.iCurrentAnimation*sSprite.iHeight][iPixelCol] != sSprite.iTransparentColor)
	      			paintPixel(sSprite.iRow+sSprite.iWidth-iPixelCol,sSprite.iColumn+iPixelRow,sSprite.iPixels[iPixelRow+sSprite.iCurrentAnimation*sSprite.iHeight][iPixelCol]);
	}

	void printHealthBar (int iRow, int iColumn)
	{
		fstream sprites;
		sprites.open("TUF_GAME/Content/Screens/HEALTH/HEALTH11.DEF", ios::in);
			unsigned short int iWidth, iHeight, iColor;
			sprites >> iWidth;
			sprites >> iHeight;
			for (int iPixelRow=0; iPixelRow <= iHeight; iPixelRow++)
				for (int iPixelCol=0; iPixelCol<= iWidth; iPixelCol++)
				{
					sprites >> iColor;
			      	paintPixel(iRow+iPixelRow,iColumn+iPixelCol,iColor);
			    }
		sprites.close();
	}

	void moveRight(sprite &sSprite, int iSteps)
	{
		if(sSprite.bIsJumping == false)
		{
			if(sSprite.iMovingAnimation == 3)
				sSprite.iMovingAnimation = 4;
			else
				sSprite.iMovingAnimation = 3;
			sSprite.iCurrentAnimation = sSprite.iMovingAnimation;
		}
		else
			sSprite.iCurrentAnimation = 3;
		int iActualAnimation;
		iActualAnimation = sSprite.iCurrentAnimation;
		sSprite.iCurrentAnimation = 0;
		print(sSprite);
		sSprite.iColumn += iSteps;
		backUp(sSprite);
		sSprite.iCurrentAnimation = iActualAnimation;
		horizontalFlip(sSprite);
		delay(60);
		sSprite.iCurrentAnimation = 0;
		print(sSprite);
		sSprite.iCurrentAnimation = 2;
		horizontalFlip(sSprite);
	}

	void moveLeft(sprite &sSprite, int iSteps)
	{
		if(sSprite.bIsJumping == false)
		{
			if(sSprite.iMovingAnimation == 3)
				sSprite.iMovingAnimation = 4;
			else
				sSprite.iMovingAnimation = 3;
			sSprite.iCurrentAnimation = sSprite.iMovingAnimation;
		}
		else
			sSprite.iCurrentAnimation = 3;
		int iActualAnimation;
		iActualAnimation = sSprite.iCurrentAnimation;
		sSprite.iCurrentAnimation = 0;
		print(sSprite);
		sSprite.iColumn -= iSteps;
		backUp(sSprite);
		sSprite.iCurrentAnimation = iActualAnimation;
		print(sSprite);
		delay(60);
		sSprite.iCurrentAnimation = 0;
		print(sSprite);
		sSprite.iCurrentAnimation = 2;
		print(sSprite);
	}

	void forHorizontalLine (int i1X, int i2X, int iY, unsigned short int iColor)
	{
	 for(short int iCounter = 0; iCounter <= i2X - i1X; iCounter++)
	 	paintPixel(i1X+iCounter, iY, iColor);
	}

	void forHorizontalRectangle (int iX, int iY, int iWidth, int iHeight, unsigned short int iColor)
	{
	 for(short int iCounter = 0; iCounter < iHeight; iCounter++)
	 	forHorizontalLine(iX,iX+iWidth,iY+iCounter,iColor);
	}

	void myChess(int iColor1, int iColor2)
	{
	 int iXSpaceCounter;
	 int iYSpaceCounter;
	 int iXCounter;
	 int iYCounter;
	 for(iYCounter = 0, iYSpaceCounter = 0; iYCounter < 320; iYCounter += 20, iYSpaceCounter++)
	    for(iXCounter = 0, iXSpaceCounter = 0; iXCounter < 200; iXCounter += 20, iXSpaceCounter++)
	       if(iYSpaceCounter % 2 == 0)
		  if(iXSpaceCounter % 2 == 0)
		     forHorizontalRectangle(iXCounter,iYCounter,20,20,iColor1);
		  else
		     forHorizontalRectangle(iXCounter,iYCounter,20,20,iColor2);
		else
		  if(iXSpaceCounter % 2 != 0)
		     forHorizontalRectangle(iXCounter,iYCounter,20,20,iColor1);
		  else
		     forHorizontalRectangle(iXCounter,iYCounter,20,20,iColor2);
	}

	void startScreen()
	{
		int iUserInput=0;
		while(iUserInput != enter)
		{
			myChess(6,7);
			forHorizontalRectangle(0,0,40,320,0);
			forHorizontalRectangle(159,0,40,320,0);
			gotoxy(11,3);
			cout << "THE ULTIMATE FIGHT" << endl;
			gotoxy(17,24);
			cout << "PF,2014" << endl;
			delay(2000);
			gotoxy(15,22);
			cout << "Press Enter" << endl;
			iUserInput = getInput();
		}
		forHorizontalRectangle(159,0,40,320,0);
		forHorizontalRectangle(48,6,105,307,0);
		gotoxy(13,8);
		cout << "GAME CONTROLS" << endl;
		gotoxy(6,11);
		cout << "KNIGHT" << endl;
		gotoxy(25,11);
		cout << "FIGHTER" << endl;
		gotoxy(2,13);
		cout << "Jump:   (W)" << endl;
		gotoxy(2,15);
		cout << "Right:  (D)" << endl;
		gotoxy(2,17);
		cout << "Left:   (A)" << endl;
		gotoxy(2,19);
		cout << "Attack: (Enter)" << endl;
		gotoxy(19,13);
		cout << "Jump:   (Arrow Up)" << endl;
		gotoxy(19,15);
		cout << "Right:  (Arrow Right)" << endl;
		gotoxy(19,17);
		cout << "Left:   (Arrow Left)" << endl;
		gotoxy(19,19);
		cout << "Attack: (Space Bar)" << endl;
		gotoxy(15,23);
		cout << "Loading" << endl;
		delay(500);
		gotoxy(15,23);
		cout << "Loading." << endl;
		delay(500);
				gotoxy(15,23);
		cout << "Loading.." << endl;
		delay(500);
		gotoxy(15,23);
		cout << "Loading..." << endl;
		delay(500);
		forHorizontalRectangle(159,0,40,320,0);
	}

	void initGame(sprite &sSprite1, sprite &sSprite2)
	{
	 	initSprite(sSprite1,"KNIGHT",4,5);
	  	initSprite(sSprite2,"FIGHTER",4,5);
	  	sSprite1.iRow = 7;
	  	sSprite1.iColumn = 22;
	  	sSprite2.iRow = 7;
	  	sSprite2.iColumn = 270;
	  	horizontalFlip2X(sSprite1);
	  	print2X(sSprite2);
	  	printHealthBar(18,44);
	  	printHealthBar(18,175);
	  	gotoxy(7,2);
	  	cout << "KNIGHT" << endl;
	  	gotoxy(28,2);
	  	cout << "FIGHTER" << endl;
	  	sSprite1.bIsToTheRight = true;
	  	sSprite1.iRow = 124;
	  	sSprite1.iColumn = 12;
	  	sSprite2.iRow = 124;
	  	sSprite2.iColumn = 290;
	  	backUp(sSprite1);
	  	horizontalFlip(sSprite1);
	  	backUp(sSprite2);
	  	print(sSprite2);
	}

	void paintScreen(unsigned short int iBitmap[10][16], char cScreenName[10])
	{
		char cConcatenate[45];
		for(int iInitCounter=0; iInitCounter<45; iInitCounter++)
					cConcatenate[iInitCounter] = 0;
		char cColor[3] = {0,0,0};
		for(int iBitmapRow=0,iRow=0; iBitmapRow<10; iBitmapRow++,iRow+=19)
			for(int iBitmapCol=0,iColumn=0; iBitmapCol<16; iBitmapCol++,iColumn+=20)
			{
				itoa(iBitmap[iBitmapRow][iBitmapCol],cColor,10);
				strcat(cConcatenate,"TUF_GAME/Content/Screens/");
				strcat(cConcatenate,cScreenName);
				strcat(cConcatenate,"/");
				strcat(cConcatenate,cScreenName);
				strcat(cConcatenate,cColor);
				strcat(cConcatenate,".DEF");
				fstream screens;
				screens.open(cConcatenate, ios::in);
					unsigned short int iWidth, iHeight, iColor;
					screens >> iWidth;
					screens >> iHeight;
					for (int iPixelRow=0; iPixelRow <= iHeight; iPixelRow++)
						for (int iPixelCol=0; iPixelCol<= iWidth; iPixelCol++)
						{
							screens >> iColor;
					      	paintPixel(iRow+iPixelRow,iColumn+iPixelCol,iColor);
					    }
				screens.close();
				for(int iErraseCounter=0; iErraseCounter<45; iErraseCounter++)
					cConcatenate[iErraseCounter] = 0;
				cColor[0] = 0;
				cColor[1] = 0;
			}
	}
#endif