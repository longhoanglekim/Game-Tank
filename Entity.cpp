#include "Entity.hpp"
#include "RenderWindow.hpp"
#include "Common_Func.hpp"
#include "ThreatObject.hpp"
using namespace std;
Entity::Entity(int posX_ , int posY_ ,const char* file,int index_p)
{
    posX=posX_;
    posY=posY_;

    velX=0;
    velY=0;
    is_alive = true;
    lives = 3;
    tex = Common_Func::loadTexture(file);
    status = UP;
    last_bullet_time = SDL_GetTicks();
    index_player = index_p;
    gain_coin = false;
    MovingLeftRight = false;
    MovingUpDown = false;
}
void Entity::handleEvent(SDL_Event& event)
{
    //ìf a key was pressed
    if(this->index_player == 1)
    {
        if(event.type == SDL_KEYDOWN&& event.key.repeat == 0)
        {
            //Adjust the velocity
            switch(event.key.keysym.sym)
            {
            case SDLK_w: velY-=step;
                        SDL_DestroyTexture(tex);
                        tex=Common_Func::loadTexture("res/tankres/Hull_01_W.png");
                        status = UP;
                        MovingUpDown = true;
                        MovingLeftRight = false;
                        break;
            case SDLK_s:velY+=step;
                        SDL_DestroyTexture(tex);
                        tex=Common_Func::loadTexture("res/tankres/Hull_01_S.png");
                        status = DOWN;
                        MovingUpDown = true;
                        MovingLeftRight = false;
                        break;
            case SDLK_a: velX-=step;
                        SDL_DestroyTexture(tex);
                        tex=Common_Func::loadTexture("res/tankres/Hull_01_A.png");
                        status = LEFT;
                        MovingLeftRight = true;
                        MovingUpDown = false;
                        break;
            case SDLK_d: velX+=step;
                        SDL_DestroyTexture(tex);
                        tex=Common_Func::loadTexture("res/tankres/Hull_01_D.png");
                        status = RIGHT;
                        MovingLeftRight = true;
                        MovingUpDown = false;
                        break;


            }

        }
        if( event.type == SDL_KEYUP&& event.key.repeat == 0 )
        {
            //Adjust the velocity
            switch(event.key.keysym.sym)
            {
            case SDLK_w: velY+=step;
                        MovingUpDown = false;
                        break;
            case SDLK_s: velY-=step;
                        MovingUpDown = false;
                        break;
            case SDLK_a: velX+=step;
                        MovingLeftRight = false;
                        break;
            case SDLK_d: velX-=step;
                        MovingLeftRight = false;
                        break;
            }
        }
    }
    else
    {
        if(event.type == SDL_KEYDOWN&& event.key.repeat == 0)
        {
            //Adjust the velocity
            switch(event.key.keysym.sym)
            {
            case SDLK_UP: velY-=step;
                        SDL_DestroyTexture(tex);
                        tex=Common_Func::loadTexture("res/tankres/new_player/Hull_01_W.png");
                        status = UP;
                        MovingUpDown = true;
                        MovingLeftRight = false;
                        break;
            case SDLK_DOWN:velY+=step;
                        SDL_DestroyTexture(tex);
                        tex=Common_Func::loadTexture("res/tankres/new_player/Hull_01_S.png");
                        status = DOWN;
                        MovingUpDown = true;
                        MovingLeftRight = false;
                        break;
            case SDLK_LEFT: velX-=step;
                        SDL_DestroyTexture(tex);
                        tex=Common_Func::loadTexture("res/tankres/new_player/Hull_01_A.png");
                        status = LEFT;
                        MovingLeftRight = true;
                        MovingUpDown = false;
                        break;
            case SDLK_RIGHT: velX+=step;
                        SDL_DestroyTexture(tex);
                        tex=Common_Func::loadTexture("res/tankres/new_player/Hull_01_D.png");
                        status = RIGHT;
                        MovingLeftRight = true;
                        MovingUpDown = false;
                        break;


            }

        }
        if( event.type == SDL_KEYUP&& event.key.repeat == 0 )
        {
            //Adjust the velocity
            switch(event.key.keysym.sym)
            {
            case SDLK_UP: velY+=step;
                        MovingUpDown = false;
                        break;
            case SDLK_DOWN: velY-=step;
                        MovingUpDown = false;
                        break;
            case SDLK_LEFT: velX+=step;
                        MovingLeftRight = false;
                        break;
            case SDLK_RIGHT: velX-=step;
                        MovingLeftRight = false;
                        break;
            }
        }
    }

}
void Entity::move(Map& gamemap)
{
    lastPosX=posX;
    lastPosY=posY;
    //move left or right
    if(!MovingUpDown)
    {
        MovingLeftRight = true;
        posX+=velX;
    }

    //If the tank went too far to the right or left
    if( ( posX  < 0  ) || ( posX + PLAYER_WIDTH  + 30  > RenderWindow::SCREEN_WIDTH  ) )
    {
        //Move back
        posX -= velX;
    }
    //move up or down
    if(!MovingLeftRight)
    {
         MovingUpDown = true;
         posY+=velY;
    }

    //If the tank went too far to the up or down
    if( ( posY < 0  )  || (posY + PLAYER_HEIGHT  + 30 > RenderWindow::SCREEN_HEIGHT ) )
    {
        //Move back
        posY -= velY;
    }

    if(checkCollision(gamemap) )
       {
            cout<< "Collided!"<<endl;
            posX=lastPosX;
            posY=lastPosY;
        }

}


