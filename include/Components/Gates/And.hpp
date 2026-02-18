/*
** EPITECH PROJECT, 2026
** nanotekspice
** File description:
** And
*/

#pragma once

#include "AComponents.hpp"

namespace nts {
    class AndComponent : public AComponent {
        public:
            AndComponent() : AComponent(3) {}
            nts::Tristate compute(std::size_t pin = 1) override {
                if (pin != 3)
                    throw Exception("Invalid pin number");

                nts::Tristate a = getLink(1);
                nts::Tristate b = getLink(2);

                if (a == nts::FALSE || b == nts::FALSE)
                    return nts::FALSE;
                if (a == nts::UNDEFINED || b == nts::UNDEFINED)
                    return nts::UNDEFINED;
                return nts::TRUE;
            }
    };
}