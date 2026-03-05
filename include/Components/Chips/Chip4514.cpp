/*
** EPITECH PROJECT, 2026
** nanotekspice
** File description:
** Chip4081
*/

#include "Chip4514.hpp"

namespace nts {

    static Tristate Q;
    static Tristate Q_bar;

    Tristate get_first_pin(std::size_t pin)
    {
        if (pin >= 8 && pin <= 11)
            values[0] = computeAND(latch_4[0], latch_3[0]);
    }

    std::vector<Tristate> get_vector(std::size_t pin)
    {
        std::vector<Tristate> latch_1(2);
        std::vector<Tristate> latch_2(2);
        std::vector<Tristate> latch_3(2);
        std::vector<Tristate> latch_4(2);
        std::vector<Tristate> values(2);

        latch_1 = computeLATCH(computeFirstGates(2))
        latch_2 = computeLATCH(computeFirstGates(3));
        latch_3 = computeLATCH(computeFirstGates(21));
        latch_4 = computeLATCH(computeFirstGates(22));

        if (pin >= 8 && pin <= 11)
            values[0] = computeAND(latch_4[0], latch_3[0]);
        if (pin >= 4 && pin <= 7)
            values[0] = computeAND(latch_3[1], latch_4[0]);
        if (pin >= 17 && pin <= 20)
            values[0] = computeAND(latch_3[0], latch_4[1]);
        if (pin >= 13 && pin <= 16)
            values[0] = computeAND(latch_3[1], latch_4[1]);
        
        if (pin == 11 || pin == 7 || pin == 18 || pin == 14)
            values[1] = computeAND(latch_1[0], latch_2[0]);
        if (pin == 9 || pin == 6 || pin == 17 || pin == 13)
            values[1] = computeAND(latch_1[1], latch_2[0]);
        if (pin == 10 || pin == 5 || pin == 20 || pin == 16)
            values[1] = computeAND(latch_1[0], latch_2[1]);
        if (pin == 8 || pin == 4 || pin == 19 || pin == 15)
            values[1] = computeAND(latch_1[1], latch_2[1]);

        return values;
    }

    Tristate Chip4514::compute(std::size_t pin)
    {
        Tristate inhibit = getLink(23);
        std::vector<Tristate> values(2);

        if ((pin < 4 || pin > 20) && pin != 12)
            throw NtsException("Invalid pin for compute or not an output pin");
        if (inhibit == True)
            return False;
        return computeNOT(computeNAND(get_vector(pin), inhibit));
    }

    std::vector<Tristate> Chips4514::computeFirstGates(std::size_t pin)
    {
        std::vector<Tristate> values = {computeNOT(getLink(pin)), computeNOT(getLink(1))};

        values[0] = computeAND(values[0], values[1]);
        values[1] = computeAND(values[0], values[1]);
        return values;
    }    

    std::vector<Tristate> Chip4514::computeLATCH(std::vector<Tristate> values)
    {
        Tristate S = values[0];
        Tristate R = values[1];

        if (S == False && R == False)
            return {Q, Q_bar};
        if (S == True && R == False) {
            Q = True;
            Q_bar = False;
            return {Q, Q_bar};
        }
        if (S == False && R == True) {
            Q = False;
            Q_bar = True;
            return {Q, Q_bar};
        }
        if (S == True && R == True) {
            Q = False;
            Q_bar = False;
            return {Q, Q_bar};
        }
        return {Undefined, Undefined};
    }

    Tristate Chip4514::computeNOT(Tristate value)
    {
        if (value == True)
            return False;
        if (value == False)
            return True;
        return Undefined;
    }

    Tristate Chip4514::computeAND(std::size_t pinA, std::size_t pinB)
    {
        Tristate vA = getLink(pinA);
        Tristate vB = getLink(pinB);

        if (vA == False || vB == False)
            return False;
        if (vA == True && vB == True)
            return True;
        return Undefined;
    }

    Tristate Chip4514::computeNAND(Tristate value_1, Tristate value_2, Tristate inhibit)
    {
        if (value_1 == True || value_2 == True || inhibit == True)
            return False;
        return True;
    }
}