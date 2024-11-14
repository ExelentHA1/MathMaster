#include "Window.hpp"

WindowRenderer::WindowRenderer()
{
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        std::cerr << "SDL Filed to initialize err: " << SDL_GetError() << std::endl; 
    }
}

WindowRenderer::~WindowRenderer()
{ }

void WindowRenderer::create(const char* title, int Width, int Height)
{
    window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, Width, Height, 0);
    if(window == nullptr){
        std::cerr << "Failed to Create window Err: " << SDL_GetError() << std::endl;
    }
    renderer = SDL_CreateRenderer(window, -1, 0);
    if(renderer == nullptr)
    {
        std::cerr << "Failed to create renderer Err: " << SDL_GetError() << std::endl;
    }
    SDL_SetRenderDrawColor(renderer, 255, 199, 0, 255); // default bg color
}

void WindowRenderer::loadImage(const char *path)
{
    // load a texture
    SDL_Surface *img = IMG_Load(path);
    if(img == nullptr)
        std::cerr << "IMG path error: " << IMG_GetError() << std::endl;
    texture = IMG_LoadTexture(renderer, path);
    SDL_FreeSurface(img); // clear Img buffer
    if(texture == nullptr)
        std::cerr << "CreateTextureFromSurface error: " << SDL_GetError() << std::endl;
}

void WindowRenderer::clear()
{
    SDL_RenderClear(renderer);
}

void WindowRenderer::present()
{
    SDL_RenderPresent(renderer);
}

void WindowRenderer::render(SDL_Texture *t,int posx, int posy, int offsetx, int offsety, int size)
{ 
    SDL_Rect dst;
	// src.x = 0;
	// src. y = 0;

	SDL_QueryTexture(t, NULL, NULL, &dst.w, &dst.h);

    // src.w = dst.w;
    // src.h = src.h;

	dst.x = posx + offsetx/size;
	dst.y = posy + offsety/size;
	dst.w = dst.w/size;
	dst.h = dst.h/size;
    // std::cout << dst.h << " " << dst.w << std::endl;
    // render
    SDL_RenderCopy(renderer, t, nullptr, &dst);
}

void WindowRenderer::clean()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}


