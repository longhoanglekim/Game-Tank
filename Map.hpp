
#pragma once
#include "RenderWindow.hpp"
#include "Entity.hpp"
#include <bits/stdc++.h>

#define BLANK_TILE 0
#define COIN_TILE 1
#define ONE_SHOT_TILE 118
#define TILE_SIZE 32
#define HARD_TILE 77
#define IMMORTAL_TILE 79
class Map
{
public:

    const static int map_y=20;
    const static int map_x=40;
    void loadMap(const char* file_csv);
    void loadTileSet(const char* file_tileset,const char* blank);
    void drawMap();
    void updateMap(int posX,int posY);
    int  posTileSet[map_y][map_x];
    SDL_Texture* tilesetTexture;
    SDL_Texture* blankTexture;
    SDL_Texture* coinTexture;
private:
    std::vector<SDL_Rect> tileset;
    SDL_Rect tileRect;
    SDL_Rect destRect;

};
