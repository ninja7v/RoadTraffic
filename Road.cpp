#include <list>
#include <iterator>
#include <iostream>
#include <GL/glut.h>
#include <GLFW/glfw3.h>

#include "Car.h"
#include "constants.h"
#include "Road.h"
#include "Intersection.h"

Road::Road() {
	
}

Road::Road(Intersection* id, Intersection* ia, bool way) {
	up = !way;
	i1 = id;
	i2 = ia;
	nextRight = nullptr;
	nextUp = nullptr;
}

bool Road::containCar() {
	if (listCar.empty()) {
		return false;
	}
	else {
		return true;
	}
}

void Road::addCar(Car *c) {
	//add at the end
	listCar.push_back(c);
	//set the car at the intersection
	c->posX = i1->posX;
	c->posY = i1->posY;
}

void Road::removeCar() {
	listCar.pop_front();
}

void Road::moveCar() {
	//condition contain car
	if (containCar()) {
		//for the first car
		Car* c1 = listCar.front();
		//conditions at the intersection
		if ((i2->posX - c1->posX + i2->posY - c1->posY) < 0.001f) {
			//if both exist
			if (nextRight && nextUp) {
				if (c1->nextRoadIsRight()) {
					nextRight->addCar(c1);
					this->removeCar();
				}
				else {
					nextUp->addCar(c1);
					this->removeCar();
				}
			}
			//if both are null
			else if (!nextRight && !nextUp) {
				this->removeCar();
			}
			//if the right exist
			else if (nextRight) {
				nextRight->addCar(c1);
				this->removeCar();
			}
			//if the up exist
			else {
				nextUp->addCar(c1);
				this->removeCar();
			}
		}
		else {
			c1->moveToIntersection(i2, up);
		}
		//for the folowing cars
		std::list<Car*>::iterator it;
		if (listCar.size() > 1) {
			for (it = next(listCar.begin()); it != listCar.end(); it++) {
				std::list<Car*>::iterator itnext = it;
				itnext = itnext--;
				if (up) {
					(*it)->moveToCar((*itnext)->posX, (*itnext)->posY, 1);
				}
				else {
					(*it)->moveToCar((*itnext)->posX, (*itnext)->posY, 0);
				}
			}
		}
	}
}

void Road::displayRoad() {
	glColor3f(1.0f, 1.0f, 1.0f);
	GLfloat line[] = {i1->posX * constants::ratioX, i1->posY * constants::ratioY, 0,
		i2->posX * constants::ratioX, i2->posY * constants::ratioY, 0
	};
	glVertexPointer(3, GL_FLOAT, 0, line);
	glDrawArrays(GL_LINES, 0, 2);
}