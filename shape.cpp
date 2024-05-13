#include "shape.h"
#include "game.h"
#include "gameConfig.h"
#include <iostream>
#include <fstream>
#include <thread>

shape::shape(game* r_pGame, point ref, bool isComposite)
{
	RefPoint = ref;
	pGame = r_pGame;
	this->isComposite = isComposite;
	fillColor = config.fillColor;
	borderColor = config.penColor;
	rotation_angle = 0;

	if (isComposite) {
		//thread matching_detection_thread(&game::matching_detection, pGame);
		//matching_detection_thread.detach();
	}
}

void shape::setRotationAngle(int increment) {
	rotation_angle += increment;

	while (rotation_angle < 0) {
		rotation_angle += 360;
	}
	while (rotation_angle >= 360) {
		rotation_angle %= 360;
	}
}

int shape::getRotationAngle() {
	return rotation_angle;
}

void shape::setRefPoint(point p)
{
	RefPoint = p;
}
void shape::setcolor(color c) {
	fillColor = c;
}

void shape::setbordercolor(color c)
{
	borderColor = c;
}

point shape::getPosition() const
{
	return RefPoint;
}
void shape::rotate(point reference) {

}
void shape::flip() {

}

void shape::matching_detection(game* pGame) {
}

void shape::saveOrnaments(ofstream& file) {

}