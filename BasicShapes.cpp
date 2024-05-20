#include <vector>
#include "BasicShapes.h"
#include "gameConfig.h"
#include <iostream>
#include <fstream>
#include <string>
#include "game.h"

point rotate_coordinates(point coords, double angle, point origin);
point reflect_coordinates(point coords, point origin);

////////////////////////////////////////////////////  class Rect  ///////////////////////////////////////

void Rect::calculate_reference() {
	RefPoint.x = upperLeft.x + wdth / 2;
	RefPoint.y = upperLeft.y + hght / 2;
}

void Rect::calculate_points() {
	upperLeft.x = RefPoint.x - wdth / 2;
	upperLeft.y = RefPoint.y - hght / 2;
	lowerBottom.x = RefPoint.x + wdth / 2;
	lowerBottom.y = RefPoint.y + hght / 2;
}

Rect::Rect(game* r_pGame, point ref, int r_hght, int r_wdth) :shape(r_pGame, ref)
{
	pGame = r_pGame;
	hght = r_hght;
	wdth = r_wdth;

	this->calculate_points();
}

void Rect::set_dims(vector<double> dims) {
	this->wdth = dims[0]; this->hght = dims[1];
}

void Rect::draw(int x = 1) const
{
	window* pW = pGame->getWind();	//get interface window
	pW->SetPen(config.penColor, config.penWidth);
	pW->SetBrush(config.fillColor);

	pW->DrawRectangle(upperLeft.x, upperLeft.y, lowerBottom.x, lowerBottom.y, FILLED);
}

void Rect::resize(double factor, point composite_reference) {
	this->hght *= factor;
	this->wdth *= factor;

	this->calculate_points();
	resizes++;
}

void Rect::rotate(point reference)
{
	vector<double> dimensions; dimensions.push_back(this->wdth); dimensions.push_back(this->hght);

	RectangleTransform RT(this->RefPoint, dimensions); RT.rotate(reference);

	this->RefPoint = RT.get_rot_ref();
	vector<double> new_dims = RT.get_rot_dims();
	vector<point> new_coords = RT.get_rot_coords();

	this->wdth = new_dims[0]; this->hght = new_dims[1];

	this->upperLeft = new_coords[0]; this->lowerBottom = new_coords[1];

}

void Rect::flip(point reference)
{
	if (reference.x != this->RefPoint.x || reference.y != this->RefPoint.y) {
		vector<double> dimensions; dimensions.push_back(this->wdth); dimensions.push_back(this->hght);

		RectangleTransform RT(this->RefPoint, dimensions); RT.flip(reference);

		this->RefPoint = RT.get_flip_ref();
		vector<double> new_dims = RT.get_flip_dims();
		vector<point> new_coords = RT.get_flip_coords();

		this->wdth = new_dims[0]; this->hght = new_dims[1];

		this->upperLeft = new_coords[0]; this->lowerBottom = new_coords[1];
	}
}


void Rect::move(char c) {


	if (c == 2) {// arrrow down
		upperLeft.y += config.gridSpacing;
		lowerBottom.y += config.gridSpacing;
	}
	else if (c == 4) {
		upperLeft.x -= config.gridSpacing;
		lowerBottom.x -= config.gridSpacing;
	}
	else if (c == 6) { // arrow down
		upperLeft.x += config.gridSpacing;
		lowerBottom.x += config.gridSpacing;
	}
	else if (c == 8) {
		upperLeft.y -= config.gridSpacing;
		lowerBottom.y -= config.gridSpacing;
	}

	calculate_reference();
}


vector<point> Rect::getCorners() {
	vector<point> corners;
	corners.push_back(upperLeft); 
	corners.push_back(lowerBottom);
	return corners;
}

vector<point> Rect::getPoints() {
	return vector<point>();
}

vector<point> Rect::getRevertedPoints() {
	return vector<point>();
}

double Rect::getRadius() {
	return NULL;
}

bool Rect::matching_detection(game* pGame, shape* predicate) {
	bool cond = (getCorners() == dynamic_cast<Rect*>(predicate)->getCorners());
	
	return cond;
}

RectangleTransform::RectangleTransform(point reference, vector<double> dimensions) {
	ref = reference;
	dims = dimensions;
}

point RectangleTransform::get_rot_ref() {
	return rotate_ref;
}

