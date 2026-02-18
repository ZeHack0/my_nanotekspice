/*
** EPITECH PROJECT, 2026
** nanotekspice
** File description:
** Output
*/

#pragma once

#include "AComponents.hpp"

namespace nts {
    class TrueComponent : public AComponent {
    public:
        TrueComponent() : AComponent(1) {}
        nts::Tristate compute(std::size_t pin = 1) override {
            if (pin != 1)
                throw Exception("Invalid pin number");
            return nts::TRUE;
        }
    };
}
