/*
** EPITECH PROJECT, 2026
** nanotekspice
** File description:
** Parser
*/

#include "../../include/Core/Parser.hpp"
#include <fstream>

namespace nts {

    std::string Parser::openFile(const std::string& filename) {
        std::ifstream ifs(filename);
        std::string content;
        std::string line;

        if (ifs.is_open() == false)
            return nullptr;
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

    void Parser::parserFile(const std::string& filename) {
        if (checkNameFile(filename) == false)
            return;
        std::string file = openFile(filename);
        std::cout << file;
    }
}
