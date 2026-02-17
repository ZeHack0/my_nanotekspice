/*
** EPITECH PROJECT, 2026
** nanotekspice
** File description:
** And
*/

#pragma once

namespace nts {
    class OrComponent : public AComponent {
        public:
            OrComponent() : AComponent(3) {}
            nts::Tristate compute(std::size_t pin = 1) override  {
                if (pin != 3)
                    throw Exception("Invalid pin number");

                nts::Tristate a = getLink(1);
                nts::Tristate b = getLink(2);

                if (a == nts::TRUE || b == nts::TRUE)
                    return nts::TRUE;
                if (a == nts::UNDEFINED || b == nts::UNDEFINED)
                    return nts::UNDEFINED;
                return nts::FALSE;
            }
    };
}
