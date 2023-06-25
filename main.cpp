#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

#include "RenderWindow.hpp"
#include "Entity.hpp"
#include "Map.hpp"
#include "BulletObject.hpp"
#include "ThreatObject.hpp"
#include "MenuGame.hpp"
#include "Common_Func.hpp"
using namespace std;

Uint32 frameStart;
int frameTime;

int main(int argc,char* argv[])
{
    //init window

    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Event e;

    RenderWindow window("game Tank",RenderWindow::SCREEN_WIDTH,RenderWindow::SCREEN_HEIGHT);
    //declare player
    Entity player1(0,320,"res/tankres/Hull_01_W.png",1 );
    Entity player2(1216,320,"res/tankres/new_player/Hull_01_W.png",2);
    Map gamemap;
    gamemap.loadTileSet("temp.png","res/coin_blank.png");
    bool gameRunning= false;

    bool quit = false;
    SDL_Texture* menu_pic = window.loadTexture("res/Menu/menu_pic.png");
    MenuGame menu;
    // declare buttons
    Button playButton = createButton("res/Menu/play_button.png",BUTTON_X,BUTTON_Y,window);
    Button quitButton = createButton("res/Menu/quit_button.png",BUTTON_X,BUTTON_Y + BUTTON_MARGIN,window);
    Button level1 = createButton("res/Menu/map1_button.png",BUTTON_X,BUTTON_Y,window);
    Button level2 = createButton("res/Menu/map2_button.png",BUTTON_X + BUTTON_MARGIN* 2,BUTTON_Y,window);
    Button mode_com = createButton("res/Menu/MODE COM.png",BUTTON_X,BUTTON_Y,window);
    Button mode_player = createButton("res/Menu/Mode Player.png",BUTTON_X + BUTTON_MARGIN* 2,BUTTON_Y,window);
    Button help = createButton("res/Menu/help_button.png",BUTTON_X + BUTTON_MARGIN*2,BUTTON_Y,window);
    Button x_ = createButton("res/Menu/x_button.png",1000,50,window);
    SDL_Texture* tur_pic = Common_Func::loadTexture("res/Menu/Tutorial.png");
    //running game
    while(!quit)
    {
        if(!menu.tutorial)
        {
            menu.runMenu(e,playButton,quitButton,help,quit,gameRunning,window,menu_pic);
        }
        else
        {
            menu.run_tutorial(e,window,quit,x_,gameRunning,tur_pic);
        }
    }
        quit = false;
        while(!quit&& gameRunning)
        {
            menu.chooseMode(e,mode_com,mode_player,quitButton,quit,gameRunning,window,menu_pic);
            if(menu.mode == modePlayer) gamemap.loadMap("res/map_level/map_vs_p.csv");
        }
        quit = false;
        if( menu.mode == modeBot)
        {
            while(!quit && gameRunning)
            {
                menu.chooseLevel(e,level1,level2,quitButton,quit,gameRunning,window,menu_pic,gamemap);
            }
        }
        vector<ThreatObject*> threat_list = make_threat_list(gamemap);
        if( menu.mode == modeBot) // play with bot
        {
            while(gameRunning )
            {
                if(player1.is_alive && !player1.gain_coin)
                {
                    SDL_RenderClear(window.renderer);

                    menu.runGameWithBot(e,gamemap,gameRunning,player1,threat_list,enemy_quantity,window);
                    if(!player1.is_alive)
                    {
                        continue;
                    }
                    Common_Func::handleFPS(FPS,frameDelay,frameStart,frameTime);
                    window.display();
                    window.clear();
                }
                else
                {
                    menu.renderResCom(e,quit,gameRunning,quitButton,player1,menu_pic,window);

                }
            }
        }
        if( menu.mode == modePlayer)
        {

            quitButton = createButton("res/Menu/quit_button.png",BUTTON_X + 120,BUTTON_Y + BUTTON_MARGIN,window);
            while(gameRunning)
           {
                if(player1.is_alive && player2.is_alive)
                {
                     SDL_RenderClear(window.renderer);

                    menu.runGameWithPlayer(e,gamemap,gameRunning,player1,player2,window);
                    Common_Func::handleFPS(FPS,frameDelay,frameDelay,frameTime);
                    window.display();
                    window.clear();
                }
                else
                {
                    menu.renderResPlayer(e,quit,gameRunning,quitButton,player1,player2,menu_pic,window);
                }
           }
        }
    //clear resource
    window.cleanUp();
    SDL_DestroyTexture(menu_pic);
    SDL_DestroyTexture(playButton.texture);
    SDL_DestroyTexture(quitButton.texture);
    SDL_DestroyTexture(level1.texture);
    SDL_DestroyTexture(level2.texture);
    SDL_DestroyTexture(mode_com.texture);
    SDL_DestroyTexture(mode_player.texture);
    SDL_DestroyTexture(help.texture);
    SDL_DestroyTexture(x_.texture);
    player1.clean();
    threat_list[0]->clean(threat_list);
    return 0;
}






