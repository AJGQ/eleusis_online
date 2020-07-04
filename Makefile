LIBS = -pthread

FLAGS = -O2 -Wall -Wextra
FLAGS_DEBUG = -g -Wall -Wextra

AUX = types/*.c

all: 
	gcc $(FLAGS) $(LIBS) -o server server.c $(AUX) &&	\
	gcc $(FLAGS) $(LIBS) -o client client.c


clean:
	rm server
