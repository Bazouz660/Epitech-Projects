##
## EPITECH PROJECT, 2023
## B-YEP-400-STG-4-1-zappy-basile.trebus-hamann
## File description:
## safecast
##

import logging

def cast_value(val, to_type: type):
    try:
        return to_type(val)
    except:
        logging.critical("Safe cast failed")