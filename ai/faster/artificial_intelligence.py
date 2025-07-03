import base64
import random
import subprocess
from color import *
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
    "food": 200,
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
    WAIT_TEAMMATES = 6
    JOIN_TEAM = 7
    DROP_ITEMS = 8
    INCANTATION = 9


class Ai:
    def __init__(self, binary, hostname, port, team, encode, child):
        self.binary = binary
        self.hostname = hostname
        self.port = port
        self.team = team
        self.encode = encode
        self.is_child = child

        self.id = random.randint(100, 999)
        self.alive = True

        self.shared_inventory = {
            "food": 0,
            "linemate": 0,
            "deraumere": 0,
            "sibur": 0,
            "mendiane": 0,
            "phiras": 0,
            "thystame": 0
        }
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
            Step.MOVE: self.move,
            Step.WAIT_TEAMMATES: self.wait_teammates,
            Step.JOIN_TEAM: self.join_team,
            Step.DROP_ITEMS: self.drop_items,
            Step.INCANTATION: self.incantation,
        }
        self.waiting_response = False
        self.map_size = [0, 0]
        self.response_queue = []
        self.last_look = []
        self.last_collect = ""
        self.next_moves = []
        self.players_ready = 0
        self.ready = False
        self.end_level = False
        self.incantating = False

    def algorithm(self):
        self.actions[self.step]()


    def broadcast(self, message):
        tmp = self.team + ":" + message
        if self.encode:
            self.to_send += "Broadcast " + base64.b64encode(tmp.encode('utf-8')).decode('utf-8')
        else:
            self.to_send += "Broadcast " + tmp


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
                subprocess.Popen(["python3", self.binary, "-h", self.hostname, "-p", str(self.port), "-n", self.team, '-c'] + ([] if self.encode else ["-e"]))
            if not self.is_child:
                self.nb_players_to_fork = 6 - int(nb_places) - 1
                self.step = Step.CREATE_PLAYERS
            tmp = self.response_queue.pop(0).split(" ")
            self.map_size[0] = int(tmp[0])
            self.map_size[1] = int(tmp[1])
            TOTAL_REQUIREMENTS["food"] = (40 * 6) * (self.map_size[0] * self.map_size[1]) / 100
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
            subprocess.Popen(["python3", self.binary, "-h", self.hostname, "-p", str(self.port), "-n", self.team, '-c'] + ([] if self.encode else ["-e"]))
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
            elif "food" in self.last_look[2] and "food" in self.last_look[3]:
                self.next_moves = ["Forward", random.choice(["Left", "Right"]), "Forward"]
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
            if loot in LOOTS and self.shared_inventory[loot] < TOTAL_REQUIREMENTS[loot]:
                return loot
        return None


    def collect(self):
        if not self.is_child:
            all_find = True
            for loot in self.shared_inventory:
                if self.shared_inventory[loot] < TOTAL_REQUIREMENTS[loot]:
                    all_find = False
                    break
            if all_find:
                self.step = Step.WAIT_TEAMMATES
                print(f"{GREEN}{self.id}: All items found, waiting for teammates!{RESET}")

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
                if self.last_collect != "food":
                    self.shared_inventory[self.last_collect] += 1
                    self.step = Step.INFORM
                elif self.inventory["food"] == TOTAL_REQUIREMENTS["food"] / 6:
                    self.shared_inventory["food"] += TOTAL_REQUIREMENTS["food"] / 6
                    self.step = Step.INFORM
                    print(f"{GREEN}{self.id}: Find all food, shared inventory updated!{RESET}")
            self.waiting_response = False


    def inform(self):
        if not self.waiting_response:
            self.broadcast(self.last_collect)
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


    def wait_teammates(self):
        if not self.waiting_response and self.last_look == []:
            self.to_send = "Look"
            self.waiting_response = True
            return

        elif not self.waiting_response:
            self.broadcast("here")
            self.waiting_response = True
            return

        elif self.waiting_response and len(self.response_queue) != 0 and self.last_look == []:
            self.last_look = self.parse_look(self.response_queue.pop(0))
            self.waiting_response = False
            #print(f"{self.id}: Look see {self.last_look[0].count('player')} players")
            if self.last_look[0].count("player") >= 6:
                print(f"{self.id}: All teammates are here, let's drop items!")
                self.step = Step.DROP_ITEMS
                self.broadcast("here")
                self.waiting_response = True
            return

        elif self.waiting_response and len(self.response_queue) != 0:
            self.response_queue.pop(0)
            self.waiting_response = False
            self.last_look = []
            return


    def join_team(self):
        if not self.waiting_response and self.next_moves != []:
            self.to_send = self.next_moves[0]
            self.waiting_response = True
            return

        elif self.waiting_response and len(self.response_queue) != 0:
            self.next_moves.pop(0)
            self.response_queue.pop(0)
            self.waiting_response = False
            return


    def get_next_item_to_drop(self):
        for item in LOOTS[1:]:
            if self.inventory[item] > 0:
                return item
        return None


    def drop_items(self):
        next_item_to_drop = self.get_next_item_to_drop()

        if not self.waiting_response and next_item_to_drop is None and not self.ready:
            self.broadcast("ready")
            self.players_ready += 1
            self.ready = True
            self.waiting_response = True

            if self.is_child == False and self.players_ready == 6:
                print(f"{GREEN}{self.id}: All players are ready, starting the incantation!{RESET}")
                self.step = Step.INCANTATION
            return

        if not self.waiting_response and next_item_to_drop is not None:
            self.to_send = f"Set {next_item_to_drop}"
            self.inventory[next_item_to_drop] -= 1
            self.waiting_response = True
            return

        elif self.waiting_response and len(self.response_queue) != 0:
            self.response_queue.pop(0)
            self.waiting_response = False


    def incantation(self):
        if not self.is_child and not self.waiting_response and not self.incantating:
            self.to_send = "Incantation\n" * 6 + "Incantation"
            self.waiting_response = True
            self.incantating = True
            return

        elif self.waiting_response and len(self.response_queue) != 0:
            self.response_queue.pop(0)
            self.waiting_response = False
            return

        if self.level == 8 and not self.end_level:
            print(f"{GREEN}{self.id}: You are level 8 !{RESET}")
            self.end_level = True
