#include <stdio.h>





















//init.c//
void init(Type Types[],Move Moves[],Pokemon Pokemons[],Player *Player1,Player *Player2);
void initTypes(Type Types[],const char *fileNAME);
void initMoves(Move Moves[],Type Types[], const char *fileNAME);
void initPokemons(Pokemon Pokemons[],Type Types[],Move Moves[], const char *fileNAME);


//game.c//


void game(Player *Player1,Player *Player2);


