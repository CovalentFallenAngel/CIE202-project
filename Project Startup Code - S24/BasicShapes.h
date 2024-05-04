//Header file for Basic shapes in the game
#pragma once
#include "shape.h"
#include <vector>

////////////////////////////////////////////////////  class Rect  ///////////////////////////////////////
//Rectanle class
/*							wdth
					---------------------
					|					|
			hght    |		 x			|     x is the reference point of the rectangle
					|					|
					--------------------
*/


class Rect:public shape
{
	int hght, wdth;	//height and width of the rectangle
	point upperLeft, lowerBottom;
public:
	Rect(game* r_pGame, point ref, int r_hght, int r_wdth);
	virtual void draw(int x) const;
	virtual void move(char c) override;
	virtual void resize(double factor) override;
	virtual void rotate(point reference);
	virtual void flip(point reference);

};

class RectangleTransform {
private:
	point trans_ref{};
	vector<double> dims;
	vector<double> trans_dims;
	vector<point> trans_coords;
	point ref{};
public:
	RectangleTransform(point reference, vector<double> dimensions);
	point get_trans_ref();
	vector<double> get_trans_dims();
	vector<point> get_trans_coords();
	void rotate(point reference, double angle = -90);
	
};

////////////////////////////////////////////////////  class circle  ///////////////////////////////////////
//Reference point of the circle is its center
class circle :public shape
{
	//Add data memebrs for class circle
	int rad;
public:	
	circle(game* r_pGame, point ref, int r);	//add more parameters for the constructor if needed
	virtual void draw(int x) const;
	virtual void move(char c) override;
	virtual void resize(double factor) override;
	virtual void rotate(point reference);
	virtual void flip(point reference);

};



class EqTriangle : public shape {
public:
	EqTriangle(game* r_pGame, point ref, int SL, int x = 1);
	virtual void move(char c) override;
	virtual void draw(int x) const;
	virtual void resize(double factor) override;
	virtual void rotate(point reference);
	virtual void flip(point reference);

private:
	int side_length;
	int x;
	point point1, point2, point3;
};


class RightTriangle : public shape {
public:
	RightTriangle(game* r_pGame, point ref, int BL, int H, int x);
	virtual void move(char c) override;
	virtual void draw(int x) const;
	virtual void resize(double factor) override;
	virtual void rotate(point reference);
	virtual void flip(point reference);

private:
	int height, base_length;
	int x;
	point point1, point2, point3;
};

class TriangleTransform {
private:
	vector<point> coords;
	vector<point> trans_coords;
	point ref{};

public:
	TriangleTransform(point p1, point p2, point p3);
	point get_trans_ref();
	vector<point> get_transformed_coords();
	vector<point> get_coords();
	void rotate(point ref, double angle = -90);
};