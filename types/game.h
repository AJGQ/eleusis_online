#ifndef GAME_H
#define GAME_H

#include <stdlib.h>
#include "player.h"
#include "deck.h"

struct game {
    Player* players;
    size_t len_players;
    Deck deck;
    Card sequence;
};

typedef struct game Game;

void game_init(Game*, Player*, size_t);


#endif
