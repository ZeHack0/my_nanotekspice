/*
** EPITECH PROJECT, 2026
** nanotekspice
** File description:
** Not
*/

#pragma once

namespace nts {
    class NotComponent : public AComponent {
        public:
            NotComponent() : AComponent(2) {}
            nts::Tristate compute(std::size_t pin = 1) override {
                if (pin != 2)
                    throw Exception("Invalid pin number");

                nts::Tristate a = getLink(1);

                if (a == nts::UNDEFINED)
                    return nts::UNDEFINED;
                return (a == nts::TRUE) ? nts::FALSE : nts::TRUE;
            }
    };
}   