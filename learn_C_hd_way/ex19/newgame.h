#ifndef __NEWGAME_H__
#define __NEWGAME_H__

#include "object.h"
#include "engine.h"

struct Monster {
    Object proto;
    int hit_points;
};
typedef struct Monster Monster;

int Monster_attack(void *self, int damage);
int Monster_init(void *self);

extern Object MonsterProto;

struct Room {
    Object proto;
    Monster *bad_guy;
    struct Room *north;
    struct Room *south;
    struct Room *east;
    struct Room *west;
};
typedef struct Room Room;

void *Room_move(void *self, Direction direction);
int Room_attack(void *self, int damage);
int Room_init(void *self);

extern Object RoomProto;

struct Map {
    Object proto;
    Room *start;
    Room *location;
};
typedef struct Map Map;

void *Map_move(void *self, Direction direction);
int Map_attack(void *self, int damage);
int Map_init(void *self);

extern Object MapProto;

typedef struct Game {
    Object proto;
    Map* map;
    int is_running;
} Game;

int game_init(void *self);
void game_update(Game* game);
int game_end(void *game);

extern Object GameProto;

int move_north(void *game);
int move_south(void *game);
int move_east(void *game);
int move_west(void *game);
int attack_action(void *game);
int cast_spell(void *game);
int show_commands(void *game);
extern Command commands[];
extern int commands_count;

#endif