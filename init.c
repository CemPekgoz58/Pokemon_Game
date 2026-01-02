#include "structs.h"

static int containsInt(const int arr[], int n, int x) {
    for (int i = 0; i < n; i++) if (arr[i] == x) return 1;
    return 0;
}

int findTypeIndex(Type Types[], const char *name) {
    for (int i = 0; i < TYPE_CO; i++)
        if (strcmp(Types[i].name, name) == 0) return i;
    return -1;
}

Type getTypeByName(Type Types[], const char *name) {
    int idx = findTypeIndex(Types, name);
    if (idx >= 0) return Types[idx];

    Type none;
    strcpy(none.name, "None");
    for (int i = 0; i < TYPE_EFF_PER_TYPE; i++) {
        strcpy(none.effects[i].attackName, "None");
        strcpy(none.effects[i].defName, "None");
        none.effects[i].multiplier = 1.0;
    }
    return none;
}

void initTypes(Type Types[], const char *fileName) {
    FILE *f = fopen(fileName, "r");
    if (!f) exit(1);

    char attack[32], defense[32];
    double mult;

    for (int t = 0; t < TYPE_CO; t++) {
        fscanf(f, "%31s", attack);
        strcpy(Types[t].name, attack);

        for (int e = 0; e < TYPE_EFF_PER_TYPE; e++) {
            fscanf(f, "%31s %lf", defense, &mult);
            strcpy(Types[t].effects[e].attackName, attack);
            strcpy(Types[t].effects[e].defName, defense);
            Types[t].effects[e].multiplier = mult;
        }
    }
    fclose(f);
}

static Category parseCategory(const char *s) {
    if (strcmp(s, "Physical") == 0) return PHYSICAL;
    return SPECIAL;
}

void initMoves(Move Moves[], Type Types[], const char *fileName) {
    FILE *f = fopen(fileName, "r");
    if (!f) exit(1);

    char name[64], typeName[32], catStr[16];
    double power;

    for (int i = 0; i < MOVE_CO; i++) {
        fscanf(f, "%63s %31s %15s %lf", name, typeName, catStr, &power);
        strcpy(Moves[i].name, name);
        Moves[i].type = getTypeByName(Types, typeName);
        Moves[i].category = parseCategory(catStr);
        Moves[i].power = power;
    }
    fclose(f);
}

void initPokemons(Pokemon Pokemons[], Type Types[], Move Moves[], const char *fileName) {
    FILE *f = fopen(fileName, "r");
    if (!f) exit(1);

    char name[64], t1[32], t2[32];
    int hp, atk, def, spA, spD, spe;

    for (int i = 0; i < POKE_CO; i++) {
        fscanf(f, "%63s %31s %31s %d %d %d %d %d %d",
               name, t1, t2, &hp, &atk, &def, &spA, &spD, &spe);

        strcpy(Pokemons[i].name, name);
        Pokemons[i].types[0] = getTypeByName(Types, t1);
        Pokemons[i].types[1] = (strcmp(t2, "-") == 0)
                               ? getTypeByName(Types, "None")
                               : getTypeByName(Types, t2);

        Pokemons[i].maxHP = hp;
        Pokemons[i].currHp = hp;
        Pokemons[i].attack = atk;
        Pokemons[i].defense = def;
        Pokemons[i].spAtk = spA;
        Pokemons[i].spDef = spD;
        Pokemons[i].speed = spe;

        int chosen[MOVES_PER_POKE] = {-1, -1, -1, -1};
        for (int m = 0; m < MOVES_PER_POKE; m++) {
            int r;
            do { r = rand() % MOVE_CO; } while (containsInt(chosen, m, r));
            chosen[m] = r;
            Pokemons[i].moves[m] = Moves[r];
        }
    }
    fclose(f);
}

void init(Type Types[], Move Moves[], Pokemon Pokemons[], Player *Player1, Player *Player2) {
    srand((unsigned)time(NULL));

    initTypes(Types, "types.txt");
    initMoves(Moves, Types, "moves.txt");
    initPokemons(Pokemons, Types, Moves, "pokemon.txt");

    strcpy(Player1->name, "Player1");
    strcpy(Player2->name, "Player2");

    Player1->currInd = 0;
    Player2->currInd = 0;

    int used[POKE_CO] = {0};

    for (int i = 0; i < TEAM_SIZE; i++) {
        int r;
        do { r = rand() % POKE_CO; } while (used[r]);
        used[r] = 1;
        Player1->Pokemons[i] = Pokemons[r];
    }

    for (int i = 0; i < TEAM_SIZE; i++) {
        int r;
        do { r = rand() % POKE_CO; } while (used[r]);
        used[r] = 1;
        Player2->Pokemons[i] = Pokemons[r];
    }
}
