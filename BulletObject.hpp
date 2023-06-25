#ifndef BULLET_OBJECT_
#define BULLET_OBJECT_

#include "Entity.hpp"
#include "RenderWindow.hpp"
#include <vector>
#include "ThreatObject.hpp"

#define BULLET_TYPE_0 0

class Map;
class Entity;
class ThreatObject;

class BulletObject
{
public:
    BulletObject();
    ~BulletObject();
    const int speed = 6;
    const int BULLET_SIZE = 32;

    bool checkCollision(Map& gamemap);


    void setPosBullet(Entity& player);
    void setPosBullet_enemy(ThreatObject* enemy);
    void handleMove(Map& gamemap,Entity & player);
    void handleMove(Map& gamemap,ThreatObject* enemy);
    void handleInputAction(SDL_Event& event,Entity & player);

    void set_bullet_list(std::vector<BulletObject*> bullet_list)
    {
        p_bullet_list= bullet_list;
    }
    std::vector<BulletObject*> get_bullet_list ()const {return p_bullet_list;}
    //bool kill_enenmy(Entity& player, )

    int posX,posY;
    int xvel,yvel;
    bool is_move = false;
    void render();
    SDL_Texture* texture ;
    int instant_status;
    int lastPosX,lastPosY;
    SDL_Rect rect;

    int bullet_type;

private:
    std::vector<BulletObject*> p_bullet_list;
};
#endif // BULLET_OBJECT_
