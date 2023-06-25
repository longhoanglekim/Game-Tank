#include "Map.hpp"
#include "Common_Func.hpp"
#include "RenderWindow.hpp"
#include <bits/stdc++.h>
using namespace std;
void Map::loadMap(const char* file_csv)
{
    std::ifstream file(file_csv);
	for (int i = 0; i < map_y; i++) {
		std::string s;
		file >> s;
		std::stringstream ss(s);
		std::string c;
		int j = 0;
		while (getline(ss, c, ',')) {
			int x = stoi(c);
			posTileSet[i][j] = x;
			j++;
		}
	}



}
void Map::loadTileSet(const char* file_tileset,const char* blank)
{
    SDL_Surface* tilesetSurface = IMG_Load(file_tileset);
    tilesetTexture = SDL_CreateTextureFromSurface(RenderWindow::renderer, tilesetSurface);
    SDL_Surface* blankSurface = IMG_Load(blank);
    blankTexture = SDL_CreateTextureFromSurface(RenderWindow::renderer,blankSurface);

    for (int i = 0; i < map_y; i++) {
        for (int j = 0; j < map_x; j++) {
            tileRect = { j * 32, i * 32, 32, 32 };
            tileset.push_back(tileRect);
        }
    }
    SDL_FreeSurface(tilesetSurface);
    SDL_FreeSurface(blankSurface);
    delete tilesetSurface;
    delete blankSurface;



}
void Map::drawMap()
{
    destRect.x=0;
    destRect.y=0;
    destRect.w=32;
    destRect.h=32;
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 40; j++) {
            tileRect = tileset[posTileSet[i][j]];
            SDL_RenderCopy(RenderWindow::renderer, tilesetTexture, &tileRect, &destRect);
            SDL_RenderCopy(RenderWindow::renderer, blankTexture ,&tileRect,&destRect);
            //SDL_RenderCopy(RenderWindow::renderer,coinTexture,&tileRect,&destRect);
            destRect.x += 32;
        }
    destRect.y += 32;
    destRect.x = 0;
    }
}


