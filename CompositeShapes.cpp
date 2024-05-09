#include "CompositeShapes.h"
#include "gameConfig.h"

point reference_shift(point refc, point refb, double factor);

////////////////////////////////////////////////////  class Sign  ///////////////////////////////////////
Sign::Sign(game* r_pGame, point ref) :shape(r_pGame, ref)
{
	//calc the ref point of the Sign base and top rectangles relative to the Sign shape
	topRef = ref;	//top rect ref is the same as the sign
	baseRef = { ref.x, ref.y + config.sighShape.topHeight / 2 + config.sighShape.baseHeight / 2 };
	RefPoint = baseRef;
	top = new Rect(pGame, topRef, config.sighShape.topHeight, config.sighShape.topWdth);
	base = new Rect(pGame, baseRef, config.sighShape.baseHeight, config.sighShape.baseWdth);
}

void Sign::draw(int x) const
{
	base->draw(1);
	top->draw(1);
}

void Sign::move(char c)
{
	base->move(c);
	top->move(c);
	RefPoint = base->getPosition();

	baseRef = base->getPosition();
	topRef = top->getPosition();
}

void Sign::resize(double factor) {

	topRef = reference_shift(RefPoint, topRef, factor);
	baseRef = reference_shift(RefPoint, baseRef, factor);

	top->setRefPoint(topRef);
	base->setRefPoint(baseRef);

	base->resize(factor);
	top->resize(factor);
}

void Sign::rotate(point reference) {
	base->rotate(RefPoint);
	top->rotate(RefPoint);
}

void Sign::flip() {
	base->flip(RefPoint);
	top->flip(RefPoint);
}

Home::Home(game* r_pGame, point ref) :shape(r_pGame, ref) {
	topRef = ref;
	baseRef = { ref.x,ref.y + config.Homeshape.side_length / 30 + config.Homeshape.basehght / 2 };
	this->RefPoint = baseRef;
	top = new EqTriangle(pGame, topRef, config.Homeshape.side_length, 1);
	base = new Rect(pGame, baseRef, config.Homeshape.basehght, config.Homeshape.basewdth);
}

void Home::draw(int x) const {
	base->draw(1);
	base->setbordercolor(BLACK);
	top->setcolor(BLUE);
	top->setbordercolor(BLUE);
	top->draw(1);
}

void Home::resize(double factor)
{
	topRef = reference_shift(RefPoint, topRef, factor);
	baseRef = reference_shift(RefPoint, baseRef, factor);

	top->setRefPoint(topRef);
	base->setRefPoint(baseRef);

	base->resize(factor);
	top->resize(factor);
}

void Home::move(char c)
{
	base->move(c);
	top->move(c);
	this->RefPoint = base->getPosition();

	baseRef = base->getPosition();
	topRef = top->getPosition();
}

void Home::rotate(point reference) {
	base->rotate(RefPoint);
	top->rotate(RefPoint);
}

void Home::flip() {
	base->flip(RefPoint);
	top->flip(RefPoint);

	RefPoint = base->getPosition();
	baseRef = base->getPosition();
	topRef = top->getPosition();
}

Person::Person(game* r_pGame, point ref) : shape(r_pGame, ref)
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
}

void Person::resize(double factor)
{
	headRef = reference_shift(RefPoint, headRef, factor);
	bodyRef = reference_shift(RefPoint, bodyRef, factor);
	leftArmRef = reference_shift(RefPoint, leftArmRef, factor);
	rightArmRef = reference_shift(RefPoint, rightArmRef, factor);
	leftLegRef = reference_shift(RefPoint, leftLegRef, factor);
	rightLegRef = reference_shift(RefPoint, rightLegRef, factor);

	head->setRefPoint(headRef);
	body->setRefPoint(bodyRef);
	Larm->setRefPoint(leftArmRef);
	Rarm->setRefPoint(rightArmRef);
	Lleg->setRefPoint(leftLegRef);
	Rleg->setRefPoint(rightLegRef);

	head->resize(factor);
	body->resize(factor);
	Larm->resize(factor);
	Rarm->resize(factor);
	Lleg->resize(factor);
	Rleg->resize(factor);
}


