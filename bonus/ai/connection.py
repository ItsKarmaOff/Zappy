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
        self.buffer = ""  # Buffer for incomplete data


    def connect(self, hostname, port):
        print(f"{YELLOW}Trying to connect to the server{RESET}")
        sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        sock.connect((hostname, port))
        sock.setblocking(False)
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

        self.buffer += data.decode()
        if '\n' not in self.buffer:
            return []
        lines = self.buffer.split('\n')
        self.buffer = lines[-1]
        complete_lines = [line for line in lines[:-1] if line]
        if complete_lines:
            print(f"{MAGENTA}Received data: {complete_lines}{RESET}")
        return complete_lines

    def send_data(self, data):
        data += '\n'
        self.socket.sendall(data.encode('utf-8'))
        print(f"{BLUE}Sent data: [{data[:-1]}]{RESET}")

    def poll(self, my_ai: Ai):
        while True:
            events = self.poller.poll(0)
            for fd, event in events:
                if event & select.POLLIN:
                    data = self.read_data()
                    if not data:
                        continue
                    for line in data:
                        find = False
                        for command in self.read_handler:
                            if line[:len(command["keyword"])] == command["keyword"]:
                                command["function"](my_ai, line)
                                find = True
                                break
                        if line.count('[') == 1 and line.count(']') == 1 and line.count(',') == 6:
                            self.handle_inventory(my_ai, line)
                            find = True
                        elif line.count('[') == 1 and line.count(']') == 1:
                            self.handle_look(my_ai, line)
                            find = True
                        if find == False:
                            print(f"{RED}Cannot find an handler for: " + line + f"{RESET}")

                if event & select.POLLOUT:
                    # my_ai.algo
                    if my_ai.to_send:
                        self.send_data(my_ai.to_send)
                        my_ai.to_send = ""
                    continue


    def handle_welcome(self, my_ai: Ai, line):
        my_ai.to_send += self.team + "\nInventory" + "\nLook"

    def handle_dead(self, my_ai: Ai, line):
        print(f"{RED}Player is dead !{RESET}")
        self.socket.close()
        exit(0)

    def handle_elevation(self, my_ai: Ai, line):
        pass

    def handle_current_level(self, my_ai: Ai, line):
        my_ai.level = int(line.split("Current level:")[1])
        my_ai.needs_to_lvl_up = REQUIREMENTS[my_ai.level]
        my_ai.reset()

    def handle_message(self, my_ai: Ai, line):
        tmp = line.split(",")
        direction = int(tmp.split(" ")[1])
        message = tmp[1][1:]


    def handle_eject(self, my_ai: Ai, line):
        direction = int(line.split(" ")[1])

    def handle_inventory(self, my_ai: Ai, line):
        tmp = line[1:-1].split(",")
        tmp = [item.lstrip() for item in tmp]
        tmp = [item.rstrip() for item in tmp]
        for item in tmp:
            key, value = item.split(" ")
            my_ai.inventory[key] = int(value)
        print(f"{GREEN}Inventory updated !{RESET}")

    def handle_look(self, my_ai: Ai, line):
        tmp = line[1:-1].split(",")
        tmp = [item.lstrip() for item in tmp]
        tmp = [item.rstrip() for item in tmp]

        my_ai.look = [[] for _ in range(len(tmp))]
        for case_index, items in enumerate(tmp):
            for item in items.split(" "):
                if item:
                    my_ai.look[case_index].append(item)

        print(f"{GREEN}Look command updated: {my_ai.look}{RESET}")
        pass
