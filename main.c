#include "structs.h"

Type Types[TYPE_CO];
Move Moves[MOVE_CO];
Pokemon Pokemons[POKE_CO];
Player Player1, Player2;

int main() {
    init(Types, Moves, Pokemons, &Player1, &Player2);
    game(&Player1, &Player2, Types); 
    return 0;
}