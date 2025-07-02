import select
import socket
from artificial_intelligence import *
from color import *


class Connection:


    def __init__(self, hostname, port, team):
        print(f"{YELLOW}Arguments: {hostname}, {port}, {team}{RESET}")
        self.team = team
        self.socket = self.connect(hostname, port)
        self.poller = select.poll()
        self.poller.register(self.socket, select.POLLIN | select.POLLOUT)
        self.read_handler = [
            {"keyword": "WELCOME", "function": self.handle_welcome},
            {"keyword": "dead", "function": self.handle_dead},
            {"keyword": "Elevation underway", "function": self.handle_elevation},
            {"keyword": "Current level:", "function": self.handle_current_level},
            {"keyword": "message", "function": self.handle_message},
            {"keyword": "eject", "function": self.handle_eject},
        ]
        self.data_to_write = ""


    def connect(self, hostname, port):
        print(f"{YELLOW}Trying to connect to the server{RESET}")
        sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        sock.connect((hostname, port))
        sock.setblocking(False)
        # sock.sendall(team.encode('utf-8'))
        print(f"{GREEN}Connection succeeded{RESET}")
        return sock


    def read_data(self):
        data = bytearray()
        try:
            while True:
                buffer = self.socket.recv(1024)
                if not buffer:
                    break
                data.extend(buffer)
        except BlockingIOError:
            pass
        return [line for line in data.decode().split("\n") if line]

    def send_data(self, data):
        data += '\n'
        self.socket.sendall(data.encode('utf-8'))

    def poll(self, my_ai: Ai):
        while True:
            events = self.poller.poll(0)
            for fd, event in events:
                if event & select.POLLIN:
                    data = self.read_data()
                    print("Received data from", fd, ":", data)
                    for line in data:
                        find = False
                        for command in self.read_handler:
                            if line[:len(command["keyword"])] == command["keyword"]:
                                command["function"](my_ai, line)
                                find = True
                                break
                        if find == False:
                            print(f"{RED}Cannot find an handler for: " + line + f"{RESET}")


                if event & select.POLLOUT:
                    if my_ai.to_send:
                        self.send_data(my_ai.to_send)
                        my_ai.to_send = ""
                    continue


    def handle_welcome(self, my_ai: Ai, line):
        my_ai.to_send += self.team

    def handle_dead(self, my_ai: Ai, line):
        print(f"{RED}Player is dead !{RESET}")
        self.socket.close()
        exit(0)

    def handle_elevation(self, my_ai: Ai, line):
        pass

    def handle_current_level(self, my_ai: Ai, line):
        my_ai.level = int(line.split("Current level:")[1])
        my_ai.needs_to_lvl_up = REQUIREMENTS[my_ai.level]

    def handle_message(self, my_ai: Ai, line):
        tmp = line.split(",")
        direction = int(tmp.split(" ")[1])
        message = tmp[1][1:]


    def handle_eject(self, my_ai: Ai, line):
        direction = int(line.split(" ")[1])

