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
    char * maxhp;
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
        {"Shadow Ball", "Ghost", "80"},
        {"Karate Chop", "Fighting", "50"},
        {"Cross Chop", "Fighting", "100"},
        {"Submission", "Fighting", "80"},
        {"Focus Punch", "Fighting", "150"},
        {"Body Slam", "Normal", "85"},
        {"Earthquake", "Ground", "100"},
        {"Blizzard", "Ice", "110"},
        {"Aurora Beam", "Ice", "65"},
        {"Thunder", "Electric", "110"},
        {"Thunderbolt", "Electric", "90"},
        {"Drill Peck", "Flying", "80"},
        {"Thunder Wave", "Electric", "10"},
        {"Fire Spin", "Fire", "35"},
        {"Lick", "Ghost", "30"},
        {"Dream Eater", "Ghost", "Psychic"}


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
        {"Snorlax", "160", "Body Slam", "Hyper Beam", "Earthquake", "Bite", "Normal", "160"},
        {"Gengar", "60", "Lick", "Shadow Ball", "Confusion", "Dream Eater", "Ghost", "60"}
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
    gfx_PrintStringXY("v0.1.2", 0, 230);
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
    randNum = randInt(0, 9);
    Pokemon player1;
    player1.name = pokemon[randNum][0];

    for (int i = 0; i < 10; i++)
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
            player1.maxhp = pokemon[i][1];
        }

    }
    static int player2maxhp, player1maxhp;

    if (randNum == 0)
    {
        gfx_ScaledTransparentSprite_NoClip(blastoise_back, 15, 55, 2, 2);
        player1maxhp = 78;
    }
    else if (randNum == 1)
    {
        gfx_ScaledTransparentSprite_NoClip(charizard_back, 15, 55, 2, 2);
        player1maxhp = 78;
    }
    else if (randNum == 2)
    {
        gfx_ScaledTransparentSprite_NoClip(venusaur_back, 15, 55, 2, 2);
        player1maxhp = 80;
    }
    else if (randNum == 3)
    {
        gfx_ScaledTransparentSprite_NoClip(alakazam_back, 15, 55, 2, 2);
        player1maxhp = 55;
    }
    else if (randNum == 4)
    {
        gfx_ScaledTransparentSprite_NoClip(arcanine_back, 15, 55, 2, 2);
        player1maxhp = 90;
    }
    else if (randNum == 5)
    {
        gfx_ScaledTransparentSprite_NoClip(gyarados_back, 15, 55, 2, 2);
        player1maxhp = 95;
    }
    else if (randNum == 6)
    {
        gfx_ScaledTransparentSprite_NoClip(dragonite_back, 15, 55, 2, 2);
        player1maxhp = 91;
    }
    else if (randNum == 7)
    {
        gfx_ScaledTransparentSprite_NoClip(mewtwo_back, 15, 55, 2, 2);
        player1maxhp = 106;
    }
    else if (randNum == 8)
    {
        gfx_ScaledTransparentSprite_NoClip(snorlax_back, 15, 55, 2, 2);
        player1maxhp = 160;

    }
    else if (randNum == 9)
    {
        gfx_ScaledTransparentSprite_NoClip(gengar_back, 15, 55, 2, 2);
        player1maxhp = 110;
    }

    srandom(rand()%rtc_Time());
    int randNum2;
    randNum2 = randInt(0, 9);
    Pokemon player2;
    player2.name = pokemon[randNum2][0];
    for (int i = 0; i < 10; i++)
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
            player2.maxhp = pokemon[i][1];

        } 
    }

    if(randNum2 == 0)
    {
        gfx_ScaledTransparentSprite_NoClip(blastoise, 180, 5, 2, 2);
        player2maxhp = 78;
    }
    else if (randNum2 == 1)
    {
        gfx_ScaledTransparentSprite_NoClip(charizard, 180, 5, 2, 2);
        player2maxhp = 78;
    }
    else if (randNum2 == 2)
    {
        gfx_ScaledTransparentSprite_NoClip(venusaur, 180, 5, 2, 2);
        player2maxhp = 80;
    }
    else if (randNum2 == 3)
    {
        gfx_ScaledTransparentSprite_NoClip(alakazam, 180, 5, 2, 2);
        player2maxhp = 55;
    }
    else if (randNum2 == 4)
    {
        gfx_ScaledTransparentSprite_NoClip(arcanine, 180, 5, 2, 2);
        player2maxhp = 90;
    }
    else if (randNum2 == 5)
    {
        gfx_ScaledTransparentSprite_NoClip(gyarados, 180, 5, 2, 2);
        player2maxhp = 95;
    }
    else if (randNum2 == 6)
    {
        gfx_ScaledTransparentSprite_NoClip(dragonite, 180, 5, 2, 2);
        player2maxhp = 91;
    }
    else if (randNum2 == 7)
    {
        gfx_ScaledTransparentSprite_NoClip(mewtwo, 180, 5, 2, 2);
        player2maxhp = 106;
    }
    else if (randNum2 == 8)
    {
        gfx_ScaledTransparentSprite_NoClip(snorlax, 180, 5, 2, 2);
        player2maxhp = 160;
    }
    else if (randNum2 == 9)
    {
        gfx_ScaledTransparentSprite_NoClip(gengar, 180, 5, 2, 2);
        player2maxhp = 60;
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
    gfx_PrintStringXY("HP: ", 160, 132);
    gfx_SetColor(2);
    gfx_FillRectangle(180, 132, 120, 8);
    gfx_SetColor(39);
    gfx_FillRectangle(182, 135, 116, 2);

    //Player 2 Box
    gfx_ScaledTransparentSprite_NoClip(dialoguebox, 5, 30, 1, 1);
    gfx_PrintStringXY(("%s", player2.name), 15, 42);
    gfx_PrintStringXY("HP: ", 15, 52);
    gfx_SetColor(2);
    gfx_FillRectangle(35, 52, 120, 8);
    gfx_SetColor(39);
    gfx_FillRectangle(37, 55, 116, 2);


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
        gfx_PrintStringXY("HP: ", 160, 132);
        gfx_SetColor(2);
        gfx_FillRectangle(180, 132, 120, 8);
        gfx_SetColor(39);
        gfx_FillRectangle(182, 135, (int)(116*(atoi(player1.hp)/(float)player1maxhp)), 2);

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
        gfx_PrintStringXY("HP: ", 15, 52);
        gfx_SetColor(2);
        gfx_FillRectangle(35, 52, 120, 8);
        gfx_SetColor(39);
        gfx_FillRectangle(37, 55, (int)(116*(atoi(player2.hp)/(float)player2maxhp)), 2);


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
    for (int i = 0; i < 37; i++)
    {
        if (moves[i][0] == move)
        {
            movedamage = atoi(moves[i][2]);
            movetype = moves[i][1];
        }
    }
    float typedamage;

    char * types[18] = {"Normal", "Fire", "Water", "Electric", "Grass", "Ice", "Fighting", "Poison", "Ground", "Flying", "Psychic", "Bug", "Rock", "Ghost", "Dragon", "Dark", "Steel", "Fairy"};

    float typechart[18][18] = {
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0.5, 0, 1, 1, 0.5, 1},
        {1, 0.5, 0.5, 1, 2, 2, 1, 1, 1, 1, 1, 2, 0.5, 1, 0.5, 1, 2, 1},
        {1, 2, 0.5, 1, 0.5, 1, 1, 1, 2, 1, 1, 1, 2, 1, 0.5, 1, 1, 1},
        {1, 1, 2, 0.5, 0.5, 1, 1, 1, 0, 2, 1, 1, 1, 1, 0.5, 1, 1, 1},
        {1, 0.5, 2, 1, 0.5, 1, 1, 0.5, 2, 0.5, 1, 0.5, 2, 1, 0.5, 1, 0.5, 1},
        {1, 0.5, 0.5, 1, 2, 0.5, 1, 1, 2, 2, 1, 1, 1, 1, 2, 1, 0.5, 1},
        {2, 1, 1, 1, 1, 2, 1, 0.5, 1, 0.5, 0.5, 0.5, 2, 0, 1, 2, 2, 0.5},
        {1, 1, 1, 1, 2, 1, 1, 0.5, 0.5, 1, 1, 1, 0.5, 0.5, 1, 1, 0, 2},
        {1, 2, 1, 2, 0.5, 1, 1, 2, 1, 0, 1, 0.5, 2, 1, 1, 1, 2, 1},
        {1, 1, 1, 0.5, 2, 1, 2, 1, 1, 1, 1, 2, 0.5, 1, 1, 1, 0.5, 1},
        {1, 1, 1, 1, 1, 1, 2, 2, 1, 1, 0.5, 1, 1, 1, 1, 0, 0.5, 1},
        {1, 0.5, 1, 1, 2, 1, 0.5, 0.5, 1, 0.5, 2, 1, 1, 0.5, 1, 2, 0.5, 0.5},
        {1, 2, 1, 1, 1, 2, 0.5, 1, 0.5, 2, 1, 2, 1, 1, 1, 1, 0.5, 1},
        {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 2, 1, 0.5, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 0.5, 0},
        {1, 1, 1, 1, 1, 1, 0.5, 1, 1, 1, 2, 1, 1, 2, 1, 0.5, 1, 0.5},
        {1, 0.5, 0.5, 0.5, 1, 2, 2, 0, 1, 1, 1, 1, 2, 1, 1, 1, 0.5, 2},
        {1, 0.5, 1, 1, 1, 1, 2, 0.5, 1, 1, 1, 1, 1, 1, 2, 2, 0.5, 1}
    };

    for (int i = 0; i < 18; i++)
    {
        if (types[i] == movetype)
        {
            for (int j = 0; j < 18; j++)
            {
                if (types[j] == defender.type)
                {
                    typedamage = typechart[i][j];
                }
            }
        }
    }

    int damage = (((2*100)/5 + 2) * movedamage)/200 * typedamage;
    return damage;
}
