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
#include <functional>

namespace nts {

    class Parser {

        public:
            Parser();
            ~Parser();
            void parserFile(const std::string& filename);
            const std::map<std::string, std::unique_ptr<IComponent>> &getComponents() const;
            std::unique_ptr<IComponent> createComponent(const std::string &type);
            std::map<std::string, std::unique_ptr<IComponent>> releaseComponents() {
                return std::move(_components);
            }

        private:
            void parseChipsets(const std::string &line);
            void parseLinks(const std::string &line);
            std::map<std::string, std::unique_ptr<IComponent>> _components;
            std::map<std::string, std::function<std::unique_ptr<IComponent>()>> _componentFactory;
            void initFactory();

        protected:
            static std::string openFile(const std::string& filename);
            static bool checkNameFile(const std::string& filename);
            static bool checkIsEmpty(const std::string& filename);
    };
}
