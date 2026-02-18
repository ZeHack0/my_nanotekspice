/*
** EPITECH PROJECT, 2026
** nanotekspice
** File description:
** Input
*/

#pragma once

#include "AComponents.hpp"

namespace nts {
    class InputComponent : public AComponent {
    public:
        InputComponent() : AComponent(1) {}
        Tristate compute(std::size_t pin = 1) override {
            if (pin != 1)
                throw Exception("Invalid pin number");
            return _pins[0];
        }
        void setValue(Tristate value) {
            _pins[0] = value;
        }
    };
}
