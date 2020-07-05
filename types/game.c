#include "game.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <sys/socket.h>
#include <unistd.h>

void game_init(Game* game){
    game->players = (Player*)malloc(MAX_PLAYERS*sizeof(Player));
    game->len_players = 0;
    deck_init(&game->deck);
    card_init(&game->sequence, ACE, SPADES);
    game->thread = (pthread_t*)malloc(sizeof(pthread_t));
    game->players_ready = 0;
    game->players_ready_mutex = (pthread_mutex_t*)malloc(sizeof(pthread_mutex_t));
    pthread_mutex_init(game->players_ready_mutex, NULL);
}

void game_wait_players(Game* game, int server_sockfd){
    while (game->players_ready < game->len_players || game->len_players == 0) {

        Player* player = &game->players[game->len_players];
        player_init( player
                , server_sockfd
                , &game->players_ready
                , game->players_ready_mutex);
        game->len_players++;

        LOCK_PR;
        if(game->players_ready == game->len_players - 1
                && game->len_players != 1){
            break;
        }
        UNLOCK_PR;

        if(pthread_create(player->thread, NULL, player_wait_ready, player)){
            fprintf(stderr, "Error creating thread\n");
            exit(EXIT_FAILURE);
        }

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
