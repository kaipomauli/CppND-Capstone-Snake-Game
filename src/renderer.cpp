#include "renderer.h"
#include <iostream>
#include <string>

Renderer::Renderer(const std::size_t screen_width,
                   const std::size_t screen_height,
                   const std::size_t grid_width, const std::size_t grid_height)
    : screen_width(screen_width),
      screen_height(screen_height),
      grid_width(grid_width),
      grid_height(grid_height) {
  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cerr << "SDL could not initialize.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create Window
  sdl_window = SDL_CreateWindow("Snake Game", SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED, screen_width,
                                screen_height, SDL_WINDOW_SHOWN);

  if (nullptr == sdl_window) {
    std::cerr << "Window could not be created.\n";
    std::cerr << " SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create renderer
  sdl_renderer = SDL_CreateRenderer(sdl_window, -1, SDL_RENDERER_ACCELERATED);
  if (nullptr == sdl_renderer) {
    std::cerr << "Renderer could not be created.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }
}

Renderer::~Renderer() {
  SDL_DestroyWindow(sdl_window);
  SDL_Quit();
}

//Circle drawing function from https://gist.github.com/derofim/912cfc9161269336f722
void fill_circle(SDL_Renderer* surface, int cx, int cy, int radius, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
    // Note that there is more to altering the bitrate of this 
    // method than just changing this value.  See how pixels are
    // altered at the following web page for tips:
    //   http://www.libsdl.org/intro.en/usingvideo.html
    static const int BPP = 4;

    //double ra = (double)radius;

    for (double dy = 1; dy <= radius; dy += 1.0)
    {
        // This loop is unrolled a bit, only iterating through half of the
        // height of the circle.  The result is used to draw a scan line and
        // its mirror image below it.

        // The following formula has been simplified from our original.  We
        // are using half of the width of the circle because we are provided
        // with a center and we need left/right coordinates.

        double dx = floor(sqrt((2.0 * radius * dy) - (dy * dy)));
        int x = cx - dx;
        SDL_SetRenderDrawColor(surface, r, g, b, a);
        SDL_RenderDrawLine(surface, cx - dx, cy + dy - radius, cx + dx, cy + dy - radius);
        SDL_RenderDrawLine(surface, cx - dx, cy - dy + radius, cx + dx, cy - dy + radius);

        // Grab a pointer to the left-most pixel for each half of the circle
        /*Uint8 *target_pixel_a = (Uint8 *)surface->pixels + ((int)(cy + r - dy)) * surface->pitch + x * BPP;
        Uint8 *target_pixel_b = (Uint8 *)surface->pixels + ((int)(cy - r + dy)) * surface->pitch + x * BPP;
        for (; x <= cx + dx; x++)
        {
            *(Uint32 *)target_pixel_a = pixel;
            *(Uint32 *)target_pixel_b = pixel;
            target_pixel_a += BPP;
            target_pixel_b += BPP;
        }*/
        /*
        // sleep for debug
        SDL_RenderPresent(gRenderer);
        std::this_thread::sleep_for(std::chrono::milliseconds{ 100 });
        */
    }
}

void Renderer::Render(Snake const snake, SDL_Point const &food,std::vector<std::shared_ptr<Square>> &sqrVec, std::vector<std::shared_ptr<Circle>>& ballVec) {
  SDL_Rect block;
  block.w = screen_width / grid_width;
  block.h = screen_height / grid_height;

  // Clear screen
  SDL_SetRenderDrawColor(sdl_renderer, 0x1E, 0x1E, 0x1E, 0xFF);
  SDL_RenderClear(sdl_renderer);

  // Render food
  SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xCC, 0x00, 0xFF);
  block.x = food.x * block.w;
  block.y = food.y * block.h;
  SDL_RenderFillRect(sdl_renderer, &block);

  // Render balls in blue

  for (auto circ : ballVec) {
      int ballRadius;
      
      double circPosX, circPosY;
      circ->getPosition(circPosX, circPosY);
      circ->getRadius(ballRadius);
      fill_circle(sdl_renderer, circPosX * (screen_width / grid_width), circPosY * (screen_height / grid_height), ballRadius * (screen_width / grid_width), 0x00, 0x00, 0xFF, 0xFF);
  };

  // Render squares in green

  for (auto squ : sqrVec) {
      int squareWidth;
      int squareHeight;
      double squarePosX, squarePosY;
      squ->getPosition(squarePosX, squarePosY);
      squ->getSize(squareWidth, squareHeight);
      block.w = squareWidth * (screen_width / grid_width);
      block.h = squareHeight * (screen_height / grid_height);
      block.x = squarePosX * (screen_width / grid_width);
      block.y = squarePosY * (screen_height / grid_height);
      SDL_SetRenderDrawColor(sdl_renderer, 0x00, 0xFF, 0x00, 0xFF);
      SDL_RenderFillRect(sdl_renderer, &block);
      };

  // Render snake's body
  block.w = screen_width / grid_width;
  block.h = screen_height / grid_height;
  SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
  for (SDL_Point const &point : snake.body) {
    block.x = point.x * block.w;
    block.y = point.y * block.h;
    SDL_RenderFillRect(sdl_renderer, &block);
  }

  
  
  
  // Render snake's head
  block.w = screen_width / grid_width;
  block.h = screen_height / grid_height;
  block.x = static_cast<int>(snake.head_x) * block.w;
  block.y = static_cast<int>(snake.head_y) * block.h;
  if (snake.alive) {
      SDL_SetRenderDrawColor(sdl_renderer, 0x00, 0x7A, 0xCC, 0xFF);
  }
  else {
      SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0x00, 0x00, 0xFF);
  }
  SDL_RenderFillRect(sdl_renderer, &block);
  // Update Screen
  SDL_RenderPresent(sdl_renderer);
}





void Renderer::UpdateWindowTitle(int score, int fps) {
  std::string title{"Snake Score: " + std::to_string(score) + " FPS: " + std::to_string(fps)};
  SDL_SetWindowTitle(sdl_window, title.c_str());
}
