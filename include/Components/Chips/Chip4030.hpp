/*
** EPITECH PROJECT, 2026
** nanotekspice
** File description:
** Chip4030
*/

#pragma once

#include "../AComponents.hpp"
#include "../../nts/Exceptions.hpp"

namespace nts {

    class Chip4030 : public AComponent {

        public:
            Chip4030(): AComponent(14) {}
            ~Chip4030() override = default;
            Tristate compute(std::size_t pin) override {
                if (pin == 3)
                    return computeXor(1, 2);
                if (pin == 4)
                    return computeXor(5, 6);
                if (pin == 10)
                    return computeXor(8, 9);
                if (pin == 11)
                    return computeXor(12, 13);
                throw NtsException("Invalid pin for compute or not an output pin");
            }

        private:
            Tristate computeXor(std::size_t pinA, std::size_t pinB) {
                Tristate vA = getLink(pinA);
                Tristate vB = getLink(pinB);

                if (vA == True || vB == True)
                    return True;
                if (vA == False && vB == False)
                    return False;
                return Undefined;
            }
    };
}