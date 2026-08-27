##
## EPITECH PROJECT, 2023
## Zappy_AI
## File description:
## Trantorian
##

from enum import Enum
from IA.src.utils.string_xor import string_xor
from IA.src.utils.create_map import create_map
from IA.src.utils.index_tab import index_tab
from collections import Counter
import math
import random
import json
import re

class Direction(Enum):
    NORTH = 1
    NW = 2
    WEST = 3
    SW = 4
    SOUTH = 5
    SE = 6
    EAST = 7
    NE = 8

RSRC = ["food", "linemate", "deraumere", "sibur", "mendiane", "phiras", "thystame"]

LEVEL = {
    1: {"player": 1, "linemate": 1, "deraumere": 0, "sibur": 0, "mendiane": 0, "phiras": 0, "thystame": 0},
    2: {"player": 2, "linemate": 1, "deraumere": 1, "sibur": 1, "mendiane": 0, "phiras": 0, "thystame": 0},
    3: {"player": 2, "linemate": 2, "deraumere": 0, "sibur": 1, "mendiane": 0, "phiras": 2, "thystame": 0},
    4: {"player": 4, "linemate": 1, "deraumere": 1, "sibur": 2, "mendiane": 0, "phiras": 1, "thystame": 0},
    5: {"player": 4, "linemate": 1, "deraumere": 2, "sibur": 1, "mendiane": 3, "phiras": 0, "thystame": 0},
    6: {"player": 6, "linemate": 1, "deraumere": 2, "sibur": 3, "mendiane": 0, "phiras": 1, "thystame": 0},
    7: {"player": 6, "linemate": 2, "deraumere": 2, "sibur": 2, "mendiane": 2, "phiras": 2, "thystame": 1}
}

class Trantorian:
    def __init__(self, inventory=None, health=10, level=0, x=0, y=0, running=True, cmd: str = None):
        self.cmd = cmd
        self.running = running
        self.inventory = {"food":0, "linemate":0, "deraumere":0, "sibur":0, "mendiane":0, "phiras":0, "thystame":0}
        self.google_drive = {}
        self.health = health
        self.level = level
        self.x = x
        self.y = y
        self.useless_slot = 0
    
    def get_nb_of_lines(self, data: list) -> int:
        data_len = len(data)
        return int(math.sqrt(data_len))

    def fill_map(self, map: list, data: list) -> list:
        nb = 1
        v = 8
        h = 0
        i = 0
        x = 0
        line = self.get_nb_of_lines(data)

        for j in range(line):
            diff = v - h
            for a in range(nb):
                map[diff][h].append(data[i])
                diff += 1
                i += 1
            nb = (nb + 2)
            h += 1
        return map

    def algorithm(self):
        directions = ["Forward\n", "Right\n", "Left\n", "Take food\n"]
        self.cmd = [random.choice(directions)]

    def find_object(self, map: list, object: str) -> list:
        v = 8
        h = 0
        row_size = self.index_tab(map[v])

        while h < row_size:
            if map[v][h] and object in map[v][h][0]:
                return [v, h]
            for diff in range(v, v - h - 1, -1):
                if map[diff][h] and object in map[diff][h][0]:
                    return [diff, h]
            for diff in range(v, v + h + 1):
                if map[diff][h] and object in map[diff][h][0]:
                    return [diff, h]
            h += 1
        return None
    
    def parse_shared_inventory(self, message):
        client, _, inventory = message.split(";")
        self.shared_inventory[self.client_num] = self.inventory
        self.shared_inventory[client] = json.loads(inventory)
        c = Counter()
        for d in self.shared_inventory:
            if d == 'total':
                continue
            c.update(self.shared_inventory[d])
        self.shared_inventory['total'] = dict(c)
     
    def parse_broadcast(self, message):

        '''message[8] = direction, message[11:] = message 
        message can be "incantation" or "inventory" or "on my way" or "ready"
        inventory : "food: 0, linemate: 0, deraumere: 0, sibur: 0, mendiane: 0, phiras: 0, thystame: 0""'''

        direction = int(message[8])
        message = self.sxor(self.team, bytes.fromhex(message[11:]).decode("utf-8"))
        if "inventory" in message:
            self.parse_shared_inventory(message[9:])
        if "incantation" in message:
            if self.clear_broadcast == 1:
                self.clear_broadcast = 0
                return
            if self.master_incantation >= 1 and int(message.split(";")[0]) > self.client_num:
                self.master_incantation = 0
                self.incantation = 0
                self.step = 0
                return
            if self.step > -1 and self.step < 4 and self.inventory["food"] > 35:
                self.step = 4
                self.commands_list = []
            if self.incantation == 1:
                self.commands_list = self.go_to_broadcast(direction)
        if "on my way" in message and self.master_incantation >= 1:
            self.nb_player_incantation += 1
        if "ready" in message and self.master_incantation >= 1:
            self.master_incantation += 1    

    def parse_look(self, look: str, object : str) -> list:
        data = look.split(",")
        liste = [' '.join(re.split('\W+', d)[1:]) for d in data]
        map = self.create_map()
        map = self.fill_map(map, liste)
        coord = self.find_object(map, object)

        if coord is None:
            directions = ["Forward\n", "Right\n", "Left\n"]
            return [random.choice(directions) for _ in range(3)]
        else:
            coord0 = int(coord[0])
            coord1 = int(coord[1])
            res = []
            if coord0 == 8 and coord1 == 0:
                return ["Take " + object + "\n"]
            else:
                if coord0 < 8:
                    res.append("Left\n")
                    for _ in range(8 - coord0):
                        res.append("Forward\n")
                if coord0 > 8:
                    res.append("Right\n")
                    for _ in range(coord0 - 8):
                        res.append("Forward\n")

                for _ in range(abs(coord1)):
                    res.append("Forward\n")

                res.append("Take " + object + "\n")
                res.append("Inventory\n")
            return res
    
    def get_inventory(self, data: str):
        for char in "[]":
            data = data.replace(char, "")
        data = [item[1:] for item in data.split(",")]
        data[-1] = data[-1][:-1]
        for elem in data:
            if elem:
                key, value = elem.split()
                self.inventory[key] = int(value)
