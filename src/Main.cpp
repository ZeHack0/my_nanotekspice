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
    (void)ac;
    nts::Parser parser;
    nts::Circuit circuit = nts::Circuit();
    parser.parserFile(av[1]);
    circuit._components = parser._components;
    return circuit.shell();
}
