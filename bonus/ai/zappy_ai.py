from color import *
from parser import *



if __name__ == "__main__":
    try:
        parser = Parser(sys.argv[1:])
        print(f"Hostname: {parser.get_hostname()}")
        print(f"Port: {parser.get_port()}")
        print(f"Team name: {parser.get_name()}")
    except SuccessException:
        sys.exit(0)
    except CriticalException as e:
        print(f"{RED}Error: {e}{RESET}", file=sys.stderr)
        sys.exit(84)
    except Exception as e:
        print(f"{RED}Unexpected error: {e}{RESET}", file=sys.stderr)
        sys.exit(84)
