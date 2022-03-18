#ifndef SQUARE_H
#define SQUARE_H

#include "obstacle.h"
#include "SDL.h"


class Square : public Obstacle, public std::enable_shared_from_this<Square>
{
public:
    // constructor / desctructor
    Square();

    // getters / setters
    SDL_Point getCurrentPos() { return SDL_Point{(int)_posX, (int)_posY}; };
    

    // typical behaviour methods
    void simulate();

    // miscellaneous
    std::shared_ptr<Square> get_shared_this() { return shared_from_this(); }

private:
    // typical behaviour methods
    void run();

    
                                   // ego speed in m/s
};

#endif