void Person::move(char c)
{
	head->move(c);
	body->move(c);
	Larm->move(c);
	Rarm->move(c);
	Lleg->move(c);
	Rleg->move(c);

	RefPoint = body->getPosition();

	headRef = head->getPosition();
	bodyRef = body->getPosition();
	leftArmRef = Larm->getPosition();
	rightArmRef = Rarm->getPosition();
	leftLegRef = Lleg->getPosition();
	rightLegRef = Rleg->getPosition();
}

ice_cream::ice_cream(game* r_pGame, point ref) : shape(r_pGame, ref) {
	scoopRef = { ref.x,ref.y };
	coneRef = { ref.x + config.ice_cream.side_lenght - 50 ,ref.y + 8 };
	RefPoint = scoopRef;
	scoop = new circle(r_pGame, scoopRef, config.ice_cream.headDiameter / 2);
	cone = new EqTriangle(r_pGame, coneRef, config.ice_cream.side_lenght, 0);
}

void ice_cream::draw(int x) const
{
	scoop->setcolor(ORANGE);
	scoop->setbordercolor(ORANGE);
	scoop->draw(1);
	cone->setcolor(WHITE);
	cone->setbordercolor(BLACK);
	cone->draw(0);
}

void ice_cream::move(char c)
{
	scoop->move(c);
	cone->move(c);

	RefPoint = scoop->getPosition();
	scoopRef = scoop->getPosition();
	coneRef = cone->getPosition();
}

void ice_cream::resize(double factor)
{

	scoopRef = reference_shift(RefPoint, scoopRef, factor);
	coneRef = reference_shift(RefPoint, coneRef, factor);

	cone->setRefPoint(coneRef);
	scoop->setRefPoint(scoopRef);

	cone->resize(factor);
	scoop->resize(factor);
}

void ice_cream::rotate(point reference) {
	scoop->rotate(RefPoint);
	cone->rotate(RefPoint);
}

void ice_cream::flip() {
	scoop->flip(RefPoint);
	cone->flip(RefPoint);

	RefPoint = scoop->getPosition();
	scoopRef = scoop->getPosition();
	coneRef = cone->getPosition();
}

