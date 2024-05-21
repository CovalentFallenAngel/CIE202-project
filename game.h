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
	bool isThinking;
	int num_matched;
	int num_matched_lvl;
	int powerUpX;
	int powerUpY;
	bool powerUpVisible;
	int powerUpDuration;
	bool good = false;
	bool isLevelingUp;
protected:
	int level, lives, steps, score, sec, act;
	int step1 = 80;

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
	void setScore(int s);
	void setLevel(int lev);
	void setLives(int live);
	void setsec(int s);
	void setact(int a);
	void setIsLevelingUp(bool);
	void actTimer(int xInteger);
	void thinkTimer(game* pGame);
	void matching_proxy();
	void increment_steps();
	void thread_hub();
	window* getWind() const;		//returns a pointer to the graphics window
	grid* getGrid() const;		//returns a pointer to the shapes grid
	toolbar* getToolBar() const;
	void decrement_lives();
	void increment_level();
	void increment_score();
	void decrement_score();
	int getMatched() const;
	void increment_match();
	void setThink(int i);
	void lost();
	void showPowerUp();
	int get_step1();
	void set_step1(int i);
	
	void levelup(game* pGame);
	void hidePowerUp();
	void powerUpTimer();
	void handlePowerUpClick(int x, int y);


	//creates an operation according to the toolbar item clicked
	operation* createRequiredOperation(toolbarItem clickedItem);

	friend void operSave::Act();
	friend void operLoad::Act();

	void run();	//start the game

};

