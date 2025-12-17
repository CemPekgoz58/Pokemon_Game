
#ifndef STRUCTS_H
#define STRUCTS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TYPE_CO 18
#define MOVE_CO 486
#define POKE_CO 1015

#define TYPE_EFF_PER_TYPE 18
#define MOVES_PER_POKE 4
#define TEAM_SIZE 6

typedef enum {
    PHYSICAL,
    SPECIAL
}Category;

typedef struct{
    char attackName[32];
    char defName[32];
    double multiplier;
}TypeEffect;

typedef struct{
    char name[32];
    TypeEffect effects[TYPE_EFF_PER_TYPE];
}Type;

typedef struct{
    char name[64];
    Type type;
    Category category ;
    double power;
}Move;

typedef struct {
    char name[64];
    Type types[2];
    int maxHP;
    int currHp;
    int attack, defense, spAtk, spDef, speed;
    Move moves[MOVES_PER_POKE];
}Pokemon;

typedef struct{
    char name[64];
    Pokemon Pokemons[TEAM_SIZE];
    int currInd;
}Player;


//init.c//
void init(Type Types[],Move Moves[],Pokemon Pokemons[],Player *Player1,Player *Player2);



void initTypes(Type Types[],const char *fileNAME);
void initMoves(Move Moves[],Type Types[], const char *fileNAME);
void initPokemons(Pokemon Pokemons[],Type Types[],Move Moves[], const char *fileNAME);


//game.c//
void game(Player *Player1,Player *Player2);
void roundPlay(Player *Player1,Player *Player2);
void Damage(Player *Player1 ,Player *Player2, int Player1Action,int Player1Choice,int Player2Action,int Player2Choice);


//helpers//
int findTypeIndex(Type Types[],const char *name);
Type getTypeByName(Type Types[],const char *name);
int Alive(Pokemon *poke);
int NextAliveInd(Player *p,int startFrom );

#endif
