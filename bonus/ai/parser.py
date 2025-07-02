import sys
from exceptions import *



class OptionType:
    NOT_REQUIRED = 0
    HOSTNAME_OPTION = 1 << 0
    PORT_OPTION = 1 << 1
    NAME_OPTION = 1 << 2
    META_OPTION = 1 << 3



class Option:
    def __init__(self, short_name, long_name, argument, description, option_type, function):
        self.short_name = short_name
        self.long_name = long_name
        self.argument = argument
        self.description = description
        self.type = option_type
        self.function = function



class Parser:
    MAX_PORT_NUMBER = 65535


    def __init__(self, argv):
        self._argv = argv
        self._options = [
            Option("h", "hostname", "machine", "The hostname of the server", OptionType.HOSTNAME_OPTION, self.__option_hostname),
            Option("p", "port", "port", "The port of the server", OptionType.PORT_OPTION, self.__option_port),
            Option("n", "name", "name", "The name of the team", OptionType.NAME_OPTION, self.__option_name),
            Option("c", "child", "", "The AI is a child", OptionType.NOT_REQUIRED, self.__option_child),
            Option("H", "help", "", "Display this help message", OptionType.META_OPTION, self.__option_help),
            Option("V", "version", "", "Display the version of the program", OptionType.META_OPTION, self.__option_version),
            Option("A", "authors", "", "Display the authors of the project", OptionType.META_OPTION, self.__option_authors)
        ]
        self._options_found = 0
        self._hostname = ""
        self._port = 0
        self._name = ""
        self._child = False

        self.__parse()


    def __parse(self):
        index = 0
        while index < len(self._argv):
            arg = self._argv[index]
            found = False
            for option in self._options:
                if arg == f"-{option.short_name}" or arg == f"--{option.long_name}":
                    index = option.function(index)
                    found = True
                    break
            if not found:
                raise CriticalException(
                    f"Invalid option: \"{arg}\"\nPlease use -H or --help to see the list of available options.")

        for option in self._options:
            if option.type != OptionType.NOT_REQUIRED and option.type != OptionType.META_OPTION:
                if (self._options_found & option.type) == 0:
                    raise CriticalException(
                        f"Missing option: -{option.short_name} or --{option.long_name}")


    def get_hostname(self):
        return self._hostname


    def get_port(self):
        return self._port


    def get_name(self):
        return self._name


    def get_child(self):
        return self._child


    def __option_hostname(self, index):
        if index + 1 >= len(self._argv):
            raise CriticalException(
                "Missing argument for -h (or --hostname) option")

        self._hostname = self._argv[index + 1]
        if not self._hostname or self._hostname.count('.') != 3:
            raise CriticalException(
                "Invalid argument for -h (or --hostname) option, it should be a valid hostname or IP address")

        self._options_found |= OptionType.HOSTNAME_OPTION
        return index + 2


    def __option_port(self, index):
        if index + 1 >= len(self._argv):
            raise CriticalException("Missing argument for -p or --port option")

        try:
            self._port = int(self._argv[index + 1])
        except ValueError:
            raise CriticalException(
                f"Invalid argument for -p (or --port) option, it must be a number between 0 and {self.MAX_PORT_NUMBER}")

        if self._port < 0 or self._port > self.MAX_PORT_NUMBER:
            raise CriticalException(
                f"Invalid argument for -p (or --port) option, it must be a number between 0 and {self.MAX_PORT_NUMBER}")

        self._options_found |= OptionType.PORT_OPTION
        return index + 2


    def __option_name(self, index):
        if index + 1 >= len(self._argv):
            raise CriticalException(
                "Missing argument for -n (or --name) option")

        self._name = self._argv[index + 1]
        if not self._name:
            raise CriticalException(
                "Invalid argument for -n (or --name) option")

        self._options_found |= OptionType.NAME_OPTION
        return index + 2


    def __option_child(self, index):
        self._child = True
        return index + 1


    def __option_help(self, index):
        print("\033[1mUSAGE:\033[0m")
        print(f"\t{sys.argv[0]} -h hostname -p port -n name\n")
        print("\033[1mOPTIONS:\033[0m")

        for option in self._options:
            if option.type != OptionType.META_OPTION:
                print(
                    f"\t-{option.short_name}, --{option.long_name}\t{option.argument}\t\t{option.description}")

        print("\n\033[1mMETA-OPTIONS:\033[0m")
        for option in self._options:
            if option.type == OptionType.META_OPTION:
                print(
                    f"\t-{option.short_name}, --{option.long_name}\t{option.argument}\t\t{option.description}")

        raise SuccessException()


    def __option_version(self, index):
        print("\033[1mVERSION:\033[0m")
        print("\tZappy AI version 1.0.0")
        #print(f"\tBuilt on: {__date__} at {__time__}")
        raise SuccessException()


    def __option_authors(self, index):
        print("\033[1mAUTHORS:\033[0m")
        print("\t\033[3m- Students of EPITECH Nice 2025 -\033[0m")
        print("\tChristophe VANDEVOIR")
        print("\tGianni TUERO")
        print("\tLou PELLEGRINO")
        print("\tNicolas TORO")
        print("\tOlivier POUECH")
        print("\tRaphaël LAUNAY")
        raise SuccessException()
