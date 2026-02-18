/*
** EPITECH PROJECT, 2026
** nanotekspice
** File description:
** Chip4071
*/

#pragma once

#include "../AComponents.hpp"
#include "../../nts/Exceptions.hpp"

namespace nts {

    class Chip4071 : public AComponent {

        public:
            Chip4071(): AComponent(14) {}
            ~Chip4071() override = default;
            Tristate compute(std::size_t pin) override {
                if (pin == 3)
                    return computeOr(1, 2);
                if (pin == 4)
                    return computeOr(5, 6);
                if (pin == 10)
                    return computeOr(8, 9);
                if (pin == 11)
                    return computeOr(12, 13);
                throw NtsException("Invalid pin for compute or not an output pin");
            }

        private:
            Tristate computeOr(std::size_t pinA, std::size_t pinB) {
                Tristate vA = getLink(pinA);
                Tristate vB = getLink(pinB);

                if (vA == False || vB == False)
                    return True;
                if (vA == True && vB == True)
                    return False;
                return Undefined;
            }
    };
}
