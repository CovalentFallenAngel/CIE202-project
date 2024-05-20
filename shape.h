#pragma once
#include <string>
using namespace std;
#include <iostream>
#include <fstream>
#include <vector>
#include "CMUgraphicsLib\CMUgraphics.h"

class game;     //forward declaration

struct point
{
	int x, y;

public:
	friend bool operator==(const point& lhs, const point& rhs) {
		const int TOLERANCE = 30;
		return (abs(lhs.x - rhs.x) < TOLERANCE && abs(lhs.y - rhs.y) < TOLERANCE);
	}
};


enum ShapeType
{
	//Basic shapes
	RCT,	//rectangle
	CRC,	//circle
	TRI,	//triangle

	//Composite shapes
	SIGN,	//a street sign

	//TODO: Add more types
};

//Base class for all shapes including Basic shapes, Composite shapes
class shape
{
protected:
	point RefPoint;		//Each shape must have a reference point
    game* pGame;        //pointer to game object
	color fillColor;	//shape fill color
	color borderColor;	//shape border color
	int rotation_angle;
	bool isComposite;
	bool isFlipped;
	int resizes;
public:
    shape(game* r_pGame, point ref, bool isComposite = false);
    virtual void draw(int x) const = 0;//for a shape to draw itself on the screen
	void setRefPoint(point p);
	void setcolor(color c);
	void setbordercolor(color c);
	void setRotationAngle(int increment);
	int getRotationAngle();
	point getPosition() const;
	virtual vector<point> getPoints();
	virtual vector<point> getCorners();
	virtual double getRadius();
	virtual string getID();
	virtual void rotate(point reference);
	virtual void resize(double factor, point composite_reference) = 0;
	virtual bool matching_detection(game* pGame, shape* predicate) = 0;
	virtual void move(char c) = 0;
	virtual void flip();
	virtual void saveOrnaments(ofstream& file);
	void addResizes(int resizes);
	void switchFlip();
};




