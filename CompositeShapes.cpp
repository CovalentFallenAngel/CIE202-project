#include "CompositeShapes.h"
#include "gameConfig.h"
#include "game.h"
#include "BasicShapes.h"
#include <iostream>
#include <fstream>

point reference_shift(point refc, point refb, double factor);

////////////////////////////////////////////////////  class Sign  ///////////////////////////////////////
Sign::Sign(game* r_pGame, point ref) :shape(r_pGame, ref, true)
{
	//calc the ref point of the Sign base and top rectangles relative to the Sign shape
	topRef = ref;	//top rect ref is the same as the sign
	baseRef = { ref.x, ref.y + config.sighShape.topHeight / 2 + config.sighShape.baseHeight / 2 };
	RefPoint = baseRef;
	top = new Rect(pGame, topRef, config.sighShape.topHeight, config.sighShape.topWdth);
	base = new Rect(pGame, baseRef, config.sighShape.baseHeight, config.sighShape.baseWdth);
}

Sign::~Sign()
{
	delete top;
	delete base;
}

void Sign::draw(int x) const
{
	base->draw(1);
	top->draw(1);
}

void Sign::move(char c)
{
	if (RefPoint.x >= 100 && RefPoint.y >= 200 && RefPoint.x <= 1200 && RefPoint.y <= 480) {
		base->move(c);
		top->move(c);
	}

	else if (RefPoint.y >= 480){
		keytype kin;
		kin = pGame->getWind()->WaitKeyPress(c);
		if (c != 2) {
			base->move(c);
			top->move(c);
		}
	}

	else if (RefPoint.y <= 200) {
		keytype kin;
		kin = pGame->getWind()->WaitKeyPress(c);
		if (c != 8) {
			base->move(c);
			top->move(c);
		}
	}

	else if (RefPoint.x <= 100) {
		keytype kin;
		kin = pGame->getWind()->WaitKeyPress(c);
		if (c != 4) {
			base->move(c);
			top->move(c);
		}
	}

	else if (RefPoint.x >= 1200) {
		keytype kin;
		kin = pGame->getWind()->WaitKeyPress(c);
		if (c != 6) {
			base->move(c);
			top->move(c);
		}
	}

	RefPoint = base->getPosition();
	baseRef = base->getPosition();
	topRef = top->getPosition();
}

void Sign::resize(double factor, point composite_reference) {

	topRef = reference_shift(RefPoint, topRef, factor);
	baseRef = reference_shift(RefPoint, baseRef, factor);

	top->setRefPoint(topRef);
	base->setRefPoint(baseRef);

	base->resize(factor, RefPoint);
	top->resize(factor, RefPoint);
	if (factor < 1) {
		addResizes(-1);
	}
	else if (factor > 1) {
		addResizes(1);
	}
}

void Sign::rotate(point reference) {
	base->rotate(RefPoint);
	top->rotate(RefPoint);
	setRotationAngle(-90);
}

void Sign::flip() {
	base->flip(RefPoint);
	top->flip(RefPoint);
	if (rotation_angle == 90 || rotation_angle == 270) {
		setRotationAngle(180);
	}

}

double Sign::getRadius() const {
	return NULL;
}

vector<point> Sign::getCorners() const {
	return vector<point>();
}

vector<point> Sign::getPoints() const {
	return vector<point>();
}

vector<point> Sign::getRevertedPoints() const{
	return vector<point>();
}

bool Sign::matching_detection(game* pGame, shape* predicate) {
	bool cond = (base->matching_detection(pGame, dynamic_cast<Sign*>(predicate)->base) &&
		top->matching_detection(pGame, dynamic_cast<Sign*>(predicate)->top));
	
	
	return cond;
}

void Sign::saveOrnaments(ofstream& file) {
	file << "Sign" << " ";
	file << RefPoint.x << " " << RefPoint.y << " ";
	file << rotation_angle << " " << resizes << " " << isFlipped << " ";
	file << static_cast<int>(getColor().ucRed) << " " << static_cast<int>(getColor().ucGreen) << " " << static_cast<int>(getColor().ucBlue) << " ";
	file << static_cast<int>(borderColor.ucRed) << " " << static_cast<int>(borderColor.ucGreen) << " " << static_cast<int>(borderColor.ucBlue) << endl;
}

string Sign::getID() const{
	return "Sign";
}

void Sign::setcolor(color c) {
	base->setcolor(c);
	top->setcolor(c);
}

color Sign::getColor() const { return base->getColor(); }

Home::Home(game* r_pGame, point ref) :shape(r_pGame, ref, true) {
	topRef = ref;
	baseRef = { ref.x,ref.y + config.Homeshape.side_length / 30 + config.Homeshape.basehght / 2 };
	this->RefPoint = baseRef;
	top = new EqTriangle(pGame, topRef, config.Homeshape.side_length, 1);
	base = new Rect(pGame, baseRef, config.Homeshape.basehght, config.Homeshape.basewdth);
}

Home::~Home()
{
	delete top;
	delete base;
}

void Home::draw(int x) const {
	base->draw(1);
	top->draw(1);
}

void Home::resize(double factor, point composite_reference)
{
	top->setRefPoint(reference_shift(composite_reference, top->getPosition(), factor));

	top->resize(factor, RefPoint);
	base->resize(factor, RefPoint);

	topRef = top->getPosition();
	if (factor < 1) {
		addResizes(-1);
	}
	else if (factor > 1) {
		addResizes(1);
	}

}