bool Entity::checkCollision(Map& gamemap)
{
    // Calculate the position of the character on the TileMap
    int leftTile = (posX  ) / TILE_SIZE;
    int rightTile = (posX + PLAYER_WIDTH + 20) / TILE_SIZE;
    int topTile =   (posY )/ TILE_SIZE;
    int bottomTile =(posY + PLAYER_HEIGHT + 20) / TILE_SIZE;
     // check if charactes has collide with a tileset on TileMap
    for (int i = topTile ; i <= bottomTile; i++) {
        for (int j = leftTile  ; j <= rightTile; j++) {

            if (gamemap.posTileSet[i][j] != BLANK_TILE && gamemap.posTileSet[i][j] != COIN_TILE) {
                return true; //
            }
        }
    }
    return false;
}
void Entity::render(SDL_Texture* tex)
{
    SDL_Rect rect;
    SDL_QueryTexture(tex,NULL,NULL,&rect.w,&rect.h);
    rect.x=posX;
    rect.y=posY;
    rect.w=PLAYER_WIDTH*2;

    rect.h=PLAYER_HEIGHT*2;

    SDL_RenderCopy(RenderWindow::renderer,tex,NULL,&rect);
    tex = NULL;
    SDL_DestroyTexture(tex);


}
void Entity::handleInputAction(SDL_Event& event, Entity& player)
{
    // Set the time interval between bullets
    const Uint32 BULLET_INTERVAL = 1500; // 3000 milliseconds = 3 seconds

    // Get the current time
    Uint32 current_time = SDL_GetTicks();

    // Check if enough time has passed since the last bullet was fired
    if (current_time - last_bullet_time >= BULLET_INTERVAL)
    {
        if (event.type == SDL_KEYDOWN && event.key.repeat == 0)
        {
            // if pressed Enter button, create a bullet
            if( player.index_player == 1)
            {
                if (event.key.keysym.sym == SDLK_j)
                {
                    BulletObject* p_bullet = new BulletObject();
                    p_bullet->setPosBullet(player);
                    p_bullet->is_move = true;
                    p_bullet_list.push_back(p_bullet);

                    // Record the time at which the bullet was created
                    last_bullet_time = current_time;

                }
            }
            else
            {
                if (event.key.keysym.sym == SDLK_RETURN)
                {
                    BulletObject* p_bullet = new BulletObject();
                    p_bullet->setPosBullet(player);
                    p_bullet->is_move = true;
                    p_bullet_list.push_back(p_bullet);

                    // Record the time at which the bullet was created
                    last_bullet_time = current_time;
                }
            }

        }
    }
}

