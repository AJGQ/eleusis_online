#include "card.h"
#include "player.h"
#include <stdlib.h>
#include <fcntl.h>

void player_init(Player* player, int sockfd){
    hand_init(player->hand);
    player->sockfd = sockfd;
}

void player_give_hand(Player* player, Hand* hand){
    player->hand = hand;
}

void player_send_hand(Player* player){
    char* buf = (char*)malloc(MAX_HAND*4*sizeof(char));
    size_t len = hand_print(player->hand, buf);
    write(player->sockfd, buf, len);
}
