#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "includes/entity.h"


int main(void) {

    Player *pP      = createPlayer("player");
    Player player   = *pP;
    Enemy *eP       = createEnemy("enemy", 10, 200);
    Enemy enemy     = *eP;

    free(eP);
    free(pP);

    player. base.hit_fn(&player.base, &enemy.base);
    enemy.  base.hit_fn(&enemy.base, &player.base);

    enemy.  base.heal_fn(&enemy.base, 10);
    player. base.heal_fn(&player.base, 5);

    return 0;
}