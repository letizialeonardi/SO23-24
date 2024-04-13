# variabile cc specifica il compilatore da utilizzare
CC=gcc  
#parametro utilizzato dal compilatore C
CFLAG=-Wall
SRC = $(wildcard *.c)
TAR = $(SRC:.c=)

all: $(TAR)

%: %.c
	$(CC) $(CFLAG)  $< -o $@