Tree::Tree(game* r_pGame, point ref) : shape(r_pGame, ref) {
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

void Tree::draw(int x) const {
	T1->setcolor(LIMEGREEN);
	T1->setbordercolor(LIMEGREEN);
	T1->draw(1);
	T2->setcolor(LIMEGREEN);
	T2->setbordercolor(LIMEGREEN);
	T2->draw(1);
	T3->setcolor(LIMEGREEN);
	T3->setbordercolor(LIMEGREEN);
	T3->draw(1);
	body->setcolor(config.fillColor = SANDYBROWN);
	body->setbordercolor(config.penColor = SANDYBROWN);
	body->draw(1);
	config.fillColor = RED;
	config.penColor = RED;
}

void Tree::move(char c)
{
	T1->move(c);
	T2->move(c);
	T3->move(c);
	body->move(c);

	RefPoint = body->getPosition();

	bodyRef = body->getPosition();
	T1Ref = T1->getPosition();
	T2Ref = T2->getPosition();
	T3Ref = T3->getPosition();
}

void Tree::resize(double factor)
{
	T1Ref = reference_shift(RefPoint, T1Ref, factor);
	T2Ref = reference_shift(RefPoint, T2Ref, factor);
	T3Ref = reference_shift(RefPoint, T3Ref, factor);
	bodyRef = reference_shift(RefPoint, bodyRef, factor);

	T1->setRefPoint(T1Ref);
	T2->setRefPoint(T2Ref);
	T3->setRefPoint(T3Ref);
	body->setRefPoint(bodyRef);

	T1->resize(factor);
	T2->resize(factor);
	T3->resize(factor);
	body->resize(factor);
}

void Tree::rotate(point reference) {
	body->rotate(RefPoint);
	T1->rotate(RefPoint);
	T2->rotate(RefPoint);
	T3->rotate(RefPoint);
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
}

Rocket::Rocket(game* r_pGame, point ref) : shape(r_pGame, ref) {
	T1Ref = { ref.x + config.Rocket.side_length - 70,ref.y - 10 };
	T2Ref = { ref.x + config.Rocket.Rbase_length - 65,ref.y + 35 };
	T3Ref = { ref.x + config.Rocket.Lbase_length - 40,ref.y + 35 };
	bodyRef = { ref.x - config.Rocket.basewdth - 9, ref.y + config.Rocket.basehght -45 };
	RefPoint = bodyRef;
	T1 = new EqTriangle(r_pGame, T1Ref, config.Rocket.side_length, 1);
	T2 = new RightTriangle(r_pGame, T2Ref, config.Rocket.Rbase_length, config.Rocket.Rhght, 2);
	T3 = new RightTriangle(r_pGame, T3Ref, config.Rocket.Lbase_length, config.Rocket.Lhght, 1);
	body = new Rect(r_pGame, bodyRef, config.Rocket.basehght, config.Rocket.basewdth);
}

void Rocket::draw(int x) const
{
	T1->setcolor(PURPLE);
	T1->setbordercolor(PURPLE);
	T1->draw(5);
	T2->setcolor(RED);
	T2->setbordercolor(RED);
	T2->draw(2);
	T3->setcolor(RED);
	T3->setbordercolor(RED);
	T3->draw(1);
	body->setcolor(config.fillColor = BLUE);
	body->setbordercolor(config.penColor = BLUE);
	body->draw(1);
	config.fillColor = RED;
	config.penColor = RED;
}

void Rocket::resize(double factor)
{

	T1Ref = reference_shift(RefPoint, T1Ref, factor);
	T2Ref = reference_shift(RefPoint, T2Ref, factor);
	T3Ref = reference_shift(RefPoint, T3Ref, factor);
	bodyRef = reference_shift(RefPoint, bodyRef, factor);

	T1->setRefPoint(T1Ref);
	T2->setRefPoint(T2Ref);
	T3->setRefPoint(T3Ref);
	body->setRefPoint(bodyRef);

	T1->resize(factor);
	T2->resize(factor);
	T3->resize(factor);
	body->resize(factor);
}

void Rocket::move(char c)
{
	T1->move(c);
	T3->move(c);
	T2->move(c);
	body->move(c);

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
}

Car::Car(game* r_pGame, point ref) :shape(r_pGame, ref)
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

void Car::draw(int x) const
{
	T1->setcolor(BLUE);
	T1->setbordercolor(BLACK);
	T1->draw(3);
	R1->setcolor(config.fillColor = CYAN);
	R1->setbordercolor(config.penColor = CYAN);
	R1->draw(3);
	R2->draw(3);
	config.fillColor = RED;
	config.penColor = RED;
	C1->setcolor(BLACK);
	C1->setbordercolor(BLACK);
	C1->draw(3);
	C2->setcolor(BLACK);
	C2->setbordercolor(BLACK);
	C2->draw(3);
}

void Car::move(char c)
{
	T1->move(c);
	R1->move(c);
	R2->move(c);
	C1->move(c);
	C2->move(c);

	RefPoint = R1->getPosition();

	T1Ref = T1->getPosition();
	R1Ref = R1->getPosition();
	R2Ref = R2->getPosition();
	C1Ref = C1->getPosition();
	C2Ref = C2->getPosition();
}


void Car::resize(double factor)
{
	T1Ref = reference_shift(RefPoint, T1Ref, factor);
	R1Ref = reference_shift(RefPoint, R1Ref, factor);
	R2Ref = reference_shift(RefPoint, R2Ref, factor);
	C1Ref = reference_shift(RefPoint, C1Ref, factor);
	C2Ref = reference_shift(RefPoint, C2Ref, factor);

	T1->setRefPoint(T1Ref);
	R1->setRefPoint(R1Ref);
	R2->setRefPoint(R2Ref);
	C1->setRefPoint(C1Ref);
	C2->setRefPoint(C2Ref);

	T1->resize(factor);
	R1->resize(factor);
	R2->resize(factor);
	C1->resize(factor);
	C2->resize(factor);
}

void Car::rotate(point reference) {
	T1->rotate(RefPoint);
	R1->rotate(RefPoint);
	R2->rotate(RefPoint);
	C1->rotate(RefPoint);
	C2->rotate(RefPoint);
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