# CPPND: Capstone Snake Game Expanded

This is my repo for the Capstone project in the [Udacity C++ Nanodegree Program](https://www.udacity.com/course/c-plus-plus-nanodegree--nd213). 
My project is to modify the snake game in the CPPND starter repo which was inspired by [this](https://codereview.stackexchange.com/questions/212296/snake-game-in-c-with-sdl) excellent StackOverflow post and set of responses.
My goal was to add independent movable objects in the scene (circles, rectangles) that float around, moving sideways or vertically up and down.
Tnese obstacles make the player lose if the head of the snake enters a collision with them.
The obstacles keep moving up and down (or from side to side) unless they collide with the body of the snake, in which case they bounce back in the other direction.
They have an internal mechanism that makes them change direction after a certain time.
The speed of those obstacles also increases as the score increases.





## Dependencies for Running Locally
* cmake >= 3.7
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* SDL2 >= 2.0
  * All installation instructions can be found [here](https://wiki.libsdl.org/Installation)
  >Note that for Linux, an `apt` or `apt-get` installation is preferred to building from source. 
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools](https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)

## Basic Build Instructions

1. Clone this repo.
2. Make a build directory in the top level directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./SnakeGame`.



## Files and Class structure
In addition to the original snake structure, I have implemented a generic obstacle class (obstacle.cpp and obstacle.h) which contain generic methods and properties for obstacles.
I have also implemented two similar types of obstacles (Squares and Circles) that will be rendered differently.
The obstacles are created in main and pushed into vectors which are then passed to the game class.
The game class gets initialized and passes the grid parameters as well as a reference to the snake to the obstacles.
As the game is ran, the obstacles are fired into each their own thread for simulation.
All obstacles keep track of the game's snake.
The obstacles run in their own direction and their direction changes upon contact with the snake body.
The game is over if the snake head collides with one of the obstacles.
The renderer was modified to render the different types of obstacles and their position. 


## Rubric points addressed
The project uses Object Oriented Programming techniques.
--> All methods are all encapsulated into the different classes, and their member variables are accessed using those methods
--> Example: the obstacle's getSize method returns the size of the obstacle
Classes use appropriate access specifiers for class members.
--> Example: To be properly inherited by children classes, the parent obstacle class sets many of its member variables as protected (such that the derived classes will get them as private).
Derived class functions override virtual base class functions.
--> The simulate class from the base obstacle class needed to be adapted for both obstacle types
The project uses smart pointers instead of raw pointers.
--> the obstacles are declared as shared ptrs and referenced throughout the program. We do not need to worry about their memory deallocation at end of program.
The project uses multithreading
--> Each obstacle gets its own thread (see simulate function in square.cpp and circle.cpp).
 
