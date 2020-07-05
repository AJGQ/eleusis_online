#include "card.h"
#include "player.h"
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

void player_init(Player* player, int server_sockfd){
    player->hand = (Hand*)malloc(sizeof(Hand));
    hand_init(player->hand);
    player->thread = (pthread_t*)malloc(sizeof(pthread_t));
    player->len_socket = sizeof(player->address);

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

void player_send_hand(Player* player){
    char* buf = (char*)malloc(MAX_HAND*4*sizeof(char));
    size_t len = hand_print(player->hand, buf);
    write(player->sockfd, buf, len);
}