void Home::move(char c)
{
	if (RefPoint.x >= 80 && RefPoint.y >= 180 && RefPoint.x <= 1280 && RefPoint.y <= 480) {
		base->move(c);
		top->move(c);
	}

	else if (RefPoint.y >= 480) {
		keytype kin;
		kin = pGame->getWind()->WaitKeyPress(c);
		if (c != 2) {
			base->move(c);
			top->move(c);
		}
	}

	else if (RefPoint.y <= 180) {
		keytype kin;
		kin = pGame->getWind()->WaitKeyPress(c);
		if (c != 8) {
			base->move(c);
			top->move(c);
		}
	}

	else if (RefPoint.x <= 80) {
		keytype kin;
		kin = pGame->getWind()->WaitKeyPress(c);
		if (c != 4) {
			base->move(c);
			top->move(c);
		}
	}

	else if (RefPoint.x >= 1280) {
		keytype kin;
		kin = pGame->getWind()->WaitKeyPress(c);
		if (c != 6) {
			base->move(c);
			top->move(c);
		}
	}

	this->RefPoint = base->getPosition();

	baseRef = base->getPosition();
	topRef = top->getPosition();

}

void Home::rotate(point reference) {
	base->rotate(RefPoint);
	top->rotate(RefPoint);

	baseRef = base->getPosition();
	topRef = top->getPosition();
	setRotationAngle(-90);
}

void Home::flip() {
	base->flip(RefPoint);
	top->flip(RefPoint);

	baseRef = base->getPosition();
	topRef = top->getPosition();
	if (rotation_angle == 90 || rotation_angle == 270) {
		setRotationAngle(180);
	}
}

double Home::getRadius() const{
	return NULL;
}

vector<point> Home::getCorners()const {
	return vector<point>();
}

vector<point> Home::getPoints() const {
	return vector<point>();
}

vector<point> Home::getRevertedPoints() const {
	return vector<point>();
}

bool Home::matching_detection(game* pGame, shape* predicate) {
	bool cond = (base->matching_detection(pGame, dynamic_cast<Home*>(predicate)->base) &&
		top->matching_detection(pGame, dynamic_cast<Home*>(predicate)->top));

	
	return cond;
}

void Home::saveOrnaments(ofstream& file) {
	file << "Home" << " ";
	file << RefPoint.x << " " << RefPoint.y << " ";
	file << rotation_angle << " " << resizes << " " << isFlipped << " ";
	file << static_cast<int>(getColor().ucRed) << " " << static_cast<int>(getColor().ucGreen) << " " << static_cast<int>(getColor().ucBlue) << " ";
	file << static_cast<int>(borderColor.ucRed) << " " << static_cast<int>(borderColor.ucGreen) << " " << static_cast<int>(borderColor.ucBlue) << endl;
}

string Home::getID() const {
	return "Home";
}
void Home::setcolor(color c) {
	base->setcolor(c);
	top->setcolor(c);
}

color Home::getColor() const { return base->getColor(); }


Person::Person(game* r_pGame, point ref) : shape(r_pGame, ref, true)
{
	// calculate the reference points of the pearson body parts relative to the Pearson shape
	headRef = { ref.x ,ref.y - 15 };                                 // head ref is the same as the pearson
	bodyRef = { ref.x - config.Person.width / 40, ref.y + config.Person.height / 2 };
	leftArmRef = { ref.x - config.Person.width / 2 - config.Person.armLength - 1, ref.y + 25 };
	rightArmRef = { ref.x + config.Person.width / 2 + config.Person.armLength - 1, ref.y + 25 };
	leftLegRef = { ref.x - config.Person.width / 4, ref.y + config.Person.height };
	rightLegRef = { ref.x + config.Person.width / 4, ref.y + config.Person.height };

	// assign the reference point
	RefPoint = bodyRef;

	// create the pearson body parts
	head = new circle(r_pGame, headRef, config.Person.headDiameter / 2);
	body = new Rect(r_pGame, bodyRef, config.Person.height, config.Person.width);
	Larm = new Rect(r_pGame, leftArmRef, config.Person.armLength, config.Person.armWidth);
	Rarm = new Rect(r_pGame, rightArmRef, config.Person.armLength, config.Person.armWidth);
	Lleg = new Rect(r_pGame, leftLegRef, config.Person.legLength, config.Person.legWidth);
	Rleg = new Rect(r_pGame, rightLegRef, config.Person.legLength, config.Person.legWidth);
}

Person::~Person()
{
	delete head;
	delete body;
	delete Larm;
	delete Rarm;
	delete Lleg;
	delete Rleg;
}

void Person::draw(int x) const
{

	head->draw(1);
	body->draw(1);
	Larm->draw(1);
	Rarm->draw(1);
	Lleg->draw(1);
	Rleg->draw(1);
}

void Person::rotate(point reference) {
	body->rotate(RefPoint);
	head->rotate(RefPoint);
	Larm->rotate(RefPoint);
	Rarm->rotate(RefPoint);
	Lleg->rotate(RefPoint);
	Rleg->rotate(RefPoint);
	setRotationAngle(-90);


}

