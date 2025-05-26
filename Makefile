##
## EPITECH PROJECT, 2025
## Zappy
## File description:
## The main Makefile of our project to compile all binaries
##



############################ RULES ############################################
.PHONY: all zappy_server zappy_gui zappy_ai debug \
 		clean fclean \
 		re re_debug \
 		unit_tests tests_run \
 		doc
###############################################################################



############################ COMPILATION ######################################

all: zappy_server zappy_gui zappy_ai
	@echo -e "\033[1;32mAll binaires are compiled.\033[0m"

zappy_server:
	@echo -e "\033[1;32mCompiling zappy_server...\033[0m"
	@$(MAKE) -C ./server/ --no-print-directory

zappy_gui:
	@echo -e "\033[1;32mCompiling zappy_gui...\033[0m"
	@$(MAKE) -C ./gui/ --no-print-directory

zappy_ai:
	@echo -e "\033[1;32mCompiling zappy_ai...\033[0m"
	@$(MAKE) -C ./ai/ --no-print-directory

debug:
	@echo -e "\033[1;32mCompiling in debug mode...\033[0m"
	@$(MAKE) -C ./server/ debug --no-print-directory
	@$(MAKE) -C ./gui/ debug --no-print-directory
	@$(MAKE) -C ./ai/ debug --no-print-directory

###############################################################################



############################ CLEAN ############################################

clean:
	@$(MAKE) -C ./server/ clean --no-print-directory
	@$(MAKE) -C ./gui/ clean --no-print-directory
	@$(MAKE) -C ./ai/ clean --no-print-directory
	@echo -e "\033[1;31mProject cleaned.\033[0m"

fclean: clean
	@$(MAKE) -C ./server/ fclean --no-print-directory
	@$(MAKE) -C ./gui/ fclean --no-print-directory
	@$(MAKE) -C ./ai/ fclean --no-print-directory
	@rm -rf zappy_server
	@rm -rf zappy_gui
	@rm -rf zappy_ai
	@echo -e "\033[1;31mProject full cleaned.\033[0m"

###############################################################################



############################ RECOMPILATION ####################################

re:	fclean all

re_debug: fclean debug

###############################################################################



############################ TESTS ############################################

unit_tests:
	#@make unit_tests --no-print-directory -C./tests/

tests_run:
	#@make tests_run --no-print-directory -C./tests/
	#@gcovr

###############################################################################



############################ DOCUMENTATION ####################################

doc: tests_run
	@mkdir -p docs/html
	@mkdir -p docs/tests
	@doxygen Doxyfile
	@gcovr --branch --html-details docs/tests/test.html
	@echo -e "\033[1;33mDocumentation generated.\033[0m"
	@google-chrome docs/html/index.html
	@google-chrome docs/tests/test.html

###############################################################################
