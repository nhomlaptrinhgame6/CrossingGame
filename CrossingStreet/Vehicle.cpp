#include "Vehicle.h"
void Vehicle::copyVehicle(const Vehicle& a)
{
	mX = a.mX;
	mY = a.mY;
};
Vehicle::Vehicle() {
	mX = mY = 0;
};
Vehicle::Vehicle(int x, int y) {
	mX = x;
	mY = y;
};
Vehicle::Vehicle(const Vehicle& a) {
	copyVehicle(a);
}
void Vehicle::setPos(int x, int y) {
	mX = x;
	mY = y;
}