#include "grid.h"
#include "game.h"
#include "gameConfig.h"
#include<cstdlib>
#include<time.h>


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
//point grid::randomPoint() {
//	return point{ rand() % cols * config.gridSpacing + uprLeft.x, rand() % rows * config.gridSpacing + uprLeft.y };
//}
//point grid::randomPoint() {
//	int x = rand() % (cols - 1) * config.gridSpacing + uprLeft.x;
//	int y = rand() % (rows - 1) * config.gridSpacing + uprLeft.y;
//	return point{ x, y };
//}
point grid::randomPoint() {
	int x = 60+ rand() %(1340-60+1) ;
	int y = 90+ rand() % (530-90+1);
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
	shapeList[shapeCount++] = newShape;
	return true;
}

void grid::setActiveShape(shape* actShape)
{
	activeShape = actShape;
}

int grid:: randomSize() {
	double random = 1 + rand() % 6, rndsize = (1 / random);
	return rndsize ; // Generate a random size 
}
void grid::addRandomShape()
{
	// Generate a random shape type
	int shapeType = rand() % 6; // Generate a random number between 0 and 6 (inclusive)

	// Generate a random point and size
	point p = randomPoint();
	int s = randomSize();
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
		newShape = new Rocket(pGame, p,s);
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
	addShape(newShape);
}

shape* grid::getActiveShape() {
	return activeShape;
}

shape** grid::getShapeList() {
	return &shapeList[0];
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

