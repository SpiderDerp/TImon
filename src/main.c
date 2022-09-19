#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <graphx.h>
#include <keypadc.h>
#include <libload.h>
#include <ti/getcsc.h>
#include "gfx/gfx.h"
#include <sys/util.h>
#include <sys/rtc.h>

typedef struct {
    char * name;
    char * hp;
    char * move1;
    char * move2;
    char * move3;
    char * move4;
    char * type;
    char * speed;
} Pokemon;

void titleScreen();
void generateField(char * moves[][3], char * pokemon[][9]);
void battle(char * moves[][3], char * pokemon[][9]);
int calcDamage(Pokemon defender, char * moves[][3], char * move);

int main(void)
{
    gfx_Begin();

    gfx_SetPalette(global_palette, sizeof_global_palette, 0);


    gfx_SetTransparentColor(0);
    gfx_FillScreen(1);
    gfx_SetTextFGColor(2);


    static char * moves[][3] =
    {
        {"Water Gun", "Water", "40"},
        {"Hydro Pump", "Water", "120"},
        {"Surf", "Water", "95"},
        {"Ice Beam", "Ice", "95"},
        {"Flamethrower", "Fire", "95"},
        {"Fire Blast", "Fire", "120"},
        {"Fly", "Flying", "95"},
        {"Dragon Claw", "Dragon", "80"},
        {"Vine Whip", "Grass", "45"},
        {"Razor Leaf", "Grass", "55"},
        {"Solar Beam", "Grass", "120"},
        {"Frenzy Plant", "Grass", "150"},
        {"Confusion", "Psychic", "50"},
        {"Psybeam", "Psychic", "65"},
        {"Psychic", "Psychic", "90"},
        {"Future Sight", "Psychic", "120"},
        {"Fire Fang", "Fire", "65"},
        {"Bite", "Dark", "60"},
        {"Dragon Rage", "Dragon", "40"},
        {"Aqua Tail", "Water", "90"},
        {"Hyper Beam", "Normal", "150"},
        {"Shadow Ball", "Ghost", "80"}
    };

    static char * pokemon[][9] =
    {
        {"Blastoise", "78", "Water Gun", "Hydro Pump", "Surf", "Ice Beam", "Water", "43"},
        {"Charizard", "78", "Flamethrower", "Fire Blast", "Fly", "Dragon Claw", "Fire", "45"},
        {"Venusaur", "80", "Vine Whip", "Razor Leaf", "Solar Beam", "Frenzy Plant", "Grass", "45"},
        {"Alakazam", "55", "Confusion", "Psybeam", "Psychic", "Future Sight", "Psychic", "90"},
        {"Arcanine", "90", "Fire Fang", "Flamethrower", "Fire Blast", "Bite", "Fire", "55"},
        {"Gyarados", "95", "Bite", "Hydro Pump", "Dragon Rage", "Aqua Tail", "Water", "81"},
        {"Dragonite", "91", "Dragon Rage", "Dragon Claw", "Fly", "Hyper Beam", "Dragon", "81"},
        {"Mewtwo", "106", "Confusion", "Psychic", "Future Sight", "Shadow Ball", "Psychic", "130"},
    };
    rtc_Enable(0);

    titleScreen();
    generateField(moves, pokemon);

    gfx_End();

    return 0;
}

void titleScreen(){
    gfx_FillScreen(2);
    gfx_SetTextFGColor(1);
    gfx_ScaledTransparentSprite_NoClip(timon, 60, 10, 2, 2);
    gfx_PrintStringXY("Press any Key to start", 85, 80);
    gfx_PrintStringXY("Controls:", 130, 120);
    gfx_PrintStringXY("/, x, - and + to select your move", 60, 140);
    gfx_PrintStringXY("2nd to confirm", 110, 160);
    gfx_PrintStringXY("Alpha to go through text boxes", 60, 180);
    gfx_PrintStringXY("Del to return to Main Menu", 80, 200);
    while(!os_GetCSC());
    return;
}

