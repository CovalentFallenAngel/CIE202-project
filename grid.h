#pragma once
#include "CompositeShapes.h"
#include "operations.h"

class game;

class grid
{
	enum { MaxShapeCount = 1000 };	//assuming max shape count = 1000

	int rows, cols;	//numner of rows and columns in the grid to draw grid points
	int height, width;
	point uprLeft;	//upper left point of the grid

	//ShapeList should hold the RANDOMLY generated shapes
	vector<shape*>shapeList;	//2D array of shape pointers

	shape* activeShape;	//The shape that the user works on to match to the ranom shapes
	int rnd;
	int shapeCount;		//current number of shapes in the list
	game* pGame;
	char key;
public:
	grid(point r_uprleft, int r_width, int r_height, game* r_pGame);
	~grid();
	void draw() const;
	void clearGridArea() const;
	bool addShape(shape* newShape);
	void setActiveShape(shape* actShape);
	vector<shape*> getShapeList();
	void setShapeList(vector<shape*> new_list);
	int getShapeCount();
	void setShapeCount(int count);
	void setKey(char key);
	char getKey();

	point randomPoint();
	void randomSize(int resize_times, shape* newShape, point RPoint);
	void randomFlip(int Flip_times, shape* newshape);
	void randomrotate(int rotate_times, shape* newshape, point RPoint);
	void addRandomShape();
	shape* getActiveShape();
	void Delete();


	friend void operSave::Act();
};

