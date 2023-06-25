#include "ThreatObject.hpp"
#include "Common_Func.hpp"
#include "RenderWindow.hpp"
#include <cmath>
#include <SDL.h>
#include <vector>
vector<ThreatObject*> make_threat_list(Map& gamemap)
{
    vector<ThreatObject*> list_threat;
    for(int i = 0;i < enemy_quantity;i++)
    {
        ThreatObject* p_object = new ThreatObject[enemy_quantity];
        p_object->rect.x = 1000;
        p_object->rect.y = 280*i;
        while(p_object->checkToMap(gamemap))
        {
            p_object->rect.y += 200;
        }

        list_threat.push_back(p_object);

    }
    return list_threat;
}
ThreatObject::ThreatObject()
{
    rect.x = 0;
    rect.y = 0;
    rect.w = 64;
    rect.h =64;
    enemy_tex = Common_Func::loadTexture("res/Enemy_res/Hull_04_UP.png");
    status_val = DOWN_;
    int lives = 2;
    is_alive = true;
    last_bullet_time = SDL_GetTicks();
}
ThreatObject::~ThreatObject()
{

}


void ThreatObject::moveRandomly(Map& gamemap,Entity& player,ThreatObject* p_threat,int index_bot,vector<ThreatObject*> list_)
{


    srand((int)time(0));
    lastPosX=rect.x;
    lastPosY=rect.y;
    switch( status_val)
    {
    case DOWN_:
        SDL_DestroyTexture(enemy_tex);
        enemy_tex = Common_Func::loadTexture("res/Enemy_res/Hull_04_DOWN.png");
        rect.y += speed;
        if( checkToMap(gamemap) || touch_player(player,p_threat) )
        {
            rect.x=lastPosX;
            rect.y=lastPosY;
            last_status = DOWN_;
        ////
            status_val = rand() % 4;
        }
        break;
    case LEFT_:
        SDL_DestroyTexture(enemy_tex);
        enemy_tex = Common_Func::loadTexture("res/Enemy_res/Hull_04_LEFT.png");
        rect.x -= speed;
        if( checkToMap(gamemap) || touch_player(player,p_threat))
        {
            rect.x=lastPosX;
            rect.y=lastPosY;
        ////
            last_status = LEFT_;
            status_val = rand() % 4;
        }
        break;
    case UP_:
        SDL_DestroyTexture(enemy_tex);
        enemy_tex = Common_Func::loadTexture("res/Enemy_res/Hull_04_UP.png");
        rect.y -= speed;
        if( checkToMap(gamemap) || touch_player(player,p_threat))
        {
            rect.x=lastPosX;
            rect.y=lastPosY;
        ////
            last_status = UP_;
            status_val = rand() % 4;
        }
        break;
    case RIGHT_:
        SDL_DestroyTexture(enemy_tex);
        enemy_tex = Common_Func::loadTexture("res/Enemy_res/Hull_04_RIGHT.png");
        rect.x += speed;
        if( checkToMap(gamemap) || touch_player(player,p_threat))
        {
            rect.x=lastPosX;
            rect.y=lastPosY;
        ////
            last_status = RIGHT_;
            status_val = rand() % 4;
        }
        break;
    }


    if( touch_player(player,p_threat))
    {
        rect.x=lastPosX;
        rect.y=lastPosY;
        ////
        player.posX = player.lastPosX;
        player.posY = player.lastPosY;
    }



}
void ThreatObject::make_bullet(ThreatObject* p_threat)
{
    // Set the time interval between bullets
        const Uint32 BULLET_INTERVAL = 3000; // 3000 milliseconds = 3 seconds

        // Get the current time
        Uint32 current_time = SDL_GetTicks();

        // Check if enough time has passed since the last bullet
        if (current_time - last_bullet_time >= BULLET_INTERVAL) {
            // Create a new instance of the bullet object
            BulletObject* new_bullet = new BulletObject();

            // Set the bullet's target to the enemy
            if(new_bullet != NULL)
            {
                new_bullet->setPosBullet_enemy(p_threat);
                new_bullet->is_move= true;
            }


            // Add the bullet to the game world

            p_threat->bullet_list.push_back(new_bullet);

            // Record the time at which the bullet was created
            last_bullet_time = current_time;
        }
}
bool ThreatObject::meet_player(BulletObject* p_bullet,Entity& player)
{
    if( player.posX < p_bullet->rect.x + p_bullet->rect.w - 15
               //left
                &&
            player.posX + player.PLAYER_WIDTH > p_bullet->rect.x - 10
            //right
            &&
            player.posY < p_bullet->rect.y + p_bullet->rect.h - 15
            //up
            &&
            //down
            player.posY + player.PLAYER_HEIGHT > p_bullet->rect.y - 15
            )
            {

                    return true;

            }
    return false;
}
void ThreatObject::RandomShot(Map& gamemap,Entity& player,ThreatObject* p_threat)
{
     for(int i=0;i< (int)p_threat->bullet_list.size();i++)
    {
        BulletObject* p_bullet = p_threat->bullet_list.at(i);

        if(p_bullet->is_move && p_bullet != nullptr)
            {
                p_bullet->handleMove(gamemap,p_threat);
                //if the bullet has collide to the map,delete it
                if(p_bullet->checkCollision(gamemap))
                    {
                        p_bullet->is_move=false;
                        p_bullet->rect.w = 0;
                        p_bullet->rect.w = 0;
                        p_bullet->texture = NULL;
                        SDL_DestroyTexture(p_bullet->texture);

                    }
                //if the bullet collided with the player,player die

                if(player.is_alive)
                    {
                        if(meet_player(p_bullet,player))
                        {
                            p_bullet->is_move = false;
                            player.lives --;
                            if(player.lives == 0)
                            {
                                SDL_DestroyTexture(player.tex);
                                player.is_alive = false;


                            }
                            player.posX = 0;
                            player.posY = 0;
                            p_bullet->texture = NULL;
                            SDL_DestroyTexture(p_bullet->texture);


                        }
                    }

                    if(p_bullet->is_move)
                    {
                        p_bullet->render();
                    }

                }

                else
               {
                   SDL_DestroyTexture(p_bullet->texture);
                   p_threat->bullet_list.erase(p_threat->bullet_list.begin() + i);
                   p_bullet = NULL;

                   delete p_bullet;

                }

    }

}



