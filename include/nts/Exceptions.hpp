/*
** EPITECH PROJECT, 2026
** nanotekspice
** File description:
** Exceptions
*/

#pragma once

#include <exception>
#include <string>

class NtsException : public std::exception {

    public:
        explicit NtsException(const std::string &msg)
            : _msg(msg) {}

        const char *what() const noexcept override {
            return _msg.c_str();
        }

    private:
        std::string _msg;
};
