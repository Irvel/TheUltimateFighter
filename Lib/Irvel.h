#ifndef Irvel
#define Irvel


//////////////////////////////////////////////////////////////////////////////
//                              Functions                                   //
//////////////////////////////////////////////////////////////////////////////


	//VER 0.6



	//bCheckForSpriteColision recieves the position of a pixel and checks if that pixel is within the bounds of a given sprite
	//If it is, then it returns true, else false
	bool bCheckForSpriteColision(sprite &sCurrent, sprite &sOther){
		/*
		if(iCol +  < sOther.iColumn){
			return false;
		}
		else if(iRow < sOther.iRow){
			return false;
		}
		else if(iCol > (sOther.iColumn + sOther.iWidth)){
			return false;
		}
		else if(iRow > (sOther.iRow + sOther.iHeight)){
			return false;
		}
		else if(iCol >= sOther.iColumn && iCol <= (sOther.iColumn + sOther.iWidth)){
			if(iRow < sOther.iRow)
				return false;
			else if(iRow > sOther.iRow)
				return false;
			else if(iRow >= sOther.iRow && iRow <= (sOther.iRow + sOther.iHeight))
				return true;
		}
		else if(iRow >= sOther.iRow && iRow <= (sOther.iRow + sOther.iHeight)){
			if(iCol < sOther.iColumn)
				return false;
			else if(iCol > sOther.iColumn)
				return false;
			else if(iCol >= sOther.iColumn && iCol <= (sOther.iColumn + sOther.iWidth))
				return true;
		}
		return false;
		*/
		//Retry
		if(sCurrent.iColumn + sCurrent.iWidth  <  sOther.iColumn){
			return false;
		}
		else{
			if (sOther.iColumn + sOther.iWidth < sCurrent.iColumn){
				return false;
			}
		}
		return true;
	}



	//Tests if the pixel recieved in a particular position is a wall
	bool bCheckForWallColision(int iRow, int iCol){
		/*
		if(retrievePixel(iRow, iCol) == 0){
			return true;
		}
		*/
		if((271 <= iCol && iCol <= 294) || (92 <= iCol && iCol <= 118)){	
			if(iRow > 120)
				return true;
			else
				return false;
		}
		return false;		
	}







/*Send Sprite that's moving, the send the other sprite in the arena
  Then the row you want to move the sprite to and then the column you want to move it to
  This function (iColides) will return 
  			0 if there is no colision
  			1 if there is a colision with a wall/platform
  			2 if there is a colision with another sprite
 */

	int iColides(sprite &sCurrentSprite, sprite &sOtherSprite, int iRowTry, int iColTry){
		//Check if it is trying to move left/right
		//cout << "iColTry: " << iColTry << "               " << retrievePixel(iRowTry + sCurrentSprite.iHeight, iColTry) << '\n';
		//cout << "sCurrentSprite.iColumn: " << sCurrentSprite.iColumn << "       " << "sCurrentSprite.iRow: " << sCurrentSprite.iRow << '\n';
		
		if (bCheckForSpriteColision(sCurrentSprite, sOtherSprite)){
			return 2;
		}

		if (iColTry < sCurrentSprite.iColumn){
			//It's moving left
			//Try top left corner
			if( bCheckForWallColision((iRowTry + sCurrentSprite.iHeight), iColTry)  ){
				return 1;
			}
		}
		else if (iColTry > sCurrentSprite.iColumn){
			//It's moving right
			if( bCheckForWallColision((iRowTry + sCurrentSprite.iHeight), (iColTry + sCurrentSprite.iWidth)) || bCheckForWallColision(iRowTry, (iColTry + sCurrentSprite.iWidth)) ){
				return 1;
			}
		}


		//Check if it is trying to move up/down
		else if (iColTry == sCurrentSprite.iColumn && iRowTry < sCurrentSprite.iRow){
			//It's moving upwards
			if( bCheckForWallColision(iRowTry, iColTry) || bCheckForWallColision(iRowTry, (iColTry + sCurrentSprite.iWidth)) ){
				return 1;
			}
		}

		else if (iColTry == sCurrentSprite.iColumn && iRowTry > sCurrentSprite.iRow){
			//It's moving downwards
			if( bCheckForWallColision(iRowTry, iColTry) || bCheckForWallColision(iRowTry, (iColTry + sCurrentSprite.iWidth)) || bCheckForWallColision((iRowTry + sCurrentSprite.iHeight), iColTry) || bCheckForWallColision((iRowTry + sCurrentSprite.iHeight), (iColTry + sCurrentSprite.iWidth)) ){
				return 1;
			}
		}

		else if (iColTry == sCurrentSprite.iColumn && iRowTry == sCurrentSprite.iRow){
			//It's attacking and not moving
			if( bCheckForWallColision((iRowTry + sCurrentSprite.iHeight), (iColTry + sCurrentSprite.iWidth)) || bCheckForWallColision(iRowTry, (iColTry + sCurrentSprite.iWidth)) ){
				return 1;
			}
		}
		return 0;
	}


#endif