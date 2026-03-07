/*
** EPITECH PROJECT, 2026
** nanotekspice
** File description:
** Chip4008
*/

#include "../../include/Components/AdvanceChips/Chip4008.hpp"

namespace nts
{
    Chip4008::Chip4008() : AComponent(16) {}

    std::pair<Tristate, Tristate> Chip4008::fullAdder(Tristate a, Tristate b, Tristate cin) {
        if (a == Undefined || b == Undefined || cin == Undefined)
            return {Undefined, Undefined};

        int sumVal = (a == True ? 1 : 0) + (b == True ? 1 : 0) + (cin == True ? 1 : 0);
        Tristate sum = (sumVal % 2 == 1) ? True : False;
        Tristate cout = (sumVal >= 2) ? True : False;

        return {sum, cout};
    }

    Tristate Chip4008::compute(std::size_t pin) {
        if (pin == 8 || pin == 16)
            return Undefined;

        Tristate a1 = getLink(7), b1 = getLink(6), cIn = getLink(9);
        Tristate a2 = getLink(5), b2 = getLink(4);
        Tristate a3 = getLink(3), b3 = getLink(2);
        Tristate a4 = getLink(1), b4 = getLink(15);

        auto res1 = fullAdder(a1, b1, cIn);
        auto res2 = fullAdder(a2, b2, res1.second);
        auto res3 = fullAdder(a3, b3, res2.second);
        auto res4 = fullAdder(a4, b4, res3.second);

        if (pin == 10)
            return res1.first;
        if (pin == 11)
            return res2.first;
        if (pin == 12)
            return res3.first;
        if (pin == 13)
            return res4.first;
        if (pin == 14)
            return res4.second;
        return Undefined;
    }
}
