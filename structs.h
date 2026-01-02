#ifndef STRUCTS_H
#define STRUCTS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/* Constants */
#define TYPE_CO 19
#define MOVE_CO 486
#define POKE_CO 1015
#define TYPE_EFF_PER_TYPE 18
#define MOVES_PER_POKE 4
#define TEAM_SIZE 6

/* Enums */
typedef enum { PHYSICAL, SPECIAL } Category;

/* Type Effect */
typedef struct {
    char attackName[32];
    char defName[32];
    double multiplier;
} TypeEffect;

/* Type */
typedef struct {
    char name[32];
    TypeEffect effects[TYPE_EFF_PER_TYPE];
} Type;

/* Move */
typedef struct {
    char name[64];
    Type type;
    Category category;
    double power;
} Move;

/* Pokemon */
typedef struct {
    char name[64];
    Type types[2];
    int maxHP;
    int currHp;
    int attack, defense, spAtk, spDef, speed;
    Move moves[MOVES_PER_POKE];
} Pokemon;

/* Player */
typedef struct {
    char name[64];
    Pokemon Pokemons[TEAM_SIZE];
    int currInd;
} Player;

/* ================= Initialization ================= */
void init(Type Types[], Move Moves[], Pokemon Pokemons[], Player *Player1, Player *Player2);
void initTypes(Type Types[], const char *fileName);
void initMoves(Move Moves[], Type Types[], const char *fileName);
void initPokemons(Pokemon Pokemons[], Type Types[], Move Moves[], const char *fileName);

/* ================= Game Functions ================= */
void game(Player *Player1, Player *Player2, Type *allTypes);
void roundPlay(Player *Player1, Player *Player2, Type *allTypes);
void applyDamage(Player *Player1, Player *Player2,
                 int Player1Action, int Player1Choice,
                 int Player2Action, int Player2Choice,
                 Type *allTypes);

/* ================= Helper Functions ================= */
int findTypeIndex(Type Types[], const char *name);
Type getTypeByName(Type Types[], const char *name);
int Alive(Pokemon *poke);
int nextAliveInd(Player *p, int startFrom);
int calculateDamage(Pokemon *att, Pokemon *def, Move *mv, Type *types);

#endif
