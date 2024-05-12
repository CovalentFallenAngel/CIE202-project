#pragma once
#include <string>
using namespace std;
#include "CMUgraphicsLib\CMUgraphics.h"

class game;     //forward declaration

struct point
{
	int x, y;

public:
	friend bool operator==(const point& lhs, const point& rhs) {
		return (abs(lhs.x - rhs.x) <= 5 && abs(lhs.y - rhs.y) <= 5);
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
public:
    shape(game* r_pGame, point ref, bool isComposite = false);
    virtual void draw(int x) const = 0;//for a shape to draw itself on the screen
	void setRefPoint(point p);
	void setcolor(color c);
	void setbordercolor(color c);
	void setRotationAngle(int increment);
	int getRotationAngle();
	point getPosition() const;
	virtual void rotate(point reference);
	virtual void resize(double factor, point composite_reference) = 0;
	virtual void matching_detection(game* pGame) = 0;
	virtual void move(char c) = 0;
	virtual void flip();

};




