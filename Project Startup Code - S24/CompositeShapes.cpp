#include "CompositeShapes.h"
#include "gameConfig.h"

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
}

void Sign::resize(double factor) {
	base->resize(factor);
	top->resize(factor);
}

void Sign::rotate() {
	base->rotate(RefPoint);
	top->rotate(RefPoint);
}

void Sign::flip() {
	base->flip(RefPoint);
	top->flip(RefPoint);
}

Home::Home(game* r_pGame, point ref) :shape(r_pGame, ref) {
	point topRef = ref;
	point baseRef = { ref.x,ref.y + config.Homeshape.side_length / 30 + config.Homeshape.basehght / 2 };
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

void Home::resize(double factor) {
	top->resize(factor);
	base->resize(factor);
}

void Home::move(char c)
{
	base->move(c);
	top->move(c);
}

void Home::rotate() {
	base->rotate(RefPoint);
	top->rotate(RefPoint);
}

void Home::flip() {
	base->flip(RefPoint);
	top->flip(RefPoint);
}

Person::Person(game* r_pGame, point ref) : shape(r_pGame, ref)
{
	// calculate the reference points of the pearson body parts relative to the Pearson shape
	point headRef = { ref.x ,ref.y - 15 };                                 // head ref is the same as the pearson
	point bodyRef = { ref.x - config.Person.width / 40, ref.y + config.Person.height / 2 };
	point leftArmRef = { ref.x - config.Person.width / 2 - config.Person.armLength - 1, ref.y + 25 };
	point rightArmRef = { ref.x + config.Person.width / 2 + config.Person.armLength - 1, ref.y + 25 };
	point leftLegRef = { ref.x - config.Person.width / 4, ref.y + config.Person.height };
	point rightLegRef = { ref.x + config.Person.width / 4, ref.y + config.Person.height };

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

void Person::rotate() {
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
}

void Person::resize(double factor)
{
	head->resize(factor);
	body->resize(factor);
	Larm->resize(factor);
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
}

ice_cream::ice_cream(game* r_pGame, point ref) : shape(r_pGame, ref) {
	point scoopRef = { ref.x,ref.y };
	point coneRef = { ref.x + config.ice_cream.side_lenght - 50 ,ref.y + 8 };
	RefPoint = coneRef;
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
}

void ice_cream::resize(double factor)
{
	scoop->resize(factor);
	cone->resize(factor);
}

void ice_cream::rotate() {
	scoop->rotate(RefPoint);
	cone->rotate(RefPoint);
}

void ice_cream::flip() {
	scoop->flip(RefPoint);
	cone->flip(RefPoint);
}

Tree::Tree(game* r_pGame, point ref) : shape(r_pGame, ref) {
	point T1Ref = { ref.x + config.Tree.side_length - 50,ref.y };
	point T2Ref = { ref.x + config.Tree.side_length - 50,ref.y - 10 };
	point T3Ref = { ref.x + config.Tree.side_length - 50,ref.y - 20 };
	point bodyRef = { ref.x - config.Tree.basewdth / 40, ref.y + config.Tree.basehght / 2 };
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
}

void Tree::resize(double factor) {
	T1->resize(factor);
	T2->resize(factor);
	T3->resize(factor);
	body->resize(factor);
}

void Tree::rotate() {
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
}

Rocket::Rocket(game* r_pGame, point ref) : shape(r_pGame, ref) {
	point T1Ref = { ref.x + config.Rocket.side_length - 70,ref.y - 10 };
	point T2Ref = { ref.x + config.Rocket.Rbase_length - 70,ref.y + 35 };
	point T3Ref = { ref.x + config.Rocket.Lbase_length - 39,ref.y + 35 };
	point bodyRef = { ref.x - config.Rocket.basewdth - 9, ref.y + config.Tree.basehght / 2 };
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
}

void Rocket::rotate() {
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
}

Car::Car(game* r_pGame, point ref) :shape(r_pGame, ref)
{
	point T1Ref = { ref.x + config.Car.T1base_length - 95,ref.y - 20 };
	point C1Ref = { ref.x + config.Car.Radius - 100,ref.y + 25 };
	point C2Ref = { ref.x + config.Car.Radius - 70,ref.y + 25 };
	point R1Ref = { ref.x - config.Car.R1wdth - 20, ref.y + config.Car.R1hght - 30 };
	point R2Ref = { ref.x - config.Car.R2wdth - 9, ref.y + config.Car.R1hght / 2 };
	RefPoint = R1Ref;
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
}


void Car::resize(double factor)
{
	T1->resize(factor);
	R1->resize(factor);
	R2->resize(factor);
	C1->resize(factor);
	C2->resize(factor);
}

void Car::rotate() {
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
}