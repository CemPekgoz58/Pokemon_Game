#include "structs.h"
#include <stdio.h>
int main()
{
    Type Types[TYPE_CO];
    Move Moves[MOVE_CO];
    Pokemon Pokemons[POKE_CO];
    Player Player1, Player2;

    initialize(Types, Moves, Pokemons, &Player1, &Player2);
    game(&Player1, &Player2);

}
int main()
{
    printf("Pokemon Game başladı!\n");
    return 0;
}
