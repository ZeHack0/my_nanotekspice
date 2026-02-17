/*
** EPITECH PROJECT, 2026
** nanotekspice
** File description:
** Main
*/

#include <iostream>

int main(void)
{
    std::string line;
    std::cout << "start nanotekspice" << std::endl;
    //parsing();
    while (getline(std::cin, line)) {
        if (line == "exit")
            break;
        //else if (line == "simulate")
        //    simulate();
        //else if (line == "display")
        //    display();
        //else
        //    std::cout << "Unknown command: " << line << std::endl;
    }
    return 0;
}
