##
## EPITECH PROJECT, 2021
## B-MUL-100-STG-1-1-myrunner-basile.trebus-hamann
## File description:
## Makefile
##

SRC	=	sources/*.c

NAME	=	my_runner

all:
	@gcc -o $(NAME) -g $(SRC) -I C:/CSFML/include -L C:/CSFML/lib/gcc -lcsfml-graphics -lcsfml-audio -lcsfml-system -lcsfml-window -lm

clean:
	@rm -f *.o
	@rm -f *~
	@rm -f *#

fclean: clean
	@rm -f $(NAME)

re: fclean all

exe: re
	@./$(NAME) map

exe2: re
	@./$(NAME) map2