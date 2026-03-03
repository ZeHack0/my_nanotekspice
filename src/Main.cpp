/*
** EPITECH PROJECT, 2026
** nanotekspice
** File description:
** Main
*/

#include <iostream>
#include "../include/Core/Parser.hpp"
#include "../include/Core/Circuit.hpp"

int main(int ac, char **av)
{
    if (ac != 2)
        return 84;
    nts::Parser parser;
    nts::Circuit circuit;

    parser.parserFile(av[1]);
    circuit.setComponents(parser.releaseComponents());
    return circuit.shell();
}
