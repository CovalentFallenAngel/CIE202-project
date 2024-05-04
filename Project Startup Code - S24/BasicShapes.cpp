#include <vector>
#include "BasicShapes.h"
#include "gameConfig.h"
#include "game.h"

point rotate_coordinates(point coords, double angle, point origin);

////////////////////////////////////////////////////  class Rect  ///////////////////////////////////////

Rect::Rect(game* r_pGame, point ref, int r_hght, int r_wdth):shape(r_pGame,ref)
{
	pGame = r_pGame;
	hght = r_hght;
	wdth = r_wdth;

	upperLeft.x = RefPoint.x - wdth / 2;
	upperLeft.y = RefPoint.y - hght / 2;
	lowerBottom.x = RefPoint.x + wdth / 2;
	lowerBottom.y = RefPoint.y + hght / 2;
}

void Rect::draw(int x = 1) const
{
	window* pW = pGame->getWind();	//get interface window
	pW->SetPen(config.penColor, config.penWidth);
	pW->SetBrush(config.fillColor);

	pW->DrawRectangle(upperLeft.x, upperLeft.y, lowerBottom.x, lowerBottom.y, FILLED);
}



void Rect::resize(double factor){
	const double x = hght;
	const double y = wdth;
	if (factor > 1) {
		if (hght < x * 2 && wdth < y * 2) {
			hght *= factor;
			wdth *= factor;
		}
	}
	if (factor < 1) {
		if (hght > x * 0.5 && wdth > y * 0.5) {
			hght *= factor;
			wdth *= factor;
		}
	}
}

void Rect::rotate(point reference)
{
	vector<double> dimensions; dimensions[0] = this->wdth; dimensions[1] = this->hght;

	RectangleTransform RT(this->RefPoint, dimensions); RT.rotate(reference);

	this->RefPoint = RT.get_trans_ref();
	vector<double> new_dims = RT.get_trans_dims();
	vector<point> new_coords = RT.get_trans_coords();

	this->wdth = new_dims[0]; this->hght = new_dims[1];

	this->upperLeft = new_coords[0]; this->lowerBottom = new_coords[1];

	this->draw(1);

}

void Rect::flip(point reference)
{
	if (reference.x != this->RefPoint.x && reference.y != this->RefPoint.y) {
		vector<double> dimensions; dimensions[0] = this->wdth; dimensions[1] = this->hght;

		RectangleTransform RT(this->RefPoint, dimensions); RT.rotate(reference, 180.0);

		this->RefPoint = RT.get_trans_ref();
		vector<double> new_dims = RT.get_trans_dims();
		vector<point> new_coords = RT.get_trans_coords();

		this->wdth = new_dims[0]; this->hght = new_dims[1];

		this->upperLeft = new_coords[0]; this->lowerBottom = new_coords[1];

		this->draw(1);
	}
}


void Rect::move(char c){

	
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


}


RectangleTransform::RectangleTransform(point reference, vector<double> dimensions) {
	ref = reference;
	dims = dimensions;
}

point RectangleTransform::get_trans_ref() {
	return trans_ref;
}

vector<double> RectangleTransform::get_trans_dims() {
	return trans_dims;
}

vector<point> RectangleTransform::get_trans_coords() {
	if (trans_coords.empty()) {
		point uL{}, lR{};
		uL.x = trans_ref.x - trans_dims[0] / 2;
		uL.y = trans_ref.y - trans_dims[1] / 2;
		lR.x = trans_ref.x + trans_dims[0] / 2;
		lR.y = trans_ref.y + trans_dims[1] / 2;

		trans_coords.push_back(uL); trans_coords.push_back(lR);
		return trans_coords;
	}
	else
		return trans_coords;
}

void RectangleTransform::rotate(point reference, double angle) {
	trans_ref = rotate_coordinates(ref, angle, reference);
	trans_dims[0] = dims[1]; trans_dims[1] = dims[0];
}

////////////////////////////////////////////////////  class circle  ///////////////////////////////////////
//TODO: Add implementation for class circle here
circle::circle(game* r_pGame, point ref, int r):shape(r_pGame,ref)
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



void circle::resize(double factor)
{
	const double r = rad;
	if (factor > 1)
		if (rad < r * 2)
			rad *= factor;
	if (factor < 1)
		if (rad > r * 0.5)
			rad *= factor;
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
	if (reference.x != this->RefPoint.x && reference.y != this->RefPoint.y) {
		this->RefPoint = rotate_coordinates(this->RefPoint, -90, reference);
		this->draw(1);
	}
}

