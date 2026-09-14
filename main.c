#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "includes/entity.h"



typedef struct Player {
    Entity base;
    char name[8];

} Player;

typedef struct Enemy {
    Entity base;
    char *name;
} Enemy;



Player *createPlayer(char *name) {
    Player *player = malloc(sizeof(Player));

    if (!player) {
        return NULL;
    }

    player->base = createEntity(100, 20);

    for (int i = 0; i < 7 && name[i] != '\0'; i++) {
        player->name[i] = name[i];
    }

    player->name[7] = '\0';

    return player;
}

Enemy *createEnemy(char *name, int damage, int life) {
    Enemy *enemy = malloc(sizeof(Enemy));

    if (!enemy) {
        return NULL;
    }

    *enemy = (Enemy) {
        .name = name,
        .base = createEntity(life, damage),
    };

    return enemy;

}
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