#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include "RenderWindow.hpp"
#include "Map.hpp"
#include "Common_Func.hpp"
#define modeBot 0
#define modePlayer 1
// Các hằng số định nghĩa kích thước và vị trí của các nút
const int BUTTON_WIDTH = 200;
const int BUTTON_HEIGHT = 100;
const int BUTTON_MARGIN = 150;
const int BUTTON_X = 500;
const int BUTTON_Y = 270;
struct Button
{
    SDL_Texture* texture;   // Hình ảnh của nút
    SDL_Rect rect;

};
Button createButton(const char* imagePath, int x, int y,RenderWindow window);

class MenuGame
{
public:
    MenuGame();
    ~MenuGame();

    void runMenu(SDL_Event& e,Button playButton,Button quitButton,Button help
                 ,bool& quit,bool& gameRunning,
                 RenderWindow window,SDL_Texture* menu_pic);

    void chooseLevel(SDL_Event& e,Button level1,Button level2,Button quitButton,
                     bool& quit,bool& gameRunning,
                     RenderWindow window,SDL_Texture* menu_pic,Map& gamemap);
    void chooseMode( SDL_Event& e,Button mode_com,Button mode_player,Button quitButton
                    ,bool& quit,bool& gameRunning,
                    RenderWindow window,SDL_Texture* menu_pic);
    void runGameWithBot(SDL_Event& e, Map& gamemap, bool& gameRunning,
                        Entity& player1,std::vector<ThreatObject*> threat_list
                        ,const int enemy_quantity,RenderWindow window
                        );
    void runGameWithPlayer(SDL_Event& e,Map& gamemap,bool& gameRunning,
                        Entity& player1,Entity& player2,RenderWindow window);
    void run_tutorial(SDL_Event& e,RenderWindow window,bool& quit,Button x_,bool& gameRunning,SDL_Texture* tur_pic);
    void renderResCom( SDL_Event& e,bool& quit,bool&gameRunning,Button& quitButton
                      ,Entity& player1 ,SDL_Texture* menu_pic ,RenderWindow window);
    void renderResPlayer(SDL_Event& e,bool& quit ,bool& gameRunning,
                         Button& quitButton,Entity& player1,Entity& player2,
                         SDL_Texture* menu_pic,RenderWindow window);
    enum MODE{ COM,PLAYER};
    int mode ;
    bool tutorial ;
};
