##
## EPITECH PROJECT, 2023
## B-YEP-400-STG-4-1-zappy-basile.trebus-hamann
## File description:
## Makefile
##

SRV = zappy_server

GUI = zappy_gui

all: srv cli ai

re: re_srv re_cli

ai:
	@make -C IA

srv:
	@make -C server
	@mv server/$(SRV) .

re_srv:
	@make re -C server
	@mv server/$(SRV) .

cli:
	@make -C gui
	@mv gui/$(GUI) .

re_cli:
	@make re -C gui
	@mv gui/$(GUI) .

clean:
	@make clean -C server
	@make clean -C gui

fclean: clean
	@rm -f $(SRV)
	@rm -f $(GUI)