void generateField(char * moves[][3], char * pokemon[][9])
{
    gfx_SetTextFGColor(2);
    gfx_ScaledTransparentSprite_NoClip(battlescene1, 0, 0, 2, 2);
    gfx_TransparentSprite(battlebase, -5, 115);
    gfx_TransparentSprite(battlebase, 160, 70);
    srandom(rtc_Time());
    int randNum;
    randNum = randInt(0, 7);
    Pokemon player1;
    player1.name = pokemon[randNum][0];
    char * string;
    for (int i = 0; i < 8; i++)
    {
        if (strcmp(pokemon[i][0], player1.name) == 0)
        {
            player1.hp = pokemon[i][1];
            player1.move1 = pokemon[i][2];
            player1.move2 = pokemon[i][3];
            player1.move3 = pokemon[i][4];
            player1.move4 = pokemon[i][5];
            player1.type = pokemon[i][6];
            player1.speed = pokemon[i][7];
        }

    }
    if (randNum == 0)
    {
        gfx_ScaledTransparentSprite_NoClip(blastoise_back, 15, 55, 2, 2);
    }
    else if (randNum == 1)
    {
        gfx_ScaledTransparentSprite_NoClip(charizard_back, 15, 55, 2, 2);
    }
    else if (randNum == 2)
    {
        gfx_ScaledTransparentSprite_NoClip(venusaur_back, 15, 55, 2, 2);
    }
    else if (randNum == 3)
    {
        gfx_ScaledTransparentSprite_NoClip(alakazam_back, 15, 55, 2, 2);
    }
    else if (randNum == 4)
    {
        gfx_ScaledTransparentSprite_NoClip(arcanine_back, 15, 55, 2, 2);
    }
    else if (randNum == 5)
    {
        gfx_ScaledTransparentSprite_NoClip(gyarados_back, 15, 55, 2, 2);
    }
    else if (randNum == 6)
    {
        gfx_ScaledTransparentSprite_NoClip(dragonite_back, 15, 55, 2, 2);
    }
    else if (randNum == 7)
    {
        gfx_ScaledTransparentSprite_NoClip(mewtwo_back, 15, 55, 2, 2);
    }

    int randNum2;
    randNum2 = randInt(0, 7);
    Pokemon player2;
    player2.name = pokemon[randNum2][0];
    for (int i = 0; i < 8; i++)
    {
        if (strcmp(pokemon[i][0], player2.name) == 0)
        {
            player2.hp = pokemon[i][1];
            player2.move1 = pokemon[i][2];
            player2.move2 = pokemon[i][3];
            player2.move3 = pokemon[i][4];
            player2.move4 = pokemon[i][5];
            player2.type = pokemon[i][6];
            player2.speed = pokemon[i][7];

        } 
    }
    
    if(randNum2 == 0)
    {
        gfx_ScaledTransparentSprite_NoClip(blastoise, 180, 5, 2, 2);
    }
    else if (randNum2 == 1)
    {
        gfx_ScaledTransparentSprite_NoClip(charizard, 180, 5, 2, 2);
    }
    else if (randNum2 == 2)
    {
        gfx_ScaledTransparentSprite_NoClip(venusaur, 180, 5, 2, 2);
    }
    else if (randNum2 == 3)
    {
        gfx_ScaledTransparentSprite_NoClip(alakazam, 180, 5, 2, 2);
    }
    else if (randNum2 == 4)
    {
        gfx_ScaledTransparentSprite_NoClip(arcanine, 180, 5, 2, 2);
    }
    else if (randNum2 == 5)
    {
        gfx_ScaledTransparentSprite_NoClip(gyarados, 180, 5, 2, 2);
    }
    else if (randNum2 == 6)
    {
        gfx_ScaledTransparentSprite_NoClip(dragonite, 180, 5, 2, 2);
    }
    else if (randNum2 == 7)
    {
        gfx_ScaledTransparentSprite_NoClip(mewtwo, 180, 5, 2, 2);
    }


    gfx_ScaledTransparentSprite_NoClip(dialoguebox, 0, 160, 2, 2);
    //Moves
    gfx_PrintStringXY(("%s\n", player1.move1), 45, 180);
    gfx_PrintStringXY(("%s\n", player1.move2), 200, 180);
    gfx_PrintStringXY(("%s\n", player1.move3), 45, 210);
    gfx_PrintStringXY(("%s\n", player1.move4), 200, 210);

    //Player 1 Box
    gfx_ScaledTransparentSprite_NoClip(dialoguebox, 150, 110, 1, 1);
    gfx_PrintStringXY(("%s\n", player1.name), 160, 122);
    gfx_PrintStringXY("HP: ", 260, 132);
    gfx_PrintStringXY(("%s\n", player1.hp), 280, 132);

    //Player 2 Box
    gfx_ScaledTransparentSprite_NoClip(dialoguebox, 5, 30, 1, 1);
    gfx_PrintStringXY(("%s", player2.name), 15, 42);
    gfx_PrintStringXY("HP: ", 115, 52);
    gfx_PrintStringXY(("%s", player2.hp), 135, 52);

    char * winner;

    //Battle
    while(atoi(player1.hp) > 0 && atoi(player2.hp) > 0) {
        char * player1move;
        kb_key_t key;
        do
        {
            kb_Scan();
            key = kb_Data[6];
            switch (key)
            {
                case kb_Div:
                    player1move = player1.move1;
                    break;
                case kb_Mul:
                    player1move = player1.move2;
                    break;
                case kb_Sub:
                    player1move = player1.move3;
                    break;
                case kb_Add:
                    player1move =  player1.move4;
                    break;
                default:
                    break;
            }

        } while (kb_Data[1] != kb_2nd);
        
        //picks a random move for the opponent
        int random = rand()%4;
        char * player2move = NULL;
        if (random == 0) {
            player2move = player2.move1;
        } else if (random == 1) {
            player2move = player2.move2;
        } else if (random == 2) {
            player2move = player2.move3;
        } else if (random == 3) {
            player2move = player2.move4;
        }

        int damage = calcDamage(player1, moves, player2move);
        if (atoi(player1.hp) - damage < 0)
        {
            damage = atoi(player1.hp);
        }
        sprintf(player1.hp, "%d", atoi(player1.hp) - damage);
        gfx_ScaledTransparentSprite_NoClip(dialoguebox, 150, 110, 1, 1);
        gfx_PrintStringXY(("%s", player1.name), 160, 122);
        gfx_PrintStringXY("HP: ", 260, 132);
        gfx_PrintStringXY(("%s", player1.hp), 280, 132);

        gfx_ScaledTransparentSprite_NoClip(dialoguebox, 0, 160, 2, 2);
        gfx_PrintStringXY(("%s", player2.name), 45, 190);
        gfx_PrintStringXY("used", 45, 200);
        gfx_PrintStringXY(("%s", player2move), 80, 200);
        if(atoi(player1.hp) <= 0){
            winner = "2";
            break;
        }
        do
        {
            kb_Scan();
            key = kb_Data[6];
        } while (!(kb_Data[2] & kb_Alpha));
        damage = calcDamage(player2, moves, player1move);
        if (atoi(player2.hp) - damage < 0)
        {
            damage = atoi(player2.hp);
        }
        sprintf(player2.hp, "%d", atoi(player2.hp) - damage);
        gfx_ScaledTransparentSprite_NoClip(dialoguebox, 5, 30, 1, 1);
        gfx_PrintStringXY(("%s", player2.name), 15, 42);
        gfx_PrintStringXY("HP: ", 115, 52);
        gfx_PrintStringXY(("%s", player2.hp), 135, 52);

        gfx_ScaledTransparentSprite_NoClip(dialoguebox, 0, 160, 2, 2);
        gfx_PrintStringXY(("%s", player1.name), 45, 190);
        gfx_PrintStringXY("used", 45, 200);
        gfx_PrintStringXY(("%s", player1move), 80, 200);
        if(atoi(player2.hp) <= 0){
            winner = "1";
            break;
        }
        while(!os_GetCSC());
        do
        {
            kb_Scan();
            key = kb_Data[6];
        } while (!(kb_Data[2] & kb_Alpha));
        gfx_ScaledTransparentSprite_NoClip(dialoguebox, 0, 160, 2, 2);
        //Moves
        gfx_PrintStringXY(("%s", player1.move1), 45, 180);
        gfx_PrintStringXY(("%s", player1.move2), 200, 180);
        gfx_PrintStringXY(("%s", player1.move3), 45, 210);
        gfx_PrintStringXY(("%s", player1.move4), 200, 210);

    }

    if (strcmp(winner, "2") == 0){
        gfx_ScaledTransparentSprite_NoClip(dialoguebox, 0, 160, 2, 2);
        gfx_PrintStringXY("Your Pokemon Fainted!", 45, 195);
        kb_key_t key;
        do
        {
            kb_Scan();
            key = kb_Data[6];
        } while (kb_Data[1] != kb_Del);
        return;
    }
    else if (strcmp(winner, "1") == 0){
        gfx_ScaledTransparentSprite_NoClip(dialoguebox, 0, 160, 2, 2);
        gfx_PrintStringXY("Your Opponent's Pokemon Fainted!", 45, 195);
        kb_key_t key;
        do
        {
            kb_Scan();
            key = kb_Data[6];
        } while (kb_Data[1] != kb_Del);
        return;
    }
    
}

