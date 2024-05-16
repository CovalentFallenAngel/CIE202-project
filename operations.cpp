#include "operations.h"
#include "game.h"
#include "CompositeShapes.h"
#include <fstream>
#include <limits>
#include <sstream>
#include <iostream>
#include <memory>

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
	int size = 1;
	//create a Rocket shape
	shape* shape = new Rocket(pGame, RocketShapeRef,size);

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

void operLoad::Act()
{
}


operMove::operMove(game* r_pGame) : operation(r_pGame)
{
}



void operMove::Act() {
	window* pWind = pGame->getWind();
	grid* pGrid = pGame->getGrid();
	keytype kin;
	char key;
	bool ismoving = true;
	do {
		kin = pWind->WaitKeyPress(key);
		pWind->FlushKeyQueue();
		pWind->FlushMouseQueue();
		if (kin == ARROW && pGrid->getActiveShape() != nullptr)
		{
			shape* as = pGrid->getActiveShape();

			as->move(key);

			pGame->increment_steps(); // count the steps
			pGame->decrement_steps();
			//pGame->levelup(pGame);

		}
		else if (kin == ESCAPE)
			ismoving = false;

		pGrid->draw();

	} while (ismoving);
}