#include "operations.h"
#include "game.h"
#include "CompositeShapes.h"
#include <fstream>
#include <limits>
#include <sstream>
#include <iostream>

/////////////////////////////////// class operation  //////////////////
operation::operation(game* r_pGame)
{
	pGame = r_pGame;
}


/////////////////////////////////// class operAddSign  //////////////////

operAddSign::operAddSign(game* r_pGame) :operation(r_pGame)
{
}

void operAddSign::Act()
{
	window* pw = pGame->getWind();
	//Add the shape to the grid
	grid* pGrid = pGame->getGrid();
	if (pGrid->getActiveShape() != nullptr)
	{
		return; // Exit the function if there is already an active shape
	}
	//align reference point to the nearest grid point
	int xGrid = config.RefX - config.RefX % config.gridSpacing;
	int yGrid = config.RefY - config.RefX % config.gridSpacing;


	//take the aligned point as the sign shape ref point
	point signShapeRef = { xGrid,yGrid };

	//create a sign shape
	shape* psh = new Sign(pGame, signShapeRef);


	pGrid->setActiveShape(psh);

}

operAddHome::operAddHome(game* r_pGame) :operation(r_pGame)
{
}

void operAddHome::Act()
{
	window* pw = pGame->getWind();
	grid* pGrid = pGame->getGrid();
	if (pGrid->getActiveShape() != nullptr)
	{
		return; // Exit the function if there is already an active shape
	}

	//align reference point to the nearest grid point
	int xGrid = config.RefX - config.RefX % config.gridSpacing;
	int yGrid = config.RefY - config.RefX % config.gridSpacing;

	//take the aligned point as the sign shape ref point
	point homeShapeRef = { xGrid,yGrid };

	shape* psh = new Home(pGame, homeShapeRef);

	//Add the shape to the grid
	pGrid->setActiveShape(psh);

}

operAddPerson::operAddPerson(game* r_pGame) :operation(r_pGame)
{
}
void operAddPerson::Act()
{
	window* pw = pGame->getWind();

	grid* pGrid = pGame->getGrid();
	if (pGrid->getActiveShape() != nullptr)
	{
		return; // Exit the function if there is already an active shape
	}

	//align reference point to the nearest grid point
	int xGrid = config.RefX - config.RefX % config.gridSpacing;
	int yGrid = config.RefY - config.RefX % config.gridSpacing;

	//take the aligned point as the Person shape ref point
	point PearsonShapeRef = { xGrid,yGrid };

	shape* psh = new Person(pGame, PearsonShapeRef);

	//Add the shape to the grid
	pGrid->setActiveShape(psh);

}

operAddice::operAddice(game* r_pGame) :operation(r_pGame)
{
}

void operAddice::Act()
{
	window* pw = pGame->getWind();
	grid* pGrid = pGame->getGrid();
	if (pGrid->getActiveShape() != nullptr)
	{
		return; // Exit the function if there is already an active shape
	}
	//align reference point to the nearest grid point
	int xGrid = config.RefX - config.RefX % config.gridSpacing;
	int yGrid = config.RefY - config.RefX % config.gridSpacing;

	//take the aligned point as the  Ice-cream shape ref point
	point iceShapeRef = { xGrid,yGrid };

	//create a Ice-cream shape
	shape* psh = new ice_cream(pGame, iceShapeRef);

	//Add the shape to the grid
	pGrid->setActiveShape(psh);

}

operAddTree::operAddTree(game* r_pGame) :operation(r_pGame)
{
}
void operAddTree::Act()
{
	window* pw = pGame->getWind();
	grid* pGrid = pGame->getGrid();
	if (pGrid->getActiveShape() != nullptr)
	{
		return; // Exit the function if there is already an active shape
	}
	//align reference point to the nearest grid point
	int xGrid = config.RefX - config.RefX % config.gridSpacing;
	int yGrid = config.RefY - config.RefX % config.gridSpacing;

	//take the aligned point as the Tree shape ref point
	point TreeShapeRef = { xGrid,yGrid };

	//create a Tree shape
	shape* psh = new Tree(pGame, TreeShapeRef);

	//Add the shape to the grid
	pGrid->setActiveShape(psh);

}

