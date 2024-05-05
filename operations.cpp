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

operAddSign::operAddSign(game* r_pGame):operation(r_pGame)
{
}

void operAddSign::Act()
{
	window* pw = pGame->getWind();
	//Add the shape to the grid
	grid* pGrid = pGame->getGrid();
	//if (pGrid->getActiveShape() != nullptr)
	//{
	//	return; // Exit the function if there is already an active shape
	//}
	//align reference point to the nearest grid point
	int xGrid = config.RefX - config.RefX % config.gridSpacing;
	int yGrid = config.RefY - config.RefX % config.gridSpacing;

	
	//take the aligned point as the sign shape ref point
	point signShapeRef = { xGrid,yGrid };

	//create a sign shape
	shape* psh = new Sign(pGame, signShapeRef);

	
	pGrid->setActiveShape(psh);

}

operAddHome::operAddHome(game* r_pGame):operation(r_pGame)
{
}

void operAddHome::Act()
{
	window* pw = pGame->getWind();


	//align reference point to the nearest grid point
	int xGrid = config.RefX - config.RefX % config.gridSpacing;
	int yGrid = config.RefY - config.RefX % config.gridSpacing;

	//take the aligned point as the sign shape ref point
	point homeShapeRef = { xGrid,yGrid };

	//create a sign shape
	shape* psh = new Home(pGame, homeShapeRef);

	//Add the shape to the grid
	grid* pGrid = pGame->getGrid();
	pGrid->setActiveShape(psh);

}

operAddPerson::operAddPerson(game* r_pGame):operation(r_pGame)
{
}
void operAddPerson::Act()
{
	window* pw = pGame->getWind();

	//TODO:
	// Don't allow adding new shape if there is alreday an active shape

	//align reference point to the nearest grid point
	int xGrid = config.RefX - config.RefX % config.gridSpacing;
	int yGrid = config.RefY - config.RefX % config.gridSpacing;

	//take the aligned point as the sign shape ref point
	point PearsonShapeRef = { xGrid,yGrid };

	//create a sign shape
	shape* psh = new Person(pGame, PearsonShapeRef);

	//Add the shape to the grid
	grid* pGrid = pGame->getGrid();
	pGrid->setActiveShape(psh);

}

operAddice::operAddice(game* r_pGame):operation(r_pGame)
{
}

void operAddice::Act()
{
	window* pw = pGame->getWind();

	//align reference point to the nearest grid point
	int xGrid = config.RefX - config.RefX % config.gridSpacing;
	int yGrid = config.RefY - config.RefX % config.gridSpacing;

	//take the aligned point as the sign shape ref point
	point iceShapeRef = { xGrid,yGrid };

	//create a sign shape
	shape* psh = new ice_cream(pGame, iceShapeRef);

	//Add the shape to the grid
	grid* pGrid = pGame->getGrid();
	pGrid->setActiveShape(psh);

}

operAddTree::operAddTree(game* r_pGame):operation(r_pGame)
{
}
void operAddTree::Act()
{
	window* pw = pGame->getWind();

	//align reference point to the nearest grid point
	int xGrid = config.RefX - config.RefX % config.gridSpacing;
	int yGrid = config.RefY - config.RefX % config.gridSpacing;

	//take the aligned point as the sign shape ref point
	point TreeShapeRef = { xGrid,yGrid };

	//create a sign shape
	shape* psh = new Tree(pGame, TreeShapeRef);

	//Add the shape to the grid
	grid* pGrid = pGame->getGrid();
	pGrid->setActiveShape(psh);

}

operAddRocket::operAddRocket(game* r_pGame) :operation(r_pGame)
{
}
void operAddRocket::Act()
{
	window* pw = pGame->getWind();
	grid* pGrid = pGame->getGrid();
	//if (pGrid->getActiveShape() != nullptr)
	//{
	//	return; // Exit the function if there is already an active shape
	//}
	//align reference point to the nearest grid point
	int xGrid = config.RefX - config.RefX % config.gridSpacing;
	int yGrid = config.RefY - config.RefX % config.gridSpacing;

	//take the aligned point as the Rocket shape ref point
	point RocketShapeRef = { xGrid,yGrid };

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
	//if (pGrid->getActiveShape() != nullptr)
	//{
	//	return; // Exit the function if there is already an active shape
	//}
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

void operResize::Act(){}

void operResize::Actmain(double factor)
{
	//// phase 2
	 grid* pGrid = pGame->getGrid();
	 shape* shape = pGrid->getActiveShape();
	 shape->resize(factor);
	 pGrid->clearGridArea();
	 pGrid->setActiveShape(shape);
}

operRotate::operRotate(game* r_pGame) :operation(r_pGame)
{
}

void operRotate::Act()
{
	// phase 2
	
	grid* pGrid = pGame->getGrid();
	shape* shape = pGrid->getActiveShape();
	point p = shape->getPosition();
	shape->rotate(p);
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
	
}

operSave::operSave(game* r_pGame) :operation(r_pGame)
{
}
void operSave::Act()
{
}

void operSave::Actmain(string filename)
{
	std::ofstream outfile(filename); 
	outfile << "Player score: " << pGame->getScore() << "\n";
	outfile << "Levels completed: " << pGame->getLevel() << "\n";
	outfile << "Lives: " << pGame->getLives() << "\n";
	outfile << "\n";

	outfile.close();
}

operLoad::operLoad(game* r_pGame) :operation(r_pGame)
{
}

void operLoad::Act()
{
}
void operLoad::Actmain(string filename) {

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
		if (kin == ARROW)
		{
			switch (key)
			{
			case 2:
				pGrid->getActiveShape()->move(key);
				ismoving = true;
				break;
			case 4:
				pGrid->getActiveShape()->move(key);
				ismoving = true;
				break;
			case 6:
				pGrid->getActiveShape()->move(key);
				ismoving = true;
				break;
			case 8:
				pGrid->getActiveShape()->move(key);
				ismoving = true;
				break;
			}

			pGame->increment_steps(); // count the steps

		}
		else if (kin == ESCAPE)
			ismoving = false;

		pGrid->draw();

	} while (ismoving);
}