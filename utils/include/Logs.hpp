/*
** EPITECH PROJECT, 2025
** nanotekspice
** File description:
** The Logs.hpp
*/

/**
 * @file Logs.hpp
 * @brief The Logs.hpp
 * @author Nicolas TORO
 */

#ifndef DEBUG_HPP_
	#define DEBUG_HPP_

#include <string>
#include <iostream>

    #define    UNUSED __attribute__((unused))
	#define    RED "\033[0;31m"
	#define    YELLOW "\033[0;33m"
    #define    GREEN "\033[0;32m"
	#define    BOLD "\033[1m"
	#define    UNDERLINE "\033[4m"
	#define    RESET "\033[0m"

namespace Lib::Logs {
	class Debug {
		public:
			Debug(const std::string file = "", const int line = 0, const std::string func = "");
			~Debug();

			static void point(const std::string file, const int line, const std::string func);
			template <typename T>
			Debug& operator<<(const T& message) {
				#ifdef DEBUG_MODE
					std::cerr << message;
				#else
					(void)message;
				#endif
				return *this;
			}
			Debug& operator<<(std::ostream& (*pf)(std::ostream&));
	};

	class Error {
		public:
			Error(const std::string file = "", const int line = 0, const std::string func = "");
			~Error();

			template <typename T>
			Error& operator<<(const T& message) {
					std::cerr << message;
					(void)message;
				return *this;
			}
			Error& operator<<(std::ostream& (*pf)(std::ostream&));
	};

	#define DEBUG Lib::Logs::Debug(__FILE__, __LINE__, __PRETTY_FUNCTION__)
    #define DEBUG_CONCAT Lib::Logs::Debug()
	#define POINT Lib::Logs::Debug::point(__FILE__, __LINE__, __PRETTY_FUNCTION__)
	#define ERROR Lib::Logs::Error(__FILE__, __LINE__, __PRETTY_FUNCTION__)
}

#endif /* DEBUG_HPP_ */
