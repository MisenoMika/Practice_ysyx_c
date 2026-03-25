#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "newgame.h"
#include "object.h"

Object MonsterProto = {
    .init = Monster_init,
    .attack = Monster_attack
};

Object RoomProto = {
    .init = Room_init,
    .move = Room_move,
    .attack = Room_attack
};

Object MapProto = {
    .init = Map_init,
    .move = Map_move,
    .attack = Map_attack
};

Object GameProto = {
    .init = game_init
};


Command commands[] = {
    {'n', move_north},
    {'s', move_south},
    {'w', move_west},
    {'e', move_east},
    {'a', attack_action},
    {'m', cast_spell},
    {'l', show_commands},
    {-1, game_end}
};

int commands_count = sizeof(commands) / sizeof(Command);

int game_init(void *self) {
    Game *game = self;
    game->map = NULL;
    game->is_running = 1;
    return 1;
}

int game_end(void *self) {
    Game* game = self;
    printf("Giving up? You suck.\n");
    game->is_running = 0;
    return 0; 
}

void game_update(Game* game) {
    Map *a_map = NEW(Map, "The Hall of the Minotaur.");
    game->map = a_map;
    
    printf("You enter the ");
    game->map->location->_(describe)(game->map->location);
    
    while(game->is_running && process_input(game, commands, commands_count)) {
    }
}

int move_north(void *self) {
    Game *game = self;
    return Map_move(game->map, NORTH) != NULL;
}

int move_south(void *self) {
    Game *game = self;
    return Map_move(game->map, SOUTH) != NULL;
}

int move_east(void *self) {
    Game *game = self;
    return Map_move(game->map, EAST) != NULL;
}

int move_west(void *self) {
    Game *game = self;
    return Map_move(game->map, WEST) != NULL;
}

int attack_action(void *self) {
    Game *game = self;
    int damage = rand() % 4;
    return Map_attack(game->map, damage);
}

int cast_spell(void *self) {
    printf("You cast a spell... but nothing happens.\n");
    return 1;
}

int show_commands(void *self) {
    printf("You can:\n");
    for(int i = 0; i < commands_count; i++) {
        printf("%c\n", commands[i].key);
    }
    return 1;
}

int Monster_init(void *self) {
    Monster *monster = self;
    monster->hit_points = 10;
    return 1;
}

int Monster_attack(void *self, int damage) {
    Monster *monster = self;

    printf("You attack %s!\n", monster->_(description));

    monster->hit_points -= damage;

    if(monster->hit_points > 0) {
        printf("It is still alive.\n");
        printf("Hit points left: %d\n", monster->hit_points);
        return 0;
    } else {
        printf("%s is dead!\n", monster->_(description));
        return 1;
    }
}

int Room_init(void *self) {
    Room *room = self;
    room->east = NULL;
    room->west = NULL;
    room->north = NULL;
    room->south = NULL;
    room->bad_guy = NULL;
    return 1;
}

void *Room_move(void *self, Direction direction) {
    Room *room = self;
    Room *next = NULL;

    if(direction == NORTH && room->north) {
        printf("You go north, into:\n");
        next = room->north;
    } else if(direction == SOUTH && room->south) {
        printf("You go south, into:\n");
        next = room->south;
    } else if(direction == EAST && room->east) {
        printf("You go east, into:\n");
        next = room->east;
    } else if(direction == WEST && room->west) {
        printf("You go west, into:\n");
        next = room->west;
    } else {
        printf("You can't go that direction.\n");
        next = NULL;
    }

    if(next) {
        next->_(describe)(next);
    }

    return next;
}

int Room_attack(void *self, int damage) {
    Room *room = self;
    Monster *monster = room->bad_guy;

    if(monster) {
        monster->_(attack)(monster, damage);
        return 1;
    } else {
        printf("You flail in the air at nothing. Idiot.\n");
        return 0;
    }
}

int Map_init(void *self) {
    Map *map = self;

    Room *hall = NEW(Room, "The great Hall");
    Room *throne = NEW(Room, "The throne room");
    Room *arena = NEW(Room, "The arena, with the minotaur");
    Room *kitchen = NEW(Room, "Kitchen, you have the knife now");
    Room *treasure_house = NEW(Room, "Treasure_house filled with WuMengDX\nbut there is a evil WuLiFang");
    arena->bad_guy = NEW(Monster, "The evil minotaur");
    treasure_house->bad_guy = NEW(Monster, "The evil WuLiFANG");

    hall->north = throne;
    hall->south = treasure_house;
    treasure_house->north = hall;
    throne->west = arena;
    throne->east = kitchen;
    throne->south = hall;
    arena->east = throne;
    kitchen->west = throne;

    map->start = hall;
    map->location = hall;

    return 1;
}

void *Map_move(void *self, Direction direction) {
    Map *map = self;
    Room *location = map->location;
    Room *next = NULL;

    next = location->_(move)(location, direction);

    if(next) {
        map->location = next;
    }

    return next;
}

int Map_attack(void *self, int damage) {
    Map* map = self;
    Room *location = map->location;

    return location->_(attack)(location, damage);
}   