point RectangleTransform::get_flip_ref() {
	return flip_ref;
}

vector<double> RectangleTransform::get_rot_dims() {
	return rotate_dims;
}

vector<double> RectangleTransform::get_flip_dims() {
	return flip_dims;
}

vector<point> RectangleTransform::get_rot_coords() {
	if (rotate_coords.empty()) {
		point uL{}, lR{};
		uL.x = rotate_ref.x - rotate_dims[0] / 2;
		uL.y = rotate_ref.y - rotate_dims[1] / 2;
		lR.x = rotate_ref.x + rotate_dims[0] / 2;
		lR.y = rotate_ref.y + rotate_dims[1] / 2;

		rotate_coords.push_back(uL); rotate_coords.push_back(lR);
		return rotate_coords;
	}
	else
		return rotate_coords;
}

vector<point> RectangleTransform::get_flip_coords() {
	if (flip_coords.empty()) {
		point uL{}, lR{};
		uL.x = flip_ref.x - flip_dims[0] / 2;
		uL.y = flip_ref.y - flip_dims[1] / 2;
		lR.x = flip_ref.x + flip_dims[0] / 2;
		lR.y = flip_ref.y + flip_dims[1] / 2;

		flip_coords.push_back(uL); flip_coords.push_back(lR);
		return flip_coords;
	}
	else
		return flip_coords;
}

void RectangleTransform::rotate(point rot_reference, double angle) {
	rotate_ref = rotate_coordinates(ref, angle, rot_reference);
	rotate_dims.push_back(dims[1]); rotate_dims.push_back(dims[0]);
}

void RectangleTransform::flip(point flip_reference) {
	flip_ref = reflect_coordinates(ref, flip_reference);
	flip_dims.push_back(dims[0]); flip_dims.push_back(dims[1]);
}

void Rect::setcolor(color c) {
	fillColor = c;
}

////////////////////////////////////////////////////  class circle  ///////////////////////////////////////
//TODO: Add implementation for class circle here
circle::circle(game* r_pGame, point ref, int r) :shape(r_pGame, ref)
{
	rad = r;
	pGame = r_pGame;
}

void circle::draw(int x = 1) const
{
	window* pW = pGame->getWind();	//get interface window
	pW->SetPen(borderColor, config.penWidth);
	pW->SetBrush(fillColor);
	pW->DrawCircle(RefPoint.x, RefPoint.y, rad, FILLED);
}

void circle::resize(double factor, point composite_reference) {
	this->rad *= factor;
	resizes++;

}


void circle::move(char c) {

	if (c == 2) // arrrow down
		RefPoint.y += config.gridSpacing;
	else if (c == 4)
		RefPoint.x -= config.gridSpacing;
	else if (c == 6) // arrow down
		RefPoint.x += config.gridSpacing;
	else if (c == 8)
		RefPoint.y -= config.gridSpacing;

}

void circle::rotate(point reference)
{
	if (reference.x != this->RefPoint.x || reference.y != this->RefPoint.y) {
		this->RefPoint = rotate_coordinates(this->RefPoint, -90, reference);
	}
}


void circle::flip(point reference)
{
	if (reference.x != this->RefPoint.x || reference.y != this->RefPoint.y) {
		this->RefPoint = reflect_coordinates(this->RefPoint, reference);
	}
}

double circle::getRadius() {
	return rad;
}

vector<point> circle::getCorners() {
	return vector<point>();
}

vector<point> circle::getPoints() {
	return vector<point>();
}

vector<point> circle::getRevertedPoints() {
	return vector<point>();
}

bool circle::matching_detection(game* pGame, shape* predicate) {
	bool cond = (rad - dynamic_cast<circle*>(predicate)->getRadius() <= 5 && 
		RefPoint == dynamic_cast<circle*>(predicate)->getPosition());
	
	return cond;
}

void circle::setcolor(color c) {
	fillColor = c;
}

////////////////////////////////////////////////////////////////////////////////////////

void EqTriangle::calculate_reference() {
	point1 = rotate_coordinates(point1, -rotation_angle, composite_reference);

	RefPoint.x = point1.x + side_length / 2;
	RefPoint.y = point1.y;

	RefPoint = rotate_coordinates(RefPoint, rotation_angle, composite_reference);
	point1 = rotate_coordinates(point1, rotation_angle, composite_reference);
}

