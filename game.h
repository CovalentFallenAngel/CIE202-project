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
	toolbar* gameToolbar;
	
	window* pWind;	//Pointer to the CMU graphics window
	grid* shapesGrid;
	int level, score, lives, steps;

public:
	game();
	~game();

	string getSrting() const;	 //Returns a string entered by the user
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
	void increment_steps();
	window* getWind() const;		//returns a pointer to the graphics window
	grid* getGrid() const;		//returns a pointer to the shapes grid
	toolbar* getToolBar() const;

	//creates an operation according to the toolbar item clicked
	operation* createRequiredOperation(toolbarItem clickedItem);



	void run();	//start the game

};

