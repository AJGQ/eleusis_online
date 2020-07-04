#ifndef GAME_H
#define GAME_H

#include <stdlib.h>
#include "player.h"
#include "deck.h"

#define MAX_PLAYERS 8

struct game {
    Player* players;
    size_t len_players;
    Deck deck;
    Card sequence;
};

typedef struct game Game;

void game_init(Game*, Player*, size_t);

void game_give_n_to_all(Game*, size_t);

void game_send_hand_to_all(Game*);

#endif
