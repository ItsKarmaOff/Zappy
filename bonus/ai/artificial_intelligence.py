import random
import subprocess
#30 bouffes par tête
#à chaque fois qu'on trouve une ressource on l'ajoute à l'inventaire et on la broadcast

LOOTS = ["food", "linemate", "deraumere", "sibur", "mendiane", "phiras", "thystame"]
REQUIREMENTS = {
        1: {"linemate": 1},
        2: {"linemate": 1, "deraumere": 1, "sibur": 1},
        3: {"linemate": 2, "sibur": 1, "phiras": 2},
        4: {"linemate": 1, "deraumere": 1, "sibur": 2, "phiras": 1},
        5: {"linemate": 1, "deraumere": 2, "sibur": 1, "mendiane": 3},
        6: {"linemate": 1, "deraumere": 2, "sibur": 3, "phiras": 1},
        7: {"linemate": 2, "deraumere": 2, "sibur": 2, "mendiane": 2, "phiras": 2, "thystame": 1},
}

TOTAL_REQUIREMENTS = {
    "food": 30,
    "linemate": 9,
    "deraumere": 8,
    "sibur": 10,
    "mendiane": 5,
    "phiras": 6,
    "thystame": 1
}

class Step:
    CONNECT_TO_TEAM = 0
    CREATE_PLAYERS = 1
    LOOK = 2
    COLLECT = 3
    INFORM = 4
    MOVE = 5


class Ai:
    def __init__(self, binary, hostname, port, team, child):
        self.binary = binary
        self.hostname = hostname
        self.port = port
        self.team = team
        self.is_child = child

        self.id = random.randint(100, 999)
        self.alive = True

        self.inventory = {
            "food": 0,
            "linemate": 0,
            "deraumere": 0,
            "sibur": 0,
            "mendiane": 0,
            "phiras": 0,
            "thystame": 0
        }

        self.nb_players_to_fork = 0
        self.to_send = ""
        self.level = 1
        self.step = Step.CONNECT_TO_TEAM
        self.actions = {
            Step.CONNECT_TO_TEAM: self.connect_to_team,
            Step.CREATE_PLAYERS: self.create_players,
            Step.LOOK: self.look,
            Step.COLLECT: self.collect,
            Step.INFORM: self.inform,
            Step.MOVE: self.move
        }
        self.waiting_response = False
        self.map_size = [0, 0]
        self.response_queue = []
        self.last_look = []
        self.last_collect = ""
        self.next_moves = []

    def parse_look(self, line):
        tmp = line[1:-1].split(",")
        tmp = [item.lstrip() for item in tmp]
        tmp = [item.rstrip() for item in tmp]

        look = [[] for _ in range(line.count(",") + 1)]
        for case_index, items in enumerate(tmp):
            for item in items.split(" "):
                if item:
                    look[case_index].append(item)

        return look


    def connect_to_team(self):
        if self.waiting_response == False and len(self.response_queue) != 0:
            self.to_send = self.team
            self.response_queue.pop(0)
            self.waiting_response = True
            return

        if self.waiting_response == True and len(self.response_queue) != 0:
            nb_places = self.response_queue.pop(0)
            if nb_places == "ko":
                print(f"Cannot connect to team {self.team}, no more places available.")
                self.alive = False
                return
            self.step = Step.LOOK
            if int(nb_places) != 0:
                subprocess.Popen(["python3", self.binary, "-h", self.hostname, "-p", str(self.port), "-n", self.team, '-c'])
            if not self.is_child:
                self.nb_players_to_fork = 6 - int(nb_places) - 1
                self.step = Step.CREATE_PLAYERS
            tmp = self.response_queue.pop(0).split(" ")
            self.map_size[0] = int(tmp[0])
            self.map_size[1] = int(tmp[1])
            self.waiting_response = False


    def create_players(self):
        if self.is_child == False and self.nb_players_to_fork > 0 and self.waiting_response == False:
            print(f"Forking a new player, {self.nb_players_to_fork} left to fork.")
            self.to_send = "Fork"
            self.nb_players_to_fork -= 1
            self.waiting_response = True
            return

        elif self.waiting_response == True and len(self.response_queue) != 0:
            print("A new player has been created.")
            subprocess.Popen(["python3", self.binary, "-h", self.hostname, "-p", str(self.port), "-n", self.team, '-c'])
            self.response_queue.pop(0)
            self.waiting_response = False

        if self.is_child or (self.nb_players_to_fork <= 0 and self.waiting_response == False):
            self.step = Step.LOOK



    def look(self):
        if not self.waiting_response:
            self.to_send = "Look"
            self.waiting_response = True

        elif self.waiting_response == True and len(self.response_queue) != 0 and self.last_look == []:
            self.last_look = self.parse_look(self.response_queue.pop(0))
            self.waiting_response = False
            #print(f"{self.id}: Look updated: {self.last_look}")
            self.step = Step.COLLECT
            if "food" in self.last_look[0]:
                return
            elif "food" in self.last_look[2]:
                self.next_moves = ["Forward"]
            elif "food" in self.last_look[1]:
                self.next_moves = ["Forward", "Left", "Forward"]
            elif "food" in self.last_look[3]:
                self.next_moves = ["Forward", "Right", "Forward"]
            else:
                self.next_moves = ["Forward"]


    def get_next_loot(self):
        for loot in self.last_look[0]:
            if loot in LOOTS and self.inventory[loot] < TOTAL_REQUIREMENTS[loot]:
                return loot
        return None


    def collect(self):
        next_loot = self.get_next_loot()
        if next_loot is None and "food" in self.last_look[0]:
            next_loot = "food"

        if not self.waiting_response and next_loot is not None:
            self.to_send = f"Take {next_loot}"
            self.last_look[0].remove(next_loot)
            self.last_collect = next_loot
            self.waiting_response = True
            return

        elif not self.waiting_response and next_loot is None:
            self.step = Step.MOVE
            return

        elif self.waiting_response and len(self.response_queue) != 0:
            response = self.response_queue.pop(0)
            if response == "ok":
                self.inventory[self.last_collect] += 1
                print(f"Collected {self.last_collect}, inventory: {self.inventory}")
                if self.last_collect != "food":
                    self.step = Step.INFORM
            self.waiting_response = False


    def inform(self):
        if not self.waiting_response:
            self.to_send = f"Broadcast {self.team}:{self.last_collect}"
            self.waiting_response = True
            return

        elif self.waiting_response and len(self.response_queue) != 0:
            self.response_queue.pop(0)
            self.waiting_response = False
            self.step = Step.COLLECT
            self.last_collect = ""


    def move(self):
        if not self.waiting_response and len(self.next_moves) == 0:
            self.last_look = []
            self.step = Step.LOOK
            return

        elif not self.waiting_response and self.next_moves:
            self.to_send = self.next_moves.pop(0)
            self.waiting_response = True
            return

        elif self.waiting_response and len(self.response_queue) != 0:
            self.response_queue.pop(0)
            self.waiting_response = False
            if len(self.next_moves) > 0:
                self.step = Step.COLLECT


    def algorithm(self):
        self.actions[self.step]()
