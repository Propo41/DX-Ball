#ifndef DECLARATIONS_H
#define DECLARATIONS_H
#define FIRST 1
#define numOfBricks 64
int canvasHeight=600;
int canvasWidth=1000;

bool noob = false;
bool amateur = false;
bool pro = false;




int nR = 0, nG = 0, nB = 0;
int aR = 0, aG = 0, aB = 0;
int pR = 0, pG = 0, pB = 0;


int box_R = 0;
int box_G = 0;
int box_B = 0;

int sum = 0;

char score[100];
int index = 0;

int endID;

int gameChance = 3;
bool gameOver = false;

char name[20];

bool enteringName = false;
int box_X = 300;
int box_Y = 300;
int box_W = 300;
int box_H = 50;


void splashEffect();
void bouncingBall();
void collision();
void ballMovement();
void constructBricks();
void menu();
void initializeDifficulty();

int brick = 0;
double dxBall;
double dyBall;
double delX = 0;
double delY = 0;

int menuImgID;
int menuID;
int overID;
int winID;

bool win = false;
char printScore[20];

bool showMenu = true;

bool atRest = true;
bool move_NE = false;
bool move_NW = false;

int r, g, b ;
int x = 250, y = 250;
char arr[100];
int i = 0;
int dx = 1;
int dy = 1;
bool musicOn = true;
int id;
int backgroundImg;


//***********board**********
int board;
int boardX=500, boardY=10;
int boardDx=140, boardDy=20;





#endif