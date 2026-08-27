##
## EPITECH PROJECT, 2023
## B-YEP-400-STG-4-1-zappy-basile.trebus-hamann
## File description:
## index_tab
##

def index_tab(self, array: list) -> int:
    i = 0
    
    for elem in array:
        if elem == []:
            return i
        i += 1
    return i