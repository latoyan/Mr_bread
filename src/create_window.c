#include "minilib.h"

void create_window()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
		  print_error();

    int size = 21;
    r_game *obj[size];
    for(int i = 0; i < size; i++){
      obj[i] = (r_game*)malloc(sizeof(r_game));
    }
    r_game *background = obj[BACKGROUND];
    r_game *floor = obj[FLOOR];
    r_game *carpet = obj[CARPET];
    r_game *entrance = obj[ENTRANCE];  //each allocated object
    r_game *head = obj[PLAYER];
    r_game *hedge = obj[HEDGE];
    r_game *hog = obj[HOG];
    r_game *loss_screen = obj[LOSS_SCREEN];
    r_game *key = obj[KEY];
    r_game *dungeon = obj[DUNGEON];
    r_game *hedge1 = obj[HEDGE1];
    r_game *hog1 = obj[HOG1];
    r_game *monster = obj[MONSTER];
    r_game *bullet = obj[BULLET];
    r_game *name = obj[NAME];
    r_game *dungeon2 = obj[DUNGEON2];
    r_game *dungeon3 = obj[DUNGEON3];
    r_game *dungeon4 = obj[DUNGEON4];
    r_game *plate = obj[PLATE];
    r_game *credits = obj[CREDITS];
    r_game *web = obj[WEB];

    r_walls *wall = (r_walls*)malloc(sizeof(r_walls));
    r_bullet *enemy = (r_bullet*)malloc(sizeof(r_bullet));
    SDL_Window *window = SDL_CreateWindow(NAME_WINDOW, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_X, WINDOW_Y, SDL_WINDOW_ALLOW_HIGHDPI);
    
    if (window == NULL) 
	      print_error();
   
    Uint32 render_flags = SDL_RENDERER_ACCELERATED; 
    SDL_Renderer *rend = SDL_CreateRenderer(window, -1, render_flags); 

    //////////////////////////////////////////
    SDL_Rect hide_Box = {4000, 4000, 0, 0};
    loss_screen->dstrect = hide_Box;
    hedge->dstrect = hide_Box;      //weird bug don't mess with this chunk of code
    hedge1->dstrect = hide_Box;  
    key->dstrect = hide_Box;
    dungeon->dstrect = hide_Box;
    dungeon2->dstrect = hide_Box;
    dungeon3->dstrect = hide_Box;
    dungeon4->dstrect = hide_Box;
    monster->dstrect = hide_Box;
    bullet->dstrect = hide_Box;
    hog->dstrect = hide_Box;
    hog1->dstrect = hide_Box;
    bullet->dstrect = hide_Box;
    plate->dstrect = hide_Box;
    credits->dstrect = hide_Box;
    web->dstrect = hide_Box;
    /////////////////////////////////////////

    head->speed = 1500;
    bullet->speed = 1500;
    hedge->speed = 0;
    hedge1->speed = 0;
    monster->speed = 0;
    bool spawn_bullet = false;
    //////////////////////////////////////////
    
    R_IMG_Load(head, "./res/image/hlebozhor.png");  //database of images
    R_IMG_Load(background, "./res/image/background.png");
    R_IMG_Load(carpet, "./res/image/carpet1.jpeg");
    R_IMG_Load(entrance, "./res/image/dungeon.png");
    R_IMG_Load(hedge, "./res/image/fireball.png"); 
    R_IMG_Load(hedge1, "./res/image/fireball.png");  
    R_IMG_Load(loss_screen, "./res/image/loss.png");
    R_IMG_Load(key, "./res/image/key.png");
    R_IMG_Load(hog, "./res/image/fireball.png"); 
    R_IMG_Load(hog1, "./res/image/fireball.png"); 
    R_IMG_Load(monster, "./res/image/monster.png");
    R_IMG_Load(dungeon, "./res/image/dungeon.png");
    R_IMG_Load(dungeon2, "./res/image/dungeon.png");
    R_IMG_Load(dungeon3, "./res/image/dungeon.png");
    R_IMG_Load(dungeon4, "./res/image/dungeon.png");
    R_IMG_Load(bullet, "./res/image/fireball.png");
    R_IMG_Load(name, "./res/image/name.png");
    R_IMG_Load(plate, "./res/image/plate.png");
    R_IMG_Load(credits, "./res/image/credits.jpeg");
    R_IMG_Load(web, "./res/image/web.png");
    R_IMG_Load(floor, "./res/image/brick.png");

    C_Wall(wall, "./res/image/wall.png", rend);
    C_Bullet(enemy, "./res/image/fireball.png", rend);
   //////////////////////////////////////////
    All_TextureFromSurface(obj, rend, size);
    main_hall(obj, wall);  //creates first map
    ////////////////////////////////////////// 
    //bool running = true;
    int close_requested = 0;
    int flag_tap_l = 0;
    int flag_tap_t = 0;
    int flagr = 0;
    int flag_tap_r = 0;
    int level_flag = 1;
    int key_flag = 0;
    int hack_flag = 0;
    SDL_Event event;

    ///////////////////////////////////////////
     if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) == -1)
      print_error();

     if ((head->music = Mix_LoadMUS("./res/music/111111.mp3")) == NULL)    ////music include 
       print_error();

     if (Mix_PlayMusic(head->music, 3) < 0)
       print_error();
    ///////////////////////////////////////////

    while (close_requested == 0) 
    {
      if (event.type == SDL_QUIT){
              close_requested = 1;
          }
        const Uint8* keystates = SDL_GetKeyboardState(NULL);
      if(keystates[SDL_SCANCODE_LEFT] && head->dstrect.x > 100){
        int temp = head->dstrect.x;
        head->dstrect.x -=  head->speed / 125;
        if(Wall_Collision(head->dstrect, wall))  //movement
          head->dstrect.x = temp;
      } 
      else if(keystates[SDL_SCANCODE_RIGHT] && head->dstrect.x < WINDOW_X_FULLSIZE - 200){
        int temp = head->dstrect.x;
        head->dstrect.x +=  head->speed / 125; 
        if(Wall_Collision(head->dstrect, wall))  //movement
        head->dstrect.x = temp; 
      }
      else if (keystates[SDL_SCANCODE_DOWN] && head->dstrect.y < WINDOW_Y_FULLSIZE - 200){
        int temp = head->dstrect.y;
        head->dstrect.y +=  head->speed / 125;
          if(Wall_Collision(head->dstrect, wall))  //movement
               head->dstrect.y = temp;
      } else if (keystates[SDL_SCANCODE_UP] && head->dstrect.y > 100){
        int temp = head->dstrect.y;
        head->dstrect.y -=  head->speed / 125;
          if(Wall_Collision(head->dstrect, wall) && head->dstrect.y > 100)  //movement
              head->dstrect.y = temp;
      }
        

      while(SDL_PollEvent(&event))
      {   
          if (event.type == SDL_QUIT){
              close_requested = 1;
          }

          int key1 = event.key.keysym.sym;   

          if (event.type == SDL_KEYDOWN && key1 == SDLK_ESCAPE){
              close_requested = 1;
          }

            if (player_enter(head->dstrect, entrance->dstrect)){
              SDL_Rect player_box = {100, 750, 100, 100};         //event for next level    
              SDL_Rect dun_Box = {0, 0, 0, 0}; 
              obj[NAME]->dstrect = dun_Box;    
              head->dstrect = player_box;                       //entrance
              hedgehog_level(obj, wall);
            }
            if (player_enter(head->dstrect, dungeon->dstrect)){
              for (int i = 0; i < 12; i++){
                wall->bound[i] = hide_Box;
              }
              if(level_flag == 1){
                  SDL_Rect dun_Box = {0, 0, 0, 0};     //player gets key and dungeon opens
                dungeon->dstrect = dun_Box;
                hedge->dstrect = hide_Box; 
                hedge1->dstrect = hide_Box;     
                hog->dstrect = hide_Box;
                hog1->dstrect = hide_Box;
                key->dstrect.x = 975;
                key->dstrect.y = 700;
                key->dstrect.w = 75;
                key->dstrect.h = 75;
                SDL_Rect player_box = {100, 100, 100, 100};         //event for next level
                head->dstrect = player_box;                       //entrance
                level_flag = 2;
                monster_level(obj, wall);
              }
            }
              if (player_enter(head->dstrect, dungeon->dstrect)){
                for (int i = 0; i < 14; i++){
                  wall->bound[i] = hide_Box;
                }
                if(level_flag == 2){
                  SDL_Rect dun_Box = {0, 0, 0, 0};     //player gets key and dungeon opens
                  dungeon->dstrect = dun_Box;
                  monster->dstrect = dun_Box;
                  bullet->dstrect = dun_Box;
                  key->dstrect.x = 975;
                  key->dstrect.y = 700;
                  key->dstrect.w = 125;
                  key->dstrect.h = 125;
                  SDL_Rect player_box = {100, 100, 100, 100};         //event for next level
                  head->dstrect = player_box;                       //entrance
                  level_flag = 3;
                  hack_level(obj, wall);
                }
                else if(level_flag == 3){
                  SDL_Rect dun_Box = {0, 0, 0, 0};     //player gets key and dungeon opens
                  dungeon->dstrect = dun_Box;
                  key->dstrect.x = 975;
                  key->dstrect.y = 700;
                  key->dstrect.w = 125;
                  key->dstrect.h = 125;
                  SDL_Rect player_box = {100, 100, 100, 100};         //event for next level
                  head->dstrect = player_box;                       //entrance
                  spawn_bullet = create_bullets(enemy, spawn_bullet);
                  level_flag = 4;
                  end_level(obj, wall);
                }
                else if(level_flag == 4){
                //SDL_Rect dun_Box = {0, 0, 125, 200};
                 // dungeon2->dstrect = dun_Box;
                  //SDL_Rect dun_Box = {0, 1336, 125, 200};
                  //dun_Box.y = 1336;
                 // dungeon3->dstrect = dun_Box;
                  //SDL_Rect dun_Box = {1923, 1336, 125, 200};
                 // dun_Box.x = 1923;
                  //dungeon4->dstrect = dun_Box;
                  SDL_Rect player_box = {700, 700, 100, 100};         //event for next level
                  head->dstrect = player_box;                     //entrance
                }
              }

      }
        if(spawn_bullet == 1){
          create_bullets(enemy, spawn_bullet);
          for(int i = 0; i < 10; i++)
            if(SDL_HasIntersection(&head->dstrect, &enemy->bound[i])){
              SDL_RenderClear(rend); 
              SDL_Rect loss_Box = {550, 520, 900, 380};       
              loss_screen->dstrect = loss_Box; 
              R_RenderCopy(loss_screen, rend);
              SDL_RenderPresent(rend);
              SDL_Delay(1000);
              SDL_Rect player_box = {100, 100, 100, 100};
              head->dstrect = player_box;
              loss_screen->dstrect = hide_Box;
            }  
          }   
        if (monster->speed != 0){
              monster_spawn(monster, bullet, wall);
        }
        if(hedge->speed != 0){  //Hedgehog start
          S_Hedgehog(hedge, hog, 1);
          S_Hedgehog1(hedge1, hog1, 1);
        }
            
       
        if(player_enter(head->dstrect, key->dstrect) && key_flag == 0){
          SDL_Rect dun_Box = {960, 175, 125, 200};     //player gets key and dungeon opens
          dungeon->dstrect = dun_Box;
          key->dstrect.x = 975;
          key->dstrect.y = 700;
          key->dstrect.w = 0;
          key->dstrect.h = 0;
          key_flag = 1;
        }
        if (level_flag == 2 && player_enter(head->dstrect, wall->bound[8])){
          wall->bound[7].w = 0;
        }
        
        if (level_flag == 2 && player_enter(head->dstrect, wall->bound[10]) && hack_flag == 0){
          head->speed = 0;
          if (flagr == 1){
            head->speed = 1500;
            hack_flag = 1;
          }
          SDL_Delay(1000 / 0.5);
          flagr = 1;
          SDL_Delay(1000 / 30);
        }
          if(SDL_HasIntersection(&head->dstrect, &plate->dstrect)){
            credit_screen(obj, rend);
            break;
          }
        
        if(player_enter(head->dstrect, key->dstrect) && key_flag == 1){
          SDL_Rect dun_Box = {925, 100, 125, 200};     //player gets key and dungeon opens
          dungeon->dstrect = dun_Box;
          key->dstrect.x = 0;
          key->dstrect.y = 0;
          key->dstrect.w = 0;
          key->dstrect.h = 0;
          key_flag = 2;
        }
        if(player_enter(head->dstrect, key->dstrect) && key_flag == 2){
          SDL_Rect dun_Box = {1723, 100, 125, 200};     //player gets key and dungeon opens
          dungeon->dstrect = dun_Box;
          key->dstrect.x = 0;
          key->dstrect.y = 0;
          key->dstrect.w = 0;
          key->dstrect.h = 0;
          key_flag = 3;
        }
        
        if (key_flag == 1){
          if (level_flag == 1 && flag_tap_l == 0 && SDL_HasIntersection(&head->dstrect, &wall->bound[8])){
          wall->bound[7].y -= 75;
          wall->bound[7].h += 75;
          wall->bound[6].h += 75;
          flag_tap_l = 1;
          }
          if (level_flag == 1 && flag_tap_t == 0 && SDL_HasIntersection(&head->dstrect, &wall->bound[9])){
          wall->bound[0].w += 75;
          wall->bound[1].w += 75;
          wall->bound[1].x -= 75;
          flag_tap_t = 1;
          }
          if (level_flag == 1 && flag_tap_r == 0 && SDL_HasIntersection(&head->dstrect, &wall->bound[10])){
          wall->bound[4].y -= 75;
          wall->bound[4].h += 75;
          wall->bound[5].h += 75;
          flag_tap_r = 1;
          }
          S_Hedgehog(hedge, hog, 0);
          S_Hedgehog1(hedge1, hog1, 0);
        }
        if (SDL_HasIntersection(&bullet->dstrect, &head->dstrect)){
        SDL_RenderClear(rend);
          SDL_Rect loss_Box = {550, 520, 900, 380};       
          loss_screen->dstrect = loss_Box; 
          R_RenderCopy(loss_screen, rend);
          SDL_RenderPresent(rend);
          SDL_Delay(1000); 
          loss_screen->dstrect = hide_Box;
          if (key_flag == 2){
            head->dstrect.x = 950;
            head->dstrect.y =  695;
          }
          else {
             head->dstrect.x = 100;
            head->dstrect.y =  100;
          }
        }
        if (SDL_HasIntersection(&monster->dstrect, &head->dstrect)){
        SDL_RenderClear(rend);
          SDL_Rect loss_Box = {550, 520, 900, 380};       
          loss_screen->dstrect = loss_Box; 
          R_RenderCopy(loss_screen, rend);
          SDL_RenderPresent(rend);
          SDL_Delay(1000); 
          loss_screen->dstrect = hide_Box;
          if (key_flag == 2){
            head->dstrect.x = 950;
            head->dstrect.y =  695;
          }
          else {
             head->dstrect.x = 100;
            head->dstrect.y =  100;
          }
        }
        if(SDL_HasIntersection(&head->dstrect, &hedge->dstrect) || SDL_HasIntersection(&head->dstrect, &hog->dstrect) || SDL_HasIntersection(&head->dstrect, &hedge1->dstrect) || SDL_HasIntersection(&head->dstrect, &hog1->dstrect) ){  // Loss Screen
          SDL_RenderClear(rend);
          SDL_Rect loss_Box = {550, 520, 900, 380};       
          loss_screen->dstrect = loss_Box; 
          R_RenderCopy(loss_screen, rend);
          SDL_RenderPresent(rend);
          SDL_Delay(1000); 
          loss_screen->dstrect = hide_Box;
          if (key_flag == 1){
            head->dstrect.x = 950;
            head->dstrect.y =  695;
          }
          else {
             head->dstrect.x = 100;
            head->dstrect.y =  695;
          }
        }
/////////////////////////////////////////////////////
    if (head->dstrect.x + head->dstrect.w > 1024*2) 
        head->dstrect.x = 1024*2 - head->dstrect.w; //Player checks for window borders

    if (head->dstrect.x < 0) 
        head->dstrect.x = 0; 

    if (head->dstrect.y + head->dstrect.h > 1536) 
        head->dstrect.y = 1536 - head->dstrect.h; 

    if (head->dstrect.y < 0) 
       head-> dstrect.y = 0;

    SDL_RenderClear(rend); 
    All_RenderCopy(obj, rend, size); //renders every other object
    R_Walls(wall, rend);  //renders walls
    r_Bullet(enemy, rend);
    SDL_RenderPresent(rend); 
    SDL_Delay(1000 / 60); 
  }
    SDL_Delay(3000);
///////////////////////////////////////////////////////
    ALL_DestroyTexture(obj, size);
    SDL_DestroyRenderer(rend); 
    SDL_DestroyWindow(window);
    SDL_Quit();
}