EqTriangle::EqTriangle(game* r_pGame, point ref, int SL, int x) : shape(r_pGame, ref) {
	side_length = SL;
	pGame = r_pGame;
	this->x = x;
	composite_reference = ref;

	if (x != 0) {
		point1.x = RefPoint.x - side_length / 2;
		point1.y = RefPoint.y;
		point2.x = RefPoint.x + side_length / 2;
		point2.y = RefPoint.y;
		point3.x = RefPoint.x;
		point3.y = RefPoint.y - sqrt(3) / 2 * side_length;
	}
	else {
		point1.x = RefPoint.x + side_length / 2;
		point1.y = RefPoint.y;
		point2.x = RefPoint.x - side_length / 2;
		point2.y = RefPoint.y;
		point3.x = RefPoint.x;
		point3.y = RefPoint.y + sqrt(3) / 2 * side_length;
		rotation_angle = 180;
	}
}

void EqTriangle::flip(point reference)
{
	if (rotation_angle == 90 || rotation_angle == 270) {
		point v1 = this->point1;
		point v2 = this->point2;
		point v3 = this->point3;

		TriangleTransform TT(v1, v2, v3);
		TT.reflect(reference);

		if (rotation_angle == 90 || rotation_angle == 270) {
			setRotationAngle(180);
		}

		vector<point> new_coords = TT.get_flip_coords();

		this->point1 = new_coords[0];
		this->point2 = new_coords[1];
		this->point3 = new_coords[2];

		calculate_reference();
	}
}

void EqTriangle::rotate(point reference) {
	point v1 = this->point1;
	point v2 = this->point2;
	point v3 = this->point3;

	TriangleTransform TT(v1, v2, v3);
	TT.rotate(reference);
	setRotationAngle(-90);

	vector<point> new_coords = TT.get_rotated_coords();

	this->point1 = new_coords[0];
	this->point2 = new_coords[1];
	this->point3 = new_coords[2];

	calculate_reference();
}

////////////////////////////////////////////////////  class triangle  ///////////////////////////////////////
void EqTriangle::draw(int x) const {
	window* pW = pGame->getWind(); // get interface window
	pW->SetPen(borderColor, config.penWidth);
	pW->SetBrush(fillColor);

	pW->DrawTriangle(point1.x, point1.y, point2.x, point2.y, point3.x, point3.y, FILLED);
}

void EqTriangle::move(char c) {

	if (c == 2) { // arrrow down
		point1.y += config.gridSpacing;
		point2.y += config.gridSpacing;
		point3.y += config.gridSpacing;
	}
	else if (c == 4) {
		point1.x -= config.gridSpacing;
		point2.x -= config.gridSpacing;
		point3.x -= config.gridSpacing;
	}
	else if (c == 6) { // arrow down
		point1.x += config.gridSpacing;
		point2.x += config.gridSpacing;
		point3.x += config.gridSpacing;
	}
	else if (c == 8) {
		point1.y -= config.gridSpacing;
		point2.y -= config.gridSpacing;
		point3.y -= config.gridSpacing;
	}

	calculate_reference();
}

point resize_points(point p, point origin, double factor) {
	point new_coords{}; new_coords.x = p.x; new_coords.y = p.y;

	new_coords.x -= origin.x; new_coords.y -= origin.y;

	new_coords.x = round(new_coords.x * factor);
	new_coords.y = round(new_coords.y * factor);

	new_coords.x += origin.x;
	new_coords.y += origin.y;

	return new_coords;
}

void EqTriangle::resize(double factor, point composite_reference) {
	this->side_length *= factor;

	setRefPoint(resize_points(RefPoint, composite_reference, factor));
	point1 = resize_points(point1, composite_reference, factor);
	point2 = resize_points(point2, composite_reference, factor);
	point3 = resize_points(point3, composite_reference, factor);
	resizes++;

}

vector<point> EqTriangle::getPoints() {
	vector<point> points;
	points.push_back(point1);
	points.push_back(point2);
	points.push_back(point3);
	return points;
}

vector<point> EqTriangle::getRevertedPoints() {
	vector<point> points;
	points.push_back(point2);
	points.push_back(point1);
	points.push_back(point3);
	return points;
}

double EqTriangle::getRadius() {
	return NULL;
}

