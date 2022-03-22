#include <iostream>
#include <random>
#include "square.h"

Square::Square()
{
    
    _posX = 0;
    _posY = 0;
    _type = ObjectType::objectSquare;
    _speed = 0.1; // m/s
    _direction = Direction::kUp;
    _width = 1;
    _height = 1;
}

Square::Square(int w, int h,double speed, Obstacle::Direction dir,int gridW,int gridH)
{

    _posX = 0;
    _posY = 0;
    _type = ObjectType::objectSquare;
    _speed = speed; // m/s
    _direction = dir;
    _width = w;
    _height = h;
    _gridWidth = gridW;
    _gridHeight = gridH;
}


void Square::simulate()
{
    // launch drive function in a thread
    threads.emplace_back(std::thread(&Square::run, this));
}

// virtual function which is executed in a thread
void Square::run()
{
    // print id of the current thread
    std::unique_lock<std::mutex> lck(_mtx);
    std::cout << "Square #" << _id << "::run: thread id = " << std::this_thread::get_id() << std::endl;
    lck.unlock();

    // initalize variables
    bool hasCollidedWithSomething = false;
       
    while (true)
    {
        
        // sleep at every iteration to reduce CPU usage
        std::this_thread::sleep_for(std::chrono::milliseconds(1));

        switch (_direction) {
        case Direction::kUp:
            _posY -= _speed;
            break;

        case Direction::kDown:
            _posY += _speed;
            break;

        case Direction::kLeft:
            _posX -= _speed;
            break;

        case Direction::kRight:
            _posX += _speed;
            break;
        }
        // Wrap the Snake around to the beginning if going off of the screen.
        _posX = fmod(_posX + _gridWidth, _gridWidth);
       _posY = fmod(_posY + _gridHeight, _gridHeight);
            
     }
        

  
}
