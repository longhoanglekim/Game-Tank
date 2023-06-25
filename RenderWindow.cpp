#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include "RenderWindow.hpp"
#include "MenuGame.hpp"
const int step=10;
SDL_Renderer* RenderWindow::renderer = nullptr;
RenderWindow::RenderWindow(const char* p_title,int p_w,int p_h)
:window(NULL)
{
    window=SDL_CreateWindow(p_title,SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,p_w,p_h,SDL_WINDOW_SHOWN);
    if(window == NULL)
    {
        cout<< "Window failed to init.Error: " << SDL_GetError() <<endl;
    }
    renderer= SDL_CreateRenderer(window, -1 ,SDL_RENDERER_ACCELERATED );
}
SDL_Texture* RenderWindow::loadTexture(const char* file_path)
{
    SDL_Texture* texture =NULL;
    texture = IMG_LoadTexture(renderer,file_path);
    if(renderer == NULL)
    {
        cout<< "Failed to load texture.Error :"<<SDL_GetError()<<endl;
    }
    return texture;
}
void RenderWindow::render(SDL_Texture* tex)
{
    SDL_RenderCopy(renderer,tex,NULL,NULL);
}

void RenderWindow::clear()
{
    SDL_RenderClear(renderer);

}
void RenderWindow ::cleanUp()
{
    SDL_DestroyRenderer(RenderWindow::renderer);
    SDL_DestroyWindow(window);
}

void RenderWindow::display()
{
    SDL_RenderPresent(renderer);
}

