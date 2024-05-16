#pragma once
#include "CMUgraphicsLib\CMUgraphics.h"
#include "toolbar.h"
#include "operations.h"
#include "grid.h"



//Main class that coordinates the game operation
class game
{

	/// Add more members if needed
	//chicco 
	// santa
	toolbar* gameToolbar;
	
	window* pWind;	//Pointer to the CMU graphics window
	grid* shapesGrid;
	shape* newshape;
	int level, lives, steps;

public:
	int score, sec, act;
	game();
	~game();

	string getString() const;	 //Returns a string entered by the user
	void createWind(int, int, int, int); //creates the game window
	void clearStatusBar() const;	//Clears the status bar
	void printMessage(string msg) const;	//Print a message on Status bar
	void createToolBar();		//creates the toolbar
	void createGrid();		//creates the shapes grid
	int getLevel() const;
	int getScore() const;
	int getLives()const;
	int get_steps() const;
	void setScore(int s);
	void setLevel(int lev);
	void setLives(int live);
	void game::setsec(int s);
	void game::setact(int a);
	void game::actTimer(int xInteger);
	void game::thinkTimer(int xInteger, game* pGame);
	void increment_steps();
	window* getWind() const;		//returns a pointer to the graphics window
	grid* getGrid() const;		//returns a pointer to the shapes grid
	toolbar* getToolBar() const;

	//creates an operation according to the toolbar item clicked
	operation* createRequiredOperation(toolbarItem clickedItem);



	void run();	//start the game

};