void Person::flip() {
	body->flip(RefPoint);
	head->flip(RefPoint);
	Larm->flip(RefPoint);
	Rarm->flip(RefPoint);
	Lleg->flip(RefPoint);
	Rleg->flip(RefPoint);

	headRef = head->getPosition();
	bodyRef = body->getPosition();
	leftArmRef = Larm->getPosition();
	rightArmRef = Rarm->getPosition();
	leftLegRef = Lleg->getPosition();
	rightLegRef = Rleg->getPosition();
	if (rotation_angle == 90 || rotation_angle == 270) {
		setRotationAngle(180);
	}
}

void Person::resize(double factor, point composite_reference)
{
	head->setRefPoint(reference_shift(RefPoint, head->getPosition(), factor));
	body->calculate_points();
	Larm->setRefPoint(reference_shift(RefPoint, Larm->getPosition(), factor));
	Rarm->setRefPoint(reference_shift(RefPoint, Rarm->getPosition(), factor));
	Lleg->setRefPoint(reference_shift(RefPoint, Lleg->getPosition(), factor));
	Rleg->setRefPoint(reference_shift(RefPoint, Rleg->getPosition(), factor));

	head->resize(factor, RefPoint);
	body->resize(factor, RefPoint);
	Larm->resize(factor, RefPoint);
	Rarm->resize(factor, RefPoint);
	Lleg->resize(factor, RefPoint);
	Rleg->resize(factor, RefPoint);

	headRef = head->getPosition();
	leftArmRef = Larm->getPosition();
	rightArmRef = Rarm->getPosition();
	leftLegRef = Lleg->getPosition();
	rightLegRef = Rleg->getPosition();

	if (factor < 1) {
		addResizes(-1);
	}
	else if (factor > 1) {
		addResizes(1);
	}
}


void Person::move(char c)
{

	if (RefPoint.x >= 100 && RefPoint.y >= 180 && RefPoint.x <= 1250 && RefPoint.y <= 460) {
		head->move(c);
		body->move(c);
		Larm->move(c);
		Rarm->move(c);
		Lleg->move(c);
		Rleg->move(c);
	}

	else if (RefPoint.y >= 460) {
		keytype kin;
		kin = pGame->getWind()->WaitKeyPress(c);
		if (c != 2) {
			head->move(c);
			body->move(c);
			Larm->move(c);
			Rarm->move(c);
			Lleg->move(c);
			Rleg->move(c);
		}
	}

	else if (RefPoint.y <= 180) {
		keytype kin;
		kin = pGame->getWind()->WaitKeyPress(c);
		if (c != 8) {
			head->move(c);
			body->move(c);
			Larm->move(c);
			Rarm->move(c);
			Lleg->move(c);
			Rleg->move(c);
		}
	}

	else if (RefPoint.x <= 100) {
		keytype kin;
		kin = pGame->getWind()->WaitKeyPress(c);
		if (c != 4) {
			head->move(c);
			body->move(c);
			Larm->move(c);
			Rarm->move(c);
			Lleg->move(c);
			Rleg->move(c);
		}
	}

	else if (RefPoint.x >= 1250) {
		keytype kin;
		kin = pGame->getWind()->WaitKeyPress(c);
		if (c != 6) {
			head->move(c);
			body->move(c);
			Larm->move(c);
			Rarm->move(c);
			Lleg->move(c);
			Rleg->move(c);
		}
	}

	RefPoint = body->getPosition();

	headRef = head->getPosition();
	bodyRef = body->getPosition();
	leftArmRef = Larm->getPosition();
	rightArmRef = Rarm->getPosition();
	leftLegRef = Lleg->getPosition();
	rightLegRef = Rleg->getPosition();

}

double Person::getRadius() const{
	return NULL;
}

vector<point> Person::getCorners() const {
	return vector<point>();
}

vector<point> Person::getPoints() const{
	return vector<point>();
}

vector<point> Person::getRevertedPoints()const {
	return vector<point>();
}

bool Person::matching_detection(game* pGame, shape* predicate) {
	bool cond = (head->matching_detection(pGame, dynamic_cast<Person*>(predicate)->head) &&
		body->matching_detection(pGame, dynamic_cast<Person*>(predicate)->body) &&
		(Larm->matching_detection(pGame, dynamic_cast<Person*>(predicate)->Larm) || 
			Larm->matching_detection(pGame, dynamic_cast<Person*>(predicate)->Rarm)) &&
		(Rarm->matching_detection(pGame, dynamic_cast<Person*>(predicate)->Rarm) || 
			Rarm->matching_detection(pGame, dynamic_cast<Person*>(predicate)->Larm)) &&
		(Lleg->matching_detection(pGame, dynamic_cast<Person*>(predicate)->Lleg) ||
			Lleg->matching_detection(pGame, dynamic_cast<Person*>(predicate)->Rleg)) &&
		(Rleg->matching_detection(pGame, dynamic_cast<Person*>(predicate)->Rleg) || 
			Rleg->matching_detection(pGame, dynamic_cast<Person*>(predicate)->Lleg)));

	
	return cond;
	
}

void Person::saveOrnaments(ofstream& file) {
	file << "Person" << " ";
	file << RefPoint.x << " " << RefPoint.y << " ";
	file << rotation_angle << " " << resizes << " " << isFlipped << " ";
	file << static_cast<int>(getColor().ucRed) << " " << static_cast<int>(getColor().ucGreen) << " " << static_cast<int>(getColor().ucBlue) << " ";
	file << static_cast<int>(borderColor.ucRed) << " " << static_cast<int>(borderColor.ucGreen) << " " << static_cast<int>(borderColor.ucBlue) << endl;
}

