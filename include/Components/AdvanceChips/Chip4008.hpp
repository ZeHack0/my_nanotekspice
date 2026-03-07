/*
** EPITECH PROJECT, 2026
** nanotekspice
** File description:
** Chip4011
*/

#pragma once

#include "../AComponents.hpp"

namespace nts {
    class Chip4008 : public AComponent {
    public:
        Chip4008();
        virtual ~Chip4008() = default;

        Tristate compute(std::size_t pin = 1) override;
        [[nodiscard]] std::string getType() const override { return "4008"; }

    private:
        std::pair<Tristate, Tristate> fullAdder(Tristate a, Tristate b, Tristate cin);
    };
}
