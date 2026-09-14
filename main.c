#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Entity Entity;

void hit(Entity *this, Entity *other);
void heal(Entity *this, int quantity);

struct Entity {
    int life;
    int damage;
    int maxHealth;

    void (*hit_fn)(Entity *this, Entity *other);
    void (*heal_fn)(Entity *this, int quantity);
};

typedef struct Player {
    Entity base;
    char name[8];

} Player;

typedef struct Enemy {
    Entity base;
    char *name;
} Enemy;

Entity createEntity(int life, int damage) {
    return (Entity) {
        .life = life,
        .damage = damage,
        .maxHealth = life,
        .hit_fn = hit,
        .heal_fn = heal
    };
}

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


void heal(Entity *this, int quantity) {
    if (this->life >= this->maxHealth) {
        return;
    }

    this->life = this->life + quantity <= this->maxHealth
        ? this->life + quantity
        : this->maxHealth;

    printf("Life : %d\n", this->life);

};

void hit(Entity *this, Entity *other) {
    printf("Other Life : %d\n", other->life);
    printf("This Life : %d\n", this->life);
    other->life -= this->damage;
    printf("Other Life : %d\n", other->life);
    printf("This Life : %d\n", this->life);
}