string Person::getID() const{
	return "Person";
}
void Person::setcolor(color c) {
	body->setcolor(c);
	head->setcolor(c);
	Larm->setcolor(c);
	Rarm->setcolor(c);
	Lleg->setcolor(c);
	Rleg->setcolor(c);
}

color Person::getColor() const { return body->getColor(); }


ice_cream::ice_cream(game* r_pGame, point ref) : shape(r_pGame, ref, true) {
	scoopRef = { ref.x,ref.y };
	coneRef = { ref.x + config.ice_cream.side_lenght - 50 ,ref.y + 8 };
	RefPoint = scoopRef;
	scoop = new circle(r_pGame, scoopRef, config.ice_cream.headDiameter / 2);
	cone = new EqTriangle(r_pGame, coneRef, config.ice_cream.side_lenght, 0);
}

ice_cream::~ice_cream()
{
	delete scoop;
	delete cone;
}

void ice_cream::draw(int x) const
{
	scoop->draw(1);
	cone->draw(0);
}

void ice_cream::move(char c)
{
	if (RefPoint.x >= 80 && RefPoint.y >= 140 && RefPoint.x <= 1280 && RefPoint.y <= 450) {
		cone->move(c);
		scoop->move(c);
	}

	else if (RefPoint.y >= 450) {
		keytype kin;
		kin = pGame->getWind()->WaitKeyPress(c);
		if (c != 2) {
			cone->move(c);
			scoop->move(c);
		}
	}

	else if (RefPoint.y <= 140) {
		keytype kin;
		kin = pGame->getWind()->WaitKeyPress(c);
		if (c != 8) {
			cone->move(c);
			scoop->move(c);
		}
	}

	else if (RefPoint.x <= 80) {
		keytype kin;
		kin = pGame->getWind()->WaitKeyPress(c);
		if (c != 4) {
			cone->move(c);
			scoop->move(c);
		}
	}

	else if (RefPoint.x >= 1280) {
		keytype kin;
		kin = pGame->getWind()->WaitKeyPress(c);
		if (c != 6) {
			cone->move(c);
			scoop->move(c);
		}
	}

	this->RefPoint = scoop->getPosition();

	coneRef = cone->getPosition();
	scoopRef = scoop->getPosition();

}

void ice_cream::resize(double factor, point composite_reference)
{
	cone->setRefPoint(reference_shift(RefPoint, cone->getPosition(), factor));

	scoop->resize(factor, RefPoint);
	cone->resize(factor, RefPoint);

	coneRef = cone->getPosition();
	scoopRef = scoop->getPosition();
	if (factor < 1) {
		addResizes(-1);
	}
	else if (factor > 1) {
		addResizes(1);
	}

}

void ice_cream::rotate(point reference) {
	scoop->rotate(RefPoint);
	cone->rotate(RefPoint);

	scoopRef = scoop->getPosition();
	coneRef = cone->getPosition();
	setRotationAngle(-90);
}

void ice_cream::flip() {
	scoop->flip(RefPoint);
	cone->flip(RefPoint);

	RefPoint = scoop->getPosition();
	scoopRef = scoop->getPosition();
	coneRef = cone->getPosition();
	if (rotation_angle == 90 || rotation_angle == 270) {
		setRotationAngle(180);
	}
}

double ice_cream::getRadius() const {
	return NULL;
}

vector<point> ice_cream::getCorners() const{
	return vector<point>();
}

vector<point> ice_cream::getPoints() const{
	return vector<point>();
}

vector<point> ice_cream::getRevertedPoints() const{
	return vector<point>();
}

void ice_cream::saveOrnaments(ofstream& file) {
	file << "Ice-Cream" << " ";
	file << RefPoint.x << " " << RefPoint.y << " ";
	file << rotation_angle << " " << resizes << " " << isFlipped << " ";
	file << static_cast<int>(getColor().ucRed) << " " << static_cast<int>(getColor().ucGreen) << " " << static_cast<int>(getColor().ucBlue) << " ";
	file << static_cast<int>(borderColor.ucRed) << " " << static_cast<int>(borderColor.ucGreen) << " " << static_cast<int>(borderColor.ucBlue) << endl;
}

bool ice_cream::matching_detection(game* pGame, shape* predicate) {
	bool cond = (cone->matching_detection(pGame, dynamic_cast<ice_cream*>(predicate)->cone) &&
		scoop->matching_detection(pGame, dynamic_cast<ice_cream*>(predicate)->scoop));

	
	return cond;
}

string ice_cream::getID() const{
	return "Ice-Cream";
}

void ice_cream::setcolor(color c) {
	cone->setcolor(c);
	scoop->setcolor(c);
}

color ice_cream::getColor() const { return cone->getColor(); }


