#ifndef GAME_H
#define GAME_H

#include <pthread.h>
#include <stdbool.h>
#include <stdlib.h>
#include "player.h"
#include "deck.h"

#define MAX_PLAYERS 8
#define LOCK pthread_mutex_lock(game->new_player)
#define UNLOCK pthread_mutex_unlock(game->new_player)


struct game {
    Player* players;
    size_t len_players;
    Deck deck;
    Card sequence;
    pthread_t* thread;
    bool ready;
    pthread_mutex_t* new_player;
};

typedef struct game Game;

void game_init(Game*);

void game_wait_players(Game*, int);
void game_wait_ready(Game*);

void game_play(Game*);
void game_give_n_to_all(Game*, size_t);

void game_send_hand_to_all(Game*);

#endif