void circle::flip(point reference)
{
	if (reference.x != this->RefPoint.x && reference.y != this->RefPoint.y) {
		this->RefPoint = rotate_coordinates(this->RefPoint, 180, reference);
		this->draw(1);
	}
}
 
 
////////////////////////////////////////////////////////////////////////////////////////
EqTriangle::EqTriangle(game* r_pGame, point ref, int SL, int x) : shape(r_pGame, ref) {
	side_length = SL;
	pGame = r_pGame;

	if (x != 0) {
		point1.x = RefPoint.x - side_length / 2;
		point1.y = RefPoint.y;
		point2.x = RefPoint.x + side_length / 2;
		point2.y = RefPoint.y;
		point3.x = RefPoint.x;
		point3.y = RefPoint.y - sqrt(3) / 2 * side_length;
	}
	else {
		point1.x = RefPoint.x - side_length / 2;
		point1.y = RefPoint.y;
		point2.x = RefPoint.x + side_length / 2;
		point2.y = RefPoint.y;
		point3.x = RefPoint.x;
		point3.y = RefPoint.y + sqrt(3) / 2 * side_length;
	}
}

void EqTriangle::flip(point reference)
{
	if (reference.x != this->RefPoint.x && reference.y != this->RefPoint.y) {
		point v1 = this->point1;
		point v2 = this->point2;
		point v3 = this->point3;

		TriangleTransform TT(v1, v2, v3);
		TT.rotate(reference);

		vector<point> new_coords = TT.get_transformed_coords();

		this->point1 = new_coords[0];
		this->point2 = new_coords[1];
		this->point3 = new_coords[2];

		this->draw(1);
	}
}

void EqTriangle::rotate(point reference) {
	point v1 = this->point1;
	point v2 = this->point2;
	point v3 = this->point3;

	TriangleTransform TT(v1, v2, v3);
	TT.rotate(reference);

	vector<point> new_coords = TT.get_transformed_coords();

	this->point1 = new_coords[0];
	this->point2 = new_coords[1];
	this->point3 = new_coords[2];

	this->draw(1);
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
}


void EqTriangle::resize(double factor) {
	const double Side = side_length;
	if (factor > 1)
		if (side_length < Side * 2)
			side_length *= factor;
	if (factor < 1)
		if (side_length > Side * 0.5)
			side_length *= factor;
}


////////////////////////////////////////////////////  class RightTriangle  ///////////////////////////////////////

RightTriangle::RightTriangle(game* r_pGame, point ref, int BL, int H, int x) :shape(r_pGame, ref) {
	base_length = BL;
	height = H;
	pGame = r_pGame;

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


void RightTriangle::resize(double factor){
	const double x = base_length;
	const double y = height;
	if (factor > 1) {
		if (height < x * 2 && base_length < y * 2) {
			height *= factor;
			base_length *= factor;
		}
	}
	if (factor < 1) {
		if (height > x * 0.5 && base_length > y * 0.5) {
			height *= factor;
			base_length *= factor;
		}
	}
}
void RightTriangle::rotate(point reference) { 
	point v1 = this->point1;
	point v2 = this->point2;
	point v3 = this->point3;

	TriangleTransform TT(v1, v2, v3);
	TT.rotate(reference);

	vector<point> new_coords = TT.get_transformed_coords();

	this->point1 = new_coords[0];
	this->point2 = new_coords[1];
	this->point3 = new_coords[2];

	this->draw(1);
} 

void RightTriangle::flip(point reference) {
	point v1 = this->point1;
	point v2 = this->point2;
	point v3 = this->point3;

	TriangleTransform TT(v1, v2, v3);
	TT.rotate(reference, 180.0);

	vector<point> new_coords = TT.get_transformed_coords();

	this->point1 = new_coords[0];
	this->point2 = new_coords[1];
	this->point3 = new_coords[2];

	this->draw(1);
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
}


point rotate_coordinates(point coords, double angle, point origin) {
	double rad_angle = angle * 3.14159 / 180;
	double rot_matrix[2][2] = { {round(cos(rad_angle)), round(sin(rad_angle))}, {round(sin(-rad_angle)), round(cos(rad_angle))} };
	point new_coords{}; new_coords.x = coords.x; new_coords.y = coords.y;

	double temp_x = new_coords.x; double temp_y = new_coords.y;

	new_coords.x -= origin.x; new_coords.y -= origin.y;

	new_coords.x = rot_matrix[0][0] * temp_x + rot_matrix[0][1] * temp_y;
	new_coords.y = rot_matrix[1][0] * temp_x + rot_matrix[1][1] * temp_y;


	new_coords.x += origin.x;
	new_coords.y += origin.y;

	return new_coords;
}


TriangleTransform::TriangleTransform(point p1, point p2, point p3) {
	coords.push_back(p1); coords.push_back(p2); coords.push_back(p3);
}

vector<point> TriangleTransform::get_transformed_coords() {

	point p1{}, p2{}, p3{};
	p1.x = trans_coords[0].x; p1.y = trans_coords[0].y;
	p2.x = trans_coords[1].x; p2.y = trans_coords[1].y;
	p3.x = trans_coords[2].x; p3.y = trans_coords[2].y;

	vector<point> transformed_points;
	transformed_points.push_back(p1);
	transformed_points.push_back(p2);
	transformed_points.push_back(p3);

	return transformed_points;
}

vector<point> TriangleTransform::get_coords() {
	return coords;
}

void TriangleTransform::rotate(point ref, double angle) {
	for (int i = 0; i < 3; i++) {
		trans_coords.push_back(rotate_coordinates(coords[i], angle, ref));
	}
}