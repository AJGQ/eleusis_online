#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <arpa/inet.h>
#include <netdb.h> /* getprotobyname */
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

#include <pthread.h>
#include "types/player.h"
#include "types/game.h"

int main(int argc, char **argv) {
    char protoname[] = "tcp";
    struct protoent *protoent;
    int enable = 1;
    int server_sockfd;
    struct sockaddr_in server_address;
    unsigned short server_port = 12345;

    if (argc > 1) {
        // in stdlib.h
        // reads argv[1] in base 10
        server_port = strtol(argv[1], NULL, 10);
    }

    // in netdb.h
    // gets the protoent of tcp
    // protoent represents the protocol info
    protoent = getprotobyname(protoname);
    if (protoent == NULL) {
        perror("getprotobyname");
        exit(EXIT_FAILURE);
    }

    // in sys/socket.h
    // returns a socket descriptor
    // inputs are (IPv4, connection protocol of tcp, tcp)
    server_sockfd = socket(
            AF_INET,
            SOCK_STREAM,
            protoent->p_proto
            /* 0 */
            );
    if (server_sockfd == -1) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    // in sys/socket.h
    // set the server_sockfd as SO_REUSEADDR
    if (setsockopt(server_sockfd, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(enable)) < 0) {
        perror("setsockopt(SO_REUSEADDR) failed");
        exit(EXIT_FAILURE);
    }

    // struct sockaddr_in in netinet/in.h
    server_address.sin_family = AF_INET;
    // hton -> host to network, l -> long, s -> short
    // htonl in arpa/inet.h
    server_address.sin_addr.s_addr = htonl(INADDR_ANY);
    // htons in arpa/inet.h
    server_address.sin_port = htons(server_port);

    // in sys/socket.h
    // "assigning a name to a socket"
    // bind the socket with the server description (family, addr, port)
    // even though the family is the same from the socket
    if (bind(
                server_sockfd,
                (struct sockaddr*)&server_address,
                sizeof(server_address)
            ) == -1
       ) {
        perror("bind");
        exit(EXIT_FAILURE);
    }

    // in sys/socket.h
    // listens for requests with a queu of length 8,
    // ie. can't have 9 or more clients connected
    if (listen(server_sockfd, MAX_PLAYERS) == -1) {
        perror("listen");
        exit(EXIT_FAILURE);
    }
    fprintf(stderr, "listening on port %d\n", server_port);

    Game game;

    game_init(&game);

    //while(1){
        game_wait_players(&game, server_sockfd);
        game_play(&game);
    //}
    
    return EXIT_SUCCESS;
}
