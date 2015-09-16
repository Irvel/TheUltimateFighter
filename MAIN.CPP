//////////////////////////////////////////////////////////////////////////////
//                                                                          //
//                        The Ultimate Fight Game                           //
//                                                                          //
//                              Created By:                                 //
//       Diego Garza Rodriguez              A00817231            ISD        //
//       Carlos Javier Sanchez Lopez        A01139506            ITC        //
//       Irvel Nduva Matias Vega            A01196346            ITC        //
//       Emilio Lopez Sanchez               A01281082            ISD        //
//                                                                          //
//                      Programming Fundamentals                            //
//                           Final Project                                  //
//                         November 25, 2014                                //
//////////////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////////////
//                              Libraries                                   //
//////////////////////////////////////////////////////////////////////////////

#include "TUF_GAME/Lib/Diego.h"
#include "TUF_GAME/Lib/Carlos.h"
#include "TUF_GAME/Lib/Irvel.h"
#include "TUF_GAME/Lib/Emilio.h"



//////////////////////////////////////////////////////////////////////////////
//                              Functions                                   //
//////////////////////////////////////////////////////////////////////////////

void paintBackground()
{
	unsigned short int iBitmap[10][16] = {
		{44,44,44,44,44,44,44,44,44,44,44,44,44,44,44,44},
		{44,44,44,44,44,44,44,44,44,44,44,44,44,44,44,44},
		{1,1,1,1,1,1,1,8,9,10,1,1,1,2,1,1},
		{1,1,1,1,1,1,11,12,13,14,1,1,5,6,7,1},
		{1,1,3,4,1,1,15,16,17,18,1,1,1,1,1,1},
		{1,19,20,1,1,21,22,23,24,25,26,27,28,29,1,1},
		{30,31,32,33,34,35,36,36,36,36,36,36,37,38,39,40},
		{41,41,41,42,43,41,41,41,41,41,41,41,42,43,41,41},
		{44,44,44,44,44,44,44,44,44,44,44,44,44,44,44,44},
		{44,44,44,44,44,44,44,44,44,44,44,44,44,44,44,44}};
	paintScreen(iBitmap,"BKG");
}

void fight (sprite &sSprite1, sprite &sSprite2)
{
//initialization of the variables
int iUserInput=0;
int iColision = 0;
//Start of the loop, when yo press 'f', 'F' or ESC it ends.
  while(iUserInput != letter_f && iUserInput != letter_F && iUserInput != keyEsc)
  {
//Here is where you code the things that change with keyboard interaction
     if(kbhit())
     {
	iUserInput = getInput();
		switch(iUserInput)
	     {
		case letter_w:
		case letter_W:
		if(sSprite1.iRow>0)
      if(sSprite1.bIsJumping == false)
      {
  		  sSprite1.bIsJumping = true;
        sSprite1.iInitPlace = sSprite1.iRow;
      }
		break;
		case letter_a:
		case letter_A:
		sSprite1.bIsToTheRight = false;
		if(sSprite1.iColumn>0)
    {
        moveLeft(sSprite1,7);
    }
		break;
		case letter_d:
		case letter_D:
		sSprite1.bIsToTheRight = true;
		if(sSprite1.iColumn<292)
    {
        moveRight(sSprite1,7);
    }
		break;
    case enter:
      attack1(sSprite1);
    break;
		case arrowUp:
		if(sSprite2.iRow>0)
      if(sSprite2.bIsJumping == false)
      {
  		  sSprite2.bIsJumping = true;
        sSprite2.iInitPlace = sSprite2.iRow;
      }
		break;
		case arrowLeft:
		sSprite2.bIsToTheRight = false;
		if(sSprite2.iColumn>5)
      moveLeft(sSprite2,7);
		break;
		case arrowRight:
		sSprite2.bIsToTheRight = true;
		if(sSprite2.iColumn<288)
        moveRight(sSprite2,7);
    break;
    case spaceBar:
      attack2(sSprite2);
    break;    
		}
 	}
//Here you code everything that you want to continue changing regardless the user interaction
  iColision = iColides(sSprite2, sSprite1, sSprite2.iInitPlace + 1, sSprite2.iColumn);
  if(iColision == 1){
    sSprite2.iInitPlace = 108;
  }
  else{
    iColision = iColides(sSprite2, sSprite1, sSprite2.iInitPlace + 1, sSprite2.iColumn + sSprite2.iWidth);
    if(iColision == 1){
      sSprite2.iInitPlace = 108;
    }
    else if(iColides(sSprite2, sSprite1, sSprite2.iInitPlace + 1, sSprite2.iColumn) == 2 || iColision == 2){
      sSprite2.iInitPlace = 124 - sSprite1.iHeight;
    }
    else{
      sSprite2.iInitPlace = 124;
    }
  }
  iColision = iColides(sSprite1, sSprite2, sSprite1.iInitPlace + 1, sSprite1.iColumn);
  if(iColision == 1){
    sSprite1.iInitPlace = 108;
  }
  else{
    iColision = iColides(sSprite1, sSprite2, sSprite1.iInitPlace + 1, sSprite1.iColumn + sSprite1.iWidth);
    if(iColision == 1){
      sSprite1.iInitPlace = 108;
    }
    else if(iColides(sSprite1, sSprite2, sSprite1.iInitPlace + 1, sSprite2.iColumn) == 2 || iColision == 2){
      sSprite1.iInitPlace = 124 - sSprite2.iHeight;
    }
    else{
      sSprite1.iInitPlace = 124;
    }
  }
jump(sSprite1);
jump(sSprite2);
  }
}



//////////////////////////////////////////////////////////////////////////////
//                            Main Program                                  //
//////////////////////////////////////////////////////////////////////////////

int main(){
  mcga();
  startScreen();
  paintBackground();
  sprite sKnight, sFighter;
  initGame(sKnight, sFighter);
  fight(sKnight, sFighter);
  return 0;
}