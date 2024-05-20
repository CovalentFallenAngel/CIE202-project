#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include "Basicshapes.h"


////////////////////////////////////////////////////  class Sign  ///////////////////////////////////////
//This class reprsents the composite shape "sign"
//The sign is composed of 2 Recatngles
/*				

					 ------------------
					|				   |
					|		 x		   |     x is the reference point of the Sign shape
					|			       |
					 ------------------
						   |   |
						   |   |
						   | . |
						   |   |
						   |   |
							---
*/

//Note: sign reference point is the center point of the top rectangle
class Sign :public shape
{
	Rect* base;
	Rect* top;

	point topRef;
	point baseRef;
public:
	Sign(game* r_pGame, point ref);
	~Sign();
	virtual void draw(int x = 5) const;
	virtual void move(char c) override;
	virtual void resize(double factor, point composite_reference) override;
	virtual void rotate(point reference);
	virtual void setcolor(color c) override;
	virtual color getColor()const override;
	virtual std::string getID() override;
	virtual void flip();
	virtual vector<point> getRevertedPoints() override;
	virtual vector<point> getPoints() override;
	virtual vector<point> getCorners() override;
	virtual double getRadius() override;
	virtual void saveOrnaments(ofstream& file) override;
	bool matching_detection(game* pGame, shape* predicate) override;


};

class Home : public shape {
	EqTriangle* top;
	Rect* base;
	int x = 1;
	
	point topRef;
	point baseRef;
public:
	Home(game* r_pGame, point ref);
	virtual void draw(int x = 5)const ;
	virtual void move(char c) override;
	virtual void resize(double factor, point composite_reference) override;
	virtual void rotate(point reference);
	virtual std::string getID() override;
	virtual void flip();
	virtual vector<point> getRevertedPoints() override;
	virtual vector<point> getPoints() override;
	virtual vector<point> getCorners() override;
	virtual double getRadius() override;
	virtual void saveOrnaments(ofstream& file) override;
	bool matching_detection(game* pGame, shape* predicate) override;
	virtual void setcolor(color c) override;
	virtual color getColor()const override;

};

class Person : public shape {
	circle* head;
	Rect* body;
	Rect* Rarm;
	Rect* Larm;
	Rect* Rleg;
	Rect* Lleg;

	point headRef;
	point bodyRef;
	point leftArmRef;
	point rightArmRef;
	point leftLegRef;
	point rightLegRef;
public:
	Person(game* r_pGame, point ref);
	~Person();
	virtual void draw(int x = 5) const;
	virtual void move(char c) override;
	virtual void resize(double factor, point composite_reference) override;
	virtual void rotate(point reference);
	virtual std::string getID() override;
	virtual void flip();
	virtual vector<point> getRevertedPoints() override;
	virtual vector<point> getPoints() override;
	virtual vector<point> getCorners() override;
	virtual double getRadius() override;
	virtual void saveOrnaments(ofstream& file) override;
	bool matching_detection(game* pGame, shape* predicate) override;
	virtual void setcolor(color c) override;
	virtual color getColor()const override;

};

class ice_cream :public shape {
	circle* scoop;
	EqTriangle* cone;
	int x = 0;
	point scoopRef;
	point coneRef;
public:
	ice_cream(game* r_pgame, point ref);
	~ice_cream();
	virtual void draw(int x = 0) const;
	virtual void move(char c) override;
	virtual void resize(double factor, point composite_reference) override;
	virtual void rotate(point reference);
	virtual std::string getID() override;
	virtual void flip();
	virtual vector<point> getRevertedPoints() override;
	virtual vector<point> getPoints() override;
	virtual vector<point> getCorners() override;
	virtual double getRadius() override;
	virtual void saveOrnaments(ofstream& file) override;
	bool matching_detection(game* pGame, shape* predicate) override;
	virtual void setcolor(color c) override;
	virtual color getColor()const override;
};

class Tree :public shape {
	EqTriangle* T1;
	EqTriangle* T2;
	EqTriangle* T3;
	Rect* body;
	int x = 1;

	point T1Ref;
	point T2Ref;
	point T3Ref;
	point bodyRef;
public:
	Tree(game* r_pgame, point ref);
	~Tree();
	virtual void draw(int x = 5) const;
	virtual void move(char c) override;
	virtual void resize(double factor, point composite_reference) override;
	virtual void rotate(point reference);
	virtual void flip();
	virtual std::string getID() override;
	virtual vector<point> getRevertedPoints() override;
	virtual vector<point> getPoints() override;
	virtual vector<point> getCorners() override;
	virtual double getRadius() override;
	virtual void saveOrnaments(ofstream& file) override;
	bool matching_detection(game* pGame, shape* predicate) override;
	virtual void setcolor(color c) override;
	virtual color getColor()const override;

};

class Rocket :public shape {
	EqTriangle* T1;
	RightTriangle* T2;
	RightTriangle* T3;
	Rect* body;

	point T1Ref, T2Ref, T3Ref, bodyRef;
public:
	Rocket(game* r_pgame, point ref);
	virtual void draw(int x =5) const;
	virtual void move(char c) override;
	virtual void resize(double factor, point composite_reference) override;
	virtual void rotate(point reference);
	virtual std::string getID() override;
	virtual void flip();
	virtual vector<point> getRevertedPoints() override;
	virtual vector<point> getPoints() override;
	virtual vector<point> getCorners() override;
	virtual double getRadius() override;
	virtual void saveOrnaments(ofstream& file) override;
	bool matching_detection(game* pGame, shape* predicate) override;
	virtual void setcolor(color c) override;
	virtual color getColor()const override;

};

class Car : public shape {
	RightTriangle* T1;
	Rect* R1;
	Rect* R2;
	circle* C1;
	circle* C2;

	point T1Ref;
	point C1Ref;
	point C2Ref;
	point R1Ref;
	point R2Ref;
public:
	Car(game* r_pGame, point ref);
	virtual void draw(int x = 5) const;
	virtual void move(char c) override;
	virtual void resize(double factor, point composite_reference) override;
	virtual void rotate(point reference);
	virtual std::string getID() override;
	virtual void flip();
	virtual vector<point> getRevertedPoints() override;
	virtual vector<point> getPoints() override;
	virtual vector<point> getCorners() override;
	virtual double getRadius() override;
	virtual void saveOrnaments(ofstream& file) override;
	bool matching_detection(game* pGame, shape* predicate) override;
	virtual void setcolor(color c) override;
	virtual color getColor()const override;
}; 