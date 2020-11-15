#pragma once

#include <list>

#include "Intersection.h"
#include "Car.h"

class Road {
public:
	bool up;
	Intersection *i1;
	Intersection *i2;
	Road *nextRight;
	Road *nextUp;
	std::list<Car*> listCar;
	Road();
	Road(Intersection *id, Intersection *ia, bool way);
	bool containCar();
	void addCar(Car *c);
	void removeCar();
	void moveCar();
	void displayRoad();
protected:

private:

};