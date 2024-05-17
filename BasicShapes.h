//Header file for Basic shapes in the game
#pragma once
#include "shape.h"
#include <iostream>
#include <fstream>
#include <string>
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
	double hght, wdth;	//height and width of the rectangle
	point upperLeft, lowerBottom;
public:
	Rect(game* r_pGame, point ref, int r_hght, int r_wdth);
	virtual void draw(int x) const;
	virtual void move(char c) override;
	virtual void resize(double factor, point composite_reference) override;
	virtual void rotate(point reference);
	virtual void flip(point reference);
	virtual void set_dims(vector<double> dims);
	virtual void calculate_points();
	virtual void calculate_reference();
	virtual vector<point> getPoints() override;
	virtual vector<point> getCorners() override;
	virtual double getRadius() override;
	virtual void saveOrnaments(ofstream& file) override;
	bool matching_detection(game* pGame, shape* predicate) override;

};

class RectangleTransform {
private:
	point rotate_ref{};
	point flip_ref{};
	vector<double> dims;
	vector<double> rotate_dims;
	vector<double> flip_dims;
	vector<point> flip_coords;
	vector<point> rotate_coords;
	point ref{};
public:
	RectangleTransform(point reference, vector<double> dimensions);
	point get_rot_ref();
	point get_flip_ref();
	vector<double> get_rot_dims();
	vector<double> get_flip_dims();
	vector<point> get_rot_coords();
	vector<point> get_flip_coords();
	virtual void rotate(point reference, double angle = -90);
	virtual void flip(point reference);
	
};

////////////////////////////////////////////////////  class circle  ///////////////////////////////////////
//Reference point of the circle is its center
class circle :public shape
{
	//Add data memebrs for class circle
	double rad;
public:	
	circle(game* r_pGame, point ref, int r);	//add more parameters for the constructor if needed
	virtual void draw(int x) const;
	virtual void move(char c) override;
	virtual void resize(double factor, point composite_reference) override;
	virtual void rotate(point reference);
	virtual void flip(point reference);
	virtual vector<point> getPoints() override;
	virtual vector<point> getCorners() override;
	virtual double getRadius() override;
	virtual void saveOrnaments(ofstream& file) override;
	bool matching_detection(game* pGame, shape* predicate);

};



class EqTriangle : public shape {
public:
	EqTriangle(game* r_pGame, point ref, int SL, int x = 1);
	virtual void move(char c) override;
	virtual void draw(int x) const;
	virtual void resize(double factor, point composite_reference) override;
	virtual void rotate(point reference);
	virtual void flip(point reference);
	virtual void calculate_reference();
	virtual void saveOrnaments(ofstream& file) override;
	bool matching_detection(game* pGame, shape* predicate) override;
	virtual vector<point> getPoints() override;
	virtual vector<point> getCorners() override;
	virtual double getRadius() override;

private:
	double side_length;
	int x;
	point point1, point2, point3;
	point composite_reference{};
};


class RightTriangle : public shape {
public:
	RightTriangle(game* r_pGame, point ref, int BL, int H, int x);
	virtual void move(char c) override;
	virtual void draw(int x) const;
	virtual void resize(double factor, point composite_reference) override;
	virtual void rotate(point reference);
	virtual void flip(point reference);
	virtual void calculate_reference();
	vector<point> getPoints() override;
	vector<point> getCorners() override;
	double getRadius() override;
	virtual void saveOrnaments(ofstream& file) override;
	bool matching_detection(game* pGame, shape* predicate) override;

private:
	double height, base_length;
	int x;
	point point1, point2, point3;
	point composite_reference{};
};

class TriangleTransform {
private:
	vector<point> coords;
	vector<point> rotate_coords;
	vector<point> reflect_coords;
	point ref{};
	point flip_ref{};

public:
	TriangleTransform(point p1, point p2, point p3);
	vector<point> get_rotated_coords();
	vector<point> get_flip_coords();
	vector<point> get_coords();
	point get_flip_ref();
	void rotate(point ref, double angle = -90);
	void reflect(point ref);
};