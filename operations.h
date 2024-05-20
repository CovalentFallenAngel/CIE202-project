#pragma once
using namespace std;
#include <iostream>
class game;
/////////////////////////////////// class operation  //////////////////
//Base class of all operations supported by the application
class operation
{
protected:
	game* pGame;	//pointer to the game class
public:
	operation(game* r_pGame);

	//Function Act:
	//Implements the action that should be taken by this operation
	//Should be overriden by derived classes
	virtual void Act() = 0;
};
/////////////////////////////////// class operAddSign  //////////////////
//Responsible for 
//1- collectign data about a new Sign shape to add
//2- Adding the new shape to the list of shapes (throgh the grid class)
class operAddSign:public operation
{
public:
	operAddSign(game* r_pGame);
	virtual void Act();
};

class operAddHome :public operation
{
public:
	operAddHome(game* r_pGame);
	virtual void Act();
};

class operMove : public operation {
public:
	operMove(game* r_pGame);
	virtual void Act();
};

class operAddPerson :public operation
{
public:
	operAddPerson(game* r_pGame);
	virtual void Act();
};

class operAddice :public operation
{
public:
	operAddice(game* r_pGame);
	virtual void Act();
};


//////////////////////////////// class operAddRocket //////////////////
//Responsible for 
/// 1 - collecting data about a new Rocket shape to add
/// 2 - Adding the new shape to the list of shapes
class operAddRocket :public operation
{
public:
	operAddRocket(game* r_pGame);
	virtual void Act();
};

//////////////////////////////// class operAddTree //////////////////
//Responsible for 
/// 1 - collecting data about a new Tree shape to add
/// 2 - Adding the new shape to the list of shapes
class operAddTree :public operation
{
public:
	operAddTree(game* r_pGame);
	virtual void Act();
};

//////////////////////////////// class operAddCar //////////////////
//Responsible for 
/// 1 - collecting data about a new car shape to add
/// 2 - Adding the new shape to the list of shapes

class operAddCar :public operation
{
public:
	operAddCar(game* r_pGame);
	virtual void Act();
};



//////////////////////////////// class operResizeUp //////////////////
//Responsible for changing the size of a shape
class operResizeUp :public operation
{
public:
	operResizeUp(game* r_pGame);
	virtual void Act();
};

//////////////////////////////// class operResizeDown //////////////////

class operResizeDown :public operation
{
public:
	operResizeDown(game* r_pGame);
	virtual void Act();
};

//////////////////////////////// class operRotate //////////////////
//Responsible for rotating the shape
class operRotate :public operation
{
public:
	operRotate(game* r_pGame);
	virtual void Act();
};

class operFlip :public operation
{
public:
	operFlip(game* r_pGame);
	virtual void Act();
};

//////////////////////////////// class operDelete //////////////////
//Responsible for deleting shape from the grid
class operDelete :public operation
{
public:
	operDelete(game* r_pGame);
	virtual void Act();
};

//////////////////////////////// class OperHint //////////////////
//Responsible for giving a hint to the player
class operHint :public operation
{
public:
	operHint(game* r_pGame);
	virtual void Act();
};

//////////////////////////////// class OperSGL //////////////////
//Responsible for selecting game level
class operSGL :public operation
{
public:
	operSGL(game* r_pGame);
	virtual void Act();
};

//////////////////////////////// class OperSave //////////////////
//Responsible for saving the progress of a player and loading it
class operSave :public operation
{
public:
	operSave(game* r_pGame);
	virtual void Act();

};

//////////////////////////////// class operLoad //////////////////
//Responsible for loading saved progress from a file
class operLoad :public operation
{
public:
	operLoad(game* r_pGame);
	virtual void Act();
};


class operRef :public operation
{
public:
	operRef(game* r_pGame);
	virtual void Act();
};

class operExit :public operation
{
public:
	operExit(game* r_pGame);
	virtual void Act();
};