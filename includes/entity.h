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

  void (*hit_fn)(Entity *this, Entity *other);
  void (*heal_fn)(Entity *this, int quantity);
};

struct Player {
  Entity base;
  char name[8];
};

struct Enemy {
  Entity base;
  char *name;
};

Enemy   *createEnemy(char *name, int damage, int life);
Player  *createPlayer(char *name);
Entity createEntity(int life, int damage);

#endif //GAME_ENTITY_H
