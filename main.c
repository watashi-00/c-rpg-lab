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


Player *createPlayer(char *name) {
    Player *player = malloc(sizeof(Player));

    if (!player) {
        return NULL;
    }

    *player = (Player) {
        .name = name,
        .base = NULL,
    };

    return player;
}
int main(void) {
    printf("Hello, World!\n");
    return 0;
}