vector<point> EqTriangle::getCorners() {
	return vector<point>();
}

bool EqTriangle::matching_detection(game* pGame, shape* predicate) { 
	bool cond = (getPoints() == dynamic_cast<EqTriangle*>(predicate)->getPoints() || (
		getPoints()) == dynamic_cast<EqTriangle*>(predicate)->getRevertedPoints());
	
	return cond;
}

void EqTriangle::setcolor(color c) {
	fillColor = c;
}

////////////////////////////////////////////////////  class RightTriangle  ///////////////////////////////////////

void RightTriangle::calculate_reference() {
	//point1 = rotate_coordinates(point1, -rotation_angle, composite_reference);
	RefPoint.x = point1.x;
	RefPoint.y = point1.y;

	RefPoint = rotate_coordinates(RefPoint, rotation_angle, composite_reference);
	//point1 = rotate_coordinates(point1, rotation_angle, composite_reference);
}

RightTriangle::RightTriangle(game* r_pGame, point ref, int BL, int H, int x) :shape(r_pGame, ref) {
	base_length = BL;
	height = H;
	pGame = r_pGame;
	this->x = x;
	composite_reference = ref;

	if (x == 1) {
		point1.x = RefPoint.x;
		point1.y = RefPoint.y;
		point2.x = RefPoint.x;
		point2.y = RefPoint.y + base_length;
		point3.x = RefPoint.x + height;
		point3.y = RefPoint.y + base_length;
	}
	else if (x == 3)
	{
		point1.x = RefPoint.x;
		point1.y = RefPoint.y;
		point2.x = RefPoint.x - base_length;
		point2.y = RefPoint.y;
		point3.x = RefPoint.x - base_length;
		point3.y = RefPoint.y - height;
	}
	else {
		point1.x = RefPoint.x;
		point1.y = RefPoint.y;
		point2.x = RefPoint.x - height;
		point2.y = RefPoint.y + base_length;
		point3.x = RefPoint.x;
		point3.y = RefPoint.y + base_length;
	}
}

void RightTriangle::draw(int x) const {
	window* pW = pGame->getWind(); // get interface window
	pW->SetPen(borderColor, config.penWidth);
	pW->SetBrush(fillColor);

	pW->DrawTriangle(point1.x, point1.y, point2.x, point2.y, point3.x, point3.y, FILLED);
}


void RightTriangle::resize(double factor, point composite_reference) {
	this->height *= factor;
	this->base_length *= factor;

	setRefPoint(resize_points(RefPoint, composite_reference, factor));
	point1 = resize_points(point1, composite_reference, factor);
	point2 = resize_points(point2, composite_reference, factor);
	point3 = resize_points(point3, composite_reference, factor);
	resizes++;

}

void RightTriangle::rotate(point reference) {
	point v1 = this->point1;
	point v2 = this->point2;
	point v3 = this->point3;

	TriangleTransform TT(v1, v2, v3);
	TT.rotate(reference);
	setRotationAngle(-90);

	vector<point> new_coords = TT.get_rotated_coords();

	this->point1 = new_coords[0];
	this->point2 = new_coords[1];
	this->point3 = new_coords[2];

	calculate_reference();
}

void RightTriangle::flip(point reference) {
	point v1 = this->point1;
	point v2 = this->point2;
	point v3 = this->point3;

	TriangleTransform TT(v1, v2, v3);
	TT.reflect(reference);

	vector<point> new_coords = TT.get_flip_coords();

	if (rotation_angle == 90 || rotation_angle == 270) {
		setRotationAngle(180);
	}

	this->point1 = new_coords[0];
	this->point2 = new_coords[1];
	this->point3 = new_coords[2];

	calculate_reference();

}

void RightTriangle::move(char c) {

	if (c == 2) { // arrrow down
		point1.y += config.gridSpacing;
		point2.y += config.gridSpacing;
		point3.y += config.gridSpacing;
	}
	else if (c == 4) {
		point1.x -= config.gridSpacing;
		point2.x -= config.gridSpacing;
		point3.x -= config.gridSpacing;
	}
	else if (c == 6) { // arrow down
		point1.x += config.gridSpacing;
		point2.x += config.gridSpacing;
		point3.x += config.gridSpacing;
	}
	else if (c == 8) {
		point1.y -= config.gridSpacing;
		point2.y -= config.gridSpacing;
		point3.y -= config.gridSpacing;
	}

	calculate_reference();
}

