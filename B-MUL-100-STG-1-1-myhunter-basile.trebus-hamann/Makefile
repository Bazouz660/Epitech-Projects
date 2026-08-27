##
## EPITECH PROJECT, 2021
## MAKEFILE
## File description:
## makefile my_hunter
##

SRC	=	sources/*.c

NAME	=	my_hunter

all:
	gcc -o $(NAME) -g $(SRC) -I C:/CSFML/include -L C:/CSFML/lib/gcc -lcsfml-graphics -lcsfml-audio -lcsfml-system -lcsfml-window -lm

clean:
	rm -f *.o
	rm -f *~
	rm -f *#

fclean: clean
	rm -f $(NAME)

re: fclean all