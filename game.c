#include "structs.h"

int Alive(Pokemon *poke) {
    return poke->currHp > 0;
}

int nextAliveInd(Player *p, int startFrom) {
    for (int i = startFrom; i < TEAM_SIZE; i++)
        if (p->Pokemons[i].currHp > 0) return i;
    for (int i = 0; i < startFrom; i++)
        if (p->Pokemons[i].currHp > 0) return i;
    return -1;
}

static int anyAlive(Player *p) {
    for (int i = 0; i < TEAM_SIZE; i++) {
        if (p->Pokemons[i].currHp > 0) {
            return 1; 
        }
    }
    return 0; 
}

static int askAction(Player *p) {
    int x;
    while (1) {
        printf("\n%s, your action (1: Attack, 2: Switch): ", p->name);
        if (scanf("%d", &x) != 1) { // sayı girilmezse buffer'ı temizle
            printf("--- INVALID INPUT! Please enter a number ---\n");
            while(getchar() != '\n'); // buffer temizleme
            continue;
        }
        if (x == 1 || x == 2) return x;
        else {
            printf("--- INVALID CHOICE: %d is not an option! ---\n", x);
        }
    }
}

static int askMoveInd(Pokemon *poke) {
    int x;
    printf("1-%s 2-%s\n3-%s 4-%s\n",
           poke->moves[0].name, poke->moves[1].name,
           poke->moves[2].name, poke->moves[3].name);
    do { scanf("%d", &x); } while (x < 1 || x > 4);
    return x - 1;
}

static int askPokemonInd(Player *p) {
    int x;
    printf("\n============================================\n");
    printf("   %s: CHOOSE YOUR POKEMON\n", p->name);
    printf("============================================\n");
    
    for (int i = 0; i < TEAM_SIZE; i++) {
        if (p->Pokemons[i].currHp > 0) {
            printf("[%d] %-15s | HP: %3d/%3d %s\n", 
                   i + 1, 
                   p->Pokemons[i].name, 
                   p->Pokemons[i].currHp, 
                   p->Pokemons[i].maxHP,
                   (i == p->currInd ? "(Already on Field)" : ""));
        } else {
            printf("[%d] %-15s | FAINTED\n", i + 1, p->Pokemons[i].name);
        }
    }
    
    printf("\nEnter the number of the Pokemon: ");
    do {
        scanf(" %d", &x);
        if (x < 1 || x > 6 || p->Pokemons[x - 1].currHp <= 0) {
            printf("Invalid selection! Choose a conscious Pokemon: ");
        }
    } while (x < 1 || x > 6 || p->Pokemons[x - 1].currHp <= 0);
    
    return x - 1;
}


static double getMulti(Type moveType, Type defenderType) {
    if (strcmp(defenderType.name, "None") == 0) return 1.0;
    for (int i = 0; i < TYPE_EFF_PER_TYPE; i++)
        if (strcmp(moveType.effects[i].defName, defenderType.name) == 0)
            return moveType.effects[i].multiplier;
    return 1.0;
}

static double getSTAB(Pokemon *att, Move *mv) {
    if (strcmp(mv->type.name, att->types[0].name) == 0) return 1.5;
    if (strcmp(mv->type.name, att->types[1].name) == 0) return 1.5;
    return 1.0;
}

int calculateDamage(Pokemon *att, Pokemon *def, Move *mv, Type *types) {
    float A = (mv->category == PHYSICAL) ? (float)att->attack : (float)att->spAtk;
    float D = (mv->category == PHYSICAL) ? (float)def->defense : (float)def->spDef;

    float multiplier1 = getMulti(mv->type, def->types[0]);
    float multiplier2 = getMulti(mv->type, def->types[1]);

    
    float stab = 1.0;
    if (strcmp(mv->type.name, att->types[0].name) == 0 || 
        strcmp(mv->type.name, att->types[1].name) == 0) {
        stab = 1.5;
    }

    float baseDamage = (mv->power * A) / D;
int totalDamage = (int)(baseDamage * multiplier1 * multiplier2 * stab + 0.5f);

    return (totalDamage <= 0) ? 1 : totalDamage;
}

