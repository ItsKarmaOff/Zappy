/*
** EPITECH PROJECT, 2025
** nanotekspice
** File description:
** The Debug.cpp
*/

#include <iostream>
#include "Logs.hpp"

Lib::Logs::Debug::Debug(const std::string file, const int line, const std::string func)
{
	#ifdef DEBUG_MODE
		if (file.empty() && line == 0 && func.empty())
			std::cerr << RESET YELLOW;
		else
			std::cerr << RESET GREEN BOLD "[FILE: " << file << ":" << line
				<< ", FUNCTION: " << func << "]: " RESET YELLOW << std::endl;
	#else
		(void)file;
		(void)line;
		(void)func;
	#endif
}

Lib::Logs::Debug::~Debug()
{
	#ifdef DEBUG_MODE
		std::cerr << RESET << std::endl;
	#endif
}

void Lib::Logs::Debug::point(const std::string file, const int line, const std::string func)
{
	#ifdef DEBUG_MODE
		std::cout << RESET GREEN BOLD "FILE: " << file << ":" << line <<
			RESET GREEN ", FUNCTION: " << func << RESET << std::endl;
	#else
		(void)file;
		(void)line;
		(void)func;
	#endif
}

Lib::Logs::Debug& Lib::Logs::Debug::operator<<(std::ostream& (*pf)(std::ostream&))
{
	#ifdef DEBUG_MODE
		std::cerr << pf;
	#else
		(void)pf;
	#endif
	return *this;
}

Lib::Logs::Error::Error(const std::string file, const int line, const std::string func)
{
	if (file.empty() && line == 0 && func.empty())
		std::cerr << RESET RED;
	else
		std::cerr << RESET GREEN BOLD "[FILE: " << file << ":" << line
			<< ", FUNCTION: " << func << "]: " RESET RED;
    std::cerr << std::endl;
}

Lib::Logs::Error::~Error()
{
	std::cerr << RESET << std::endl;
}

Lib::Logs::Error& Lib::Logs::Error::operator<<(std::ostream& (*pf)(std::ostream&))
{
	std::cerr << pf;
	return *this;
}
