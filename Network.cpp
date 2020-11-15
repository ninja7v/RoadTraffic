#include <GL/glut.h>
#include <GLFW/glfw3.h>
#include <time.h>

#include "Network.h"
#include "constants.h"
#include "global.h"
#include "Intersection.h"
#include "Road.h"

Network::Network() {
	//intersections
	for (int k = 0; k < constants::sizeX; k++) {
		for (int l = 0; l < constants::sizeY; l++) {
			i[k][l] = Intersection(k * constants::epsilon, l * constants::epsilon);
		}
	}

	//roads
	//conditions for strait line
	min = 0;
	if (constants::sizeY == 1) {
		min = 1;
	}
	max = 1;
	if (constants::sizeX == 1) {
		max = 0;
	}
	//declarations
	for (int b = min; b < max + 1; b++) { //b=0^ b=1->
		for (int k = 0; k < constants::sizeX; k++) {
			for (int l = 0; l < constants::sizeY; l++) {
				if (b == 0) { //^
					if (l != constants::sizeY - 1) {
						r[b][k][l] = Road(&i[k][l], &i[k][l + 1], b);
					}
				}
				else { //->
					if (k != constants::sizeX - 1) {
						r[b][k][l] = Road(&i[k][l], &i[k + 1][l], b);
					}
				}
			}
		}
	}
	//linking
	for (int b = min; b < max + 1; b++) { //b=0^ b=1->
		for (int k = 0; k < constants::sizeX; k++) {
			for (int l = 0; l < constants::sizeY; l++) {
				if (b == 0) { //^
					if (l != constants::sizeY - 2) {
						r[b][k][l].nextUp = &r[0][k][l + 1];
					}
					if (k != constants::sizeX - 1) {
						r[b][k][l].nextRight = &r[1][k][l + 1];
					}
				}
				else { //->
					if (l != constants::sizeY - 1) {
						r[b][k][l].nextUp = &r[0][k + 1][l];
					}
					if (k != constants::sizeX - 2) {
						r[b][k][l].nextRight = &r[1][k + 1][l];
					}
				}
			}
		}
	}

	//cars
	for (int k = 0; k < constants::nbCarMax; k++) {
		c[k] = Car();
		if (constants::sizeX > 1 && constants::sizeY > 1) {
			if (c[k].nextRoadIsRight()) {
				r[1][0][0].addCar(&c[k]);
			}
			else {
				r[0][0][0].addCar(&c[k]);
			}
		}
		else if (constants::sizeX > 1) {
			r[1][0][0].addCar(&c[k]);
		}
		else if (constants::sizeY > 1) {
			r[0][0][0].addCar(&c[k]);
		}
	}
}

void Network::displayNetwork() {
	GLFWwindow* window;
	glfwInit();
	window = glfwCreateWindow(constants::SCREEN_WIDTH, constants::SCREEN_HEIGHT, "Network", NULL, NULL);
	glfwMakeContextCurrent(window);

	glViewport(0.0f, 0.0f, constants::SCREEN_WIDTH, constants::SCREEN_HEIGHT); // specifies the part of the window to which OpenGL will draw (in pixels), convert from normalised to pixels
	glMatrixMode(GL_PROJECTION); // projection matrix defines the properties of the camera that views the objects in the world coordinate frame. Here you typically set the zoom factor, aspect ratio and the near and far clipping planes
	glLoadIdentity(); // replace the current matrix with the identity matrix and starts us a fresh because matrix transforms such as glOrpho and glRotate cumulate, basically puts us at (0, 0, 0)
	glOrtho(0, constants::SCREEN_WIDTH, 0, constants::SCREEN_HEIGHT, 0, 1); // essentially set coordinate system
	glMatrixMode(GL_MODELVIEW); // (default matrix mode) modelview matrix defines how your objects are transformed (meaning translation, rotation and scaling) in your world
	glLoadIdentity(); // same as above comment

	global::t0 = clock();
	while (!glfwWindowShouldClose(window)) {
		glClear(GL_COLOR_BUFFER_BIT);
		//roads
		glEnable(GL_LINE_SMOOTH);
		glEnableClientState(GL_VERTEX_ARRAY);
		glLineWidth(4);
		for (int b = min; b < max + 1; b++) { //b=0^ b=1->
			for (int k = 0; k < constants::sizeX; k++) {
				for (int l = 0; l < constants::sizeY; l++) {
					if (b == 0) { //^
						if (l != constants::sizeY - 1) {
							r[b][k][l].displayRoad();
						}
					}
					else { //->
						if (k != constants::sizeX - 1) {
							r[b][k][l].displayRoad();
						}
					}
				}
			}
		}
		glDisableClientState(GL_VERTEX_ARRAY);
		glDisable(GL_LINE_SMOOTH);

		//intersections
		glEnable(GL_POINT_SMOOTH);
		glEnableClientState(GL_VERTEX_ARRAY);
		glPointSize(20);
		for (int k = 0; k < constants::sizeX; k++) {
			for (int l = 0; l < constants::sizeY; l++) {
				i[k][l].displayIntersection();
			}
		}
		glDisableClientState(GL_VERTEX_ARRAY);
		glDisable(GL_POINT_SMOOTH);
		
		//Cars
		this->updateCarPosition();
		glEnableClientState(GL_VERTEX_ARRAY);
		glPointSize(20);
		for (int k = 0; k < constants::nbCarMax; k++) {
			c[k].displayCar();
		}
		glDisableClientState(GL_VERTEX_ARRAY);

		// Swap front and back buffers
		glfwSwapBuffers(window);
		// Poll for and process events
		glfwPollEvents();
	}
	glfwTerminate();
}

void Network::updateCarPosition() {
	//conditions for strait line
	for (int b = min; b < max + 1; b++) { //b=0^ b=1->
		for (int k = 0; k < constants::sizeX; k++) {
			for (int l = 0; l < constants::sizeY; l++) {
				if (b == 0) { //^
					if (l != constants::sizeY - 1) {
						r[b][k][l].moveCar();
					}
				}
				else { //->
					if (k != constants::sizeX - 1) {
						r[b][k][l].moveCar();
					}
				}
			}
		}
	}
}