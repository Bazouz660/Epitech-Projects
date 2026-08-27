##
## EPITECH PROJECT, 2023
## Zappy_AI
## File description:
## client
##

from IA.src.trantorian import Trantorian
import socket
import selectors
import subprocess
from IA.src.utils.safecast import cast_value

class Client() :

    def __init__(self, hostname: str, port: str, team_name: str, client_id: str):
        self.team = team_name
        self.hostname = hostname
        self.port = port
        self.client_num = 0
        self.socket = None
        self.selectors = selectors.DefaultSelector()
        self.ia = Trantorian(self.team)
        self.client_id = int(client_id)
        self.logged = False
        self.just_log = 0

    def connect_to_server(self):
        self.socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.socket.setblocking(False)
        self.socket.connect_ex((self.hostname, cast_value(self.port, int)))
        fd = selectors.EVENT_READ | selectors.EVENT_WRITE
        self.selectors.register(self.socket, fd)

    def close_client(self):
        self.selectors.unregister(self.socket)
        self.socket.close()

    def send_cmd(self):
        """launch the algorithm"""
        if self.logged == True:
            self.ia.algorithm()
        if self.ia.cmd and self.ia.running == True:
            '''print("sending cmd", self.ia.cmd)'''
            if self.ia.cmd == (self.team + '\n') and not self.logged:
                self.just_log = 1
            cmd_string = ''.join(self.ia.cmd)
            self.socket.send(cmd_string.encode())
            self.ia.cmd = ""
            self.ia.running = False

    def init_info(self, cmd):
        self.ia.useless_slot = cast_value(cmd, int)
        self.ia.data_to_write = ""
        self.just_log = 2
        cmd = cmd.split()
        """self.data_width = cast_value(cmd[0], int)
        self.data_height = cast_value(cmd[1], int)"""
        self.ia.data_to_write = ""
        self.just_log = 3
        self.logged = True
        self.ia.run = 1

    def read_serv(self, cmd):
        events = self.selectors.select(timeout=None)
        for key, mask in events:
            if mask & selectors.EVENT_READ:
                data = key.fileobj.recv(1024).decode("utf-8")
            if not data:
                self.close_client()
                print("Server disconnected")
                exit(0)
            else:
                cmd += data
        tmp = cmd.split("\n")
        for elem in tmp[:-1]:
            if "dead" in elem:
                print("Trantorian ", self.client_id, "died")
                exit(0)
            if "WELCOME" in elem and self.logged == False:
                self.ia.cmd = self.team + "\n"
            if self.just_log == 1:
                self.init_info(elem)
            if "Elevation underway" in elem:
                self.ia.cmd = "Incantation\n"
            if "Current level" in elem:
                self.ia.level = cast_value(elem.split()[1], int)
                if self.ia.level == 8:
                    print("Trantorian " + self.client_id + " won")
                    exit(0)
            if "Take" in self.ia.cmd and "food" not in self.ia.cmd and elem == "ok":
                self.ia.cmd = ""
            if self.ia.cmd == "Inventory\n":
                try:
                    self.ia.get_inventory(elem)
                except ValueError:
                    print("Error ", elem)
                    pass
            if self.ia.cmd == "Look\n":
                self.ia.look = elem
            if self.ia.cmd == "Connect_nbr":
                self.ia.useless_slot = cast_value(elem, int)
                if (
                    self.ia.useless_slot != 0
                    and self.client_num < 6
                    and self.ia.fork == True
                    ):
                    subprocess.Popen(
                                [
                                    "python3",
                                    "zappy_ai",
                                    "-p",
                                    self.port,
                                    "-n",
                                    self.team,
                                    "-i",
                                    str(self.client_num + 1),
                                ]
                    )
                self.ia.fork = False
            cmd = cmd.split("\n")[-1]
            self.ia.running = True
        return cmd


    def run_client(self):
        cmd = ""
        while True:
            fd = self.selectors.select(timeout=None)
            for key, mask in fd:
                if mask & selectors.EVENT_READ:
                    cmd = self.read_serv(cmd)
                if mask & selectors.EVENT_WRITE:
                    self.send_cmd()