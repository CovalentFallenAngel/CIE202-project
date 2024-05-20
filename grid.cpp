#include "grid.h"
#include "game.h"
#include "gameConfig.h"
#include<cstdlib>
#include<time.h>
#include <cmath>


grid::grid(point r_uprleft, int wdth, int hght, game* pG)
{
	uprLeft = r_uprleft;
	height = hght;
	width = wdth;
	pGame = pG;
	rows = height / config.gridSpacing;
	cols = width / config.gridSpacing;
	shapeCount = 0;
	srand(time(nullptr));
	key = NULL;

	for (int i = 0; i < MaxShapeCount; i++)
		shapeList[i] = nullptr;

	activeShape = nullptr;

}

grid::~grid()
{
	for (int i = 0; i < shapeCount; i++)
		delete shapeList[i];
}

void grid::draw() const
{
	clearGridArea();
	window* pWind = pGame->getWind();
	
	pWind->SetPen(config.gridDotsColor,1);
	pWind->SetBrush(config.gridDotsColor);

	//draw dots showing the grid reference points
	for (int r = 1; r < rows; r++)
		for (int c = 0; c < cols; c++)
			pWind->DrawCircle(c * config.gridSpacing, r * config.gridSpacing + uprLeft.y, 1);
			//pWind->DrawPixel(c * config.gridSpacing, r * config.gridSpacing + uprLeft.y);

	//Draw ALL shapes
	for (int i = 0; i < shapeCount; i++)
			if (shapeList[i])
				shapeList[i]->draw(1);	//draw each shape

	//Draw the active shape
	if(activeShape)
		activeShape->draw(1);
}

void grid::Delete()
{
	delete activeShape;
	activeShape = nullptr;
	clearGridArea();
	window* pWind = pGame->getWind();
	

	pWind->SetPen(config.gridDotsColor, 1);
	pWind->SetBrush(config.gridDotsColor);

	for (int r = 1; r < rows; r++)
		for (int c = 0; c < cols; c++)
			pWind->DrawCircle(c * config.gridSpacing, r * config.gridSpacing + uprLeft.y, 1);

	for (int i = 0; i < shapeCount; i++)
		if (shapeList[i])
			shapeList[i]->draw(1);
}

void grid::clearGridArea() const
{
	window* pWind = pGame->getWind();	
	pWind->SetPen(config.bkGrndColor, 1);
	pWind->SetBrush(config.bkGrndColor);
	pWind->DrawRectangle(uprLeft.x, uprLeft.y, uprLeft.x + width, uprLeft.y + height);
}

//////////////////////////////Generate Random Points///////////////////////////

point grid::randomPoint() {
	int x = 120+ rand() %(240-120+1) ;
	int y = 160+ rand() % (470-160+1);
	x -= x % config.gridSpacing;
	y -= y % config.gridSpacing+6;
	return point{ x, y };
}

//Adds a shape to the randomly created shapes list.
bool grid::addShape(shape* newShape)
{
	//TODO:
	// 1- Check that the shape can be drawn witout being clipped by grid boundaries
	// 2- check shape count doesn't exceed maximum count
	// return false if any of the checks fail

	
	//Here we assume that the above checks are passed
	shapeList[shapeCount++] = newShape;
	return true;
}

void grid::setActiveShape(shape* actShape)
{
	activeShape = actShape;
}

//////////////////////////////Generate Random Size///////////////////////////
void grid:: randomSize(int reize_times, shape* &newshape ) {
	for (int i = 0; i < abs(reize_times); i++) {
		if (reize_times > 0) {
			newshape->resize(1.1, newshape->getPosition());
		}
		else {
			newshape->resize(0.9, newshape->getPosition());
		}
	}
}

//////////////////////////////Generate Random Flip///////////////////////////
void grid::randomFlip(int Flip_times, shape*& newshape)
{
	for (int i = 0; i < Flip_times; i++) {
		newshape->flip();
	}
}

//////////////////////////////Generate Random Rotate///////////////////////////
void grid::randomrotate(int rotate_times, shape* newshape)
{
	for (int i = 0; i < rotate_times; i++) {
		newshape->rotate(newshape->getPosition());
	}
}


void grid::addRandomShape()
{
	// Generate a random shape type
	int shapeType = 1+ rand() % (6-1+1); // Generate a random number between 1 and 6 (inclusive)

	// Generate a random point 
	point p = randomPoint();
	//Generate a random number for rotate,flip and size
	int s = -2+ rand() %(2-(-2)+1) ;
	int r = rand() % 4 ;
	int f = rand() % 4 ;
	int rnd = 1 + rand() % (10 - 1 + 1);
	// Create a random shape based on the generated type, point
	shape* newShape =nullptr;
	switch (shapeType) {
	case 1:
		newShape = new Car(pGame, p);
		break;
	case 2:
		newShape = new Home(pGame, p);
		break;
	case 3:
		newShape = new Rocket(pGame, p);
		break;
	case 4:
		newShape = new ice_cream(pGame, p);
		break;
	case 5:
		newShape = new Person(pGame, p);
		break;
	case 6:
		newShape = new Tree(pGame, p);
		break;
	}
	randomSize(s, newShape);
	randomFlip(f, newShape);
	randomrotate(r, newShape);
	if (pGame->getLevel() < 3) {
		randomizecolor(rnd, newShape);
	}
	else {
		newShape->setcolor(BLACK);
		window* pw = pGame->getWind();
	}
	addShape(newShape);
}

void grid::randomizecolor(int rnd,shape* newshape) {
	switch (rnd)
	{
	case 1:
		newshape->setbordercolor(ORANGE);
		newshape->setcolor(ORANGE);
		break;
	case 2:
		newshape->setbordercolor(GREY);
		newshape->setcolor(GREY);
		break;
	case 3:
		newshape->setbordercolor(BLUE);
		newshape->setcolor(BLUE);
		break;
	case 4:
		newshape->setbordercolor(VIOLET);
		newshape->setcolor(VIOLET);
		break;
	case 5:
		newshape->setbordercolor(BROWN);
		newshape->setcolor(BROWN);
		break;
	case 6:
		newshape->setbordercolor(GREEN);
		newshape->setcolor(GREEN);
		break;
	case 7:
		newshape->setbordercolor(DARKGOLDENROD);
		newshape->setcolor(DARKGOLDENROD);
		break;
	case 8:
		newshape->setbordercolor(DARKMAGENTA);
		newshape->setcolor(DARKMAGENTA);
		break;
	case 9:
		newshape->setbordercolor(WHITESMOKE);
		newshape->setcolor(WHITESMOKE);
		break;
	case 10:
		newshape->setbordercolor(CYAN);
		newshape->setcolor(CYAN);
		break;
	}
}

shape* grid::getActiveShape() {
	return activeShape;
}

shape* grid::getShapeList() {
	return shapeList[0];
}

int grid::getShapeCount() {
	return shapeCount;
}


char grid::getKey() {
	return key;
}

void grid::setKey(char k) {
	key = k;
}