vector<point> RightTriangle::getPoints() {
	vector<point> points;
	points.push_back(point1);
	points.push_back(point2);
	points.push_back(point3);
	return points;
}

vector<point> RightTriangle::getRevertedPoints() {
	vector<point> points;
	points.push_back(point1);
	points.push_back(point2);
	points.push_back(point3);
	return points;
}

double RightTriangle::getRadius() {
	return NULL;
}

vector<point> RightTriangle::getCorners() {
	return vector<point>(); 
}

bool RightTriangle::matching_detection(game* pGame, shape* predicate) {
	bool cond = (getPoints() == dynamic_cast<RightTriangle*>(predicate)->getPoints() || 
		getPoints() == dynamic_cast<RightTriangle*>(predicate)->getRevertedPoints());
	
	return cond;
}

point rotate_coordinates(point coords, double angle, point origin) {
	double rad_angle = angle * 3.141592653 / 180;
	double rot_matrix[2][2] = { {round(cos(rad_angle)), round(sin(rad_angle))}, {round(sin(-rad_angle)), round(cos(rad_angle))} };
	point new_coords{}; new_coords.x = coords.x; new_coords.y = coords.y;

	new_coords.x -= origin.x; new_coords.y -= origin.y;

	double temp_x = new_coords.x; double temp_y = new_coords.y;

	new_coords.x = rot_matrix[0][0] * temp_x + rot_matrix[0][1] * temp_y;
	new_coords.y = rot_matrix[1][0] * temp_x + rot_matrix[1][1] * temp_y;


	new_coords.x += origin.x;
	new_coords.y += origin.y;

	return new_coords;
}

point reflect_coordinates(point coords, point origin) {
	double rot_matrix[2][2] = { {-1, 0}, {0, 1} };
	point new_coords{}; new_coords.x = coords.x; new_coords.y = coords.y;

	new_coords.x -= origin.x; new_coords.y -= origin.y;

	double temp_x = new_coords.x; double temp_y = new_coords.y;

	new_coords.x = rot_matrix[0][0] * temp_x + rot_matrix[0][1] * temp_y;
	new_coords.y = rot_matrix[1][0] * temp_x + rot_matrix[1][1] * temp_y;


	new_coords.x += origin.x;
	new_coords.y += origin.y;

	return new_coords;
}


TriangleTransform::TriangleTransform(point p1, point p2, point p3) {
	coords.push_back(p1); coords.push_back(p2); coords.push_back(p3);
}

vector<point> TriangleTransform::get_rotated_coords() {

	point p1{}, p2{}, p3{};
	p1.x = rotate_coords[0].x; p1.y = rotate_coords[0].y;
	p2.x = rotate_coords[1].x; p2.y = rotate_coords[1].y;
	p3.x = rotate_coords[2].x; p3.y = rotate_coords[2].y;

	vector<point> rotated_points;
	rotated_points.push_back(p1);
	rotated_points.push_back(p2);
	rotated_points.push_back(p3);

	return rotated_points;
}

vector<point> TriangleTransform::get_flip_coords() {

	point p1{}, p2{}, p3{};
	p1.x = reflect_coords[0].x; p1.y = reflect_coords[0].y;
	p2.x = reflect_coords[1].x; p2.y = reflect_coords[1].y;
	p3.x = reflect_coords[2].x; p3.y = reflect_coords[2].y;

	vector<point> reflected_points;
	reflected_points.push_back(p1);
	reflected_points.push_back(p2);
	reflected_points.push_back(p3);

	return reflected_points;
}

vector<point> TriangleTransform::get_coords() {
	return coords;
}

point TriangleTransform::get_flip_ref() {
	return flip_ref;
}

void TriangleTransform::rotate(point reference, double angle) {
	for (int i = 0; i < 3; i++) {
		rotate_coords.push_back(rotate_coordinates(coords[i], angle, reference));
	}
}

void TriangleTransform::reflect(point reference) {
	for (int i = 0; i < 3; i++) {
		reflect_coords.push_back(reflect_coordinates(coords[i], reference));
	}
	flip_ref = reflect_coordinates(ref, reference);
}

void RightTriangle::setcolor(color c) {
	fillColor = c;
}