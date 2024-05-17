#include "game.h"
#include "gameConfig.h"
#include <thread>
#include <memory>
using namespace std;



game::game()
{
	level = 1;
	score = 0;
	lives = 5;
	steps = 0;
	sec = 11;
	act = 16;
	xsteps = 80;

	//Create the main window
	createWind(config.windWidth, config.windHeight, config.wx, config.wy);


	//Create and draw the grid
	//draw the grid and all shapes it contains.
	createGrid();
	shapesGrid->draw();
	
	//Create and clear the status bar
	clearStatusBar();

	//Create and draw the toolbar
	createToolBar();

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

int game::get_xsteps() const { return xsteps; }

int game::get_steps() const { return steps; }

void game::setScore(int s) { score = s; }

void game::setLives(int live) { lives = live; }

void game::setLevel(int lev) { level = lev; }

void game::increment_steps() { 
	int xInteger = config.toolbarItemWidth * 17 + 65;
	steps++;
	pWind->SetPen(config.bkGrndColor);
	pWind->SetBrush(config.bkGrndColor);
	pWind->DrawRectangle(xInteger + 100, 0, 1320, 20);
	pWind->SetPen(BLACK);
	pWind->DrawInteger(xInteger + 100, 0, steps);
	toolbar* tb = getToolBar();
	delete tb;
	createToolBar();
}

void game::decrement_xsteps() {
	int xInteger = config.toolbarItemWidth * 17 + 65;
	xsteps--;
	pWind->SetPen(config.bkGrndColor);
	pWind->SetBrush(config.bkGrndColor);
	pWind->DrawRectangle(xInteger + 100, 40, 1320, 60);
	pWind->SetPen(BLACK);
	pWind->DrawInteger(xInteger + 100, 40, xsteps);
	toolbar* tb = getToolBar();
	delete tb;
	createToolBar();
}

void game::setsec(int s) { sec = s; }

void game::setact(int a) { act = a; }

//bool startacting = false;

void game::thinkTimer(game* pGame)
{
	int xInteger = config.toolbarItemWidth * 17 + 65;
		
	if (shapesGrid->getActiveShape() != nullptr) {
		while (sec > 0) {
			clock_t stop = clock() + CLOCKS_PER_SEC;
			while (clock() < stop) {}
			sec--;
			
			pWind->SetPen(config.bkGrndColor);
			pWind->SetBrush(config.bkGrndColor);
			pWind->DrawRectangle(xInteger + 100, 20, 1320, 40);
			pWind->SetPen(BLACK);
			pWind->DrawInteger(xInteger + 100, 20, sec);
		}
		actTimer(xInteger);
	}

	//else if (k == 2 || k == 4 || k == 6 || k == 8) {
	//	getGrid()->getActiveShape()->move(c);
	//}

		//startacting = true;
	//thread act_thread(&game::actTimer, pGame, xInteger);
	//act_thread.detach();
}

//void game::levelup(game* pGame) {
//	if (sh->matching_detection(pGame) == true) {
//		int l = pGame->getLevel();
//		pGame->setLevel(l++);
//	}
//}

void game::actTimer(int xInteger){
	while (act > 0) {
		clock_t stop = clock() + CLOCKS_PER_SEC;
		while (clock() < stop) {}
		act--;
		pWind->SetPen(config.bkGrndColor);
		pWind->SetBrush(config.bkGrndColor);
		pWind->DrawRectangle(xInteger + 100, 20, 1320, 40);
		pWind->SetPen(BLACK);
		pWind->DrawInteger(xInteger + 100, 20, act);
	}

	//if (act == 0 && sh->matching_detection(pGame) == false) {
	//	score--;
	//	lives--;
	//}

	//else if (act > 0 && sh->matching_detection(pGame) == true) {
	//	score += 2;
	//	lives ++;
	//}
}

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

 toolbar* game::getToolBar() const {
	 return gameToolbar;
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
	if (op != nullptr) { delete op; }
	switch (clickedItem)
	{
	case ITM_SIGN:
		op = new operAddSign(this);
		printMessage("You clicked on the Sign shape!");
		break;
	case ITM_ICE:
		printMessage("You clicked on the Icecream shape!");
		op = new operAddice(this);
		break;
	case ITM_CAR:
		printMessage("You clicked on the Car shape!");
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
		printMessage("You clicked on Upscale!");
		operResize* Sizeup;
		Sizeup = new operResize(this);
		Sizeup->Actmain(1.1);
		break;
	case ITM_Dec:
		printMessage("You clicked on Downscale!");
		operResize* Sizedown;
		Sizedown = new operResize(this);
		Sizedown->Actmain(0.9);
		break;
	case ITM_Rotate:
		printMessage("You clicked on Rotate!");
		op = new operRotate(this);
		break;
	case ITM_Flip:
		printMessage("You clicked on Flip!");
		op = new operFlip(this);
		break;
	case ITM_Ref:
		printMessage("You clicked on Refresh!");
		break;
	case ITM_Hint:
		printMessage("You clicked on Hint!");
		break;
	case ITM_del:
		op = new operDelete(this);
		printMessage("You clicked on Delete!");
		break;
	case ITM_SGL:
		printMessage("Choose the game level and press Enter");
		op = new operSGL(this);
		break;
	case ITM_SAL:
		printMessage("You clicked on Save!");
		op = new operSave(this);
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



string game::getString() const
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

void game::matching_proxy() {
	shape** shape_array = this->getGrid()->getShapeList();
	int scount = this->getGrid()->getShapeCount();
	int isMatched = 0;
	for (int i = 0; i < scount; i++) {
		if ((*shape_array)[i].getID() == this->getGrid()->getActiveShape()->getID()) {
			bool check = (*shape_array)[i].matching_detection(this, this->getGrid()->getActiveShape());
			// ^^^ replace active shape with the array of random shapes ^^^

			if (check == true) {
				isMatched++;
			}
		}
	}

	if (isMatched != 0) {
		score += 2;
		getGrid()->Delete();
	}
	else {
		score--;
	}

	toolbar* tb = getToolBar();
	delete tb;
	createToolBar();
	
}

void game::thread_hub() {
	window* pWind = this->getWind();
	grid* pGrid = this->getGrid();
	while (true) {
		keytype kin;
		char c;
		pWind->FlushKeyQueue();
		pWind->FlushMouseQueue();
		kin = pWind->WaitKeyPress(c);
		pGrid->setKey(c);
		if (c == '1') {
			thinkTimer(this);
		}
		else if (kin == ARROW) {
			operMove* p1 = new operMove(this);
			p1->Act();
		}
		else if (c == 32) {
			matching_proxy();
		}
		
	}
}


////////////////////////////////////////////////////////////////////////
void game::run() 
{
	//This function reads the position where the user clicks to determine the desired operation
	int x, y;
	bool isExit = false;

	hub_thread = thread(&game::thread_hub, this);
	hub_thread.detach();

	/*operMove* p1;
	p1 = new operMove(this);
	thread new_thread(&operMove::Act, p1);
	new_thread.detach();*/

	if (level == 1) {
		shapesGrid->addRandomShape();
	}
	if (level == 2) {
		shapesGrid->addRandomShape();
		shapesGrid->addRandomShape();
	}

	//Change the title
	pWind->ChangeTitle("- - - - - - - - - - SHAPE HUNT Team 1 - - - - - - - - - -");
	toolbarItem clickedItem=ITM_CNT;
	do
	{
		//printMessage("Ready...");
		//1- Get user click
		//if (startacting) {
		
			pWind->WaitMouseClick(x, y);	//Get the coordinates of the user click
			
			//2-Explain the user click
			//If user clicks on the Toolbar, ask toolbar which item is clicked
			if (y >= 0 && y < config.toolBarHeight)
			{
				clickedItem = gameToolbar->getItemClicked(x);

				//3-create the approp operation accordin to item clicked by the user
				operation* op = createRequiredOperation(clickedItem);
				if (op)
					op->Act();

				//4-Redraw the grid after each action
				shapesGrid->draw();
				

			}
		
	} while (clickedItem!=ITM_EXIT);

	hub_thread.~thread();
}