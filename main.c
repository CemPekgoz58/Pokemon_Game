#include "structs.h"


int main() {
    
    Type *Types = malloc(sizeof(Type) * TYPE_CO);
    Move *Moves = malloc(sizeof(Move) * MOVE_CO);
    Pokemon *Pokemons = malloc(sizeof(Pokemon) * POKE_CO);

    Player Player1, Player2;

    if (!Types || !Moves || !Pokemons) {
        printf("Memory allocation failed!\n");
        return 1;
    }

    init(Types, Moves, Pokemons, &Player1, &Player2);
    game(&Player1, &Player2, Types);

    free(Types);
    free(Moves);
    free(Pokemons);

    return 0;
}

