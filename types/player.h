#ifndef PLAYER_H
#define PLAYER_H

#include <netinet/in.h>
#include <pthread.h>
#include <stdlib.h>
#include "card.h"
#include "hand.h"

struct player {
    Hand* hand;
    int sockfd;
    pthread_t* thread;
    struct sockaddr_in address;
    socklen_t len_socket;
};

typedef struct player Player;

void player_init(Player*, int);

void player_give_hand(Player*, Hand*);

void player_send_hand(Player*);

#endif
