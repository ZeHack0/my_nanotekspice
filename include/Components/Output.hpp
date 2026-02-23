/*
** EPITECH PROJECT, 2026
** nanotekspice
** File description:
** Output
*/

#pragma once

#include "AComponents.hpp"
#include "../nts/Exceptions.hpp"

namespace nts {
    class OutputComponent : public AComponent {
    public:
        OutputComponent() : AComponent(1) {}
        Tristate compute(std::size_t pin = 1) override {
            if (pin != 1)
                throw NtsException("Invalid pin number");
            return getLink(1);
        }
    };
}
