#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <vector>
#include <thread>
#include <mutex>

enum ObjectType
{
    noObject,
    objectSquare,
    objectBall,
    objectTriangle,
};

class Obstacle
{
public:
    // constructor / desctructor
    Obstacle();
    ~Obstacle();
    enum class Direction { kUp, kDown, kLeft, kRight };

    // getter and setter
    int getID() { return _id; }
    void setPosition(double x, double y);
	void setSize(int x, int y);
    void getPosition(double &x, double &y);
	void getSize(int &x, int &y);
    ObjectType getType() { return _type; }

    // typical behaviour methods
    virtual void simulate(){};

protected:
    Direction _direction;
    ObjectType _type;                 // identifies the class type
    int _id;                          // every traffic object has its own unique id
    double _posX, _posY;              // object position in pixels
	int _width, _height;              // object position in pixels
    std::vector<std::thread> threads; // holds all threads that have been launched within this object
    static std::mutex _mtx;           // mutex shared by all traffic objects for protecting cout 
                                 // position on current street
    double _speed;
private:
    static int _idCnt; // global variable for counting object ids
};

#endif