void Entity::handleBullet(Map& gamemap,Entity& player,vector<ThreatObject*> threat_list)
{
    for(int i=0;i< p_bullet_list.size();i++)
    {
        BulletObject* p_bullet = p_bullet_list.at(i);
        if( p_bullet == nullptr)
            {
                ++i;
                continue;
            }

        if(p_bullet->is_move && p_bullet != nullptr)
            {

                if(p_bullet->rect.y  > RenderWindow::SCREEN_HEIGHT)
                {
                    p_bullet->is_move=false;
                    p_bullet->rect.w = 0;
                    p_bullet->rect.w = 0;
                    p_bullet->texture = NULL;
                }

                p_bullet->handleMove(gamemap,player);
                //if the bullet has collide to the map,delete it
                if(p_bullet->checkCollision(gamemap))
                    {
                        p_bullet->is_move=false;
                        p_bullet->rect.w = 0;
                        p_bullet->rect.w = 0;
                        p_bullet->texture = NULL;

                    }
                //if the bullet collided with the enemy,kill it
                for(int i = 0; i< (int)threat_list.size();i++)
                {
                    if(threat_list[i]->is_alive)
                    {
                        if(meet_enemy(p_bullet,threat_list[i]))
                        {
                            p_bullet->is_move = false;


                            SDL_DestroyTexture( threat_list[i]->enemy_tex);

                        }
                    }
                    if(p_bullet->is_move)
                    {
                        p_bullet->render();
                    }
                }

            }

           else
           {
               SDL_DestroyTexture(p_bullet->texture);
               p_bullet_list.erase(p_bullet_list.begin() + i);
               p_bullet = NULL;

               delete p_bullet;
           }

    }


}
void Entity::handleBullet(Map& gamemap,Entity& player ,Entity& component)
{

    for(int i=0;i< (int)p_bullet_list.size();i++)
    {
        BulletObject* p_bullet = p_bullet_list.at(i);
        if( p_bullet == nullptr)
            {
                ++i;
                continue;
            }

        if(p_bullet->is_move && p_bullet != nullptr)
            {

                if(p_bullet->rect.y  > RenderWindow::SCREEN_HEIGHT)
                {
                    p_bullet->is_move=false;
                    p_bullet->rect.w = 0;
                    p_bullet->rect.w = 0;
                    p_bullet->texture = NULL;
                }

                p_bullet->handleMove(gamemap,player);
                //if the bullet has collide to the map,delete it
                if(p_bullet->checkCollision(gamemap))
                    {
                        p_bullet->is_move=false;
                        p_bullet->rect.w = 0;
                        p_bullet->rect.w = 0;
                        p_bullet->texture = NULL;

                    }
                //if the bullet has collided to the enemy,kill
                if( meet_another(p_bullet,component))
                {
                    p_bullet->is_move=false;
                    p_bullet->rect.w = 0;
                    p_bullet->rect.w = 0;
                    p_bullet->texture = NULL;
                    component.lives--;
                    if( component.lives == 0)
                    {
                        component.is_alive = false;
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
               p_bullet_list.erase(p_bullet_list.begin() + i);
               p_bullet = NULL;

               delete p_bullet;
           }

    }

}
bool Entity::meet_enemy(BulletObject* p_bullet,ThreatObject* p_threat)
{
            if( p_threat->rect.x + 30< p_bullet->rect.x + p_bullet->rect.w
               //left
                &&
            p_threat->rect.x + p_threat->rect.w - 30> p_bullet->rect.x
            //right
            &&
            p_threat->rect.y + 15< p_bullet->rect.y + p_bullet->rect.h
            //up
            &&
            //down
            p_threat->rect.y + p_threat->rect.h - 20> p_bullet->rect.y
            )
            {
                    p_threat->is_alive = false;
                    return true;

            }



    return false;
}
bool Entity::meet_another(BulletObject* p_bullet,Entity& component)
{
    if( component.posX < p_bullet->rect.x + p_bullet->rect.w - 15
               //left
                &&
            component.posX + component.PLAYER_WIDTH > p_bullet->rect.x - 10
            //right
            &&
            component.posY < p_bullet->rect.y + p_bullet->rect.h - 15
            //up
            &&
            //down
            component.posY + component.PLAYER_HEIGHT > p_bullet->rect.y - 15
        )
            {

                    return true;

            }
    return false;

}
void Entity::clean()
{
    SDL_DestroyTexture(tex);
}
