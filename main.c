#include <stdio.h>
#include <stdlib.h>

typedef struct Entity {
    int life;
    int damage;
} Entity;

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
