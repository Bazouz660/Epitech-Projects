##
## EPITECH PROJECT, 2021
## Tower Defence
## File description:
## Makefile
##

SRC	=	src/*.c	\
		src/utils/*.c	\
		src/animations/*.c	\
		src/collisions/*.c	\
		src/inputs/*.c	\
		src/player_attacks/*.c	\
		src/menu/main/draw/*.c	\
		src/menu/main/events/*.c	\
		src/menu/main/init_elements/*.c	\
		src/menu/settings/sound/*.c	\
		src/menu/settings/*.c	\
		src/enemies/*.c	\
		src/enemies/inits/*.c	\
		src/particles/*.c	\
		src/campfires/*.c	\
		src/inits/*.c	\
		src/inventory/*.c	\
		src/map/*.c	\
		src/dialogue/*.c	\
		src/destroy/*.c	\
		src/pause/*.c	\
		src/shop/*.c	\
		src/chests/*.c	\
		src/npc/*.c \

NAME	=	my_rpg

all:
	@gcc -o $(NAME) -g $(SRC) -I include -I C:/CSFML/include -L C:/CSFML/lib/gcc -lcsfml-graphics -lcsfml-audio -lcsfml-system -lcsfml-window -lm

clean:
	@rm -f *.o
	@rm -f *~
	@rm -f *#

fclean: clean
	@rm -f $(NAME)

re: fclean all

exe: re
	@./$(NAME)
