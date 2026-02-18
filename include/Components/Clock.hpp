/*
** EPITECH PROJECT, 2026
** nanotekspice
** File description:
** Clock
*/

#pragma once

#include "AComponents.hpp"

namespace nts {
    class ClockComponent : public AComponent {
    private:
        Tristate _state;
        
    public:
        ClockComponent() : AComponent(1), _state(False) {}
        Tristate compute(std::size_t pin = 1) override {
            if (pin != 1)
                throw Exception("Invalid pin number");
            return _state;
        }
        void simulate(std::size_t tick) override {
            (void)tick;
            _state = (_state == False) ? True : False;
        }
    };
}
