#include <GL/glut.h>
#include <GLFW/glfw3.h>
#include <time.h>

#include "Intersection.h"
#include "constants.h"
#include "global.h"

Intersection::Intersection() {
	
}

Intersection::Intersection(float x, float y) {
	posX = x;
	posY = y;
}

bool Intersection::isRedDown() {
	if (((clock() - global::t0) / 1000) % 2 != 0) {
		return true;
	}
	else {
		return false;
	}
}

bool Intersection::isRedLeft() {
	if (((clock() - global::t0) / 1000) % 2 != 0) {
		return false;
	}
	else {
		return true;
	}
}

void Intersection::displayIntersection() {
	GLfloat point[] = {posX * constants::ratioX, posY * constants::ratioY};
	if (isRedLeft()) {
		glColor3f(1.0f, 0.0f, 0.0f);
	}
	else {
		glColor3f(0.0f, 1.0f, 0.0f);
	}
	glVertexPointer(2, GL_FLOAT, 0, point);
	glDrawArrays(GL_POINTS, 0, 1);
}