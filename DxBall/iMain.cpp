#include "declarations.h"
#include "iGraphics.h"
#include <iostream>
#include <cstdio>


using namespace std;


void iMouseMove(int mx, int my)
{

	
}
void iPassiveMouseMove(int mx, int my)
{
	
	if ( mx < (canvasWidth - boardDx) && mx > 0)
		boardX = mx;

	cout << mx << " " << my << endl;
}

void iMouse(int button, int state, int mx, int my)
{

	if (mx > 442-40 && mx < 442+40 && my >433-40 && my<433+40) // starting game box
	{
		initializeDifficulty();

		enteringName = false;
		showMenu = false;
		return;
		
	}


		if (mx >= box_X && mx <= box_X + box_W && my >= box_Y && my <= box_Y + box_H && showMenu) // selecting the name box
		{
			if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
			{
				enteringName = true;
				state = GLUT_UP;
			}
		}

		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && !showMenu && !gameOver) //starting the game; shooting the ball from board
		{
			atRest = false;
			PlaySound("music\\zapsplat_warfare_mortar_projectile_launch_002_25232.wav", NULL, SND_ASYNC);

		}


		// DIFFICULTY LEVEL BOXES

		if (mx > 380 && mx <480 && my >200 && my < 230 && showMenu) // NOOB
		{
			if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
			{
				noob = true;
				amateur = false;
				pro = false;

				state = GLUT_UP;
			}
		}

		else if (mx > 380 && mx <480 && my >150 && my < 180 && showMenu) // amateur
		{
			if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
			{
				
				noob = false;
				amateur = true;
				pro = false;


				state = GLUT_UP;
			}
		}


		else if (mx > 380 && mx <480 && my >100 && my < 130 && showMenu) // pro
		{
			if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
			{

				noob = false;
				amateur = false;
				pro = true;


				state = GLUT_UP;
			}
		}

	

	
}

/*
function iKeyboard() is called whenever the user hits a key in keyboard.
key- holds the ASCII value of the key pressed.
*/

void iKeyboard(unsigned char key)
{
	if (enteringName)
	{
		static int i = 0;
		if (key == '\b')
		{
			name[--i] = '\0';
		}
		else if (key == '\r')
		{
			//enteringName = false;
			//showMenu = false;

			//return;
		}
		else
		{
			
			name[i] = key;
			i++;

		}
		
	}
	
	
}

void iSpecialKeyboard(unsigned char key)
{

	
	if (key == GLUT_KEY_RIGHT)
	{
		
				
	}
	if (key == GLUT_KEY_LEFT)
	{
	
		
	}
	
	if (key == GLUT_KEY_HOME)
	{
		
		
	}
	
}

void move()
{
	
	

}

typedef struct BrickStructure{

	double height=15, width=50;
	double x, y;
	int r, g, b;
	bool show = true;

}BrickStructure;

int tempHeight = 15;
int tempWidth = 50;


BrickStructure bricks[numOfBricks];

void initializeDifficulty()
{
	if (noob)
	{
		delX = 1;
		delY = 1;

	}
	else if (amateur)
	{
		delX = 4;
		delY = 4;

	}
	else if (pro)
	{
		delX = 6;
		delY = 6;

	}
}


void ballMovement()
{
	//cout << delX << " " << delY << endl;
	if (atRest)
	{
		dxBall = boardX + (boardDx / 2);
		dyBall = boardDy + 20;

		return;

	}
	else
	{

		dxBall += delX;
		dyBall += delY;

		bouncingBall();

		collision();


	}
	 

}

void bouncingBall()
{


	if (dxBall >= canvasWidth || dxBall <= 0)
	{	

		PlaySound("music\\wall_impact.wav", NULL, SND_ASYNC);
		delX *= (-1);

	}
	
	else if (dyBall >= canvasHeight)
	{
		PlaySound("music\\wall_impact.wav", NULL, SND_ASYNC);
		delY *= (-1);

	}
		

	else if (dyBall <= 0) // OUT OF CANVAS
	{
		
		PlaySound("music\\Byeball.wav", NULL, SND_ASYNC);

		gameChance--;
		if (!gameChance) //game over
		{
			index = 0;
			gameOver = true;
			PlaySound("music\\gameover.wav", NULL, SND_ASYNC);
			return;

		}

		//*******RESETTING VALUES OF BALL'S SPEED***************
			
		atRest = true;
		initializeDifficulty();
	

	}
	
	
}


void collision()
{
	cout << "num of bricks:  " << numOfBricks << endl;
	if (brick == numOfBricks)
	{
		win = true;

		return;

	}


	if ((dxBall >= boardX && dxBall <= boardX + boardDx / 2) && (dyBall >= boardY && (dyBall <= boardDy + boardY)))
	{
		PlaySound("music\\Boing.wav", NULL, SND_ASYNC);

		delY *= (-1);
	

	}
	
	else if ((dxBall > boardX + boardDx / 2) &&  dxBall <= boardX+boardDx  && (dyBall >= boardY && (dyBall <= boardDy + boardY)))
	{
		PlaySound("music\\Boing.wav", NULL, SND_ASYNC);

		delY *= (-1);
		
	}
	
	for (int i = 0; i < numOfBricks; i++)								//COLLISION OF BALL WITH BRICKS
	{
		if (bricks[i].show)
		{
			if (dxBall >= bricks[i].x && dxBall <= bricks[i].x + bricks[i].width)
			{
				if (dyBall >= bricks[i].y && dyBall <= bricks[i].y + bricks[i].height)
				{
					bricks[i].show = false;
					PlaySound("music\\brick_impact.wav", NULL, SND_ASYNC);
					delY *= (-1);
					sum += 10;										//CALCULATING THE SUM OF SCORES
					sprintf_s(score, "SCORE : %d", sum);
					sprintf_s(printScore, "%d", sum);
					brick++;
										
				
				}
			}
		}
	}
	
	

}



