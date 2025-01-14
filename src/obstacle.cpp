#include <algorithm>
#include <iostream>
#include <chrono>
#include "obstacle.h"

// init static variable
int Obstacle::_idCnt = 0;

std::mutex Obstacle::_mtx;

void Obstacle::setPosition(double x, double y)
{
    _posX = x;
    _posY = y;
}

void Obstacle::setSize(int x, int y)
{
    _width = x;
    _height= y;
}

void Obstacle::getPosition(double &x, double &y)
{
    x = _posX;
    y = _posY;
}

void Obstacle::getSize(int &x, int &y)
{
    x = _width;
    y = _height;
}

Obstacle::Obstacle()
{
    _type = ObjectType::noObject;
    _id = _idCnt++;
    _snk = nullptr;
}

Obstacle::~Obstacle()
{
    // set up thread barrier before this object is destroyed
    std::for_each(threads.begin(), threads.end(), [](std::thread &t) {
        t.join();
    });
    std::cout << "Obstacle object with ID " << this->getID() << " is getting destroyed." << std::endl;
}
