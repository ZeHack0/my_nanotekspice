/*
** EPITECH PROJECT, 2026
** nanotekspice
** File description:
** Chip4081
*/

#pragma once

#include "../AComponents.hpp"

namespace nts {

    class Chip4081 : public AComponent {

        public:
            Chip4081() : AComponent(14) {}
            ~Chip4081() override = default;
            Tristate compute(std::size_t pin) override {
                if (pin == 3)
                    return computeAnd(1, 2);
                if (pin == 4)
                    return computeAnd(5, 6);
                if (pin == 10)
                    return computeAnd(8, 9);
                if (pin == 11)
                    return computeAnd(12, 13);
                throw NtsException("Invalid pin for compute or not an output pin");
            }

        private:
            Tristate computeAnd(std::size_t pinA, std::size_t pinB) {
                Tristate vA = getLink(pinA);
                Tristate vB = getLink(pinB);

                if (vA == False || vB == False)
                    return False;
                if (vA == True && vB == True)
                    return True;
                return Undefined;
            }
        };
}
