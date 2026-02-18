/*
** EPITECH PROJECT, 2026
** nanotekspice
** File description:
** Chip4011
*/

#pragma once

#include "../AComponents.hpp"
#include "../../nts/Exceptions.hpp"

namespace nts {

    class Chip4011 : public AComponent {

        public:
            Chip4011(): AComponent(14) {}
            ~Chip4011() override = default;
            Tristate compute(std::size_t pin) override {
                if (pin == 3)
                    return computeNand(1, 2);
                if (pin == 4)
                    return computeNand(5, 6);
                if (pin == 10)
                    return computeNand(8, 9);
                if (pin == 11)
                    return computeNand(12, 13);
                throw NtsException("Invalid pin for compute or not an output pin");
            }

        private:
            Tristate computeNand(std::size_t pinA, std::size_t pinB) {
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
