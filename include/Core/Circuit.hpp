/*
** EPITECH PROJECT, 2026
** nanotekspice
** File description:
** Circuit
*/

#pragma once

#include "../nts/IComponent.hpp"
#include <map>
#include <memory>
#include <string>
#include <vector>
#include <iostream>

namespace nts
{
    class Circuit
    {
        private:
            std::size_t _tick;
            std::map<std::string, std::unique_ptr<nts::IComponent>> _components;

            std::string get_cmdline(const std::string line);
            nts::Tristate convert_value(const std::string value);
            void exec_cmd(const std::string cmd);
            void loop_sim();

        public:
            Circuit() : _tick(0), _components() {};
            ~Circuit() = default;

            void simulate();
            void display() const;
            void set_value(const std::string name);
            int shell();
            void setComponents(std::map<std::string, std::unique_ptr<nts::IComponent>> components) {
                _components = std::move(components);
            }
    };
}
