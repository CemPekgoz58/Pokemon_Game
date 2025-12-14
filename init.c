#include "structs.h"

int findTypeIndex(Type Types[], const char *name)
{
    for (int i = 0; i < TYPE_CO; i++)
    {
        if (strcmp(Types[i].name, name) == 0)
            return i;
    }
    return -1;
}

Type getTypeWithName(Type Types[], const char *name)
{
    int idx = findTypeIndex(Types, name);
    if (idx >= 0)
        return Types[idx];
    Type none;
    strcpy(none.name, "None");
    for (int i = 0; i < TYPE_EFF_PER_TYPE; i++)
    {
        strcpy(none.typeeffects[i].attackName, "None");
        strcpy(none.typeeffects[i].defenseName, Types[i].name); // not super critical
        none.typeeffects[i].multiplier = 1.0;
    }
    return none;
}

void Types(Type Types[], const char *fileName)
{
    FILE *f = fopen(filename, "r");
    if (!f)
    {
        perror("types.txt");
        exit(1);
    }
    char attack[32], defense[32];
    double mult;

    for (int t = 0; t < TYPE_CO; t++)
    {
        if (fscanf(f, "%31s", attack) != 1)
        {
            printf("types parse error\n");
            exit(1);
        }
        strcpy(Types[t].name, attack);

        for (int e = 0; e < TYPE_EFF_PER_TYPE; e++)
        {
            if (fscanf(f, "%31s %lf", defense, &mult) != 2)
            {
                printf("types parse error\n");
                exit(1);
            }
            strcpy(Types[t].typeeffects[e].attackName, attack);
            strcpy(Types[t].typeeffects[e].defenseName, defense);
            Types[t].typeeffects[e].multiplier = mult;
        }
    }
    fclose(f);
}

MoveCategory parseCategory(const char *s)
{
    if (strcmp(s, "Physical") == 0)
        return PHYSICAL;
    return SPECIAL;
}

void Moves(Move Moves[], Type Types[], const char *filename)
{
    FILE *f = fopen(filename, "r");
    if (!f)
    {
        perror("moves.txt");
        exit(1);
    }
    char name[64], typeName[32], catStr[16];
    double power;

    for (int i = 0; i < MOVE_CO; i++)
    {
        fscanf(f, "%63s %31s %15s %lf", name, typeName, catStr, &power);
        strcpy(Moves[i].name, name);
        Moves[i].type = getTypeByName(Types, typeName);
        if (strcmp(catStr, "Physical") == 0)
        {
            Moves[i].category = PHYSICAL;
        }
        else
        {
            Moves[i].category = SPECIAL;
        }
        Moves[i].power = power;
    }
    fclose(f);
}

static int containsInt(const int arr[], int n, int x)
{
    for (int i = 0; i < n; i++)
        if (arr[i] == x)
            return 1;
    return 0;
}

void initializePokemons(Pokemon Pokemons[], Type Types[], Move Moves[], const char *filename)
{
    FILE *f = fopen(filename, "r");
    if (!f)
    {
        perror("pokemon.txt");
        exit(1);
    }

    char name[64], t1[32], t2[32];
    int hp, atk, def, spA, spD, spe;

    for (int i = 0; i < POKE_CO; i++)
    {
        if (fscanf(f, "%63s %31s %31s %d %d %d %d %d %d",
                   name, t1, t2, &hp, &atk, &def, &spA, &spD, &spe) != 9)
        {
            printf("pokemon parse error at line %d\n", i + 1);
            exit(1);
        }

        strcpy(Pokemons[i].name, name);
        Pokemons[i].types[0] = getTypeByName(Types, t1);

        if (strcmp(t2, "-") == 0)
        {
            strcpy(Pokemons[i].types[1].name, "None");
            for (int k = 0; k < TYPE_EFF_PER_TYPE; k++)
            {
                strcpy(Pokemons[i].types[1].typeeffects[k].attackName, "None");
                strcpy(Pokemons[i].types[1].typeeffects[k].defenseName, Types[k].name);
                Pokemons[i].types[1].typeeffects[k].multiplier = 1.0;
            }
        }
        else
        {
            Pokemons[i].types[1] = getTypeByName(Types, t2);
        }

        Pokemons[i].maxHP = hp;
        Pokemons[i].currentHP = hp;
        Pokemons[i].attack = atk;
        Pokemons[i].defense = def;
        Pokemons[i].spAtk = spA;
        Pokemons[i].spDef = spD;
        Pokemons[i].speed = spe;

        // random unique 4 moves
        int chosen[MOVES_PER_POKE];
        for (int m = 0; m < MOVES_PER_POKE; m++)
        {
            int r;
            do
            {
                r = rand() % MOVE_CO;
            } while (containsInt(chosen, m, r));
            chosen[m] = r;
            Pokemons[i].moves[m] = Moves[r];
        }
    }

    fclose(f);
}