operAddRocket::operAddRocket(game* r_pGame) :operation(r_pGame)
{
}
void operAddRocket::Act()
{
	window* pw = pGame->getWind();
	grid* pGrid = pGame->getGrid();
	if (pGrid->getActiveShape() != nullptr)
	{
		return; // Exit the function if there is already an active shape
	}
	//align reference point to the nearest grid point
	int xGrid = config.RefX - config.RefX % config.gridSpacing;
	int yGrid = config.RefY - config.RefX % config.gridSpacing;

	//take the aligned point as the Rocket shape ref point
	point RocketShapeRef = { xGrid,yGrid };
	double size = 1;
	//create a Rocket shape
	shape* shape = new Rocket(pGame, RocketShapeRef);

	//Add the shape to the grid
	pGrid->setActiveShape(shape);

}


operAddCar::operAddCar(game* r_pGame) :operation(r_pGame)
{
}
void operAddCar::Act()
{
	window* pw = pGame->getWind();
	grid* pGrid = pGame->getGrid();
	if (pGrid->getActiveShape() != nullptr)
	{
		return; // Exit the function if there is already an active shape
	}
	//align reference point to the nearest grid point
	int xGrid = config.RefX - config.RefX % config.gridSpacing;
	int yGrid = config.RefY - config.RefX % config.gridSpacing;

	//take the aligned point as the sign shape ref point
	point signShapeRef = { xGrid,yGrid };

	//create a car shape
	shape* shape = new Car(pGame, signShapeRef);

	//Add the shape to the grid
	pGrid->setActiveShape(shape);

}


operResize::operResize(game* r_pGame) :operation(r_pGame)
{
}

void operResize::Act() {}

void operResize::Actmain(double factor)
{
	 grid* pGrid = pGame->getGrid();
	 shape* shape = pGrid->getActiveShape();
	 shape->resize(factor, shape->getPosition());
	 pGrid->clearGridArea(); 
	 pGrid->setActiveShape(shape);
}

operRotate::operRotate(game* r_pGame) :operation(r_pGame) {}

void operRotate::Act()
{
	grid* pGrid = pGame->getGrid();
	shape* shape = pGrid->getActiveShape();
	if (shape != nullptr) {
		point p = shape->getPosition();
		shape->rotate(p);
		shape->draw(1);
	}
}

operFlip::operFlip(game* r_pGame) :operation(r_pGame) {}

void operFlip::Act() {
	grid* pGrid = pGame->getGrid();
	shape* shape = pGrid->getActiveShape();
	if (shape != nullptr) {
		shape->flip();
	}
}



operDelete::operDelete(game* r_pGame) :operation(r_pGame)
{
}
void operDelete::Act()
{
	grid* pGrid = pGame->getGrid();
	pGrid->Delete();
}

operHint::operHint(game* r_pGame) :operation(r_pGame)
{
	shape* myShape = pGame->getGrid()->getActiveShape();
	myShape->setcolor(RED);
	myShape->draw(1);
	Sleep(200);
	myShape->setcolor(BLACK);
	myShape->draw(1);
}
void operHint::Act()
{
}

operSGL::operSGL(game* r_pGame) :operation(r_pGame)
{
}
void operSGL::Act()
{
	
	int level = stoi(pGame->getString());
	pGame->setLevel(level);
	toolbar* tb = pGame->getToolBar();
	delete tb;
	pGame->createToolBar();
}

operSave::operSave(game* r_pGame) :operation(r_pGame)
{
}
void operSave::Act()
{
	ofstream file("saved_data.txt");
	file << pGame->getScore() << " " << pGame->getLevel() << " " << pGame->getLives() << endl;
	int num = pGame->getGrid()->shapeCount;
	for (int i = 0; i < num; i++) {
		if (pGame->getGrid()->shapeList[i]) {
			pGame->getGrid()->shapeList[i]->saveOrnaments(file);
		}
	}
	file.close();
}

operLoad::operLoad(game* r_pGame) :operation(r_pGame)
{
}

