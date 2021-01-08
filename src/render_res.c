#include "minilib.h"

void R_IMG_Load(r_game *head, char *image)
{
  if ((head->surface = IMG_Load(image)) == NULL)  
		print_error();
}

void R_TextureFromSurface(r_game *head, SDL_Renderer *rend)
{                                                   
    head->texture = SDL_CreateTextureFromSurface(rend, head->surface);   
    SDL_QueryTexture(head->texture, NULL, NULL, &head->dstrect.w, &head->dstrect.h);     
    SDL_FreeSurface(head->surface);                                                                                      
}

void R_RenderCopy(r_game *head, SDL_Renderer *rend)
{
    SDL_RenderCopy(rend, head->texture, NULL, &head->dstrect);    
}

void R_SDL_DestroyTexture(r_game *head)
{
    SDL_DestroyTexture(head->texture); 
}

void All_TextureFromSurface(r_game **obj, SDL_Renderer *rend, int size){
	for(int i = 0; i < size; i++){
		R_TextureFromSurface(obj[i], rend);
	}
}

void All_RenderCopy(r_game **obj, SDL_Renderer *rend, int size){
	for(int i = 0; i < size; i++)
		R_RenderCopy(obj[i], rend);
}

void ALL_DestroyTexture(r_game **obj, int size){
	for(int i = 0; i < size; i++)
		R_SDL_DestroyTexture(obj[i]);
}

bool Wall_Collision(SDL_Rect player, r_walls *barrier){

	for(int i = 0; i < 14; i++){
	if(SDL_HasIntersection(&player, &barrier->bound[i]))
		return true;
	if(i == 7){
            i = 10;
        }
    
    if(i == 11){
        i = 12;
    }
    }
	return false;
}

void R_Walls(r_walls *head, SDL_Renderer *rend){
	for(int i = 0; i < 14; i++){
        SDL_RenderCopy(rend, head->texture, NULL, &head->bound[i]);
        if(i == 7){
            i = 10;
        }
        if(i == 12){
            i = 13;
        }
    }		
}

void r_Bullet(r_bullet *bullet, SDL_Renderer *rend){
    for(int i = 0; i < 10; i++){
        SDL_RenderCopy(rend, bullet->texture, NULL, &bullet->bound[i]);
    }
}

void C_Wall(r_walls *head, char *image, SDL_Renderer *rend){
	SDL_Surface *img;
	if ((img = IMG_Load(image)) == NULL)
		print_error();
    head->texture = SDL_CreateTextureFromSurface(rend, img);   
    SDL_QueryTexture(head->texture, NULL, NULL, NULL, NULL);     
    SDL_FreeSurface(img); 
}

void C_Bullet(r_bullet *bullet, char *image, SDL_Renderer *rend){
    SDL_Surface *img;
    if ((img = IMG_Load(image)) == NULL)
        print_error();
    bullet->texture = SDL_CreateTextureFromSurface(rend, img);   
    SDL_QueryTexture(bullet->texture, NULL, NULL, NULL, NULL);     
    SDL_FreeSurface(img); 
}

void main_hall(r_game **obj, r_walls *wall){
	SDL_Rect carpet_Box = {100, 700, WINDOW_X_FULLSIZE-200, 200};
    obj[CARPET]->dstrect = carpet_Box;
    SDL_Rect floor_Box = {100, 100, WINDOW_X_FULLSIZE-200, WINDOW_Y_FULLSIZE-200};
    obj[FLOOR]->dstrect = floor_Box;
    SDL_Rect entrance_Box = {1800, 650, 125, 200};
    obj[ENTRANCE]->dstrect = entrance_Box;
    SDL_Rect back_Rect = {0, 0, 1024*2, 768*2};
    obj[BACKGROUND]->dstrect = back_Rect;
    SDL_Rect nol = {0,0,0,0};
    wall->bound[0] = nol;
    // SDL_Rect wall_Rect = {0, 300, 1024, 150};
    // wall->bound[0] = wall_Rect;
    // wall_Rect.x = 1024;
    // wall->bound[1] = wall_Rect;
    // wall_Rect.y += 750;
    // wall->bound[2] = wall_Rect;
    // wall_Rect.x = 0;
    // wall->bound[3] = wall_Rect;
    SDL_Rect player_box = {150, 750, 100, 100};
    obj[PLAYER]->dstrect = player_box;
    SDL_Rect name_Rect = {599, 108, 900, 240};
    obj[NAME]->dstrect = name_Rect;
}

