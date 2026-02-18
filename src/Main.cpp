/*
** EPITECH PROJECT, 2026
** nanotekspice
** File description:
** Main
*/

#include <iostream>
#include "../include/Core/Parser.hpp"

int main(int ac, char **av)
{
    (void)ac;
    //std::string line;
    nts::Parser parser;
    parser.parserFile(av[1]);
    //while (getline(std::cin, line)) {
    //    if (line == "exit")
    //        break;
        //else if (line == "simulate")
        //    simulate();
        //else if (line == "display")
        //    display();
        //else
        //    std::cout << "Unknown command: " << line << std::endl;
    //}
    return 0;
}
