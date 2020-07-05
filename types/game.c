#include "game.h"
#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>
#include <sys/socket.h>
#include <unistd.h>

void game_init(Game* game){
    game->players = (Player*)malloc(MAX_PLAYERS*sizeof(Player));
    game->len_players = 0;
    deck_init(&game->deck);
    card_init(&game->sequence, ACE, SPADES);
    game->thread = (pthread_t*)malloc(sizeof(pthread_t));
    game->ready = false;
    game->new_player = (pthread_mutex_t*)malloc(sizeof(pthread_mutex_t));
}

void game_wait_players(Game* game, int server_sockfd){
    // for now only 2 players
    while (game->len_players < 2) {

        player_init( &game->players[game->len_players], server_sockfd);

        game->len_players++;
    }

}

void game_play(Game* game){
    game_give_n_to_all(game, 14);
    game_send_hand_to_all(game);
}

void game_give_n_to_all(Game* game, size_t n){
    for(size_t player_idx = 0; player_idx < game->len_players; player_idx++){
        Player* player = &game->players[player_idx];
        Hand* hand = player->hand;
        for(size_t card_idx = 0; card_idx < n; card_idx++){
            int err = deck_get(&game->deck, &hand->cards[hand->len_cards]);
            assert(err == 0);
            hand->len_cards++;
        }
    }
}

void game_send_hand_to_all(Game* game){
    for(size_t player_idx = 0; player_idx < game->len_players; player_idx++){
        player_send_hand(&game->players[player_idx]);
    }
}
