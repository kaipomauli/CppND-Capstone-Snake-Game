#ifndef CIRCLE_H
#define  CIRCLE_H

#include "obstacle.h"
#include "SDL.h"


class Circle : public Obstacle, public std::enable_shared_from_this<Circle>
{
public:
    // constructor / desctructor
   Circle();
    Circle(int r,double speed,Obstacle::Direction dir,int gridW,int gridH);
    void getRadius(int &r) { r = _radius; };
    // typical behaviour methods
    void simulate();
    
    // miscellaneous
    std::shared_ptr<Circle> get_shared_this() { return shared_from_this(); }

private:
    // typical behaviour methods
    void run();
    int _radius;
    
                                   
};

#endif