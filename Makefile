CC = gcc
CFLAGS = -Wall -Wextra -g

SRC = src/main.c src/audit.c 

target = elevate

all: 
	$(CC) $(CFLAGS) $(SRC) -o $(target)

clean:
	rm -f $(target)