void reconstruct_shape(shape* newShape, int rot_angle, int resizes, bool isFlipped) {
	newShape->setRotationAngle(rot_angle);
	int rot_num = newShape->getRotationAngle() / 90;

	for (int j = 0; j < rot_num; j++) {
		newShape->rotate(newShape->getPosition());
	}

	if (isFlipped) {
		newShape->flip();
	}

	if (resizes < 0) {

		for (int k = 0; k < abs(resizes); k++) {
			newShape->resize(0.9, newShape->getPosition());
		}
	}

	else if (resizes >= 0) {

		for (int k = 0; k < resizes; k++) {
			newShape->resize(1.1, newShape->getPosition());
		}
	}
}

void operLoad::Act()
{
	ifstream file("saved_data.txt");
	vector<string>retrieved_data;
	string data;
	while (file >> data) {
		retrieved_data.push_back(data);
	}

	pGame->score = stoi(retrieved_data[0]);
	pGame->level = stoi(retrieved_data[1]);
	pGame->lives = stoi(retrieved_data[2]);

	grid* old_grid = pGame->getGrid();
	delete old_grid;
	pGame->createGrid();

	for (int i = 3; i < retrieved_data.size(); i += 12) {
		shape* newShape = nullptr;
		string shape_name = retrieved_data[i];
		point RPoint{ stoi(retrieved_data[i + 1]), stoi(retrieved_data[i + 2]) };
		int rot_angle = stoi(retrieved_data[i + 3]);
		int resizes = stoi(retrieved_data[i + 4]);
		bool isFlipped = stoi(retrieved_data[i + 5]);

		if (shape_name == "Car") {
			newShape = new Car(pGame, RPoint);
		}
		else if (shape_name == "Home") {
			newShape = new Home(pGame, RPoint);
		}
		else if (shape_name == "Rocket") {
			newShape = new Rocket(pGame, RPoint);
		}
		else if (shape_name == "Ice-Cream") {
			newShape = new ice_cream(pGame, RPoint);
		}
		else if (shape_name == "Person") {
			newShape = new Person(pGame, RPoint);
		}
		else if (shape_name == "Tree") {
			newShape = new Tree(pGame, RPoint);
		}
		reconstruct_shape(newShape, rot_angle, resizes, isFlipped);
		pGame->getGrid()->addShape(newShape);
	}

	file.close();
}


operRef::operRef(game* r_pGame) : operation(r_pGame) 
{
}


void operRef::Act()
{
	grid* pGrid = pGame->getGrid();
	delete pGrid;
	pGame->createGrid();
	pGrid = pGame->getGrid();
	int lev = pGame->getLevel();
	int l = pGame->getLives();
	int x;
	x = (2 * lev) - 1;
	if (l > 0) {
		for (int i = 0; i < x; i++) {
			pGrid->addRandomShape();
		}
		pGame->decrement_lives();
	}
	if (l == 0) {
		pGame->getWind()->SetPen(config.bkGrndColor);
		pGame->getWind()->SetBrush(config.bkGrndColor);
		pGame->getWind()->DrawRectangle(config.toolbarItemWidth * 17 + 65, 0, 1190, 20);
		pGame->getWind()->SetPen(BLACK);
		pGame->getWind()->DrawString(config.toolbarItemWidth * 17 + 65, 0, "Game Over");
		//pGame->getWind()->SetPen(WHITE);
		//pGame->getWind()->SetBrush(WHITE);
		//pGame->getWind()->DrawRectangle(550, 200, 700, 300);
		//pGame->getWind()->SetPen(BLACK, 5);
		//pGame->getWind()->SetFont(20, BOLD, MODERN, "Arial");
		//pGame->getWind()->DrawString(650, 300, "Game Over");
		pGame->setThink(1);
	}
}


operMove::operMove(game* r_pGame) : operation(r_pGame)
{
}



void operMove::Act() {
	window* pWind = pGame->getWind();
	grid* pGrid = pGame->getGrid();
	char key = pGrid->getKey();
	
	if (pGrid->getActiveShape() != nullptr)
	{
		shape* as = pGrid->getActiveShape();

		as->move(key);

		pGame->increment_steps(); // count the steps
		//pGame->levelup(pGame);
		pGrid->draw();
		
	}
}