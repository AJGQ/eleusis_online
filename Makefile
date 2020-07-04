LIBS = -pthread

FLAGS = -O2 -Wall -Wextra
FLAGS_DEBUG = -g -O0 -Wall -Wextra

AUX = types/*.c

all: 
	gcc $(FLAGS) $(LIBS) -o server server.c $(AUX)


clean:
	rm server
