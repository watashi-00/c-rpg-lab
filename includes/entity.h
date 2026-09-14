#ifndef GAME_ENTITY_H
#define GAME_ENTITY_H

#include <stdio.h>
#include <stdlib.h>

#define ENTITY_FIELDS(X) \
    X(health, int)       \
    X(maxHealth, int)    \
    X(damage, int)

typedef struct Entity Entity;
typedef struct Player Player;
typedef struct Enemy  Enemy;

typedef enum EntityType {
    PLAYER_ENTITY,
    MOB_ENTITY
} EntityType;

typedef struct EntityVTable {
#define X(field, type) \
    type (*get_##field)(const Entity *self); \
    void (*set_##field)(Entity *self, type val);

    ENTITY_FIELDS(X)
#undef X

    void (*hit)(Entity *self, Entity *other);
    void (*heal)(Entity *self, int quantity);
} EntityVTable;

struct Entity {
    const EntityVTable *vtable;
    EntityType type;

#define X(field, type) type field;
    ENTITY_FIELDS(X)
#undef X
};

struct Player {
    Entity base;
    char name[8];
};

struct Enemy {
    Entity base;
    char *name;
};

Entity  createEntity(int life, int damage);
Player *createPlayer(char *name);
Enemy  *createEnemy(char *name, int damage, int life);

#endif // GAME_ENTITY_H
