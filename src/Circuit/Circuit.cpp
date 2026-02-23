/*
** EPITECH PROJECT, 2026
** nanotekspice
** File description:
** Circuit
*/

#include "../../include/Core/Circuit.hpp"
#include "../../include/Components/Input.hpp"
#include <iostream>
#include <string>
#include <sys/wait.h>

void nts::Circuit::simulate()
{
    _tick++;
    for (auto &[name, comp] : _components)
        comp->simulate(_tick);
}

std::string get_cmdline(const std::string line)
{
    std::string result;
    for (char c : line)
        if (c != ' ' && c != '\t')
            result += c;
    return result;
}

nts::Tristate convert_value(const std::string value)
{
    if (value == "True")
        return nts::Tristate::True;
    if (value == "False")
        return nts::Tristate::False;
    else
        return nts::Tristate::Undefined;
}

void set_value(const std::string cmd)
{
    size_t pos = cmd.find("=");
    std::string name = cmd.substr(0, pos);
    std::string value = cmd.substr(pos + 1);
    auto it = _components.find(name);
    nts::Tristate state = convert_value(value);

    if (state == nts::Tristate::Undefined) {
        std::cout << "Invalid value: " << value << std::endl;
        return;
    }
    if (it == _components.end())
        std::cout << "Component not found: " << name << std::endl;
    nts::InputComponent *inp = dynamic_cast<InputComponent *>(it->second.get());
        if (!inp)
            return;
    inp->setValue(value);
}

void exec_cmd(const std::string line)
{
    std::string cmd = get_cmdline(line);
        if (cmd.find("=") != std::string::npos)
            set_value(cmd);
        if (cmd == "simulate")
            simulate();
        //else if (cmd == "display")
        //    display();
        //else if (cmd == "loop")
        //    loop_sim();
        else
            std::cout << "Unknown command: " << cmd << std::endl;
}

int shell()
{
    std::string line = "";

    while (true) {
        std::cout << " > ";
        if (!std::getline(std::cin, line))
            break;
        if (line == "exit")
            exit(0);
        if (line.empty())
            continue;
        else
            exec_cmd(line);
    }
    return 0;
}