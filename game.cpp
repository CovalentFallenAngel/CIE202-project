#include "game.h"
#include "gameConfig.h"
#include <thread>
#include <memory>
#include<chrono>
using namespace std;



game::game()
{
	level = 1;
	score = 0;
	lives = 5;
	steps = 0;
	sec = 21;
	act = 31;
	isThinking = false;
	isLevelingUp = true;
	num_matched = 0;
	num_matched_lvl = 0;


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
	if (shapesGrid != nullptr) {
		delete shapesGrid;
	}
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

int game::getMatched() const {
	return num_matched;
}

int game::get_step1() {
	return step1;
}

void game::set_step1(int i) {
	step1 = i;
}

void game::setThink(int i) {
	if (i == 0)
		isThinking = false;
	else if (i == 1)
		isThinking = true;
}

int game::get_steps() const { return steps; }

void game::setScore(int s) { score = s; }

void game::setLives(int live) { lives = live; }

void game::setLevel(int lev) { level = lev; }

void game::increment_steps() { 
	int xInteger = config.toolbarItemWidth * 18 + 65;
	int clevel = level - 1;
	if (steps != 80 && level < 3) {
		set_step1(80);
		steps += 1;
		pWind->SetFont(20, BOLD, MODERN, "Arial");
		pWind->SetPen(config.bkGrndColor);
		pWind->SetBrush(config.bkGrndColor);
		pWind->DrawRectangle(xInteger + 96, 0, 1350, 20);
		pWind->SetPen(BLACK);
		pWind->DrawInteger(xInteger + 96, 0, steps);
		toolbar* tb = getToolBar();
		delete tb;
		tb = nullptr;
		createToolBar();
		
		if (steps == 80) {
			lives -= 1;
			steps = 0;
		}

		if (lives == 0)
			lost();
	}

	if (good == true) {
		steps = 0;
		good = false;
	}

	if (steps != 200 && level > 2) {
		set_step1(200);
		steps += 1;
		pWind->SetFont(20, BOLD, MODERN, "Arial");
		pWind->SetPen(config.bkGrndColor);
		pWind->SetBrush(config.bkGrndColor);
		pWind->DrawRectangle(xInteger + 96, 0, 1350, 20);
		pWind->SetPen(BLACK);
		pWind->DrawInteger(xInteger + 96, 0, steps);
		toolbar* tb = getToolBar();
		delete tb;
		tb = nullptr;
		createToolBar();
		
		if (steps == 200) {
			lives -= 1;
			steps = 0;
		}

		if (lives == 0)
			lost();
	}

}


void game::decrement_lives() {
	int xInteger = config.toolbarItemWidth * 17 + 65;
	lives -= 1;
	pWind->SetFont(20, BOLD, MODERN, "Arial");
	pWind->SetPen(config.bkGrndColor);
	pWind->SetBrush(config.bkGrndColor);
	pWind->DrawRectangle(xInteger + 3, 0, 1147, 20);
	pWind->SetPen(BLACK);
	pWind->DrawInteger(xInteger, 0, lives);
	toolbar* tb = getToolBar();
	delete tb;
	tb = nullptr;
	createToolBar();
}

void game::setIsLevelingUp(bool cond) {
	isLevelingUp = cond;
}

void game::increment_level() {
	int xInteger = config.toolbarItemWidth * 18 + 65;
	level += 1;
	setIsLevelingUp(true);
	pWind->SetFont(20, BOLD, MODERN, "Arial");
	pWind->SetPen(config.bkGrndColor);
	pWind->SetBrush(config.bkGrndColor);
	pWind->DrawRectangle(xInteger, 20, 1250, 40);
	pWind->SetPen(BLACK);
	pWind->DrawInteger(xInteger, 20, level);
	toolbar* tb = getToolBar();
	delete tb;
	tb = nullptr;
	createToolBar();
}

void game::increment_score() {
	int xInteger = config.toolbarItemWidth * 18 + 65;
	score += 2;
	pWind->SetFont(20, BOLD, MODERN, "Arial");
	pWind->SetPen(config.bkGrndColor);
	pWind->SetBrush(config.bkGrndColor);
	pWind->DrawRectangle(xInteger, 40, 1260, 60);
	pWind->SetPen(BLACK);
	pWind->DrawInteger(xInteger, 40, score);
	toolbar* tb = getToolBar();
	delete tb;
	tb = nullptr;
	createToolBar();
}

void game::decrement_score() {
	int xInteger = config.toolbarItemWidth * 18 + 65;
	score -= 1;
	pWind->SetFont(20, BOLD, MODERN, "Arial");
	pWind->SetPen(config.bkGrndColor);
	pWind->SetBrush(config.bkGrndColor);
	pWind->DrawRectangle(xInteger, 40, 1260, 60);
	pWind->SetPen(BLACK);
	pWind->DrawInteger(xInteger, 40, score);
	toolbar* tb = getToolBar();
	delete tb;
	tb = nullptr;
	createToolBar();
}

void game::increment_match() {
	int xInteger = config.toolbarItemWidth * 18 + 65;
	num_matched ++;
	pWind->SetFont(20, BOLD, MODERN, "Arial");
	pWind->SetPen(config.bkGrndColor);
	pWind->SetBrush(config.bkGrndColor);
	pWind->DrawRectangle(xInteger + 120, 40, 1366, 60);
	pWind->SetPen(BLACK);
	pWind->DrawInteger(xInteger + 120, 40, num_matched);
	toolbar* tb = getToolBar();
	delete tb;
	createToolBar();
}

void game::lost() {
	getWind()->SetPen(config.bkGrndColor);
	getWind()->SetBrush(config.bkGrndColor);
	getWind()->DrawRectangle(config.toolbarItemWidth * 17 + 65, 0, 1366, 60);
	getWind()->SetFont(40, BOLD, MODERN, "Arial");
	getWind()->SetPen(BLACK);
	getWind()->DrawString(config.toolbarItemWidth * 17 + 65, 0, "Game Over");
	setThink(1);
	Sleep(3000);
	delete pWind;
	delete shapesGrid;
	
}

void game::setsec(int s) { sec = s; }

void game::setact(int a) { act = a; }



void game::thinkTimer(game* pGame)
{
	int xInteger = config.toolbarItemWidth * 18 + 65;
	while (sec > 0) {
		clock_t stop = clock() + CLOCKS_PER_SEC;
		while (clock() < stop) {}
		sec--;
		
		pWind->SetPen(config.bkGrndColor);
		pWind->SetBrush(config.bkGrndColor);
		pWind->DrawRectangle(xInteger + 122, 20, 1366, 40);
		pWind->SetPen(BLACK);
		pWind->DrawInteger(xInteger + 122, 20, sec);
	}
	sec = 21;
	isThinking = false;
	thread actThread(&game::actTimer, this, xInteger);
	actThread.detach();
	
}

void game::actTimer(int xInteger){
	
	int n_matched = num_matched;
	while (act > 0) {
		clock_t stop = clock() + CLOCKS_PER_SEC;
		while (clock() < stop) {}
		act--;
		pWind->SetPen(config.bkGrndColor);
		pWind->SetBrush(config.bkGrndColor);
		pWind->DrawRectangle(xInteger + 122, 20, 1366, 40);
		pWind->SetPen(BLACK);
		pWind->DrawInteger(xInteger + 122, 20, act);
	}
	act = 31;

	bool wasMatched = (num_matched - n_matched > 0);

	if (/*act == 0 && */wasMatched == false) {
		decrement_lives();
		decrement_score();
	}

	if (lives == 0) {
		lost();
	}
	
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
////////////////////////////////////////power up//////////////////////////
void game::showPowerUp() {
	powerUpX = rand() % config.windWidth;
	powerUpY = (config.toolBarHeight)+rand() % (config.toolBarHeight- config.windHeight+1);
	powerUpVisible = true;
	powerUpDuration = 5;

	// Draw power-up on screen
	pWind->SetPen(BLUE);
	pWind->SetBrush(BLUE);
	pWind->DrawCircle(powerUpX, powerUpY, 20);

	// Start timer to hide power-up after 5 seconds
	thread powerUpThread(&game::powerUpTimer, this);
	powerUpThread.detach();

}

void game::hidePowerUp() {
	powerUpVisible = false;
	// Clear power-up from screen
	pWind->SetPen(config.bkGrndColor);
	pWind->SetBrush(config.bkGrndColor);
	pWind->DrawCircle(powerUpX, powerUpY, 20);
}

void game::powerUpTimer() {
	while (powerUpDuration > 0) {
		clock_t stop = clock() + CLOCKS_PER_SEC;
		while (clock() < stop) {}
		powerUpDuration--;
	}
	hidePowerUp();
}

void game::handlePowerUpClick(int x, int y) {
	if (powerUpVisible && (x - powerUpX) * (x - powerUpX) + (y - powerUpY) * (y - powerUpY) <= 400) { // Radius = 20
		powerUpVisible = false;
		hidePowerUp();

		// Remove one smaller shape
		shapesGrid->removeRandomShape();
	}
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
		op = new operResizeUp(this);
		increment_steps();
		break;
	case ITM_Dec:
		printMessage("You clicked on Downscale!");
		op = new operResizeDown(this);
		increment_steps();
		break;
	case ITM_Rotate:
		printMessage("You clicked on Rotate!");
		op = new operRotate(this);
		increment_steps();
		break;
	case ITM_Flip:
		printMessage("You clicked on Flip!");
		op = new operFlip(this);
		increment_steps();
		break;
	case ITM_Ref:
		printMessage("You clicked on Refresh!");
		op = new operRef(this);
		break;
	case ITM_Hint:
		if (level < 3) {
			printMessage("Hints are only given after level 3!");
		}
		else {
			op = new operHint(this);
			increment_steps();
		}
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
	case ITM_Load:
		printMessage("You clicked on Load!");
		op = new operLoad(this);
		break;
	case ITM_EXIT:
		printMessage("Do You want to save cuurent progress? (y/n): ");
		op = new operExit(this);
		break;
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
	auto startTime = chrono::steady_clock::now();
	vector<shape*> shape_array = this->getGrid()->getShapeList();
	shape* ashape = nullptr;
	shape* matchedShape = nullptr;
	int isMatched = 0;
	
	for (int i = 0; i < this->getGrid()->getShapeCount(); i++) {

		shape_array = this->getGrid()->getShapeList();
		if (shape_array[i] != nullptr) {

			ashape = this->getGrid()->getActiveShape();
			if (shape_array[i]->getID() == ashape->getID())
			{
				bool check = shape_array[i]->matching_detection(this, ashape);

				if (check == true) {
					isMatched++;
					num_matched_lvl++;
					increment_match();
					increment_score();
					if (num_matched_lvl >= 2 * level - 1) {
						increment_level();
						good = true;
						num_matched_lvl = 0;
					}
					delete shape_array[i];
					shape_array.erase(std::next(shape_array.begin(), i));
					this->getGrid()->setShapeCount(shape_array.size());
					this->getGrid()->setShapeList(shape_array);
					this->getGrid()->Delete();
					break;
				}
			}
		}

		toolbar* tb = getToolBar();
		delete tb;
		tb = nullptr;
		createToolBar();

	}
	auto endTime = chrono::steady_clock::now();
	auto elapsedTime = chrono::duration_cast<chrono::seconds>(endTime - startTime);

	// Show power-up if a match was made within 10 seconds
	if (elapsedTime.count() <= 10 && isMatched > 0) {
		showPowerUp();
	}
	
	if (isMatched == 0) {
		decrement_score();
	}
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
		pGrid = this->getGrid();
		pGrid->setKey(c);
		if (c == '1' && shapesGrid->getActiveShape() != nullptr) {
			isThinking = true;
			thinkTimer(this);
		}
		else if (kin == ARROW && isThinking == false) {
			operMove* p1 = new operMove(this);
			p1->Act();
		}
		else if (c == 32) {
			matching_proxy();
		}
		
	}
}

void game::run() 
{
	//This function reads the position where the user clicks to determine the desired operation
	int x, y;
	bool isExit = false;
	int current_level = level - 1;

	hub_thread = thread(&game::thread_hub, this);
	hub_thread.detach();

	
	//Change the title
	pWind->ChangeTitle("- - - - - - - - - - SHAPE HUNT Team 1 - - - - - - - - - -");
	toolbarItem clickedItem=ITM_CNT;
	
	do
	{
		//printMessage("Ready...");
		//1- Get user click
		//if (startacting) {
		if (level > current_level && isLevelingUp) {
			int numofShapes = (2 * level) - 1;
			for (int i = 0; i < numofShapes; i++) {
				shapesGrid->addRandomShape();
			}
			shapesGrid->draw();
			current_level = level;
		}
		pWind->WaitMouseClick(x, y);	//Get the coordinates of the user click
		if (powerUpVisible && isThinking == false) {
			handlePowerUpClick(x, y);
		}
		/*if (powerUpVisible) {
			handlePowerUpClick(x, y);
		}*/
		//2-Explain the user click
		//If user clicks on the Toolbar, ask toolbar which item is clicked
		if (y >= 0 && y < config.toolBarHeight && isThinking == false)
		{
			clickedItem = gameToolbar->getItemClicked(x);

			//3-create the approp operation accordin to item clicked by the user
			operation* op = createRequiredOperation(clickedItem);
			if (op)
				op->Act();

		}
		//4-Redraw the grid after each action

		shapesGrid->draw();
		
	} while (clickedItem!=ITM_EXIT);

	hub_thread.~thread();
}