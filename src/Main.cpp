/*
** EPITECH PROJECT, 2026
** nanotekspice
** File description:
** Main
*/

#include <iostream>
#include "../include/Core/Parser.hpp"
#include "../include/Core/Circuit.hpp"
#include "../include/nts/Exceptions.hpp"

int main(int ac, char **av)
{
    try {
        if (ac != 2)
            throw NtsException("Usage: ./nanotekspice [file]");
        nts::Parser parser;
        nts::Circuit circuit;
        parser.parserFile(av[1]);
        circuit.setComponents(parser.releaseComponents());
        return circuit.shell();
    } catch (const NtsException& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 84;
    } catch (const std::exception& e) {
        std::cerr << "Internal Error: " << e.what() << std::endl;
        return 84;
    }
}
