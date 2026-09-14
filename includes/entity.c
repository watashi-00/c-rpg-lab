#include "entity.h"

#include <stdio.h>
#include <stdlib.h>

static void entity_hit(Entity *self, Entity *other) {
    printf("Other Life : %d\n", other->health);
    printf("This Life : %d\n", self->health);
    other->health -= self->damage;
    printf("Other Life : %d\n", other->health);
    printf("This Life : %d\n", self->health);
}

static void entity_heal(Entity *self, int quantity) {
    if (self->health >= self->maxHealth) {
        return;
    }

    self->health = self->health + quantity <= self->maxHealth
        ? self->health + quantity
        : self->maxHealth;

    printf("Life : %d\n", self->health);
}

#define X(field, type)                                                       \
    static type impl_get_##field(const Entity *self) {                       \
        return self->field;                                                  \
    }                                                                        \
    static void impl_set_##field(Entity *self, type val) {                   \
        self->field = val;                                                   \
    }

ENTITY_FIELDS(X)
#undef X

static const EntityVTable g_entity_vtable = {
#define X(field, type) \
    .get_##field = impl_get_##field, \
    .set_##field = impl_set_##field,

    ENTITY_FIELDS(X)
#undef X

    .hit = entity_hit,
    .heal = entity_heal
};

Entity createEntity(int life, int damage) {
    return (Entity) {
        .vtable = &g_entity_vtable,
        .health = life,
        .maxHealth = life,
        .damage = damage,
        .type = MOB_ENTITY
    };
}

Player *createPlayer(char *name) {
    Player *player = malloc(sizeof(Player));

    if (!player) {
        return NULL;
    }

    player->base = createEntity(100, 20);
    player->base.type = PLAYER_ENTITY;

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
    enemy->base.type = MOB_ENTITY;

    return enemy;
}