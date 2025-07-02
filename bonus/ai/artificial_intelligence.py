import subprocess
#30 bouffes par tête
#à chaque fois qu'on trouve une ressource on l'ajoute à l'inventaire et on la broadcast

LOOTS = ["linemate", "deraumere", "sibur", "mendiane", "phiras", "thystame"]
REQUIREMENTS = {
        1: {"linemate": 1},
        2: {"linemate": 1, "deraumere": 1, "sibur": 1},
        3: {"linemate": 2, "sibur": 1, "phiras": 2},
        4: {"linemate": 1, "deraumere": 1, "sibur": 2, "phiras": 1},
        5: {"linemate": 1, "deraumere": 2, "sibur": 1, "mendiane": 3},
        6: {"linemate": 1, "deraumere": 2, "sibur": 3, "phiras": 1},
        7: {"linemate": 2, "deraumere": 2, "sibur": 2, "mendiane": 2, "phiras": 2, "thystame": 1},
}

class Step:
    CONNECT_TO_TEAM = 0
    CREATE_PLAYERS = 1
    COLLECT = 2


class Ai:
    def __init__(self, binary, hostname, port, team, child):
        self.binary = binary
        self.hostname = hostname
        self.port = port
        self.team = team
        self.is_child = child

        self.id = 0
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
        self.needs_to_lvl_up = REQUIREMENTS[1]
        self.last_look = []
        self.look_is_up_to_date = False
        self.step = Step.CONNECT_TO_TEAM
        self.actions = {
            Step.CONNECT_TO_TEAM: self.connect_to_team,
            Step.CREATE_PLAYERS: self.create_players,
            Step.COLLECT: self.collect,
        }
        self.waiting_response = False
        self.map_size = [0, 0]
        self.response_queue = []


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
            if int(nb_places) != 0:
                print(self.is_child)
                subprocess.Popen(["python3", self.binary, "-h", self.hostname, "-p", str(self.port), "-n", self.team, '-c'])
                self.step = Step.COLLECT
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
            self.step = Step.COLLECT



    def collect(self):
        pass


    def algorithm(self):
        self.actions[self.step]()
