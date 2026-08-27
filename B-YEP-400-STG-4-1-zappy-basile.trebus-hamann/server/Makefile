##
## EPITECH PROJECT, 2023
## zappy
## File description:
## Makefile
##

SRC := $(shell find $(SOURCEDIR) -name '*.c')

NAME = zappy_server

CFLAGS = -g -W -luuid -I include

OBJ = ${SRC:.c=.o}

%.o: %.c
	@gcc -o $@ -c $< $(CFLAGS)

all: ${OBJ}
	@gcc -o $(NAME) $(OBJ) $(CFLAGS)

clean:
	@rm -f ${OBJ}
	@rm -f *~
	@rm -f *#
	@rm -f vgcore*

fclean: clean
	@rm -f $(NAME)

re: fclean all
