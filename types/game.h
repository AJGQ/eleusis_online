#ifndef GAME_H
#define GAME_H

#include <pthread.h>
#include <stdbool.h>
#include <stdlib.h>
#include "player.h"
#include "deck.h"

#define MAX_PLAYERS 8
#define LOCK_PR pthread_mutex_lock(game->players_ready_mutex)
#define UNLOCK_PR pthread_mutex_unlock(game->players_ready_mutex)


struct game {
    Player* players;
    size_t len_players;
    Deck deck;
    Card sequence;
    pthread_t* thread;
    size_t players_ready;
    pthread_mutex_t* players_ready_mutex;
};

typedef struct game Game;

void game_init(Game*);

void game_wait_players(Game*, int);
void* game_wait_ready(void*);

void game_play(Game*);
void game_give_n_to_all(Game*, size_t);

void game_send_hand_to_all(Game*);

#endif