static void doAttack(Player *attP, Player *defP, int moveIndex, Type *allTypes) {
    Pokemon *att = &attP->Pokemons[attP->currInd];
    Pokemon *def = &defP->Pokemons[defP->currInd];
    Move *mv = &att->moves[moveIndex];

    int before = def->currHp;
    // Artik allTypes dizisini buraya gönderiyoruz:
    int dmg = calculateDamage(att, def, mv, allTypes); 

    def->currHp -= dmg;
    if (def->currHp < 0) def->currHp = 0;

    printf("\n%s's %s used %s!\n", attP->name, att->name, mv->name);
    printf("It dealt %d damage! (%s HP: %d/%d -> %d/%d)\n",
           dmg, def->name, before, def->maxHP, def->currHp, def->maxHP);

    if (def->currHp == 0) {
        printf("!!! %s fainted!\n", def->name);
    }
}
void applyDamage(Player *P1, Player *P2, int a1, int choice1, int a2, int choice2, Type *allTypes) {
    // Switch varsa uygula önce
    if (a1 == 2) P1->currInd = choice1;
    if (a2 == 2) P2->currInd = choice2;

    Pokemon *p1 = &P1->Pokemons[P1->currInd];
    Pokemon *p2 = &P2->Pokemons[P2->currInd];

    if (a1 == 1 && a2 == 1) { 
        int move1 = choice1; // move index
        int move2 = choice2; // move index
        if (p1->speed >= p2->speed) {
            doAttack(P1, P2, move1, allTypes);
            if (p2->currHp > 0) doAttack(P2, P1, move2, allTypes);
        } else {
            doAttack(P2, P1, move2, allTypes);
            if (p1->currHp > 0) doAttack(P1, P2, move1, allTypes);
        }
    } else if (a1 == 1 && a2 == 2) {
        doAttack(P1, P2, choice1, allTypes);
    } else if (a1 == 2 && a2 == 1) {
        doAttack(P2, P1, choice2, allTypes);
    }
}

void roundPlay(Player *P1, Player *P2, Type *allTypes) {
    printf("\n=== ACTIVE ===\n");
    printf("%s: %s (HP %d/%d)\n", P1->name,
           P1->Pokemons[P1->currInd].name,
           P1->Pokemons[P1->currInd].currHp,
           P1->Pokemons[P1->currInd].maxHP);

    printf("%s: %s (HP %d/%d)\n\n", P2->name,
           P2->Pokemons[P2->currInd].name,
           P2->Pokemons[P2->currInd].currHp,
           P2->Pokemons[P2->currInd].maxHP);

    int a1 = askAction(P1);
    int a2 = askAction(P2);

    int c1 = (a1 == 1) ? askMoveInd(&P1->Pokemons[P1->currInd])
                        : askPokemonInd(P1);
    int c2 = (a2 == 1) ? askMoveInd(&P2->Pokemons[P2->currInd])
                        : askPokemonInd(P2);

    // Saldırı ve switch uygulaması
    applyDamage(P1, P2, a1, c1, a2, c2, allTypes);

    // Fainted Pokémon kontrolü ve sonraki Pokémon çağrısı
    if (P1->Pokemons[P1->currInd].currHp <= 0) {
        int ni = nextAliveInd(P1, P1->currInd + 1);
        if (ni != -1) {
            P1->currInd = ni;
            printf(">>> Player1 sends out %s!\n", P1->Pokemons[ni].name);
        }
    }
    if (P2->Pokemons[P2->currInd].currHp <= 0) {
        int ni = nextAliveInd(P2, P2->currInd + 1);
        if (ni != -1) {
            P2->currInd = ni;
            printf(">>> Player2 sends out %s!\n", P2->Pokemons[ni].name);
        }
    }
}



void game(Player *P1, Player *P2, Type *allTypes) { 
    while (anyAlive(P1) && anyAlive(P2)) roundPlay(P1, P2, allTypes); 
    if (anyAlive(P1)) printf("%s WINS\n", P1->name);
    else printf("%s WINS\n", P2->name);
}
