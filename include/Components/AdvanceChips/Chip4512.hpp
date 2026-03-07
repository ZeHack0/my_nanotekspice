/*
** EPITECH PROJECT, 2026
** nanotekspice
** File description:
** Chip4512
*/

#pragma once

#include "../AComponents.hpp"

namespace nts {

    class Chip4512 : public AComponent {

    public:
        Chip4512(): AComponent(16) {}
        ~Chip4512() override = default;
        Tristate compute(std::size_t pin) override;
        [[nodiscard]] std::string getType() const override { return "4512"; }
    };
}
