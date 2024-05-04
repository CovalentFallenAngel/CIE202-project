#pragma once
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
	virtual void draw(int x = 5) const;
	virtual void move(char c) override;
	virtual void resize(double factor) override;
	virtual void rotate();
	virtual void flip();
};

class Home : public shape {
	EqTriangle* top;
	Rect* base;
	int x = 1;
public:
	Home(game* r_pGame, point ref);
	virtual void draw(int x = 5)const ;
	virtual void move(char c) override;
	virtual void resize(double factor) override;
	virtual void rotate();
	virtual void flip();
};

class Person : public shape {
	circle* head;
	Rect* body;
	Rect* Rarm;
	Rect* Larm;
	Rect* Rleg;
	Rect* Lleg;
public:
	Person(game* r_pGame, point ref);
	virtual void draw(int x = 5) const;
	virtual void move(char c) override;
	virtual void resize(double factor) override;
	virtual void rotate();
	virtual void flip();
};

class ice_cream :public shape {
	circle* scoop;
	EqTriangle* cone;
	int x = 0;
public:
	ice_cream(game* r_pgame, point ref);
	virtual void draw(int x = 0) const;
	virtual void move(char c) override;
	virtual void resize(double factor) override;
	virtual void rotate();
	virtual void flip();
};

class Tree :public shape {
	EqTriangle* T1;
	EqTriangle* T2;
	EqTriangle* T3;
	Rect* body;
	int x = 1;
public:
	Tree(game* r_pgame, point ref);
	virtual void draw(int x = 5) const;
	virtual void move(char c) override;
	virtual void resize(double factor) override;
	virtual void rotate();
	virtual void flip();
};

class Rocket :public shape {
	EqTriangle* T1;
	RightTriangle* T2;
	RightTriangle* T3;
	Rect* body;
public:
	Rocket(game* r_pgame, point ref);
	virtual void draw(int x =5) const;
	virtual void move(char c) override;
	virtual void resize(double factor) override;
	virtual void rotate();
	virtual void flip();
};

class Car : public shape {
	RightTriangle* T1;
	Rect* R1;
	Rect* R2;
	circle* C1;
	circle* C2;
public:
	Car(game* r_pGame, point ref);
	virtual void draw(int x = 5) const;
	virtual void move(char c) override;
	virtual void resize(double factor) override;
	virtual void rotate();
	virtual void flip();
}; 