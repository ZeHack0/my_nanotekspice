/*
** EPITECH PROJECT, 2026
** nanotekspice
** File description:
** Circuit
*/

#pragma once

#include "IComponent.hpp"
#include <map>
#include <memory>
#include <string>
#include <vector>

namespace nts
{
    class Circuit
    {
        private:
        std::map<std::string, std::unique_ptr<nts::IComponent>> _components;
        std::vector<std::string> _inputNames;
        std::vector<std::string> _outputNames;
        std::size_t _tick;
        Factory _factory;

        std::string get_cmdline(const std::string line);
        nts::Tristate convert_value(const std::string value);
        void exec_cmd(const std::string cmd);
        //void loop_sim();
        
        
        public:
            Circuit();
            ~Circuit() = default;
    
            void simulate();
            //void display() const;
            void set_value(const std::string &name, nts::Tristate value);
            void shell();
    };
}
