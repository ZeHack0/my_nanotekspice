/*
** EPITECH PROJECT, 2026
** nanotekspice
** File description:
** Circuit
*/

#include "../../include/Core/Circuit.hpp"
#include "../../include/Components/Input.hpp"
#include <csignal>


namespace nts
{
    static volatile bool is_running = true;

    static void sigint_handler(int)
    {
        is_running = false;
    }

    void Circuit::display() const
    {
        char temp;
        nts::Tristate state;
    
        std::cout << "tick: " << _tick << std::endl;
        std::cout << "input(s):" << std::endl;
        for (const auto &[name, comp] : _components) {
            if (comp->getType() == "input") {
                state = comp->compute(1);
                if (state == nts::Tristate::Undefined)
                    temp = 'U';
                else if (state == nts::Tristate::True)
                    temp = '1';
                else
                    temp = '0';
                std::cout << "  " << name << ": " << temp << std::endl;
            }
        }
        std::cout << "output(s):" << std::endl;
        for (const auto &[name, comp] : _components) {
            if (comp->getType() == "output") {
                state = comp->compute(1);
                if (state == nts::Tristate::Undefined)
                    temp = 'U';
                else if (state == nts::Tristate::True)
                    temp = '1';
                else
                    temp = '0';
                std::cout << "  " << name << ": " << temp << std::endl;
            }
        }
    }

    void Circuit::loop_sim()
    {
        is_running = true;
        std::signal(SIGINT, sigint_handler);
        while (is_running) {
            simulate();
            display();
        }
        std::signal(SIGINT, SIG_DFL);
    }

    void Circuit::simulate()
    {
        _tick++;
        for (auto &[name, comp] : _components)
            comp->simulate(_tick);
    }

    std::string Circuit::get_cmdline(const std::string line)
    {
        std::string result;
        for (char c : line)
            if (c != ' ' && c != '\t')
                result += c;
        return result;
    }

    nts::Tristate Circuit::convert_value(const std::string value)
    {
        if (value == "1")
            return nts::Tristate::True;
        if (value == "0")
            return nts::Tristate::False;
        if (value == "U")
            return nts::Tristate::Undefined;
        else
            throw NtsException("Invalid value: " + value);
    }

    void Circuit::set_value(const std::string cmd)
    {
        size_t pos = cmd.find("=");
        std::string name = cmd.substr(0, pos);
        std::string value = cmd.substr(pos + 1);
        auto it =  _components.find(name);
        nts::Tristate state = convert_value(value);

        for (const auto& [key, _] : _components)
            std::cout << key << '\n';
        if (it == _components.end())
            std::cout << "Component not found: " << name << std::endl;
        nts::InputComponent *inp = dynamic_cast<InputComponent *>(it->second.get());
            if (!inp)
                return;
        inp->setValue(state);
    }

    void Circuit::exec_cmd(const std::string line)
    {
        std::string cmd = get_cmdline(line);
            if (cmd.find("=") != std::string::npos)
                set_value(cmd);
            else if (cmd == "simulate")
                simulate();
            else if (cmd == "display")
                display();
            else if (cmd == "loop")
                loop_sim();
            else
                std::cout << "Unknown command: " << cmd << std::endl;
    }

    int Circuit::shell()
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
}