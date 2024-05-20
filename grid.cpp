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

	/*for (int i = 0; i < MaxShapeCount; i++)
		shapeList[i] = nullptr;*/

	activeShape = nullptr;

}

grid::~grid()
{
	/*for (int i = 0; i < shapeCount; i++)
		delete[] shapeList[i];*/
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
			if (shapeList[i] != nullptr)
				shapeList[i]->draw(1);	//draw each shape

	//Draw the active shape
	if(activeShape != nullptr)
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
	y -= y % config.gridSpacing;
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
	shapeList.push_back(newShape);
	shapeCount = shapeList.size();
	return true;
}

void grid::setActiveShape(shape* actShape)
{
	activeShape = actShape;
}

//////////////////////////////Generate Random Size///////////////////////////
void grid:: randomSize(int resize_times, shape* newshape, point RPoint) {
	for (int i = 0; i < abs(resize_times); i++) {
		if (resize_times > 0) {
			newshape->resize(1.1, RPoint);
		}
		else {
			newshape->resize(0.9, RPoint);
		}
	}
}

//////////////////////////////Generate Random Flip///////////////////////////
void grid::randomFlip(int Flip_times, shape* newshape)
{
	for (int i = 0; i < Flip_times; i++) {
		newshape->flip();
	}
}

//////////////////////////////Generate Random Rotate///////////////////////////
void grid::randomrotate(int rotate_times, shape* newshape, point RPoint)
{
	for (int i = 0; i < rotate_times; i++) {
		newshape->rotate(RPoint);
	}
}


void grid::addRandomShape()
{
	// Generate a random shape type
	int shapeType = rand() % 6 + 1; // Generate a random number between 0 and 6 (inclusive)

	// Generate a random point 
	point p = randomPoint();
	//Generate a random number for rotate,flip and size
	int s = -2+ rand() %(2-(-2)+1) ;
	int r = rand() % 4 ;
	int f = rand() % 4 ;
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
	randomSize(s, newShape, p);
	randomFlip(f, newShape);
	randomrotate(r, newShape, p);
	addShape(newShape);
}

shape* grid::getActiveShape() {
	return activeShape;
}

vector<shape*> grid::getShapeList() {
	return shapeList;
}

void grid::setShapeList(vector<shape*> new_list) {
	shapeList = new_list;
}

int grid::getShapeCount() {
	return shapeCount;
}

void grid::setShapeCount(int count) {
	shapeCount = count;
}


char grid::getKey() {
	return key;
}

void grid::setKey(char k) {
	key = k;
}

