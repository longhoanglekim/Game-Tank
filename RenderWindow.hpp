#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include "Entity.hpp"

using namespace std;
const int FPS = 60;
const int frameDelay= 1000/ FPS;

class Entity;
class RenderWindow
{
public:

    RenderWindow(const char* p_title,int p_w,int p_h);
    SDL_Texture* loadTexture(const char* file_path);
    void clear();
    void render(SDL_Texture* tex);
    const static  int SCREEN_WIDTH=1280;
    const static int SCREEN_HEIGHT=640 ;

    void draw(SDL_Texture* tex,SDL_Rect src,SDL_Rect dest);
    void display();
    void cleanUp();
    SDL_Window* window;
    static SDL_Renderer* renderer;

private:

};