bool player_enter(SDL_Rect player, SDL_Rect entrance){
	if(SDL_HasIntersection(&player, &entrance))
		return true;
	return false;
}
void monster_level(r_game **obj, r_walls *wall){
    //SDL_Rect carpet_Box = {100, 350, WINDOW_X_FULLSIZE - 200, 800};
    //obj[CARPET]->dstrect = carpet_Box;
    SDL_Rect entrance_Box = {0, 0, 0, 0};
    obj[ENTRANCE]->dstrect = entrance_Box;
    SDL_Rect web_Box = {1850, 1250, 250, 250};
    obj[WEB]->dstrect = web_Box;
    SDL_Rect wall_Rect = {200, 200, 650, 75};
    wall->bound[0] = wall_Rect; // top left
    wall_Rect.x += 900;
    wall_Rect.w = 700;
    wall->bound[1] = wall_Rect; // ????
    wall_Rect.x -= 900;
    wall_Rect.w = 75;
    wall_Rect.h = 1050;    
    wall->bound[2] = wall_Rect; // left side
    wall_Rect.y += 1050;
    wall_Rect.w = 1625;
    wall_Rect.h = 75;
    wall->bound[3] = wall_Rect; // ????
    wall_Rect.y -= 1050;
    wall_Rect.w = 75;
    wall_Rect.x += 1565;
    wall_Rect.h = 1125;
    wall->bound[4] = wall_Rect; // right side
    wall_Rect.w = 1250;
    wall_Rect.h = 75;
    wall_Rect.x -=1375;
    wall_Rect.y += 185;
    wall->bound[5] = wall_Rect; // center top
    wall_Rect.w = 100;
    wall_Rect.h = 655;
    wall->bound[6] = wall_Rect; // center left
    wall_Rect.w = 1250;
    wall_Rect.h = 75;
    wall_Rect.y += 580;
    wall->bound[7] = wall_Rect;  //center bottom
    wall_Rect.w = 100;
    wall_Rect.h = 400;
    wall_Rect.x = 1750;
    wall_Rect.y = 1336;
    wall->bound[8] = wall_Rect;  //??
    wall->bound[9] = wall_Rect; //??
    wall_Rect.x = 0;
    wall_Rect.y = 1336;
    wall->bound[10] = wall_Rect; //????
    wall_Rect.w = 75;
    wall_Rect.h = 650;
    wall_Rect.x = 1570;
    wall_Rect.y = 385;
    wall->bound[11] = wall_Rect;
    SDL_Rect dung_Rect = {0, 0, 0, 0};
    obj[DUNGEON]->dstrect = dung_Rect;
    monster_spawn(obj[MONSTER], obj[BULLET], wall);
}
void end_level(r_game **obj, r_walls *wall){
    //SDL_Rect carpet_Box = {100, 350, WINDOW_X_FULLSIZE - 200, 800};
    //obj[CARPET]->dstrect = carpet_Box;
    SDL_Rect entrance_Box = {0, 0, 0, 0}; 
    obj[ENTRANCE]->dstrect = entrance_Box;
    SDL_Rect plate_Box = {1800, 750, 100, 100};
    obj[PLATE]->dstrect = plate_Box;
    SDL_Rect key_Box = {0, 0 , 0, 0};
    obj[KEY]->dstrect = key_Box;
    wall->bound[0] = entrance_Box;
}

