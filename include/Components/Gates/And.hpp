/*
** EPITECH PROJECT, 2026
** nanotekspice
** File description:
** And
*/

#pragma once

#include "../AComponents.hpp"
#include "../../nts/Exceptions.hpp"

namespace nts {
    class AndComponent : public AComponent {
        public:
            AndComponent() : AComponent(3) {}
            Tristate compute(std::size_t pin = 1) override {
                if (pin != 3)
                    throw NtsException("Invalid pin number");

                Tristate a = getLink(1);
                Tristate b = getLink(2);

                if (a == False || b == False)
                    return False;
                if (a == Undefined || b == Undefined)
                    return Undefined;
                return True;
            }
    };
}
