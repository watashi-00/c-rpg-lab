#include <stdio.h>
#include <stdlib.h>

typedef struct Entity Entity;

void hit(Entity *this, Entity *other);

struct Entity {
    int life;
    int damage;

    void (*hit_fn)(Entity *this, Entity *other);

};

typedef struct Player {
    char *name;
    Entity *base;

} Player;

Entity *createEntity(int life, int damage) {
    Entity *entity = malloc(sizeof(Entity));

    if (!entity) {
        return NULL;
    }

    *entity = (Entity) {
        .life = life,
        .damage = damage
    };

    return entity;
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
int main(void) {
    printf("Hello, World!\n");
    return 0;
}


void hit(Entity *this, Entity *other) {
    other->life -= this->damage;
}