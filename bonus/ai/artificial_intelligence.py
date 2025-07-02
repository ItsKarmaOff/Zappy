from enum import Enum, auto


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

class State(Enum):
    TEAM = auto()
    IDLE = auto()
    CHECKING_FOOD = auto()
    SEARCHING_FOOD = auto()
    PROCESSING_LOOK = auto()
    TAKING_FOOD = auto()
    WAITING = auto()

class Ai:
    def __init__(self, team):
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
        self.state = State.TEAM

    def algo(self):
        if self.to_send:
            return
        if self.state == State.TEAM or self.state == State.WAITING:
            return
        if self.state == State.IDLE:
            self.to_send = "Inventory"
            self.state = State.WAITING

        elif self.state == State.SEARCHING_FOOD:
            self.to_send = "Look"
            self.state = State.WAITING

        elif self.state == State.PROCESSING_LOOK:
            food_index = -1
            for case, items in enumerate(self.look):
                if "food" in items:
                    food_index = case
                    break
            if food_index == -1:
                self.to_send = "Forward"
                self.state = State.WAITING
            if food_index == 0:
                self.to_send = "Take food"
                self.state = State.WAITING
            else:
                self.navigate_to_food(food_index)
                self.state = State.WAITING

    def navigate_to_food(self, food_index):
        if food_index < 0 or food_index >= len(self.look):
            return
        pass
