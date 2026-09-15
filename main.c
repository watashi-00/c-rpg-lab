#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "includes/entity.h"


static Player rPlayer;
static bool player_defined;
const static Enemy *gEnemy;

void changeName() {
    char player_name[8];

    printf("Enter player name: ");
    scanf("%7s", player_name);

    if (player_defined) {
        char temp_name[8];

        strcpy(temp_name, rPlayer.name);
        strcpy(rPlayer.name, player_name);

        printf("Changed player name: %s -> %s\n", temp_name, player_name);

        return;
    }

    Player *pPlayer = createPlayer(player_name);
    rPlayer = *pPlayer;

    free(pPlayer);
    player_defined = true;

    printf("Player name: %s\n", rPlayer.name);

}

int main(void) {

    while (true) { // core loop
        changeName();

    }
    return 0;
}