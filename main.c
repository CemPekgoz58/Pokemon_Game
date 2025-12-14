<<<<<<< HEAD
#include "structs.h"

int main()
{
    Type Types[TYPE_CO];
    Move Moves[MOVE_CO];
    Pokemon Pokemons[POKE_CO];
    Player Player1, Player2;

    initialize(Types, Moves, Pokemons, &Player1, &Player2);
    game(&Player1, &Player2);

=======
#include <stdio.h>

int main()
{
    printf("Pokemon Game başladı!\n");
>>>>>>> bc35602d5288ffc2aa15763a050283b26c23c7d2
    return 0;
}