Tree::Tree(game* r_pGame, point ref) : shape(r_pGame, ref, true) { 
	T1Ref = { ref.x + config.Tree.side_length - 50,ref.y };
	T2Ref = { ref.x + config.Tree.side_length - 50,ref.y - 10 };
	T3Ref = { ref.x + config.Tree.side_length - 50,ref.y - 20 };
	bodyRef = { ref.x - config.Tree.basewdth / 40, ref.y + config.Tree.basehght / 2 };
	RefPoint = bodyRef;
	T1 = new EqTriangle(r_pGame, T1Ref, config.Tree.side_length, 1);
	T2 = new EqTriangle(r_pGame, T2Ref, config.Tree.side_length, 1);
	T3 = new EqTriangle(r_pGame, T3Ref, config.Tree.side_length, 1);
	body = new Rect(r_pGame, bodyRef, config.Tree.basehght, config.Tree.basewdth);
}

Tree::~Tree()
{
	delete T1;
	delete T2;
	delete T3;
	delete body;
}

void Tree::draw(int x) const {
	T1->draw(1);
	T2->draw(1);
	T3->draw(1);
	body->draw(1);
}

void Tree::move(char c)
{


	if (RefPoint.x >= 80 && RefPoint.y >= 180 && RefPoint.x <= 1280 && RefPoint.y <= 480) {
		T1->move(c);
		T2->move(c);
		T3->move(c);
		body->move(c);
	}

	else if (RefPoint.y >= 480) {
		keytype kin;
		kin = pGame->getWind()->WaitKeyPress(c);
		if (c != 2) {
			T1->move(c);
			T2->move(c);
			T3->move(c);
			body->move(c);
		}
	}

	else if (RefPoint.y <= 180) {
		keytype kin;
		kin = pGame->getWind()->WaitKeyPress(c);
		if (c != 8) {
			T1->move(c);
			T2->move(c);
			T3->move(c);
			body->move(c);
		}
	}

	else if (RefPoint.x <= 80) {
		keytype kin;
		kin = pGame->getWind()->WaitKeyPress(c);
		if (c != 4) {
			T1->move(c);
			T2->move(c);
			T3->move(c);
			body->move(c);
		}
	}

	else if (RefPoint.x >= 1280) {
		keytype kin;
		kin = pGame->getWind()->WaitKeyPress(c);
		if (c != 6) {
			T1->move(c);
			T2->move(c);
			T3->move(c);
			body->move(c);
		}
	}

	RefPoint = body->getPosition();

	bodyRef = body->getPosition();
	T1Ref = T1->getPosition();
	T2Ref = T2->getPosition();
	T3Ref = T3->getPosition();
}

void Tree::resize(double factor, point composite_reference)
{
	T1->setRefPoint(reference_shift(composite_reference, T1->getPosition(), factor));
	T2->setRefPoint(reference_shift(composite_reference, T2->getPosition(), factor));
	T3->setRefPoint(reference_shift(composite_reference, T3->getPosition(), factor));
	body->setRefPoint(reference_shift(composite_reference, body->getPosition(), factor));

	T1->resize(factor, RefPoint);
	T2->resize(factor, RefPoint);
	T3->resize(factor, RefPoint);
	body->resize(factor, RefPoint);

	T1Ref = T1->getPosition();
	T2Ref = T2->getPosition();
	T3Ref = T3->getPosition();
	bodyRef = body->getPosition();

	if (factor < 1) {
		addResizes(-1);
	}
	else if (factor > 1) {
		addResizes(1);
	}
}

void Tree::rotate(point reference) {
	body->rotate(RefPoint);
	T1->rotate(RefPoint);
	T2->rotate(RefPoint);
	T3->rotate(RefPoint);
	setRotationAngle(-90);
}

void Tree::flip() {
	body->flip(RefPoint);
	T1->flip(RefPoint);
	T2->flip(RefPoint);
	T3->flip(RefPoint);

	RefPoint = body->getPosition();

	bodyRef = body->getPosition();
	T1Ref = T1->getPosition();
	T2Ref = T2->getPosition();
	T3Ref = T3->getPosition();
	if (rotation_angle == 90 || rotation_angle == 270) {
		setRotationAngle(180);
	}
}

double Tree::getRadius()const {
	return NULL;
}

vector<point> Tree::getCorners()const {
	return vector<point>();
}

vector<point> Tree::getPoints()const {
	return vector<point>();
}

vector<point> Tree::getRevertedPoints()const {
	return vector<point>();
}

bool Tree::matching_detection(game* pGame, shape* predicate) {
	bool cond = (body->matching_detection(pGame, dynamic_cast<Tree*>(predicate)->body) &&
		T1->matching_detection(pGame, dynamic_cast<Tree*>(predicate)->T1) &&
		T2->matching_detection(pGame, dynamic_cast<Tree*>(predicate)->T2) &&
		T3->matching_detection(pGame, dynamic_cast<Tree*>(predicate)->T3));

	
	return cond;
}

string Tree::getID()const {
	return "Tree";
}

void Tree::saveOrnaments(ofstream& file) {
	file << "Tree" << " ";
	file << RefPoint.x << " " << RefPoint.y << " ";
	file << rotation_angle << " " << resizes << " " << isFlipped << " ";
	file << static_cast<int>(getColor().ucRed) << " " << static_cast<int>(getColor().ucGreen) << " " << static_cast<int>(getColor().ucBlue) << " ";
	file << static_cast<int>(borderColor.ucRed) << " " << static_cast<int>(borderColor.ucGreen) << " " << static_cast<int>(borderColor.ucBlue) << endl;
}

void Tree::setcolor(color c) {
	body->setcolor(c);
	T1->setcolor(c);
	T2->setcolor(c);
	T3->setcolor(c);
}

color Tree::getColor() const { return T1->getColor(); }


