#include <iostream>
#include <random>
#include "circle.h"
#include <cmath>
#include<algorithm>

Circle::Circle()
{

	_posX = 0;
	_posY = 0;
	_type = ObjectType::objectBall;
	_speed = 0.1; // m/s
	_direction = Direction::kUp;
	
}

Circle::Circle(int r, double speed, Obstacle::Direction dir, int gridW, int gridH)
{

	_posX = 0;
	_posY = 0;
	_type = ObjectType::objectBall;
	_speed = speed; // m/s
	_direction = dir;
	_gridWidth = gridW;
	_gridHeight = gridH;
	_radius = r;
}


void Circle::simulate()
{
	// launch drive function in a thread
	threads.emplace_back(std::thread(&Circle::run, this));
}

// virtual function which is executed in a thread
void Circle::run()
{
	Uint32 title_timestamp = SDL_GetTicks();
	Uint32 frame_start;
	Uint32 frame_end;
	Uint32 frame_duration;
	int frame_count = 0;
	// print id of the current thread
	std::unique_lock<std::mutex> lck(_mtx);
	std::cout << "Cirlce #" << _id << "::run: thread id = " << std::this_thread::get_id() << std::endl;
	lck.unlock();


	

	while (_snk->alive)
	{
		_speed = _snk->speed * 0.75;
		frame_start = SDL_GetTicks();



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
		
		//check for collision between snake body and circle bounding box
		for (auto const& item : _snk->body) {
			
				if(_posX-_radius < item.x + 1 && _posX-_radius + 2*_radius > item.x && _posY-_radius < item.y + 1 && 2*_radius + _posY-_radius > item.y){
				switch (_direction) {
				case Direction::kUp:
					_posY += _speed;
					_direction = Direction::kDown;
					break;

				case Direction::kDown:
					_posY -= _speed;
					_direction = Direction::kUp;
					break;

				case Direction::kLeft:
					_posX += _speed;
					_direction = Direction::kRight;
					break;

				case Direction::kRight:
					_posX -= _speed;
					_direction = Direction::kLeft;
					break;
				}
				break;
			}
		}

		frame_end = SDL_GetTicks();
		frame_count++;
		frame_duration = frame_end - frame_start;

		// After every 30 seconds, change direction
		if (frame_end - title_timestamp >= 30000) {
			switch (_direction) {
			case Direction::kUp:
				
				_direction = Direction::kLeft;
				break;

			case Direction::kDown:
				
				_direction = Direction::kRight;
				break;

			case Direction::kLeft:
				
				_direction = Direction::kUp;
				break;

			case Direction::kRight:
				
				_direction = Direction::kDown;
				break;
			}
			frame_count = 0;
			title_timestamp = frame_end;
		}

		if (frame_duration < _target_frame_duration) {
			SDL_Delay(_target_frame_duration - frame_duration);
		}
		SDL_Rect obs{ _posX - _radius,_posY - _radius,_radius * 2,_radius * 2 };
		SDL_Rect snake_head{ _snk->head_x,_snk->head_y,1,1 };
		if(SDL_HasIntersection(&obs, &snake_head))
		{
			_snk->alive = false;
			break;
		}
	}
	lck.lock();
	std::cout << "Circle #" << _id << "::run: thread id = " << std::this_thread::get_id() << ", snake died. Exiting." << std::endl;
	lck.unlock();

}
