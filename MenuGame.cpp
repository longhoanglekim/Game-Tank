
#include "MenuGame.hpp"
#include "Common_Func.hpp"
Button createButton(const char* imagePath, int x, int y,RenderWindow window) {
        // Tạo nút mới
        Button button;

        // Tải hình ảnh và chuyển đổi thành texture
        button.texture = window.loadTexture(imagePath);
        if (button.texture == NULL) {
            std::cout << "Failed to load button image"<<endl;
        }

    // Lấy thông tin kích thước của texture
    SDL_QueryTexture(button.texture, NULL, NULL, &button.rect.w, &button.rect.h);

    // Đặt vị trí của nút
    button.rect.x = x;
    button.rect.y = y;

    return button;
}

MenuGame::MenuGame()
{
    mode = 10; //chua chon mođe
    tutorial = false;
}
MenuGame::~MenuGame()
{

}
void MenuGame::runMenu(SDL_Event& e,Button playButton,Button quitButton,Button help,
                       bool& quit,bool& gameRunning,
                       RenderWindow window,
                       SDL_Texture* menu_pic)
{

    // Xử lý sự kiện
        while (SDL_PollEvent(&e)) {
            // Nhấp chuột
            if (e.type == SDL_MOUSEBUTTONDOWN) {
                // Kiểm tra xem chuột có trên nút Play không
                if (e.button.x >= playButton.rect.x && e.button.x <= playButton.rect.x + playButton.rect.w
                        && e.button.y >= playButton.rect.y && e.button.y <= playButton.rect.y + playButton.rect.h) {
                    std::cout << "Play button clicked!" << std::endl;
                    gameRunning = true;
                    quit = true;
                }
                // kiểm tra xem chuột có trên nút Help k
                else if (e.button.x >=help.rect.x && e.button.x <= help.rect.x + help.rect.w
                        && e.button.y >= help.rect.y && e.button.y <= help.rect.y + help.rect.h) {
                    tutorial = true ;
                }



                // Kiểm tra xem chuột có trên nút Quit không
                else if (e.button.x >= quitButton.rect.x && e.button.x <= quitButton.rect.x + quitButton.rect.w
                        && e.button.y >= quitButton.rect.y && e.button.y <= quitButton.rect.y + quitButton.rect.h) {
                    gameRunning = false;
                    quit = true;
                }

            }
            // Nhấn phím ESC
            else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE) {
                quit = true;
            }
            // Sự kiện thoát khỏi cửa sổ
            else if (e.type == SDL_QUIT) {
                    gameRunning = false;
                quit = true;
            }
        }

        // Xóa màn hình
        SDL_RenderClear(window.renderer);

        // Vẽ các nút lên màn hình
        SDL_Rect dest = { 0,0,1280,640};

        SDL_RenderCopy(window.renderer,menu_pic,NULL,&dest);
        SDL_RenderCopy(window.renderer, playButton.texture, NULL, &playButton.rect);
        SDL_RenderCopy(window.renderer, quitButton.texture, NULL, &quitButton.rect);
        SDL_RenderCopy(window.renderer,help.texture,NULL , &help.rect);
        // Cập nhật màn hình
        SDL_RenderPresent(window.renderer);

}
void MenuGame::run_tutorial(SDL_Event& e,RenderWindow window,bool& quit,Button x_,bool& gameRunning,SDL_Texture* tur_pic)
{

    SDL_Rect dest = {0,0,1280,640};
    while(SDL_PollEvent(&e))
    {
        // Nhấp chuột
        if (e.type == SDL_MOUSEBUTTONDOWN) {
                // Kiểm tra xem chuột có trên nút X không
                if (e.button.x >= x_.rect.x && e.button.x <= x_.rect.x + x_.rect.w
                        && e.button.y >= x_.rect.y && e.button.y <= x_.rect.y + x_.rect.h) {
                    std::cout << "Turn off tutorial!" << std::endl;
                    tutorial = false;
                }

        }
        if( e.type == SDL_QUIT)
        {
            gameRunning = false;
        }
    }
    SDL_RenderCopy(window.renderer,tur_pic,NULL,&dest);
    SDL_RenderCopy(window.renderer,x_.texture,NULL,&x_.rect);
    window.display();

}
void MenuGame::chooseMode(SDL_Event& e,Button mode_com,Button mode_player,Button quitButton
                          ,bool& quit,bool& gameRunning,
                          RenderWindow window,SDL_Texture* menu_pic)
{
     // Xử lý sự kiện
    while (SDL_PollEvent(&e)) {
            // Nhấp chuột
            if (e.type == SDL_MOUSEBUTTONDOWN) {
                // Kiểm tra xem chuột có trên nút Mode_com không
                if (e.button.x >= mode_com.rect.x && e.button.x <= mode_com.rect.x + mode_com.rect.w
                        && e.button.y >= mode_com.rect.y && e.button.y <= mode_com.rect.y + mode_com.rect.h) {
                    std::cout << "PLAY WITH BOT!" << std::endl;
                    mode = COM;
                    quit = true;
                    }
                // Kiểm tra xem chuột có trên nút Mode_Player không
                else if (e.button.x >= mode_player.rect.x && e.button.x <= mode_player.rect.x + mode_player.rect.w
                        && e.button.y >= mode_player.rect.y && e.button.y <= mode_player.rect.y + mode_player.rect.h) {
                    std::cout << "Play with someone!" << std::endl;
                    mode = PLAYER;
                    quit = true;
                    }
                 // Kiểm tra xem chuột có trên nút Quit không
                else if (e.button.x >= quitButton.rect.x && e.button.x <= quitButton.rect.x + quitButton.rect.w
                        && e.button.y >= quitButton.rect.y && e.button.y <= quitButton.rect.y + quitButton.rect.h) {
                    gameRunning = false;
                    quit = true;
                    }
                }


            // Sự kiện thoát khỏi cửa sổ
            else if (e.type == SDL_QUIT) {
                gameRunning = false;
                quit = true;
            }
        }

        // Xóa màn hình
        SDL_RenderClear(window.renderer);

        // Vẽ các nút lên màn hình
        SDL_Rect dest = { 0,0,1280,640};
        SDL_RenderCopy(window.renderer,menu_pic,NULL,&dest);
        SDL_RenderCopy(window.renderer, mode_com.texture, NULL, &mode_com.rect);
        SDL_RenderCopy(window.renderer, mode_player.texture, NULL, &mode_player.rect);
        SDL_RenderCopy(window.renderer, quitButton.texture, NULL, &quitButton.rect);

        // Cập nhật màn hình
        SDL_RenderPresent(window.renderer);

}
void MenuGame::chooseLevel(SDL_Event& e,Button level1,Button level2,Button quitButton
                           ,bool& quit,bool& gameRunning
                           ,RenderWindow window,
                           SDL_Texture* menu_pic,Map& gamemap)
{
    // Xử lý sự kiện
    while (SDL_PollEvent(&e)) {
            // Nhấp chuột
            if (e.type == SDL_MOUSEBUTTONDOWN) {
                // Kiểm tra xem chuột có trên nút level1 không
                if (e.button.x >= level1.rect.x && e.button.x <= level1.rect.x + level1.rect.w
                        && e.button.y >= level1.rect.y && e.button.y <= level1.rect.y + level1.rect.h) {
                    std::cout << "Map 1 button clicked!" << std::endl;
                    gamemap.loadMap("res/map_level/1.csv");
                    quit = true;
                    }
                // Kiểm tra xem chuột có trên nút level2 không
                else if (e.button.x >= level2.rect.x && e.button.x <= level2.rect.x + level2.rect.w
                        && e.button.y >= level2.rect.y && e.button.y <= level2.rect.y + level2.rect.h) {
                    std::cout << "Map 2 button clicked!" << std::endl;
                    gamemap.loadMap("res/map_level/map2.csv");
                    quit = true;
                    }
                 // Kiểm tra xem chuột có trên nút Quit không
                else if (e.button.x >= quitButton.rect.x && e.button.x <= quitButton.rect.x + quitButton.rect.w
                        && e.button.y >= quitButton.rect.y && e.button.y <= quitButton.rect.y + quitButton.rect.h) {
                    gameRunning = false;
                    quit = true;
                    }
                }


            // Sự kiện thoát khỏi cửa sổ
            else if (e.type == SDL_QUIT) {
                gameRunning = false;
                quit = true;
            }
        }

        // Xóa màn hình
        SDL_RenderClear(window.renderer);

        // Vẽ các nút lên màn hình
        SDL_Rect dest = { 0,0,1280,640};
        SDL_RenderCopy(window.renderer,menu_pic,NULL,&dest);
        SDL_RenderCopy(window.renderer, level1.texture, NULL, &level1.rect);
        SDL_RenderCopy(window.renderer, level2.texture, NULL, &level2.rect);
        SDL_RenderCopy(window.renderer, quitButton.texture, NULL, &quitButton.rect);

        // Cập nhật màn hình
        SDL_RenderPresent(window.renderer);

}
void MenuGame::runGameWithBot(SDL_Event& e,Map& gamemap
                              ,bool& gameRunning,Entity& player1,std::vector<ThreatObject*> threat_list
                              ,const int enemy_quantity,RenderWindow window)
{
            gamemap.drawMap();
                //check event from keyboard or mouse
                while( SDL_PollEvent( &e ) != 0 )
                {

                //User requests quit
                            if( e.type == SDL_QUIT )
                            {
                                gameRunning=false;
                            }

                            //Handle input for player
                            if(player1.is_alive)
                            {
                                player1.handleEvent(e);
                                player1.handleInputAction(e,player1);
                            }
                            if(player1.posX + (float)player1.PLAYER_WIDTH >= 32 * 39 - 16 &&
                               player1.posY + (float)player1.PLAYER_HEIGHT >= 32 * 9 - 20 &&
                               player1.posY  <=  32 * 10 - 15)
                            {
                                player1.gain_coin = true;
                                break;

                            }
                }


                player1.handleBullet(gamemap,player1,threat_list);

                for(int i = 0;i < enemy_quantity;i++)
                {
                    if(threat_list[i]->is_alive)
                    {
                        threat_list[i]->make_bullet(threat_list[i]);
                        threat_list[i]->RandomShot(gamemap,player1,threat_list[i]);
                        threat_list[i]->moveRandomly(gamemap,player1,threat_list[i],i,threat_list);
                        threat_list[i]->render();
                    }
                }

                if(player1.is_alive)
                {
                    player1.move(gamemap);
                    player1.render(player1.tex);
                }

}
void MenuGame::runGameWithPlayer(SDL_Event& e,Map& gamemap,bool& gameRunning,
                                 Entity& player1,Entity& player2
                                 ,RenderWindow window)
{
                gamemap.drawMap();
                //check event from keyboard or mouse
                while( SDL_PollEvent( &e ) != 0 )
                {

                //User requests quit
                            if( e.type == SDL_QUIT )
                            {
                                gameRunning=false;
                            }

                            //Handle input for player
                            if(player1.is_alive)
                            {
                                player1.handleEvent(e);
                                player1.handleInputAction(e,player1);
                            }

                            if( player2.is_alive)
                            {
                                player2.handleEvent(e);
                                player2.handleInputAction(e,player2);
                            }

                }


                player1.handleBullet(gamemap,player1,player2);
                player2.handleBullet(gamemap,player2,player1);


                if(player1.is_alive)
                {
                    player1.move(gamemap);
                    player1.render(player1.tex);
                }

                if(player2.is_alive)
                {
                    player2.move(gamemap);
                    player2.render(player2.tex);
                }


}
void MenuGame::renderResCom(SDL_Event& e,bool& quit,bool& gameRunning,Button& quitButton,
                            Entity& player1,SDL_Texture* menu_pic,RenderWindow window)
{
    if(player1.gain_coin)
        {
            menu_pic = window.loadTexture("res/Menu/WinBot.png");
        }
    else
        {
            menu_pic = window.loadTexture("res/Menu/LoseBot.png");
        }
    if(player1.gain_coin || !player1.is_alive)
        {
            quit = false;
            quitButton.rect.x =  600;
            quitButton.rect.y = 300;
            SDL_Rect dest = { 0,0,1280,640};
                while(SDL_PollEvent(&e))
                {
                // Nhấp chuột
                    if (e.type == SDL_MOUSEBUTTONDOWN)
                    {
                    // Kiểm tra xem chuột có trên nút quit không
                            if (e.button.x >= quitButton.rect.x && e.button.x <= quitButton.rect.x + quitButton.rect.w
                            && e.button.y >= quitButton.rect.y && e.button.y <= quitButton.rect.y + quitButton.rect.h) {
                            gameRunning = false;
                        }

                    }
                    if( e.type == SDL_QUIT)
                    {
                        gameRunning = false;
                    }
                }
        SDL_RenderCopy(window.renderer,menu_pic,NULL,&dest);
        SDL_RenderCopy(window.renderer,quitButton.texture,NULL,&quitButton.rect);
        window.display();
        }
}
void MenuGame::renderResPlayer(SDL_Event& e,bool& quit,bool& gameRunning,Button& quitButton,
                               Entity& player1,Entity& player2,
                               SDL_Texture* menu_pic,RenderWindow window)
{
    if(!player1.is_alive || !player2.is_alive)

    {

                if(player1.is_alive)
                {
                    menu_pic = window.loadTexture("res/Menu/Player1won.png");
                }
                else
                {
                    menu_pic = window.loadTexture("res/Menu/Player2won.png");
                }
                SDL_Rect dest = {0,0,1280,640};
                while(SDL_PollEvent(&e))
                {
                // Nhấp chuột
                    if (e.type == SDL_MOUSEBUTTONDOWN)
                    {
                    // Kiểm tra xem chuột có trên nút quit không
                            if (e.button.x >= quitButton.rect.x && e.button.x <= quitButton.rect.x + quitButton.rect.w
                            && e.button.y >= quitButton.rect.y && e.button.y <= quitButton.rect.y + quitButton.rect.h) {
                            gameRunning = false;
                        }

                    }
                    if( e.type == SDL_QUIT)
                    {
                        gameRunning = false;
                    }
                }
        SDL_RenderCopy(window.renderer,menu_pic,NULL,&dest);
        SDL_RenderCopy(window.renderer,quitButton.texture,NULL,&quitButton.rect);
        window.display();

    }


}