Rocket::Rocket(game* r_pGame, point ref) : shape(r_pGame, ref, true) {
	T1Ref = { (ref.x + config.Rocket.side_length - 70),(ref.y - 10) };
	T2Ref = { (ref.x + config.Rocket.Rbase_length - 65),(ref.y + 35)};
	T3Ref = { (ref.x + config.Rocket.Lbase_length - 40),(ref.y + 35) };
	bodyRef = { (ref.x - config.Rocket.basewdth - 9), (ref.y + config.Rocket.basehght - 45) };
	RefPoint = bodyRef;
	T1 = new EqTriangle(r_pGame, T1Ref, config.Rocket.side_length, 1);
	T2 = new RightTriangle(r_pGame, T2Ref, config.Rocket.Rbase_length, config.Rocket.Rhght, 2);
	T3 = new RightTriangle(r_pGame, T3Ref, config.Rocket.Lbase_length, config.Rocket.Lhght, 1);
	body = new Rect(r_pGame, bodyRef, config.Rocket.basehght, config.Rocket.basewdth);
}

Rocket::~Rocket()
{
	delete T1;
	delete T2;
	delete T3;
	delete body;
}

void Rocket::draw(int x) const
{
	T1->draw(5);
	T2->draw(2);
	T3->draw(1);
	body->draw(1);
}

void Rocket::resize(double factor, point composite_reference)
{
	T1->setRefPoint(reference_shift(RefPoint, T1->getPosition(), factor));
	T2->setRefPoint(reference_shift(RefPoint, T2->getPosition(), factor));
	T3->setRefPoint(reference_shift(RefPoint, T3->getPosition(), factor));
	body->setRefPoint(reference_shift(RefPoint, body->getPosition(), factor));

	T1->resize(factor, RefPoint);
	T2->resize(factor, RefPoint);
	T3->resize(factor, RefPoint);
	body->resize(factor, RefPoint);

	T1Ref = T1->getPosition();
	T2Ref = T2->getPosition();
	T3Ref = T3->getPosition();
	bodyRef = body->getPosition();

	if (factor < 1) {
		addResizes(-1);
	}
	else if (factor > 1) {
		addResizes(1);
	}
}

void Rocket::move(char c)
{

	if (RefPoint.x >= 100 && RefPoint.y >= 150 && RefPoint.x <= 1250 && RefPoint.y <= 460) {
		T1->move(c);
		T2->move(c);
		T3->move(c);
		body->move(c);
	}

	else if (RefPoint.y >= 460) {
		keytype kin;
		kin = pGame->getWind()->WaitKeyPress(c);
		if (c != 2) {
			T1->move(c);
			T2->move(c);
			T3->move(c);
			body->move(c);
		}
	}

	else if (RefPoint.y <= 150) {
		keytype kin;
		kin = pGame->getWind()->WaitKeyPress(c);
		if (c != 8) {
			T1->move(c);
			T2->move(c);
			T3->move(c);
			body->move(c);
		}
	}

	else if (RefPoint.x <= 100) {
		keytype kin;
		kin = pGame->getWind()->WaitKeyPress(c);
		if (c != 4) {
			T1->move(c);
			T2->move(c);
			T3->move(c);
			body->move(c);
		}
	}

	else if (RefPoint.x >= 1250) {
		keytype kin;
		kin = pGame->getWind()->WaitKeyPress(c);
		if (c != 6) {
			T1->move(c);
			T2->move(c);
			T3->move(c);
			body->move(c);
		}
	}

	RefPoint = body->getPosition();

	bodyRef = body->getPosition();
	T1Ref = T1->getPosition();
	T2Ref = T2->getPosition();
	T3Ref = T3->getPosition();

}

void Rocket::rotate(point reference) {
	body->rotate(RefPoint);
	T1->rotate(RefPoint);
	T2->rotate(RefPoint);
	T3->rotate(RefPoint);
	setRotationAngle(-90);
}

void Rocket::flip() {
	body->flip(RefPoint);
	T1->flip(RefPoint);
	T2->flip(RefPoint);
	T3->flip(RefPoint);

	RefPoint = body->getPosition();

	bodyRef = body->getPosition();
	T1Ref = T1->getPosition();
	T2Ref = T2->getPosition();
	T3Ref = T3->getPosition();
	if (rotation_angle == 90 || rotation_angle == 270) {
		setRotationAngle(180);
	}
}

double Rocket::getRadius() const{
	return NULL;
}

vector<point> Rocket::getCorners() const {
	return vector<point>();
}

vector<point> Rocket::getPoints() const {
	return vector<point>();
}

vector<point> Rocket::getRevertedPoints() const{
	return vector<point>();
}

