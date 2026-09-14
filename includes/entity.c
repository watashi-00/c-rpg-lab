//
// Created by watashi on 9/14/26.
//

#include "entity.h"

#include <stdio.h>

void hit(Entity *this, Entity *other);
void heal(Entity *this, int quantity);

Entity createEntity(int life, int damage) {
    return (Entity) {
        .health = life,
        .damage = damage,
        .maxHealth = life,
        .hit_fn = hit,
        .heal_fn = heal
    };
}

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

