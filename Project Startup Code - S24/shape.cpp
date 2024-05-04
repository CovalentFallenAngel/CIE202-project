#include "shape.h"
#include "game.h"
#include "gameConfig.h"

shape::shape(game* r_pGame, point ref)
{
	RefPoint = ref;
	pGame = r_pGame;
	fillColor = config.fillColor;
	borderColor = config.penColor;
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



//void ResizeRect(double& r_hght, double& r_wdth, double factor) {
//    const double x = r_hght;
//    const double y = r_wdth;
//    if (factor > 1)
//        if (r_hght < x * 2 && r_wdth < y * 2) {
//            r_hght *= factor;
//            r_wdth *= factor;
//        }
//    if (factor < 1)
//        if (r_hght > x * 0.5 && r_wdth > y * 0.5) {
//            r_hght *= factor;
//            r_wdth *= factor;
//        }
//}
//
//void ResizeCircle(double& r, double factor) {
//    const double rad = r;
//    if (factor > 1)
//        if (r < rad * 2)
//            r *= factor;
//    if (factor < 1)
//        if (r > rad * 0.5)
//            r *= factor;
//}
//
//void ResizeEqTriangle(double& SL, double factor) {
//    const double Side = SL;
//    if (factor > 1)
//        if (SL < Side * 2)
//            SL *= factor;
//    if (factor < 1)
//        if (SL > Side * 0.5)
//            SL *= factor;
//}
//
//void ResizeRocket(double& r_hght, double& r_wdth, double& SL, double factor) {
//    ResizeRect(r_hght, r_wdth, factor);
//    ResizeEqTriangle(SL, factor);
//}
//
//void ResizeTree(double& r_hght, double& r_wdth, double& SL, double factor) {
//    ResizeRect(r_hght, r_wdth, factor);
//    ResizeEqTriangle(SL, factor);
//}
//
//void ResizeCar(double& r_hght, double& r_wdth, double& r, double factor) {
//    ResizeRect(r_hght, r_wdth, factor);
//    ResizeCircle(r, factor);
//}
//
//void ResizeHome(double& r_hght, double& r_wdth, double& SL, double factor) {
//    ResizeEqTriangle(SL, factor);
//    ResizeRect(r_hght, r_wdth, factor);
//}
//
//void ResizePerson(double& r_hght, double& r_wdth, double& r, double factor) {
//    ResizeRect(r_hght, r_wdth, factor);
//    ResizeCircle(r, factor);
//}
//
//void ResizeCone(double& r, double& SL, double factor) {
//    ResizeEqTriangle(SL, factor);
//    ResizeCircle(r, factor);
//}