void credit_screen(r_game **obj, SDL_Renderer *rend){
    SDL_RenderClear(rend); 
    SDL_Rect credits_Box = {600, 200, 1200, 1200};       
    obj[CREDITS]->dstrect = credits_Box; 
    R_RenderCopy(obj[CREDITS], rend);
    SDL_RenderPresent(rend);
}

void hack_level(r_game **obj, r_walls *wall){
    //SDL_Rect carpet_Box = {100, 350, WINDOW_X_FULLSIZE - 200, 800};
    //obj[CARPET]->dstrect = carpet_Box;
    SDL_Rect entrance_Box = {0, 0, 0, 0};
    obj[ENTRANCE]->dstrect = entrance_Box;
    // obj[14]->dstrect = entrance_Box;
    // obj[15]->dstrect = entrance_Box;
    // obj[16]->dstrect = entrance_Box;
    SDL_Rect key_Box = {975, 700 , 125, 125};
    obj[KEY]->dstrect = key_Box;
    SDL_Rect hack_Box = {0, 900, 636, 636};
    wall->bound[0] = hack_Box;
    hack_Box.x = 836;
    hack_Box.h = 436;
    wall->bound[1] = hack_Box; 
    hack_Box.h = 636;
    hack_Box.x = 1672;
    hack_Box.w = 376;
    wall->bound[2] = hack_Box;
    hack_Box.h = 600;
    hack_Box.x = 1100;
    hack_Box.w = 75;
    hack_Box.y = 300;
    wall->bound[3] = hack_Box;
    wall->bound[4] = hack_Box;
    wall->bound[5] = hack_Box;
    wall->bound[6] = hack_Box;
    wall->bound[7] = hack_Box;
    wall->bound[8] = hack_Box;
    wall->bound[9] = hack_Box;
    wall->bound[10] = hack_Box;
    wall->bound[11] = hack_Box;
    hack_Box.h = 636;
    hack_Box.x = 0;
    hack_Box.w = 2048;
    hack_Box.y = 900;
    wall->bound[12] = hack_Box;
    hack_Box.h = 300;
    hack_Box.x = 1100;
    hack_Box.w = 75;
    hack_Box.y = 0;
    wall->bound[13] = hack_Box;
    
}

void hedgehog_level(r_game **obj, r_walls *wall){
	SDL_Rect carpet_Box = {0, 0, 0, 0};
    obj[CARPET]->dstrect = carpet_Box;
    SDL_Rect entrance_Box = {0, 0, 0, 0};
    obj[ENTRANCE]->dstrect = entrance_Box;
    SDL_Rect key_Box = {950, 695 , 125, 125};
    obj[KEY]->dstrect = key_Box;
    SDL_Rect wall_Rect = {700, 400, 250, 75};
    wall->bound[0] = wall_Rect;
    wall_Rect.x += 400;
    wall->bound[1] = wall_Rect;
    wall_Rect.y += 575;
    wall->bound[2] = wall_Rect;
    wall_Rect.x -= 400;
    wall->bound[3] = wall_Rect;
    wall_Rect.h = 250;
    wall_Rect.w = 75;
    wall_Rect.x += 575;
    wall_Rect.y -= 175;
    wall->bound[4] = wall_Rect; 
    wall_Rect.y -= 400;
    wall->bound[5] = wall_Rect;
    wall_Rect.x -= 575;
    wall->bound[6] = wall_Rect;
    wall_Rect.y += 400;
    wall->bound[7] = wall_Rect;

    SDL_Rect trap_box = {775, 650, 15, 150};
    wall->bound[8] = trap_box;
    trap_box.x += 175;
    trap_box.y -= 175;
    trap_box.h = 15;
    trap_box.w = 150;
    wall->bound[9] = trap_box;
    trap_box.x += 310;
    trap_box.y += 175;
    trap_box.h = 150;
    trap_box.w = 15;
    wall->bound[10] = trap_box;
    
    S_Hedgehog(obj[HEDGE], obj[HOG], 1);
    S_Hedgehog1(obj[HEDGE], obj[HOG], 1);
}


