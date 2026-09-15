#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "includes/entity.h"


static Player rPlayer;
static bool player_defined;
const static Enemy *gEnemy;

void changeName() {
    char player_name[8];

    printf("Enter player name: ");
    scanf("%s", player_name);

    Player *pPlayer = createPlayer(player_name);
    rPlayer = *pPlayer;

    printf("Player name: %s\n", rPlayer.name);

    free(pPlayer);
    player_defined = true;
}

int main(void) {

    while (true) { // core loop
        if (!player_defined) {
            changeName();
        }

    }
    return 0;
}