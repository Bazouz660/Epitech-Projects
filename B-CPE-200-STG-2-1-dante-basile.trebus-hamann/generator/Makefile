##
## EPITECH PROJECT, 2021
## Tower Defence
## File description:
## Makefile
##

SRC	=	src/*.c

NAME	=	generator

all:
	@gcc -o $(NAME) $(SRC)

clean:
	@rm -f *.o
	@rm -f *~
	@rm -f *#

fclean: clean
	@rm -f $(NAME)

re: fclean all

exe: re
	@./$(NAME)
