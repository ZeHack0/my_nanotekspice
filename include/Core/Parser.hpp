/*
** EPITECH PROJECT, 2026
** nanotekspice
** File description:
** Parser
*/

#pragma once

#include "../nts/IComponent.hpp"
#include <iostream>
#include <map>
#include <memory>

namespace nts {

    class Parser {

        public:
            void parserFile(const std::string& filename);
            const std::map<std::string, std::unique_ptr<IComponent>> &getComponents() const;

        private:
            void parseChipsets(const std::string &line);
            void parseLinks(const std::string &line);
            std::map<std::string, std::unique_ptr<IComponent>> _components;

        protected:
            static std::string openFile(const std::string& filename);
            static bool checkNameFile(const std::string& filename);
    };
}
