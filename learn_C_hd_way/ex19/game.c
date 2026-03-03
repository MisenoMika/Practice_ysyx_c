#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "newgame.h"
#include "object.h"

int main(int argc, char *argv[])
{
    srand(time(NULL));
    Game* game = NEW(Game, "Minotaur Adventure");

    while(game->is_running) {
        game_update(game);
    }

    return 0;
}