//
// Created by watashi on 9/14/26.
//

#ifndef GAME_ENTITY_H
#define GAME_ENTITY_H

typedef struct Entity Entity;
typedef struct Player Player;
typedef struct Enemy  Enemy;
typedef enum EntityType EntityType;

enum EntityType {
  PLAYER_ENTITY,
  MOB_ENTITY,
};

struct Entity {
  int health;
  int damage;
  int maxHealth;
  EntityType type;
};

struct Player {
  Entity entity;
};

Entity *createEntity(int life, int damage);



#endif //GAME_ENTITY_H
