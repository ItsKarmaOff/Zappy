import select
import socket
from artificial_intelligence import *
from color import *



class Connection:
    def __init__(self, my_ai: Ai):
        self.my_ai = my_ai
        self.socket = self.connect()
        self.my_ai.id = self.socket
        self.poller = select.poll()
        self.poller.register(self.socket, select.POLLIN | select.POLLOUT)
        self.udp_handler = [
            {"keyword": "dead", "function": self.handle_dead},
            {"keyword": "Current level:", "function": self.handle_current_level},
            {"keyword": "message", "function": self.handle_message},
            {"keyword": "eject", "function": self.handle_eject},
        ]
        self.buffer = ""


    def connect(self):
        print(f"{YELLOW}Trying to connect to the server{RESET}")
        sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        sock.connect((self.my_ai.hostname, self.my_ai.port))
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


    def poll(self):
        while self.my_ai.alive:
            events = self.poller.poll(0)
            for fd, event in events:

                if event & select.POLLIN:
                    response_to_erase = []
                    self.my_ai.response_queue += self.read_data()
                    for line_index in range(len(self.my_ai.response_queue)):
                        for command in self.udp_handler:
                            if self.my_ai.response_queue[line_index][:len(command["keyword"])] == command["keyword"]:
                                command["function"](self.my_ai.response_queue[line_index])
                                break
                        if line.count('[') == 1 and line.count(']') == 1 and line.count(',') == 6:
                            self.handle_inventory(my_ai, line)
                            find = True
                        elif line.count('[') == 1 and line.count(']') == 1:
                            self.handle_look(my_ai, line)
                            find = True
                        if find == False:
                            print(f"{RED}Cannot find an handler for: " + line + f"{RESET}")
                my_ai.algo()
                if event & select.POLLOUT:
                    if my_ai.to_send:
                        self.send_data(my_ai.to_send)
                        my_ai.to_send = ""
                    continue


    def handle_welcome(self, my_ai: Ai, line):
        my_ai.to_send += self.team
        my_ai.state = State.IDLE

    def handle_dead(self, line):
        print(f"{RED}Player is dead !{RESET}")
        self.my_ai.alive = False
        self.socket.close()
        exit(0)

    def handle_elevation(self, line):
        pass

    def handle_current_level(self, line):
        self.my_ai.level = int(line.split("Current level:")[1])
        self.my_ai.needs_to_lvl_up = REQUIREMENTS[self.my_ai.level]
        self.my_ai.reset()

    def handle_message(self, line):
        tmp = line.split(",")
        direction = int(tmp.split(" ")[1])
        message = tmp[1][1:]


    def handle_eject(self, line):
        direction = int(line.split(" ")[1])

    def handle_inventory(self, line):
        tmp = line[1:-1].split(",")
        tmp = [item.lstrip() for item in tmp]
        tmp = [item.rstrip() for item in tmp]
        for item in tmp:
            key, value = item.split(" ")
            self.my_ai.inventory[key] = int(value)
        print(f"{GREEN}Inventory updated !{RESET}")
        my_ai.state = State.SEARCHING_FOOD

    def handle_look(self, line):
        tmp = line[1:-1].split(",")
        tmp = [item.lstrip() for item in tmp]
        tmp = [item.rstrip() for item in tmp]

        self.my_ai.look = [[] for _ in range(len(tmp))]
        for case_index, items in enumerate(tmp):
            for item in items.split(" "):
                if item:
                    self.my_ai.look[case_index].append(item)

        print(f"{GREEN}Look command updated: {my_ai.look}{RESET}")
        my_ai.state = State.PROCESSING_LOOK
        pass
