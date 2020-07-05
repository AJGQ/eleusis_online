#include "card.h"
#include "player.h"
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#define LOCK_PR pthread_mutex_lock(player->players_ready_mutex)
#define UNLOCK_PR pthread_mutex_unlock(player->players_ready_mutex)

void player_init( Player* player
        , int server_sockfd
        , size_t* players_ready
        , pthread_mutex_t* players_ready_mutex){
    player->hand = (Hand*)malloc(sizeof(Hand));
    hand_init(player->hand);
    player->thread = (pthread_t*)malloc(sizeof(pthread_t));
    player->len_socket = sizeof(player->address);
    player->players_ready = players_ready;
    player->players_ready_mutex = players_ready_mutex;
    player->ready = true;
    // in sys/socket.h
    // it populates the client_address and client_len 
    // coming from server_sockfd
    // ... only connects to one at a time
    player->sockfd = accept(
            server_sockfd,
            (struct sockaddr*)&player->address,
            &player->len_socket
            );
}

void player_give_hand(Player* player, Hand* hand){
    player->hand = hand;
}

void* player_wait_ready(void* player_ptr){
    Player* player = (Player*) player_ptr;
    ssize_t nbytes_read;
    char buffer[BUFSIZ];

    while ((nbytes_read = read(player->sockfd, buffer, BUFSIZ)) > 0) {
        printf("received:\n");
        if(buffer[0] == 'r' && !player->ready){ 
            LOCK_PR;
            player->ready = true;
            (*player->players_ready)++;
            UNLOCK_PR;
        }
        write(STDOUT_FILENO, buffer, nbytes_read);
    }

    return NULL;
}

void player_send_hand(Player* player){
    char* buf = (char*)malloc(MAX_HAND*4*sizeof(char));
    size_t len = hand_print(player->hand, buf);
    write(player->sockfd, buf, len);
}
