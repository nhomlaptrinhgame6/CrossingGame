#include "Animal.h"
Animal::Animal() {
	mX = mY = 0;
};
Animal::Animal(int x, int y) {
	mX = x;
	mY = y;
};
void Animal::setPos(int x, int y) {
	mX = x;
	mY = y;
};