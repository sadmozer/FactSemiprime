
CC		= gcc
CFLAGS	+= -Wall -g
LIBS	= -lgmp
SRC		= FactSemiprime.c

.PHONY: test

all: 
	$(CC) $(SRC) $(CFLAGS) -o test $(LIBS) 