#pragma once

#include "Intersection.h"

class Car {
public:
	float posX, posY, speed;
	int tc = 0;
	Car();
	void moveToCar(float tx, float ty, bool up);
	void moveToIntersection(Intersection *inter, bool up);
	void displayCar();
	bool nextRoadIsRight();
protected:

private:

};