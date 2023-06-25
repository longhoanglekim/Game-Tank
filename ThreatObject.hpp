#pragma once
#include <bits/stdc++.h>
#include "RenderWindow.hpp"
#include "Map.hpp"
#include "Entity.hpp"
#include "Common_Func.hpp"
#include <SDL.h>
#include <SDL_image.h>
#include "BulletObject.hpp"
const int enemy_quantity = 3;
class Map;
class Entity;
class BulletObject;
using namespace std;

class ThreatObject
{
public:
    //const value
    const int ENEMY_WIDTH = 63;
    const int ENEMY_HEIGHT = 63;
    const int speed = 1;
    //constructor and destructor
    ThreatObject();
    ~ThreatObject();
    // function
    bool checkToMap(Map& gamemap);


    void moveRandomly(Map& gamemap,Entity& player,ThreatObject* p_threat,int index_bot,vector<ThreatObject*> list_);
    void render();
    //handle bullet
    std::vector<BulletObject*> get_bullet_list() {return bullet_list;};
    void set_bullet_list(std::vector<BulletObject*> new_bullet) { bullet_list = new_bullet;};
    void initBullet(BulletObject* p_bullet);
    void make_bullet(ThreatObject* p_threat);
    bool meet_player(BulletObject* p_bullet,Entity& player);
    bool touch_player(Entity& player,ThreatObject* p_threat);

    void RandomShot(Map& gamemap,Entity& player,ThreatObject* p_threat);
    void clean(vector<ThreatObject*> threat_list);
    // variables
    Uint32 last_bullet_time ;
    SDL_Rect rect;
    int lastPosX,lastPosY;
    int status_val;
    SDL_Texture* enemy_tex;



    enum Type_move
    {
        UP_ = 0,
        DOWN_ =1,
        LEFT_ = 2,
        RIGHT_ = 3
    };
    int lives;
    bool is_alive;
    int index_ ;
    int last_status ;
private:
    std::vector<BulletObject*> bullet_list;
};
vector<ThreatObject*> make_threat_list(Map& gamemap);