void S_Hedgehog(r_game *hedge, r_game *hog, int check){
    if (check == 1){
        if(hedge->speed == 0){
        SDL_Rect hedge_Rect = {200, 150, 100, 100};
        hedge->dstrect = hedge_Rect;
        hedge->speed = 1500;
        SDL_Rect hog_Rect = {1800, 1300, 100, 100};
        hog->dstrect = hog_Rect;
        hog->speed = 1500;
        }
        if (hedge->dstrect.x != 1800 && hedge->dstrect.y < 150)
            hedge->dstrect.x += hedge->speed / 30; 
    
        if (hedge->dstrect.x > 1799 && hedge->dstrect.y != 1300)
            hedge->dstrect.y += hedge->speed / 30; 

        if (hedge->dstrect.y > 1299 && hedge->dstrect.x > 50){
            hedge->dstrect.x -= hedge->speed / 30; 
        }

        if (hedge->dstrect.x <= 200 && hedge->dstrect.y > 1) {
            hedge->dstrect.y -= hedge->speed / 30;
        }

        if (hog->dstrect.x != 1800 && hog->dstrect.y < 150)
            hog->dstrect.x += hog->speed / 30; 
    
        if (hog->dstrect.x > 1799 && hog->dstrect.y != 1300)
           hog->dstrect.y += hog->speed / 30; 

        if (hog->dstrect.y > 1299 && hog->dstrect.x > 50){
            hog->dstrect.x -= hog->speed / 30; 
        }
        if (hog->dstrect.x <= 200 && hog->dstrect.y > 1) {
           hog-> dstrect.y -= hog->speed / 30;
        }
    }
    else if (check == 0){
        if(hedge->speed == 0){
        SDL_Rect hedge_Rect = {250, 200, 100, 100};
        hedge->dstrect = hedge_Rect;
        hedge->speed = 2000;
        SDL_Rect hog_Rect = {1750, 1250, 100, 100};
        hog->dstrect = hog_Rect;
        hog->speed = 2000;
        }
        if (hedge->dstrect.x != 1600 && hedge->dstrect.y < 300)
            hedge->dstrect.x += hedge->speed / 30; 
    
        if (hedge->dstrect.x > 1599 && hedge->dstrect.y != 1050)
            hedge->dstrect.y += hedge->speed / 30; 

        if (hedge->dstrect.y > 1049 && hedge->dstrect.x > 50){
            hedge->dstrect.x -= hedge->speed / 30; 
        }

        if (hedge->dstrect.x <= 449 && hedge->dstrect.y > 1) {
            hedge->dstrect.y -= hedge->speed / 30;
        }

        if (hog->dstrect.x != 1600 && hog->dstrect.y < 300)
            hog->dstrect.x += hog->speed / 30; 
    
        if (hog->dstrect.x > 1599 && hog->dstrect.y != 1050)
           hog->dstrect.y += hog->speed / 30; 

        if (hog->dstrect.y > 1049 && hog->dstrect.x > 50){
            hog->dstrect.x -= hog->speed / 30; 
        }
        if (hog->dstrect.x <= 449 && hog->dstrect.y > 1) {
           hog-> dstrect.y -= hog->speed / 30;
        }
    }
}
void S_Hedgehog1(r_game *hedge1, r_game *hog1, int check){
    if (check == 0){
    if(hedge1->speed == 0){
    SDL_Rect hedge1_Rect = {200, 150, 100, 100};
    hedge1->dstrect = hedge1_Rect;
    hedge1->speed = 1500;
    SDL_Rect hog1_Rect = {1800, 1300, 100, 100};
    hog1->dstrect = hog1_Rect;
    hog1->speed = 1500;
    }
    if (hedge1->dstrect.x != 1800 && hedge1->dstrect.y < 150)
        hedge1->dstrect.x += hedge1->speed / 30; 
    
    if (hedge1->dstrect.x > 1799 && hedge1->dstrect.y != 1300)
        hedge1->dstrect.y += hedge1->speed / 30; 

    if (hedge1->dstrect.y > 1299 && hedge1->dstrect.x > 50){
        hedge1->dstrect.x -= hedge1->speed / 30; 
    }

     if (hedge1->dstrect.x <= 200 && hedge1->dstrect.y > 1) {
        hedge1->dstrect.y -= hedge1->speed / 30;
    }

    if (hog1->dstrect.x != 1800 && hog1->dstrect.y < 150)
        hog1->dstrect.x += hog1->speed / 30; 
    
    if (hog1->dstrect.x > 1799 && hog1->dstrect.y != 1300)
        hog1->dstrect.y += hog1->speed / 30; 

     if (hog1->dstrect.y > 1299 && hog1->dstrect.x > 50){
         hog1->dstrect.x -= hog1->speed / 30; 
     }
     if (hog1->dstrect.x <= 200 && hog1->dstrect.y > 1) {
       hog1-> dstrect.y -= hog1->speed / 30;
    }
    }
}

