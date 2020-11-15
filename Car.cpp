#include <cstdlib> //rand()
#include <iostream>
#include <GL/glut.h>
#include <math.h>
#include <time.h>

#include "Car.h"
#include "constants.h"
#include "global.h"

Car::Car() {
    posX = 0.0f;
    posY = 0.0f;
    speed = 1.0f;//pixel per seconds
}

void Car::moveToCar(float tx, float ty, bool up) {
    //distance with the car in front
    //sqrt(pow((tx - posx) * epsilon, 2) + pow((ty - posy)) * epsilon, 2));
    float distance = (tx - posX + ty - posY) * constants::epsilon;
    if (distance < constants::distanceSecurity){
        speed = 0;
    }
    else {
        //speed function
        speed = constants::speedMax - (constants::speedMax * constants::distanceSecurity) / distance;
        if (!up) {
            posX += speed;
            //posX += ((speed * (clock() - global::t0) / 1000) - (speedt0 * (tc - global::t0) / 1000));
        }
        else {
            posY += speed;
            //posY += ((speed * (clock() - global::t0) / 1000) - (speedt0 * (tc - global::t0) / 1000));
        }
    }
}

void Car::moveToIntersection(Intersection *inter, bool up) {
    bool isRed;
    if ((up && inter->isRedDown()) || (!up && inter->isRedLeft())){
        isRed = true;
    }
    else {
        isRed = false;
    }
    //distance with the intersection in front
    //sqrt(pow((tx - posx) * epsilon, 2) + pow((ty - posy)) * epsilon, 2));
    float distance = (inter->posX - posX + inter->posY - posY);
    //speedt0 = speed;
    if (distance < constants::distanceSecurity && isRed) {
        speed = 0;
    }
    else if (isRed) {
        speed = constants::speedMax - (constants::speedMax * constants::distanceSecurity) / distance;
    }
    else {
        speed = constants::speedMax;
    }
    if (up) {
        posY += speed;
        //posY += ((speed * (clock() - global::t0) / 1000) - (speedt0 * (tc - global::t0) / 1000));
    }
    else {
        posX += speed;
        //posX += ((speed * (clock() - global::t0) / 1000) - (speedt0 * (tc - global::t0) / 1000));
    }
    //tc = clock();
}

void Car::displayCar() {
    GLfloat point[] = { posX * constants::ratioX, posY * constants::ratioY };
    glColor3f(0.5f, 0.0f, 0.5f);
    glVertexPointer(2, GL_FLOAT, 0, point);
    glDrawArrays(GL_POINTS, 0, 1);
}

bool Car::nextRoadIsRight() {
    return rand() % 2;
}