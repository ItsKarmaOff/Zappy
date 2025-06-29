/*
** EPITECH PROJECT, 2025
** Libmy
** File description:
** The Exceptions class declaration
*/
/**
 * @file Exceptions.hpp
 * @brief The Exceptions class declaration
 * @author Christophe VANDEVOIR, Gianni TUERO, Lou PELLEGRINO,
 * Nicolas TORO, Olivier POUECH and Raphael LAUNAY
 */

#ifndef EXCEPTIONS_HPP_
    #define EXCEPTIONS_HPP_

    #include <exception>
    #include <string>

namespace Lib {
    /**
     * @class Exceptions
     * @brief Class for all exceptions
     */
    class Exceptions
    {
        public:
            /**
             * @class Critical
             * @brief Class for all critical exceptions
             */
            class Critical : public std::exception
            {
                public:
                    /**
                     * @brief Constructor of the Critical
                     * @param message The message of the Critical
                     */
                    Critical(const std::string &message) : _message(message) { }

                    /**
                     * @brief Destructor of the Critical
                     */
                    ~Critical() override = default;

                    /**
                     * @brief Get the message of the exception
                     * @return <b>const char *</b> The message of the exception
                     */
                    const char *what() const noexcept override
                    {
                        return _message.c_str();
                    }

                private:
                    std::string _message; /* The message of the exception */
            };



            /**
             * @class Warning
             * @brief Class for all warning exceptions
             */
            class Warning : public std::exception
            {
                public:
                    /**
                     * @brief Constructor of the Warning
                     * @param message The message of the Warning
                     */
                    Warning(const std::string &message) : _message(message) { }

                    /**
                     * @brief Destructor of the Warning
                     */
                    ~Warning() override = default;

                    /**
                     * @brief Get the message of the exception
                     * @return <b>const char *</b> The message of the exception
                     */
                    const char *what() const noexcept override
                    {
                        return _message.c_str();
                    }

                private:
                    std::string _message; /* The message of the exception */
            };



            /**
             * @class Success
             * @brief Class for all help exceptions
             */
            class Success : public std::exception
            {
                public:
                    /**
                     * @brief Constructor of the Success
                     * @param message The message of the Success
                     */
                    Success(const std::string &message) : _message(message) { }

                    /**
                     * @brief Destructor of the Success
                     */
                    ~Success() override = default;

                    /**
                     * @brief Get the message of the exception
                     * @return <b>const char *</b> The message of the exception
                     */
                    const char *what() const noexcept override
                    {
                        return _message.c_str();
                    }

                private:
                    std::string _message; /* The message of the exception */
            };
    };
}

#endif /* EXCEPTIONS_HPP_ */