void monster_spawn(r_game *monster, r_game *bullet, r_walls *wall){
    if (monster->speed == 0){
        SDL_Rect monster_Rect = {300, 1150, 100, 100};
        monster->dstrect = monster_Rect;
        monster->speed = 1000;
    }
    if(monster->dstrect.x == 1650 && monster->dstrect.y == 1150){
        monster->dstrect.y = 1151;
        SDL_Rect bullet_Rect = {monster->dstrect.x + 35, monster->dstrect.y, 50, 50};
        bullet->dstrect = bullet_Rect;
    }
    if(monster->dstrect.x == 300 && monster->dstrect.y == 1151){
        monster->dstrect.y = 1150;
        SDL_Rect bullet_Rect = {monster->dstrect.x + 15, monster->dstrect.y, 50, 50};
        bullet->dstrect = bullet_Rect;
    }
    if (monster->dstrect.x >=300 && monster->dstrect.x < 1651 && monster->dstrect.y == 1150){
        monster->dstrect.x += monster->speed / 100;
        bullet->dstrect.y -= bullet->speed / 200;
    }
    if (monster->dstrect.x >300 && monster->dstrect.x <= 1650 && monster->dstrect.y == 1151){
        monster->dstrect.x -= monster->speed / 100;
        bullet->dstrect.y -= bullet->speed / 200;
    } 
    if (SDL_HasIntersection(&bullet->dstrect, &wall->bound[5])){
        bullet->dstrect.w = 0;
    }
}

bool create_bullets(r_bullet *bullet, bool spawn_bullet){
    if(spawn_bullet == 0){
        SDL_Rect bullet_box = {200, 100, 100, 100};
    
    for(int i = 0; i < 5; i++){
        bullet_box.x += 300;
        bullet->bound[i] = bullet_box;
    }
    bullet_box.x = 50;
    bullet_box.y = 1300;
    for(int j = 5; j < 10; j++){
        bullet_box.x += 300;
        bullet_box.h = 99;
        bullet->bound[j] = bullet_box;
    }
        bullet->speed = 1000;
        spawn_bullet = true;
    }
    for(int k = 0; k < 10; k++){
        if(bullet->bound[k].h == 99  ){
            bullet->bound[k].y -= bullet->speed / 30;
        }else if(bullet->bound[k].h == 100){
            bullet->bound[k].y += bullet->speed / 30;
        }
        if(bullet->bound[k].y < 100){
            bullet->bound[k].h = 100;
        }else if(bullet->bound[k].y > 1300 ){
            bullet->bound[k].h = 99;
        }
    }
    return spawn_bullet;
}
