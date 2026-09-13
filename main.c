#include <stdio.h>
#include <stdlib.h>

typedef struct Entity Entity;

void hit(Entity *this, Entity *other);
void heal(Entity *this, int quantity);

struct Entity {
    int life;
    int damage;

    void (*hit_fn)(Entity *this, Entity *other);
    void (*heal_fn)(Entity *this, int quantity);
};

typedef struct Player {
    Entity base;
    char *name;

} Player;

typedef struct Enemy {
    Entity base;
    char *name;
} Enemy;

Entity createEntity(int life, int damage) {
    return (Entity) {
        .life = life,
        .damage = damage,
        .hit_fn = hit,
    };
}

Player *createPlayer(char *name) {
    Player *player = malloc(sizeof(Player));

    if (!player) {
        return NULL;
    }

    *player = (Player) {
        .name = name,
        .base = createEntity(100, 20),
    };

    return player;
}

Enemy *createEnemy(char *name, int damage, int life) {
    Enemy *enemy = malloc(sizeof(Enemy));

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

    player.base.hit_fn(&player.base, &player2.base);

    return 0;
}


void heal(Entity *this, int quantity) {
    if (this->life >= 100) {
        return;
    }

    this->life = this->life + quantity <= 100
        ? this->life + quantity
        : 100;

};

void hit(Entity *this, Entity *other) {
    printf("Other Life : %d\n", other->life);
    printf("This Life : %d\n", this->life);
    other->life -= this->damage;
    printf("Other Life : %d\n", other->life);
    printf("This Life : %d\n", this->life);
}