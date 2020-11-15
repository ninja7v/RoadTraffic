#pragma once

#include "constants.h"
#include "global.h"
#include "Intersection.h"
#include "Road.h"
#include "Car.h"

//we consider a Manhatan network
class Network {
public:
	//case of a line
	int min, max;
	Intersection i[constants::sizeX][constants::sizeY];
	Road r[2][constants::sizeX][constants::sizeY];
	Car c[constants::nbCarMax];
	Network();
	void displayNetwork();
	void updateCarPosition();
protected:

private:

};