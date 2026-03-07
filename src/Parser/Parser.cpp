/*
** EPITECH PROJECT, 2026
** nanotekspice
** File description:
** Parser
*/

#include "Core/Parser.hpp"
#include "nts/Exceptions.hpp"
#include "Components/Input.hpp"
#include "Components/Chips/Chip4001.hpp"
#include "Components/AdvanceChips/Chip4008.hpp"
#include "Components/Chips/Chip4011.hpp"
#include "Components/Chips/Chip4030.hpp"
#include "Components/AdvanceChips/Chip4512.hpp"
#include "Components/AdvanceChips/Chip4514.hpp"
#include "Components/Chips/Chip4069.hpp"
#include "Components/Chips/Chip4071.hpp"
#include "Components/Chips/Chip4081.hpp"
#include "Components/Output.hpp"

#include <fstream>
#include <sstream>
#include <functional>

namespace nts {

    Parser::Parser() {
        initFactory();
    }

    Parser::~Parser() = default;

    std::string Parser::openFile(const std::string& filename) {
        std::ifstream ifs(filename);
        std::string content;
        std::string line;

        if (ifs.is_open() == false)
            throw NtsException("Files doesn't exist");
        while (std::getline(ifs, line)) {
            size_t commentPos = line.find('#');
            if (commentPos != std::string::npos)
                line = line.substr(0, commentPos);
            line.erase(line.find_last_not_of(" \t\n\r\f\v") + 1,
                std::string::npos);
            if (!line.empty())
                content += line + "\n";
        }
        return content;
    }

    bool Parser::checkNameFile(const std::string& filename) {
        if (filename.length() < 4)
            return false;

        size_t dotPos = filename.find_last_of('.');
        if (dotPos == std::string::npos)
            return false;
        if (filename.substr(dotPos) != ".nts")
            return false;
        return true;
    }

    bool Parser::checkIsEmpty(const std::string& filename) {
        std::string content = openFile(filename);

        if (content[0] == '\0')
            return false;
        return true;
    }

    bool Parser::validateSections(const std::string& filename) {
        std::ifstream file(filename);
        std::string line;
        bool hasChipsets = false;
        bool hasLinks = false;
        int chipsetCount = 0;
        int linkCount = 0;
        std::string currentSection;

        while (std::getline(file, line)) {
            size_t commentPos = line.find('#');
            if (commentPos != std::string::npos)
                line = line.substr(0, commentPos);
            line.erase(line.find_last_not_of(" \t\n\r\f\v") + 1, 0);
            line.erase(0, line.find_first_not_of(" \t\n\r\f\v"));

            if (line.empty())
                continue;

            if (line == ".chipsets:") {
                hasChipsets = true;
                currentSection = line;
            } else if (line == ".links:") {
                hasLinks = true;
                currentSection = line;
            } else {
                if (currentSection == ".chipsets:") chipsetCount++;
                if (currentSection == ".links:") linkCount++;
            }
        }
        if (!hasChipsets || chipsetCount == 0)
            return false;
        if (!hasLinks || linkCount == 0)
            return false;
        return true;
    }


    void Parser::parseChipsets(const std::string& line) {
        std::stringstream ss(line);
        std::string type;
        std::string name;

        if (!(ss >> type >> name))
            throw NtsException("Invalid chipset Format");
        if (_components.find(name) != _components.end())
            throw NtsException("This composant '" + name + "' is already exist");

        auto newComponent = createComponent(type);
        if (!newComponent)
            throw NtsException("Unknown component type : " + type);
        _components[name] = std::move(newComponent);
    }

    void Parser::parseLinks(const std::string& line) {
        std::stringstream ss(line);
        std::string part1;
        std::string part2;

        if (!(ss >> part1 >> part2))
            throw NtsException("Invalid chipset Format");
        auto splitContact = [](const std::string& contact) {
            size_t pos = contact.find(':');
            if (pos == std::string::npos) {
                throw NtsException("Invalid contact Format (missing ':') : " + contact);
            }

            std::string name = contact.substr(0, pos);
            std::string pinStr = contact.substr(pos + 1);

            return std::make_pair(name, std::stoul(pinStr));
        };

        auto [name1, pin1] = splitContact(part1);
        auto [name2, pin2] = splitContact(part2);
        if (_components.find(name1) == _components.end() || _components.find(name2) == _components.end())
            throw NtsException("impossible Links : Unknow composant.");
        _components[name1]->setLink(pin1, *_components[name2], pin2);
    }

    void Parser::parserFile(const std::string& filename) {
        if (checkNameFile(filename) == false)
            throw NtsException("Invalid File: Wring file");
        if (checkIsEmpty(filename) == false)
            throw NtsException("Invalid File: Empty file");
        if (validateSections(filename) == false)
            throw std::runtime_error("Section .chipsets Or Section .links: is missing or empty");

        std::string content = openFile(filename);
        std::stringstream ss(content);
        std::string line;
        std::string section;

        while (std::getline(ss, line)) {
            if (line == ".chipsets:" || line == ".links:") {
                section = line;
                continue;
            }
            if (section == ".chipsets:") {
                parseChipsets(line);
            } else if (section == ".links:") {
                parseLinks(line);
            }
        }
    }

    void Parser::initFactory() {
        _componentFactory["4001"] = []() { return std::make_unique<Chip4001>(); };
        _componentFactory["4008"] = []() { return std::make_unique<Chip4008>(); };
        _componentFactory["4011"] = []() { return std::make_unique<Chip4011>(); };
        _componentFactory["4512"] = []() { return std::make_unique<Chip4512>(); };
        _componentFactory["4514"] = []() { return std::make_unique<Chip4514>(); };
        _componentFactory["4030"] = []() { return std::make_unique<Chip4030>(); };
        _componentFactory["4069"] = []() { return std::make_unique<Chip4069>(); };
        _componentFactory["4071"] = []() { return std::make_unique<Chip4071>(); };
        _componentFactory["4081"] = []() { return std::make_unique<Chip4081>(); };
        _componentFactory["input"] = []() { return std::make_unique<InputComponent>(); };
        _componentFactory["output"] = []() { return std::make_unique<OutputComponent>(); };
    }

    std::unique_ptr<IComponent> Parser::createComponent(const std::string &type) {
        auto it = _componentFactory.find(type);

        if (it != _componentFactory.end()) {
            return it->second();
        }
        return nullptr;
    }
}
