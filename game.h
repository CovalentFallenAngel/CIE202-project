#pragma once
#include "CMUgraphicsLib\CMUgraphics.h"
#include "toolbar.h"
#include "operations.h"
#include "grid.h"



//Main class that coordinates the game operation
class game
{

	/// Add more members if needed

	shape* sh;
	toolbar* gameToolbar;
	
	window* pWind;	//Pointer to the CMU graphics window
	grid* shapesGrid;

	shape* newshape;
	/*int level, lives, steps;*/

	thread hub_thread;
protected:
	int level, lives, steps, score, sec, act, xsteps;


public:
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
	int get_xsteps() const;
	void setScore(int s);
	void setLevel(int lev);
	void setLives(int live);
	void setsec(int s);
	void setact(int a);
	void actTimer(int xInteger);
	void thinkTimer(game* pGame);
	void matching_proxy();
	void increment_steps();
	void thread_hub();
	window* getWind() const;		//returns a pointer to the graphics window
	grid* getGrid() const;		//returns a pointer to the shapes grid
	toolbar* getToolBar() const;
	void decrement_xsteps();
	void decrement_lives();
	void increment_level();
	//void levelup(game* pGame);

	//creates an operation according to the toolbar item clicked
	operation* createRequiredOperation(toolbarItem clickedItem);

	friend void operSave::Act();
	friend void operLoad::Act();

	void run();	//start the game

};

