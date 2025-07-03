/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** The Parser class declaration
*/
/**
 * @file Parser.hpp
 * @brief The Parser class declaration
 * @author Christophe VANDEVOIR, Gianni TUERO, Lou PELLEGRINO,
 * Nicolas TORO, Olivier POUECH and Raphael LAUNAY
 */

#ifndef PARSER_HPP_
    #define PARSER_HPP_

    #include "Lib.hpp"

class Parser;

constexpr int MAX_PORT_NUMBER = 65535; ///< Maximum port number allowed

/**
 * @enum OptionType
 * @brief Represents the type of an option
 */
enum OptionType {
    NOT_REQUIRED = 0, ///< The option is not required
    HOSTNAME_OPTION = 1 << 0, ///< The option is a hostname option
    PORT_OPTION = 1 << 1, ///< The option is a port option
    NAME_OPTION = 1 << 2, ///< The option is a names option
    META_OPTION = 1 << 3, ///< The option is a meta option
};

/**
 * @struct Option
 * @brief Represents a program option
 */
struct Option {
    std::string shortName; ///< The short name of the option
    std::string longName;  ///< The long name of the option
    std::string argument; ///< The argument of the option
    std::string description; ///< The description of the option
    OptionType type; ///< The type of the option
    void (Parser::*function)(size_t &index); ///< The function to call when the option is found
};

/**
 * @class Parser
 * @brief The Parser class is responsible for parsing command line arguments and options.
 */
class Parser
{
    public:

        //////////////// Constructors and Destructor ///////////////////////

        /**
         * @brief Constructor for the Parser class
         * @param argc The number of arguments
         * @param argv The arguments
         */
        Parser(int const &argc, char ** const &argv);

        /**
         * @brief Destructor for the Parser class
         */
        ~Parser();



        //////////////// Getters ///////////////////////////////////////////

        /**
         * @brief Get the hostname
         * @return The hostname
         */
        const std::string &getHostname() const;

        /**
         * @brief Get the port number
         * @return The port number
         */
        const int &getPort() const;

        /**
         * @brief Get the name of the team
         * @return The name of the team
         */
        const std::string &getName() const;



    private:

        //////////////// Options ///////////////////////////////////////////

        /**
         * @brief Parse the option hostname
         * @param index The index of the option in the arguments
         */
        void _optionHostname(size_t &index);

        /**
         * @brief Parse the option port
         * @param index The index of the option in the arguments
         */
        void _optionPort(size_t &index);

        /**
         * @brief Parse the option name
         * @param index The index of the option in the arguments
         */
        void _optionName(size_t &index);

        /**
         * @brief Parse the option help
         * @param index The index of the option in the arguments
         */
        void _optionHelp(size_t &index);

        /**
         * @brief Parse the option version
         * @param index The index of the option in the arguments
         */
        void _optionVersion(size_t &index);

        /**
         * @brief Parse the option authors
         * @param index The index of the option in the arguments
         */
        void _optionAuthors(size_t &index);



        //////////////// Private Attributes ////////////////////////////////

        int const &_argc; ///< The number of arguments
        char ** const &_argv; ///< The arguments

        std::vector<Option> _options; ///< The list of options
        uint8_t _optionsFound = 0; ///< The options found

        int _port; ///< The port number
        std::string _hostname; ///< The hostname
        std::string _name; ///< The name of the team
};

#endif /* PARSER_HPP_ */
