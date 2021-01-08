#ifndef MINILIB_H
#define MINILIB_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL_ttf.h"
#include "SDL_mixer.h"

#define NAME_WINDOW "Hello World"

#define WINDOW_X 1024 // width   на самом деле 1024
#define WINDOW_Y 768 // height   на самом деле 768
#define WINDOW_X_FULLSIZE WINDOW_X * 2
#define WINDOW_Y_FULLSIZE WINDOW_Y * 2

#define BACKGROUND 0
#define FLOOR 1
#define CARPET 2
#define ENTRANCE 3
#define PLAYER 4
#define HEDGE 5
#define HOG 6
#define LOSS_SCREEN 7
#define KEY 8 
#define DUNGEON 9
#define HEDGE1 10
#define HOG1 11
#define MONSTER 12
#define BULLET 13
#define NAME 14
#define DUNGEON2 15
#define DUNGEON3 16
#define DUNGEON4 17
#define PLATE 18
#define CREDITS 19
#define WEB 20

typedef struct walls
{
	int count;
	SDL_Rect bound[14];
	SDL_Texture *texture;
}r_walls;

typedef struct bullet
{   
    int speed;
    SDL_Rect bound[10];
    SDL_Texture *texture;
}r_bullet;

typedef struct resources_game {
    SDL_Surface *win_surface;
    SDL_Surface *image;
    int speed; 
    SDL_Rect dstrect;
    SDL_Texture *texture;
    SDL_Surface *surface;
    Mix_Music *music;
}r_game;

void create_window();

void R_TextureFromSurface(r_game *head, SDL_Renderer *rend);
void R_IMG_Load(r_game *head, char *image);
void R_RenderCopy(r_game *head, SDL_Renderer *rend);
void R_SDL_DestroyTexture(r_game *head);
void All_TextureFromSurface(r_game **obj, SDL_Renderer *rend, int size);
void ALL_DestroyTexture(r_game **obj, int size);
void All_RenderCopy(r_game **obj, SDL_Renderer *rend, int size);
bool Wall_Collision(SDL_Rect player, r_walls *barrier);
void R_Walls(r_walls *head, SDL_Renderer *rend);
void C_Wall(r_walls *head, char *image, SDL_Renderer *rend);
void main_hall(r_game **obj, r_walls *wall);
bool player_enter(SDL_Rect player, SDL_Rect entrance);
void hedgehog_level(r_game **obj, r_walls *wall);
void S_Hedgehog(r_game *hedge, r_game *hog, int check);
void monster_level(r_game **obj, r_walls *wall);
void S_Hedgehog1(r_game *hedge1, r_game *hog1, int check);
void print_all_error(void);
void print_error(void);
void monster_spawn(r_game *monster, r_game *bullet, r_walls *wall);
void hack_level(r_game **obj, r_walls *wall);
void end_level(r_game **obj, r_walls *wall);
void r_Bullet(r_bullet *bullet, SDL_Renderer *rend);
bool create_bullets(r_bullet *bullet, bool spawn_bullet);
void C_Bullet(r_bullet *bullet, char *image, SDL_Renderer *rend);
void credit_screen(r_game **credits, SDL_Renderer *rend);
#endif