int calcDamage(Pokemon defender, char * moves[][3], char * move) {
    int movedamage;
    char * movetype;
    for (int i = 0; i < 22; i++)
    {
        if (moves[i][0] == move)
        {
            movedamage = atoi(moves[i][2]);
            movetype = moves[i][1];
        }
    }
    float typedamage;
    if(strcmp(movetype,"Fire") == 0 && strcmp(defender.type,"Grass") == 0) {
        typedamage = 2;
    } else if(strcmp(movetype,"Fire") == 0 && strcmp(defender.type,"Water") == 0) {
        typedamage = 0.5;
    } else if(strcmp(movetype,"Fire") == 0 && strcmp(defender.type,"Fire") == 0) {
        typedamage = 0.5;
    } else if(strcmp(movetype,"Water") == 0 && strcmp(defender.type,"Fire") == 0) {
        typedamage = 2;
    } else if(strcmp(movetype,"Water") == 0 && strcmp(defender.type,"Grass") == 0) {
        typedamage = 0.5;
    } else if(strcmp(movetype,"Water") == 0 && strcmp(defender.type,"Water") == 0) {
        typedamage = 0.5;
    } else if(strcmp(movetype,"Grass") == 0 && strcmp(defender.type,"Water") == 0) {
        typedamage = 2;
    } else if(strcmp(movetype,"Grass") == 0 && strcmp(defender.type,"Fire") == 0) {
        typedamage = 0.5;
    } else if(strcmp(movetype,"Grass") == 0 && strcmp(defender.type,"Grass") == 0) {
        typedamage = 0.5;
    } else if(strcmp(movetype,"Ghost") == 0 && strcmp(defender.type,"Psychic") == 0) {
        typedamage = 2;
    } else if(strcmp(movetype,"Psychic") == 0 && strcmp(defender.type,"Psychic") == 0) {
        typedamage = 0.5;
    } else if(strcmp(movetype,"Dark") == 0 && strcmp(defender.type, "Psychic") == 0) {
        typedamage = 2;
    } else {
        typedamage = 1;
    }

    int damage = (((2*100)/5 + 2) * movedamage)/200 * typedamage;
    return damage;
}