bool ThreatObject::checkToMap(Map& gamemap)
{
    if(                     rect.x < 0 || rect.y <0 ||
       rect.x + ENEMY_WIDTH > RenderWindow::SCREEN_WIDTH  || rect.y + ENEMY_HEIGHT > RenderWindow::SCREEN_HEIGHT )
       return true;
    // Tính toán vị trí của nhân vật trên TileMap
    int leftTile = (rect.x + 10) / TILE_SIZE;
    int rightTile = (rect.x + ENEMY_WIDTH - 20) / TILE_SIZE;
    int topTile =   (rect.y + 10)/ TILE_SIZE;
    int bottomTile =(rect.y+ ENEMY_HEIGHT ) / TILE_SIZE;
     // Kiểm tra xem nhân vật có đang va chạm với một ô vuông trên TileMap không
    for (int i = topTile ; i <= bottomTile; i++) {
        for (int j = leftTile ; j <= rightTile; j++) {
            if (gamemap.posTileSet[i][j] != BLANK_TILE && gamemap.posTileSet[i][j] != 0) {
                return true; // Nếu có va chạm thì trả về true
            }
        }
    }
    return false;
}
bool ThreatObject::touch_player(Entity& player,ThreatObject* p_threat)
{
    if (player.posX + player.PLAYER_WIDTH > p_threat->rect.x - 20&&
        //threat is on the left of player
        player.posX < p_threat->rect.x + p_threat->rect.w - 20&&
        //threat is on the right of player
        player.posY + player.PLAYER_HEIGHT > p_threat->rect.y - 25&&
        //threat is under the player
        player.posY < p_threat->rect.y + p_threat->rect.h - 20 ) {
        //threat is on the player
        return true;
    }
    return false;
}

void ThreatObject::render()
{
    SDL_QueryTexture(enemy_tex,NULL,NULL,&rect.w,&rect.h);
    rect.w = 64;
    rect.h = 64;
    SDL_RenderCopy(RenderWindow::renderer,enemy_tex,NULL,&rect);

}
void ThreatObject::clean(vector<ThreatObject*> threat_list)
{
    for(int i = 0 ;i < (int)threat_list.size();i++)
    {
        SDL_DestroyTexture(threat_list[i]->enemy_tex);
        delete threat_list[i];
    }

}
