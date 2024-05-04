#include "game.h"
#include "gameConfig.h"
using namespace std;



game::game()
{
	level = 1;
	score = 0;
	lives = 5;
	//Create the main window
	createWind(config.windWidth, config.windHeight, config.wx, config.wy);

	//Create and draw the toolbar
	createToolBar();

	//Create and draw the grid
	createGrid();
	shapesGrid->draw();	//draw the grid and all shapes it contains.

	//Create and clear the status bar
	clearStatusBar();
}

game::~game()
{
	delete pWind;
	delete shapesGrid;
}

int game::getLevel() const {
	return level;
}

int game::getLives() const {
	return lives;
}

int game::getScore() const {
	return score;
}
void game::setScore(int s) { score = s; }

void game::setLives(int live) { lives = live; }

void game::setLevel(int lev) { level = lev; }


//////////////////////////////////////////////////////////////////////////////////////////
void game::createWind(int w, int h, int x, int y) 
{
	pWind = new window(w, h, x, y);
	pWind->SetBrush(config.bkGrndColor);
	pWind->SetPen(config.bkGrndColor, 1);
	pWind->DrawRectangle(0, 0, w, h);
}
//////////////////////////////////////////////////////////////////////////////////////////
void game::clearStatusBar() const
{
	//Clear Status bar by drawing a filled rectangle
	pWind->SetPen(config.statusBarColor, 1);
	pWind->SetBrush(config.statusBarColor);
	pWind->DrawRectangle(0, config.windHeight - config.statusBarHeight, config.windWidth, config.windHeight);
}

//////////////////////////////////////////////////////////////////////////////////////////
//Draws the menu (toolbar) in the mode
void game::createToolBar()
{
	gameToolbar = new toolbar(this);
}

void game::createGrid()
{	
	//calc some grid parameters
	point gridUpperLeftPoint = { 0, config.toolBarHeight };
	int gridHeight = config.windHeight - config.toolBarHeight - config.statusBarHeight;
	//create the grid
	shapesGrid = new grid(gridUpperLeftPoint, config.windWidth, gridHeight, this);
}

operation* game::createRequiredOperation(toolbarItem clickedItem)
{
	operation* op=nullptr;
	switch (clickedItem)
	{
	case ITM_SIGN:
		op = new operAddSign(this);
		printMessage("You clicked on the Sign shape!");
		break;
	case ITM_ICE:
		printMessage("You clicked on the icecream shape!");
		op = new operAddice(this);
		break;
	case ITM_CAR:
		printMessage("You clicked on the car shape!");
		op = new operAddCar(this);
		break;
	case ITM_Person:
		printMessage("You clicked on the Person shape!");
		op = new operAddPerson(this);
		break;
	case ITM_Home:
		printMessage("You clicked on the Home shape!");
		op = new operAddHome(this);
		break;
	case ITM_Rocket:
		printMessage("You clicked on the Rocket shape");
		op = new operAddRocket(this);
		break;
	case ITM_Tree:
		printMessage("You clicked on the Tree shape!");
		op = new operAddTree(this);
		break;
	case ITM_Inc:
		printMessage("You clicked on Increase");
		operResize* Sizeup;
		Sizeup = new operResize(this);
		Sizeup->Actmain(1.1);
		break;
	case ITM_Dec:
		printMessage("You clicked on decrease");
		operResize* Sizedown;
		Sizedown = new operResize(this);
		Sizedown->Actmain(0.9);
		break;
	case ITM_Rotate:
		printMessage("You clicked on rotate!");
		op = new operRotate(this);
		op->Act();
		break;
	case ITM_Ref:
		printMessage("You clicked on refresh");
		break;
	case ITM_Hint:
		printMessage("You clicked on Hint");
		break;
	case ITM_del:
		op = new operDelete(this);
		op->Act();
		printMessage("You clicked on Delete");
		break;
	case ITM_SGL:
		printMessage("You clicked on select game level");
		operLoad* operL;
		operL = new operLoad(this);
		operL->Actmain("Saved_Data.Txt");
		break;
	case ITM_SAL:
		
		printMessage("You clicked on save");
		operSave* oper;
		oper = new operSave(this);
		oper->Actmain("Saved_Data.Txt");
		break;
	
	case ITM_EXIT:
	default:
		break;
	}
	return op;
}


//////////////////////////////////////////////////////////////////////////////////////////

void game::printMessage(string msg) const	//Prints a message on status bar
{
	clearStatusBar();	//First clear the status bar

	pWind->SetPen(config.penColor, 50);
	pWind->SetFont(24, BOLD, BY_NAME, "Arial");
	pWind->DrawString(10, config.windHeight - (int)(0.85 * config.statusBarHeight), msg);
}



window* game::getWind() const		//returns a pointer to the graphics window
{
	return pWind;
}



string game::getSrting() const
{
	string Label;
	char Key;
	keytype ktype;
	pWind->FlushKeyQueue();
	while (1)
	{
		ktype = pWind->WaitKeyPress(Key);
		if (ktype == ESCAPE)	//ESCAPE key is pressed
			return "";	//returns nothing as user has cancelled label
		if (Key == 13)	//ENTER key is pressed
			return Label;
		if (Key == 8)	//BackSpace is pressed
			if (Label.size() > 0)
				Label.resize(Label.size() - 1);
			else
				Key = '\0';
		else
			Label += Key;
		printMessage(Label);
	}
}

grid* game::getGrid() const
{
	// TODO: Add your implementation code here.
	return shapesGrid;
}



////////////////////////////////////////////////////////////////////////
void game::run() 
{
	//This function reads the position where the user clicks to determine the desired operation
	int x, y;
	bool isExit = false;

	

	//Change the title
	pWind->ChangeTitle("- - - - - - - - - - SHAPE HUNT Team 1 - - - - - - - - - -");
	toolbarItem clickedItem=ITM_CNT;
	do
	{
		//printMessage("Ready...");
		//1- Get user click
		pWind->WaitMouseClick(x, y);	//Get the coordinates of the user click

		//2-Explain the user click
		//If user clicks on the Toolbar, ask toolbar which item is clicked
		if (y >= 0 && y < config.toolBarHeight)
		{
			clickedItem=gameToolbar->getItemClicked(x);

			//3-create the approp operation accordin to item clicked by the user
			operation* op = createRequiredOperation(clickedItem);
			if (op)
				op->Act();

			//4-Redraw the grid after each action
			shapesGrid->draw();

		}	


		operMove* p1;
		p1 = new operMove(this);
		p1->Act();
		
	//	keytype kin;
	//	char key;
	//	bool ismoving = true;
	//	do{
	//		kin = pWind->WaitKeyPress(key);
	//		pWind->FlushKeyQueue();
	//		pWind->FlushMouseQueue();
	//		operMove* p1;
	//		p1 = new operMove(this);
	//		if (kin == ARROW)
	//		{
	//			switch (key)
	//			{
	//			case 2:
	//				p1->Actmain(key);
	//				ismoving = true;
	//				break;
	//			case 4:
	//				p1->Actmain(key);
	//				ismoving = true;
	//			case 6:
	//				p1->Actmain(key);
	//				ismoving = true;
	//			case 8:
	//				p1->Actmain(key);
	//				ismoving = true;
	//			}
	//		}
	//		else if (kin == ESCAPE)
	//			ismoving = false;
	//		shapesGrid->draw();
	//		
	//	}while (ismoving);




	} while (clickedItem!=ITM_EXIT);
}