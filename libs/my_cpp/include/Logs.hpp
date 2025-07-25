/*
** EPITECH PROJECT, 2025
** Libmy
** File description:
** The Logs class declaration
*/
/**
 * @file Logs.hpp
 * @brief The Logs class declaration
 * @author Christophe VANDEVOIR, Gianni TUERO, Lou PELLEGRINO,
 * Nicolas TORO, Olivier POUECH and Raphael LAUNAY
 */

#ifndef LOGS_HPP_
	#define LOGS_HPP_

    #include <exception>
    #include <string>
    #include <concepts>
    #include <algorithm>
    #include <netinet/in.h>
    #include <sys/socket.h>
    #include <sys/types.h>
    #include <arpa/inet.h>
    #include <unistd.h>
    #include <poll.h>
    #include <filesystem>
    #include <cstdlib>
    #include <cstring>
    #include <vector>
    #include <unordered_map>
    #include <functional>
    #include <csignal>
    #include <fstream>
    #include <pwd.h>
	#include <cmath>
    #include <sys/stat.h>
    #include <sys/mman.h>
    #include <fcntl.h>
    #include <sys/ioctl.h>
    #include <iomanip>
    #include <iostream>
    #include <unordered_set>
    #include <map>
    #include <thread>
    #include <queue>
    #include <mutex>
    #include <string_view>
    #include <dlfcn.h>
    #include <random>
    #include <mqueue.h>
    #include <sys/wait.h>
    #include <barrier>
    #include <sys/poll.h>
    #include <condition_variable>
    #include <regex>

    #define    ENDL RESET "\n\r"
    #define    RESET "\033[0m"
    #define    BLACK_LOGS "\033[0;30m"
    #define    RED_LOGS "\033[0;31m"
    #define    GREEN_LOGS "\033[0;32m"
    #define    YELLOW_LOGS "\033[0;33m"
    #define    BLUE_LOGS "\033[0;34m"
    #define    MAGENTA_LOGS "\033[0;35m"
    #define    CYAN "\033[0;36m"
    #define    WHITE_LOGS "\033[0;37m"
    #define    LIGHT_GREY "\033[0;37m"
    #define    DARK_GREY "\033[0;90m"
    #define    BOLD "\033[1m"
    #define    ITALIC "\033[3m"
    #define    UNDERLINE "\033[4m"
    #define    BLINK "\033[5m"
    #define    REVERSE "\033[7m"
    #define    HIDDEN "\033[8m"

    #define UNUSED __attribute__((unused))

namespace Lib::Logs {
    /**
     * @class Time
     * @brief A class that represents the time
     * @details This class is used to get the local time
     */
    class Time {
        public:
            /**
             * @brief Gets the local time
             * @return <b>std::string</b> The local time
             */
            static std::string getLocalTime();
    };



    /**
     * @class Debug
     * @brief A class for debugging
     * @details This class is used to print debug messages
     */
    class Debug {
        public:
            /**
             * @brief Constructor of the Debug
             * @param file The file that contains the debug
             * @param line The line that contains the debug
             * @param func The function that contains the debug
             */
            Debug(const std::string file = "", const int line = 0, const std::string func = "");
            /**
             * @brief Destructor of the Debug
             */
            ~Debug();



            /**
             * @brief Print a debug point
             * @param file The file that contains the debug point
             * @param line The line that contains the debug point
             * @param func The function that contains the debug point
             */
            static void point(const std::string file, const int line, const std::string func);



            /**
             * @brief Print a debug message
             * @param message The message to print
             * @return <b>Debug &</b> The debug object
             */
            template <typename T> Debug& operator<<(const T& message) {
                #ifdef DEBUG_MODE
                std::cerr << message;
                #else
                (void)message;
                #endif
                return *this;
            }
            /**
             * @brief Print a debug message
             * @param pf The message to print
             * @return <b>Debug &</b> The debug object
             */
            Debug& operator<<(std::ostream& (*pf)(std::ostream&));
    };



    /**
     * @class Error
     * @brief A class for errors
     * @details This class is used to print error messages
     */
    class Error {
        public:
            /**
             * @brief Constructor of the Error
             * @param file The file that contains the error
             * @param line The line that contains the error
             * @param func The function that contains the error
             */
            Error(const std::string file = "", const int line = 0, const std::string func = "");
            /**
             * @brief Destructor of the Error
             */
            ~Error();



            /**
             * @brief Print an error message
             * @param message The message to print
             * @return <b>Error &</b> The error object
             */
            template <typename T>
            Error& operator<<(const T& message) {
                std::cerr << message;
                return *this;
            }
            /**
             * @brief Print an error message
             * @param pf The message to print
             * @return <b>Error &</b> The error object
             */
            Error& operator<<(std::ostream& (*pf)(std::ostream&));
    };



    /**
     * @class Warning
     * @brief A class for warnings
     * @details This class is used to print warning messages
     */
    class Warning {
        public:
            /**
             * @brief Constructor of the Warning
             * @param file The file that contains the warning
             * @param line The line that contains the warning
             * @param func The function that contains the warning
             */
            Warning(const std::string file = "", const int line = 0, const std::string func = "");
            /**
             * @brief Destructor of the Warning
             */
            ~Warning();



            /**
             * @brief Print a warning message
             * @param message The message to print
             * @return <b>Warning &</b> The warning object
             */
            template <typename T>
            Warning& operator<<(const T& message) {
                std::cerr << message;
                return *this;
            }
            /**
             * @brief Print a warning message
             * @param pf The message to print
             * @return <b>Warning &</b> The warning object
             */
            Warning& operator<<(std::ostream& (*pf)(std::ostream&));
    };



    /* Logs macros */

    #define DEBUG Lib::Logs::Debug(__FILE__, __LINE__, __PRETTY_FUNCTION__)
    #define DEBUG_CONCAT Lib::Logs::Debug()
    #define POINT Lib::Logs::Debug::point(__FILE__, __LINE__, __PRETTY_FUNCTION__)
    #define ERROR Lib::Logs::Error(__FILE__, __LINE__, __PRETTY_FUNCTION__)
    #define WARNING Lib::Logs::Warning(__FILE__, __LINE__, __PRETTY_FUNCTION__)
}

#endif /* LOGS_HPP_ */
