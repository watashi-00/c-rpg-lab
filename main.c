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
    Entity base;

} Player;

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
int main(void) {

    Player *pP = createPlayer("player");
    Player player   = *pP;
    Player player2  = *pP;
    free(pP);

    player.base.hit_fn(&player.base, &player2.base);

    return 0;
}


void hit(Entity *this, Entity *other) {
    printf("Other Life : %d\n", other->life);
    printf("This Life : %d\n", this->life);
    other->life -= this->damage;
    printf("Other Life : %d\n", other->life);
    printf("This Life : %d\n", this->life);
}