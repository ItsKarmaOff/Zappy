import select
import socket
from artificial_intelligence import *
from color import *



class Connection:
    def __init__(self, my_ai: Ai):
        self.my_ai = my_ai
        self.socket = self.connect()
        #self.my_ai.id = self.socket.fileno()
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
        #if complete_lines:
        #    if not self.my_ai.is_child:
        #       print(f"{BLUE}{self.my_ai.id}: Received data: {complete_lines}{RESET}")
        #    else:
        #        print(f"{MAGENTA}{self.my_ai.id}: Received data: {complete_lines}{RESET}")
        return complete_lines


    def send_data(self, data):
        data += '\n'
        self.socket.sendall(data.encode('utf-8'))
        #print(f"{BLUE}{self.my_ai.id}: Sent data: [{data[:-1]}]{RESET}")


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
                                response_to_erase.append(line_index)
                                break
                        #if not find:
                        #    print(f"{RED}Cannot find an handler for: " + self.my_ai.response_queue[line_index] + f"{RESET}")
                    for line_index in sorted(response_to_erase, reverse=True):
                        self.my_ai.response_queue.pop(line_index)
                    #print(f"{MAGENTA}{self.my_ai.id}: Response queue: {self.my_ai.response_queue}{RESET}")


                if event & select.POLLOUT:
                    if self.my_ai.to_send:
                        self.send_data(self.my_ai.to_send)
                        self.my_ai.to_send = ""
                    self.my_ai.algorithm()


    def handle_welcome(self, line):
        self.my_ai.to_send += self.team

    def handle_dead(self, line):
        print(f"{RED}{self.my_ai.id}Player is dead !{RESET}")
        self.my_ai.alive = False
        self.socket.close()
        exit(0)

    def handle_elevation(self, line):
        pass

    def handle_current_level(self, line):
        self.my_ai.level = int(line.split("Current level:")[1])
        self.my_ai.step = Step.INCANTATION
        #self.my_ai.needs_to_lvl_up = REQUIREMENTS[self.my_ai.level]


    def handle_message(self, line):
        tmp = line.split(",")
        direction = int(tmp[0].split(" ")[1])
        message = tmp[1][1:]
        if self.my_ai.encode:
            try:
                message = base64.b64decode(message).decode('utf-8')
            except:
                print(f"{RED}{self.my_ai.id}: Failed to decode message: {message}{RESET}")
                return

        if message[:len(self.my_ai.team)] != self.my_ai.team:
            print(f"{YELLOW}{self.my_ai.id}: Received message from the wrong team: {message}{RESET}")
        for loot in LOOTS:
            if loot == message[len(self.my_ai.team) + 1:]:
                if loot != "food":
                    self.my_ai.shared_inventory[loot] += 1
                else:
                    self.my_ai.shared_inventory[loot] += TOTAL_REQUIREMENTS[loot] / 6
                #print(f"{GREEN}{self.my_ai.id}: Shared inventory updated: {loot} + 1{RESET}")
                return
        if message == self.my_ai.team + ":here":
            # if self.my_ai.step != Step.DROP_ITEMS or direction != 0:
            self.my_ai.step = Step.JOIN_TEAM
            if not self.my_ai.next_moves:
                if direction == 0:
                    # print(f"{GREEN}{self.my_ai.id}: I will drop my items!{RESET}")
                    # self.my_ai.step = Step.DROP_ITEMS
                    print(f"{GREEN}{self.my_ai.id}: I'm here")
                elif direction in (2, 1, 8):
                    self.my_ai.next_moves = ["Forward"]
                elif direction in (5, 6, 7):
                    self.my_ai.next_moves = ["Right"]
                else:
                    self.my_ai.next_moves = ["Left"]
        elif message == self.my_ai.team + ":drop":
            self.my_ai.step = Step.DROP_ITEMS
        elif message == self.my_ai.team + ":ready":
            self.my_ai.players_ready += 1
            if not self.my_ai.is_child:
                print(f"{GREEN}{self.my_ai.id}: Player is ready! Total ready players: {self.my_ai.players_ready}{RESET}")
            if self.my_ai.is_child == False and self.my_ai.players_ready >= 6:
                print(f"{GREEN}{self.my_ai.id}: All players are ready, starting the incantation!{RESET}")
                self.my_ai.step = Step.INCANTATION


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

    def handle_look(self, line):
        tmp = line[1:-1].split(",")
        tmp = [item.lstrip() for item in tmp]
        tmp = [item.rstrip() for item in tmp]

        self.my_ai.look = [[] for _ in range(len(tmp))]
        for case_index, items in enumerate(tmp):
            for item in items.split(" "):
                if item:
                    self.my_ai.look[case_index].append(item)

        self.my_ai.look_is_up_to_date = True
        print(f"{GREEN}Look command updated: {self.my_ai.look}{RESET}")