bool Rocket::matching_detection(game* pGame, shape* predicate) {
	bool T2Check, T3Check;
	bool cond = (T1->matching_detection(pGame, dynamic_cast<Rocket*>(predicate)->T1) && 
		body->matching_detection(pGame, dynamic_cast<Rocket*>(predicate)->body));

	if (cond) {
		T2Check = (T2->matching_detection(pGame, dynamic_cast<Rocket*>(predicate)->T2));
		if (!T2Check) {
			int rot_angle = dynamic_cast<Rocket*>(predicate)->getRotationAngle();
			while (dynamic_cast<Rocket*>(predicate)->getRotationAngle() != 0) {
				dynamic_cast<Rocket*>(predicate)->rotate(dynamic_cast<Rocket*>(predicate)->getPosition());
			}
			dynamic_cast<Rocket*>(predicate)->flip();
			
			while (dynamic_cast<Rocket*>(predicate)->getRotationAngle() != rot_angle) {
				dynamic_cast<Rocket*>(predicate)->rotate(dynamic_cast<Rocket*>(predicate)->getPosition());
			}

			T2Check = (T2->matching_detection(pGame, dynamic_cast<Rocket*>(predicate)->T2));

			while (dynamic_cast<Rocket*>(predicate)->getRotationAngle() != 0) {
				dynamic_cast<Rocket*>(predicate)->rotate(dynamic_cast<Rocket*>(predicate)->getPosition());
			}
			dynamic_cast<Rocket*>(predicate)->flip();

			while (dynamic_cast<Rocket*>(predicate)->getRotationAngle() != rot_angle) {
				dynamic_cast<Rocket*>(predicate)->rotate(dynamic_cast<Rocket*>(predicate)->getPosition());
			}
		}
		T3Check = (T3->matching_detection(pGame, dynamic_cast<Rocket*>(predicate)->T3));
		if (!T3Check) {
			int rot_angle = dynamic_cast<Rocket*>(predicate)->getRotationAngle();
			while (dynamic_cast<Rocket*>(predicate)->getRotationAngle() != 0) {
				dynamic_cast<Rocket*>(predicate)->rotate(dynamic_cast<Rocket*>(predicate)->getPosition());
			}
			dynamic_cast<Rocket*>(predicate)->flip();

			while (dynamic_cast<Rocket*>(predicate)->getRotationAngle() != rot_angle) {
				dynamic_cast<Rocket*>(predicate)->rotate(dynamic_cast<Rocket*>(predicate)->getPosition());
			}

			T3Check = (T3->matching_detection(pGame, dynamic_cast<Rocket*>(predicate)->T3));

			while (dynamic_cast<Rocket*>(predicate)->getRotationAngle() != 0) {
				dynamic_cast<Rocket*>(predicate)->rotate(dynamic_cast<Rocket*>(predicate)->getPosition());
			}
			dynamic_cast<Rocket*>(predicate)->flip();

			while (dynamic_cast<Rocket*>(predicate)->getRotationAngle() != rot_angle) {
				dynamic_cast<Rocket*>(predicate)->rotate(dynamic_cast<Rocket*>(predicate)->getPosition());
			}
		}
	}

	
	return (cond && T2Check && T3Check);
}

void Rocket::saveOrnaments(ofstream& file) {
	file << "Rocket" << " ";
	file << RefPoint.x << " " << RefPoint.y << " ";
	file << rotation_angle << " " << resizes << " " << isFlipped << " ";
	file << static_cast<int>(getColor().ucRed) << " " << static_cast<int>(getColor().ucGreen) << " " << static_cast<int>(getColor().ucBlue) << " ";
	file << static_cast<int>(borderColor.ucRed) << " " << static_cast<int>(borderColor.ucGreen) << " " << static_cast<int>(borderColor.ucBlue) << endl;
}

string Rocket::getID() const{
	return "Rocket";
}
void Rocket::setcolor(color c) {
	body->setcolor(c);
	T1->setcolor(c);
	T2->setcolor(c);
	T3->setcolor(c);
}

color Rocket::getColor() const { return body->getColor(); }


Car::Car(game* r_pGame, point ref) :shape(r_pGame, ref, true)
{
	T1Ref = { ref.x + config.Car.T1base_length - 95,ref.y - 20 };
	C1Ref = { ref.x + config.Car.Radius - 100,ref.y + 25 };
	C2Ref = { ref.x + config.Car.Radius - 70,ref.y + 25 };
	R1Ref = { ref.x - config.Car.R1wdth - 20, ref.y + config.Car.R1hght - 30 };
	R2Ref = { ref.x - config.Car.R2wdth - 9, ref.y + config.Car.R1hght / 2 };
	RefPoint = R2Ref;
	T1 = new RightTriangle(r_pGame, T1Ref, config.Car.T1base_length, config.Car.T1hght, 3);
	R1 = new Rect(r_pGame, R1Ref, config.Car.R1hght, config.Car.R1wdth);
	R2 = new Rect(r_pGame, R2Ref, config.Car.R2hght, config.Car.R2wdth);
	C1 = new circle(r_pGame, C1Ref, config.Car.Radius);
	C2 = new circle(r_pGame, C2Ref, config.Car.Radius);
}

Car::~Car()
{
	delete T1;
	delete R1;
	delete R2;
	delete C1;
	delete C2;
}

void Car::draw(int x) const
{
	
	T1->draw(3);
	
	R1->draw(3);
	R2->draw(3);
	C1->draw(3);
	C2->draw(3);
}

