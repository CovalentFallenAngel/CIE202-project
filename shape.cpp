#include "shape.h"
#include "game.h"
#include "gameConfig.h"
#include <iostream>
#include <fstream>
#include <thread>
#include <string>

shape::shape(game* r_pGame, point ref, bool isComposite)
{
	RefPoint = ref;
	pGame = r_pGame;
	this->isComposite = isComposite;
	isFlipped = false;
	fillColor = config.fillColor;
	borderColor = config.penColor;
	rotation_angle = 0;
	resizes = 0;

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

int shape::getRotationAngle() const{
	return rotation_angle;
}

void shape::setRefPoint(point p)
{
	RefPoint = p;
}
void shape::setcolor(color c) {
	fillColor = c;
	borderColor = c;
}
color shape::getColor() const {
	return fillColor;
}

point shape::getPosition() const
{
	return RefPoint;
}
void shape::rotate(point reference) {

}
void shape::flip() {

}

bool shape::matching_detection(game* pGame, shape* predicate) {
	return true;
}

void shape::saveOrnaments(ofstream& file) {

}

vector<point> shape::getPoints() {
	return vector<point>();
}

vector<point> shape::getRevertedPoints() {
	return vector<point>();
}

vector<point> shape::getCorners() {
	return vector<point>();
}

double shape::getRadius() {
	return NULL;
}

string shape::getID() {
	return "";
}

void shape::addResizes(int resize_num) {
	resizes += resize_num;
}

void shape::switchFlip() {
	if (isFlipped == true) {
		isFlipped = false;
	}
	else {
		isFlipped = true;
	}
}

int shape::getResizes() const {
	return resizes;
}