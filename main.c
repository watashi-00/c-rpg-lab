#include <stdio.h>
#include <stdlib.h>

#include "includes/entity.h"

int main(void) {
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