void iDraw()
{
	//cout << '10' << endl;
	iClear();

	if (showMenu)
	{
		menu();
	}
	else if(gameOver)
	{

		iShowImage(0, 0, canvasWidth, canvasHeight, overID);
		iSetColor(255, 255, 255);
		iText(488, 196, name, GLUT_BITMAP_TIMES_ROMAN_24);
		iText(492, 105, printScore, GLUT_BITMAP_TIMES_ROMAN_24);
	
	//	exit(0);

	}

	else if (win)
	{
		iShowImage(0, 0, canvasWidth, canvasHeight, winID); 
		//iText();
	}

	else
	{
		
		iShowImage(0, 0, canvasWidth, canvasHeight, backgroundImg); //prints the background
		iShowImage(boardX, boardY, boardDx, boardDy, board);		//prints the board

		iSetColor(230, 247, 49);
		iFilledCircle(dxBall, dyBall, 10, 100);					// prints the ball;


		for (int i = 0; i < numOfBricks; i++)
		{
			if (bricks[i].show)
			{
				iSetColor(bricks[i].r, bricks[i].g, bricks[i].b);
				iFilledRectangle(bricks[i].x, bricks[i].y, 50, 15);

			}

		}

		iSetColor(184, 226, 111);
	
		iText(5, 10, score , GLUT_BITMAP_HELVETICA_18);
	
	}

	
}

void constructBricks()
{
	int temp = 500;
	int j = 1;

	bricks[0].x = 100;

	int cond = 16;
	int sumX = bricks[0].x + tempWidth;

	for (int i = 0; i<4; i++) // numOfBricks in one row =16 ; thus 4*16 = 64 which is the total number of bricks
	{

		bricks[i].y = temp;
		while (true) //16 bricks in one row
		{
			bricks[j].r = rand() % 255;
			bricks[j].g = rand() % 255;
			bricks[j].b = rand() % 255;


			bricks[j].x = sumX;
			bricks[j].y = temp;

			sumX += tempWidth;

			if (j == cond)
			{
				sumX = tempWidth;

				break;
			}

			j++;
		}
		temp -= tempHeight;
		cond += 16;



	}




}

void menu()
{
	iShowImage(0, 0, canvasWidth, canvasHeight, menuID);
	iSetColor(0, 0, 0);

	iText(400-10, 500, "DX-BALL", GLUT_BITMAP_TIMES_ROMAN_24);
	iText(400-11, 500 - 1, "DX-BALL", GLUT_BITMAP_TIMES_ROMAN_24);

	iText(box_X + 60, box_Y + 60, "ENTER NAME", GLUT_BITMAP_TIMES_ROMAN_24);

	iSetColor(box_R, box_G, box_B);

	iRectangle(box_X, box_Y, box_W, box_H);
	iRectangle(box_X - 1, box_Y - 1, box_W, box_H);

	if (enteringName)
	{
		box_R = 255;
		box_G = 0;
		box_B = 84;
		iSetColor(0, 0, 0);
		iText(box_X + 10, box_Y + 10, name, GLUT_BITMAP_TIMES_ROMAN_24);

		i++;

	}


	/*

	GLUT_BITMAP_9_BY_15
	GLUT_BITMAP_8_BY_13
	GLUT_BITMAP_TIMES_ROMAN_10
	GLUT_BITMAP_TIMES_ROMAN_24
	GLUT_BITMAP_HELVETICA_10
	GLUT_BITMAP_HELVETICA_12
	GLUT_BITMAP_HELVETICA_18
	
	*/

	//****PRINTING difficulty boxes*****
	
	iText(380, 260, "SET DIFFICULTY", GLUT_BITMAP_8_BY_13);

	if (noob)
	{
		nR = 255;
		nG = 0;
		nB = 84;

		 aR = 0, aG = 0, aB = 0;
		 pR = 0, pG = 0, pB = 0;
	}
	else if (amateur)
	{

		aR = 255;
		aG = 0;
		aB = 84;

		nR = 0, nG = 0, nB = 0;
		pR = 0, pG = 0, pB = 0;

	}
	else if (pro)
	{
		pR = 255;
		pG = 0;
		pB = 84;

		nR = 0, nG = 0, nB = 0;
		aR = 0, aG = 0, aB = 0;

	}


	iSetColor(nR, nG, nB);
	iRectangle(380, 200, 100, 30);
	iText(410, 210, "NOOB", GLUT_BITMAP_9_BY_15);

	iSetColor(aR, aG, aB);
	iRectangle(380, 150, 100, 30);
	iText(400, 160, "AMATEUR", GLUT_BITMAP_9_BY_15);

	iSetColor(pR, pG, pB);
	iRectangle(380, 100, 100, 30);
	iText(400, 110, "IM PROO", GLUT_BITMAP_9_BY_15);

	iSetColor(255, 0, 84);
	iFilledCircle(442, 443, 40, 1000);
	

}


int main()
{
	iInitialize(canvasWidth, canvasHeight, "DX-BALL");
    backgroundImg = iLoadImage("images\\dx_ball_background.png");
	menuID = iLoadImage("images\\8.jpg");
	overID = iLoadImage("images\\GAMEOVER.png");
	winID = iLoadImage("images\\WIN.png");

	board = iLoadImage("images\\dxball_png_board.png");


	constructBricks();

	iSetTimer(0, ballMovement); 
	
	iStart();

	return 0;
}