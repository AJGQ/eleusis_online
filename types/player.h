#ifndef PLAYER_H
#define PLAYER_H

#include <netinet/in.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include "card.h"
#include "hand.h"

struct player {
    Hand* hand;
    int sockfd;
    pthread_t* thread;
    struct sockaddr_in address;
    socklen_t len_socket;
    size_t* players_ready;
    pthread_mutex_t* players_ready_mutex;
    bool ready;
};

typedef struct player Player;

void player_init( Player* , int , size_t* , pthread_mutex_t*);

void* player_wait_ready(void*);

void player_give_hand(Player*, Hand*);

void player_send_hand(Player*);

#endif