void Car::move(char c)
{

	if (RefPoint.x >= 100 && RefPoint.y >= 150 && RefPoint.x <= 1250 && RefPoint.y <= 460) {
		T1->move(c);
		R1->move(c);
		R2->move(c);
		C1->move(c);
		C2->move(c);
	}

	else if (RefPoint.y >= 460) {
		keytype kin;
		kin = pGame->getWind()->WaitKeyPress(c);
		if (c != 2) {
			T1->move(c);
			R1->move(c);
			R2->move(c);
			C1->move(c);
			C2->move(c);
		}
	}

	else if (RefPoint.y <= 150) {
		keytype kin;
		kin = pGame->getWind()->WaitKeyPress(c);
		if (c != 8) {
			T1->move(c);
			R1->move(c);
			R2->move(c);
			C1->move(c);
			C2->move(c);
		}
	}

	else if (RefPoint.x <= 100) {
		keytype kin;
		kin = pGame->getWind()->WaitKeyPress(c);
		if (c != 4) {
			T1->move(c);
			R1->move(c);
			R2->move(c);
			C1->move(c);
			C2->move(c);
		}
	}

	else if (RefPoint.x >= 1250) {
		keytype kin;
		kin = pGame->getWind()->WaitKeyPress(c);
		if (c != 6) {
			T1->move(c);
			R1->move(c);
			R2->move(c);
			C1->move(c);
			C2->move(c);
		}
	}

	RefPoint = R1->getPosition();

	T1Ref = T1->getPosition();
	R1Ref = R1->getPosition();
	R2Ref = R2->getPosition();
	C1Ref = C1->getPosition();
	C2Ref = C2->getPosition();

}


void Car::resize(double factor, point composite_reference)
{
	T1->setRefPoint(reference_shift(RefPoint, T1->getPosition(), factor));
	R1->setRefPoint(reference_shift(RefPoint, R1->getPosition(), factor));
	R2->setRefPoint(reference_shift(RefPoint, R2->getPosition(), factor));
	C1->setRefPoint(reference_shift(RefPoint, C1->getPosition(), factor));
	C2->setRefPoint(reference_shift(RefPoint, C2->getPosition(), factor));

	T1->resize(factor, RefPoint);
	R1->resize(factor, RefPoint);
	R2->resize(factor, RefPoint);
	C1->resize(factor, RefPoint);
	C2->resize(factor, RefPoint);

	T1Ref = T1->getPosition();
	R1Ref = R1->getPosition();
	R2Ref = R2->getPosition();
	C1Ref = C1->getPosition();
	C2Ref = C2->getPosition();

	if (factor < 1) {
		addResizes(-1);
	}
	else if (factor > 1) {
		addResizes(1);
	}
}

void Car::rotate(point reference) {
	T1->rotate(RefPoint);
	R1->rotate(RefPoint);
	R2->rotate(RefPoint);
	C1->rotate(RefPoint);
	C2->rotate(RefPoint);
	setRotationAngle(-90);
}

void Car::flip() {
	T1->flip(RefPoint);
	R1->flip(RefPoint);
	R2->flip(RefPoint);
	C1->flip(RefPoint);
	C2->flip(RefPoint);

	RefPoint = R1->getPosition();

	T1Ref = T1->getPosition();
	R1Ref = R1->getPosition();
	R2Ref = R2->getPosition();
	C1Ref = C1->getPosition();
	C2Ref = C2->getPosition();
	if (rotation_angle == 90 || rotation_angle == 270) {
		setRotationAngle(180);
	}
	switchFlip();

}

double Car::getRadius() const {
	return NULL;
}

vector<point> Car::getCorners() const{
	return vector<point>();
}

vector<point> Car::getPoints() const {
	return vector<point>();
}

vector<point> Car::getRevertedPoints() const{
	return vector<point>();
}

bool Car::matching_detection(game* pGame, shape* predicate) {
	bool cond = (T1->matching_detection(pGame, dynamic_cast<Car*>(predicate)->T1) &&
		R1->matching_detection(pGame, dynamic_cast<Car*>(predicate)->R1) &&
		R2->matching_detection(pGame, dynamic_cast<Car*>(predicate)->R2) &&
		(C1->matching_detection(pGame, dynamic_cast<Car*>(predicate)->C1) ||
			C1->matching_detection(pGame, dynamic_cast<Car*>(predicate)->C2)) &&
		(C2->matching_detection(pGame, dynamic_cast<Car*>(predicate)->C2) ||
			C2->matching_detection(pGame, dynamic_cast<Car*>(predicate)->C2)));

	
	return cond;
}

void Car::saveOrnaments(ofstream& file) {
	file << "Car" << " ";
	file << RefPoint.x << " " << RefPoint.y << " ";
	file << rotation_angle << " " << resizes << " " << isFlipped << " ";
	file << static_cast<int>(getColor().ucRed) << " " << static_cast<int>(getColor().ucGreen) << " " << static_cast<int>(getColor().ucBlue) << " ";
	file << static_cast<int>(borderColor.ucRed) << " " << static_cast<int>(borderColor.ucGreen) << " " << static_cast<int>(borderColor.ucBlue) << endl;
}

string Car::getID() const {
	return "Car";
}

point reference_shift(point refc, point refb, double factor) {
	point diff{};
	diff.x = refc.x - refb.x;
	diff.y = refc.y - refb.y;

	point shift{};
	shift.x = round((1 - factor) * diff.x);
	shift.y = round((1 - factor) * diff.y);

	point new_ref{};
	new_ref.x = refb.x + shift.x;
	new_ref.y = refb.y + shift.y;

	return new_ref;
}
void Car::setcolor(color c) {
	T1->setcolor(c);
	C1->setcolor(c);
	C2->setcolor(c);
	R1->setcolor(c);
	R2->setcolor(c);
}

color Car::getColor() const { return T1->getColor(); }
