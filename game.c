#include "structs.h"

int Alive(Pokemon *poke) {
    return (*poke).currHp>0;
}

int nextAliveInd(Player *p, int startFrom){
    for(int i=startFrom; i<TEAM_SIZE; i++){
        if((*p).Pokemons[i].currHp>0){
      return i;
        }
    }
        for(int i=0; i<startFrom; i++){
            if((*p).Pokemons[i].currHp>0){
                return i;
            }
            
        }
        return -1;
    }


    static int anyAlive(Player *p){
        for(int i=0; i<TEAM_SIZE; i++){
            if((*p).Pokemons[i].currHp>0){
                return 1;
            }
        }return 0;
    }

    void game(Player *Player1, Player *Player2){
        while(anyAlive(Player1)&&anyAlive(Player2)){
            roundPlay(Player1,Player2);
        }
        if(anyAlive(Player1)){
            printf("%s WINS!!!! \n", (*Player2).name);  
        }else{
            printf("%s WINS!!!! \n", (*Player1).name);
        }
    }
    
    static int askAction(Player *p){
       int x;
       do{
        printf("%s: 1-ATTACK 2-CHANGE POKEMON\n", *p->name);
        scanf("%d", &x);
       } while(x!=1 && x!=2);
       return x;
    }
    
    static int askMoveInd(Pokemon *poke){
        int x;
        printf("1-%s   2-%s\n3-%s. 4-%s\nSELECT A MOVE: ",
        *poke->moves[0].name, *poke->moves[1].name,
        *poke->moves[2].name, *poke->moves[3].name );
    do{
        scanf("%d", &x);
    }
    while (x<1 || x>4);
    return x-1;
    
    }
    static int askPokemonInd(Player *p){
        int x;
        printf("AVAILABLE POKEMONS:\n");
        for(int i=0; i<TEAM_SIZE; i++){
            if(p->Pokemons[i].currHp>0){
                printf("%d-%s  ", i+1, *p->Pokemons[i].name);
            }
        }
        printf("\nSELECT A POKEMON TO SWITCH: ");
        do{
            scanf("%d",&x);
            if (x<1 || x>6)
            {
                continue;
            }
            if (*p->Pokemons[x-1].currHp<=0)x=-1;
            {
                /* code */
            }
            
            
        }
    }

    


static double getMulti(Type moveType,Type defenderType){
    if(strcmp(defenderType.name,"None")==0)return 1.0;
    
    for (int i = 0; i < TYPE_EFF_PER_TYPE; i++)
    {
if (strcmp(moveType.effects[i].defName,defenderType.name)==0){
    return moveType.effects[i].multiplier;
}
    }
    return 1.0;   
}
static double getSTAB(Pokemon *attacker,Move *mv){
    if(strcmp(mv->type.name,attacker->types[0].name)==0)return 1.5;
    if(strcmp(mv->type.name,attacker->types[1].name)==0)return 1.5;
}

static int calculateDamage(Pokemon *att,Pokemon *def,Move *mv){
    double A=(mv->category == PHYSICAL) ? att->attack : att->spAtk;
    double D=(mv->category == PHYSICAL) ? def->defense : def->spDef;
    if (D<=0)D=1;
    double x1=getMulti(mv->type,def->types[0]);
    double x2=getMulti(mv->type,def->types[1]);
    double stab=getSTAB(att,mv);
    double dmg=mv->power*(A/D)*x1*x2*stab;

    int intDmg=(int)(dmg+0,5);
    if(intDmg<1)intDmg=1;
    return intDmg;
}
void applyDamage(Player *Player1, Player *Player2,
                 int Player1Action, int Player1Choice,
                 int Player2Action, int Player2Choice) {
    if (Player1Action == 2) Player1->currInd = Player1Choice;
    if (Player2Action == 2) Player2->currInd = Player2Choice;

    Pokemon *pk1 = &Player1->Pokemons[Player1->currInd];
    Pokemon *pk2 = &Player2->Pokemons[Player2->currInd];

    if (Player1Action == 2 && Player2Action == 2) return;

    int p1First = (pk1->speed >= pk2->speed);
   }

static void doAttack(Player *attP,Player *defP,int moveIndex){
        Pokemon *att = &attP->Pokemons[attP->currInd];
                Pokemon *def = &defP->Pokemons[defP->currInd];
    Move *mv=&att ->moves[moveIndex];

    int dmg=calculateDamage(att,def,mv);
    def->currHp-=dmg;
    printf("%s used %s and dealt %d damage!\n", att->name, mv->name, dmg);
        if (def->currHp <= 0) {
            def->currHp = 0;
            printf("%s fainted!\n", def->name);
        }
    
}   
if(Player1First)
{
if (player1)
{
    /* code */
}
}



