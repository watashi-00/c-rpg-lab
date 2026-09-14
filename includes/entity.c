//
// Created by watashi on 9/14/26.
//

#include "entity.h"

#include <stdio.h>
#include <stdlib.h>

void hit(Entity *this, Entity *other);
void heal(Entity *this, int quantity);

Enemy   *createEnemy(char *name, int damage, int life);
Player  *createPlayer(char *name);

void heal(Entity *this, int quantity) {
    if (this->health >= this->maxHealth) {
        return;
    }

    this->health = this->health + quantity <= this->maxHealth
        ? this->health + quantity
        : this->maxHealth;

    printf("Life : %d\n", this->health);

};

void hit(Entity *this, Entity *other) {
    printf("Other Life : %d\n", other->health);
    printf("This Life : %d\n", this->health);
    other->health -= this->damage;
    printf("Other Life : %d\n", other->health);
    printf("This Life : %d\n", this->health);
}

Entity createEntity(int life, int damage) {
    return (Entity) {
        .health = life,
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