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
    Player *pP      = createPlayer("player");
    Player player   = *pP;
    Enemy *eP       = createEnemy("enemy", 10, 200);
    Enemy enemy     = *eP;

    free(eP);
    free(pP);

    player.base.vtable->hit(&player.base, &enemy.base);
    enemy.base.vtable->hit(&enemy.base, &player.base);

    enemy.base.vtable->heal(&enemy.base, 10);
    player.base.vtable->heal(&player.base, 5);

    printf("Enemy Health (Getter): %d\n", enemy.base.vtable->get_health(&enemy.base));
    enemy.base.vtable->set_health(&enemy.base, 150);
    printf("Enemy Health (After Setter): %d\n", enemy.base.vtable->get_health(&enemy.base));

    return 0;
}