/*
** EPITECH PROJECT, 2026
** nanotekspice
** File description:
** Chip4069
*/

#pragma once

#include "../AComponents.hpp"
#include "../../nts/Exceptions.hpp"

namespace nts {

    class Chip4069 : public AComponent {

        public:
            Chip4069(): AComponent(14) {}
            ~Chip4069() override = default;
            Tristate compute(std::size_t pin) override {
                if (pin == 2)
                    return computeNot(1);
                if (pin == 4)
                    return computeNot(3);
                if (pin == 6)
                    return computeNot(5);
                if (pin == 8)
                    return computeNot(9);
                if (pin == 10)
                    return computeNot(11);
                if (pin == 12)
                    return computeNot(13);
                throw NtsException("Invalid pin for compute or not an output pin");
            }

        private:
            Tristate computeNot(std::size_t pin) {
                Tristate v = getLink(pin);

                if (v == False)
                    return True;
                if (v == True)
                    return False;
                return Undefined;
            }
    };
}
