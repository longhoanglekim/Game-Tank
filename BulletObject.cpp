#include "BulletObject.hpp"
#include "Common_Func.hpp"
#include "RenderWindow.hpp"


using namespace std;
BulletObject::BulletObject()
{
    posX = 0;
    posY = 0;
    xvel = 0;
    yvel = 0;
    bullet_type = BULLET_TYPE_0;
}
BulletObject::~BulletObject()
{
    texture = NULL;
    SDL_DestroyTexture(texture);
}
void BulletObject::setPosBullet(Entity & player)
{
    if(bullet_type == BULLET_TYPE_0)
        {
            instant_status = player.status;
            switch(player.status)
            {
            case UP:
                    rect.x= player.posX + player.PLAYER_WIDTH /2;
                    rect.y= player.posY ;
                    rect.w= BULLET_SIZE ;
                    rect.h= BULLET_SIZE ;
                    texture = Common_Func::loadTexture("res/bulletres/player_bullet/Heavy_Shell_UP.png");
                    break;
            case DOWN:
                    rect.x= player.posX + player.PLAYER_WIDTH/2;
                    rect.y= player.posY ;
                    rect.w= BULLET_SIZE ;
                    rect.h= BULLET_SIZE ;
                    texture = Common_Func::loadTexture("res/bulletres/player_bullet/Heavy_Shell_DOWN.png");
                    break;
            case LEFT:
                    rect.x= player.posX;
                    rect.y= player.posY + player.PLAYER_HEIGHT/2;
                    rect.w= BULLET_SIZE;
                    rect.h= BULLET_SIZE;
                    texture = Common_Func::loadTexture("res/bulletres/player_bullet/Heavy_Shell_LEFT.png");
                    break;


            case RIGHT:
                    rect.x= player.posX + player.PLAYER_HEIGHT/2;
                    rect.y= player.posY + player.PLAYER_HEIGHT/2 ;
                    rect.w= BULLET_SIZE;
                    rect.h= BULLET_SIZE;
                    texture = Common_Func::loadTexture("res/bulletres/player_bullet/Heavy_Shell_RIGHT.png");
                    break;
            }
        }
}
void BulletObject::setPosBullet_enemy(ThreatObject* enemy)
{
    instant_status = enemy->status_val;
            switch(instant_status)
            {
            case UP:
                    rect.x= enemy->rect.x+ 15;
                    rect.y= enemy->rect.y  - TILE_SIZE;
                    rect.w= BULLET_SIZE ;
                    rect.h= BULLET_SIZE ;
                    texture = Common_Func::loadTexture("res/bulletres/player_bullet/Heavy_Shell_UP.png");
                    break;
            case DOWN:
                    rect.x= enemy->rect.x+ 15;
                    rect.y= enemy->rect.y + TILE_SIZE;
                    rect.w= BULLET_SIZE ;
                    rect.h= BULLET_SIZE ;
                    texture = Common_Func::loadTexture("res/bulletres/player_bullet/Heavy_Shell_DOWN.png");
                    break;
            case LEFT:
                    rect.x= enemy->rect.x - TILE_SIZE;
                    rect.y= enemy->rect.y + 15;
                    rect.w= BULLET_SIZE;
                    rect.h= BULLET_SIZE;
                    texture = Common_Func::loadTexture("res/bulletres/player_bullet/Heavy_Shell_LEFT.png");
                    break;


            case RIGHT:
                    rect.x= enemy->rect.x + TILE_SIZE;
                    rect.y= enemy->rect.y + 15 ;
                    rect.w= BULLET_SIZE;
                    rect.h= BULLET_SIZE;
                    texture = Common_Func::loadTexture("res/bulletres/player_bullet/Heavy_Shell_RIGHT.png");
                    break;
            }

}
void BulletObject::handleMove(Map& gamemap,Entity& player)
{
    lastPosX=rect.x;
    lastPosY=rect.y;

    switch(instant_status)
    {
    case UP:
        rect.y -= speed;
        break;
    case DOWN:
        rect.y += speed;
        break;
    case LEFT:
        rect.x -=speed;
        break;
    case RIGHT:
        rect.x +=speed;
        break;
    }

    if(rect.x > RenderWindow::SCREEN_WIDTH|| rect.y > RenderWindow::SCREEN_HEIGHT|| rect.x < 0|| rect.y < 0)
    // if the bullet goes off-screen
    {
        is_move = false;

    }



}
void BulletObject::handleMove(Map& gamemap,ThreatObject* enemy)
{
    lastPosX=enemy->rect.x;
    lastPosY=enemy->rect.y;

    switch(instant_status)
    {
    case UP:
        rect.y -= speed;
        break;
    case DOWN:
        rect.y += speed;
        break;
    case LEFT:
        rect.x -=speed;
        break;
    case RIGHT:
        rect.x +=speed;
        break;
    }

    if(rect.x > RenderWindow::SCREEN_WIDTH|| rect.y > RenderWindow::SCREEN_HEIGHT || rect.x < 0|| rect.y < 0)
    // if the bullet goes off-screen
    {
        rect.w = 0;
        rect.y = 0;
        is_move = false;
        texture = NULL;
        SDL_DestroyTexture(texture);
    }



}
void BulletObject::render()
{
    SDL_QueryTexture(texture,NULL,NULL,&rect.w,&rect.h);
    rect.w=BULLET_SIZE ;
    rect.h=BULLET_SIZE ;
    SDL_RenderCopy(RenderWindow::renderer,texture,NULL,&rect);

}

bool BulletObject::checkCollision(Map& gamemap)
{
    //split the bullet into smaller unit
    int col = (rect.x + rect.w / 2) / TILE_SIZE;
    int row = (rect.y + rect.h / 2) / TILE_SIZE;


    if (row >= 0 && row < gamemap.map_y&& col >= 0 && col < gamemap.map_x)
        {
            if (gamemap.posTileSet[row][col] == HARD_TILE)
            {
                gamemap.posTileSet[row][col] = ONE_SHOT_TILE;
                 return true;
            }
            if (gamemap.posTileSet[row][col] == ONE_SHOT_TILE )
            {
                gamemap.posTileSet[row][col] = 0;
                 return true;
            }
            if( gamemap.posTileSet[row][col] == IMMORTAL_TILE ) return true;
        }
    return false;
}



