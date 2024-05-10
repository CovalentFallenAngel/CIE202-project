#include "shape.h"
#include "game.h"
#include "gameConfig.h"

shape::shape(game* r_pGame, point ref)
{
	RefPoint = ref;
	pGame = r_pGame;
	fillColor = config.fillColor;
	borderColor = config.penColor;
	rotation_angle = 0;
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