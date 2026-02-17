/*
** EPITECH PROJECT, 2026
** nanotekspice
** File description:
** False
*/

#pragma once

namespace nts {
    class FalseComponent : public AComponent {
    public:
        FalseComponent() : AComponent(1) {}
        nts::Tristate compute(std::size_t pin = 1) override {
            if (pin != 1)
                throw Exception("Invalid pin number");
            return nts::FALSE;
        }
    };
}
