/*
** EPITECH PROJECT, 2026
** nanotekspice
** File description:
** False
*/

#pragma once

#include "AComponents.hpp"
#include "../nts/Exceptions.hpp"

namespace nts {
    class FalseComponent : public AComponent {
    public:
        FalseComponent() : AComponent(1) {}
        Tristate compute(std::size_t pin = 1) override {
            if (pin != 1)
                throw NtsException("Invalid pin number");
            return False;
        }
    };
}
