/*
** EPITECH PROJECT, 2026
** nanotekspice
** File description:
** Chip4081
*/

#include "../../include/Components/AdvanceChips/Chip4514.hpp"
#include "../../include/nts/Exceptions.hpp"

namespace nts {

    Chip4514::Chip4514() : AComponent(24)
    {
        latch_1 = Latch();
        latch_2 = Latch();
        latch_3 = Latch();
        latch_4 = Latch();
    }

    std::vector<Tristate> Chip4514::get_vector(std::size_t pin)
    {
        std::vector<Tristate> values = {Undefined, Undefined};

        latch_1.computeLATCH(computeFirstGates(2));
        latch_2.computeLATCH(computeFirstGates(3));
        latch_3.computeLATCH(computeFirstGates(21));
        latch_4.computeLATCH(computeFirstGates(22));

        if (pin >= 8 && pin <= 11)
            values[0] = computeAND(latch_4._Q, latch_3._Q);
        if (pin >= 4 && pin <= 7)
            values[0] = computeAND(latch_3._Q_bar, latch_4._Q);
        if (pin >= 17 && pin <= 20)
            values[0] = computeAND(latch_3._Q, latch_4._Q_bar);
        if (pin >= 13 && pin <= 16)
            values[0] = computeAND(latch_3._Q_bar, latch_4._Q_bar);

        if (pin == 11 || pin == 7 || pin == 18 || pin == 14)
            values[1] = computeAND(latch_1._Q, latch_2._Q);
        if (pin == 9 || pin == 6 || pin == 17 || pin == 13)
            values[1] = computeAND(latch_1._Q_bar, latch_2._Q);
        if (pin == 10 || pin == 5 || pin == 20 || pin == 16)
            values[1] = computeAND(latch_1._Q, latch_2._Q_bar);
        if (pin == 8 || pin == 4 || pin == 19 || pin == 15)
            values[1] = computeAND(latch_1._Q_bar, latch_2._Q_bar);

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
        values = get_vector(pin);
        return computeNOT(computeNAND(values, inhibit));
    }

    std::vector<Tristate> Chip4514::computeFirstGates(std::size_t pin)
    {
        std::vector<Tristate> values = {computeNOT(getLink(pin)), computeNOT(getLink(1))};

        values[0] = computeAND(values[0], values[1]);
        values[1] = computeAND(values[0], values[1]);
        return values;
    }

    void Chip4514::Latch::computeLATCH(std::vector<Tristate> values)
    {
        _S = values[0];
        _R = values[1];

        if (_S == False && _R == False)
            return;
        if (_S == True && _R == False) {
            _Q = True;
            _Q_bar = False;
            return;
        }
        if (_S == False && _R == True) {
            _Q = False;
            _Q_bar = True;
            return;
        }
        if (_S == True && _R == True) {
            _Q = False;
            _Q_bar = False;
            return;
        }
        _Q = Undefined;
        _Q_bar = Undefined;
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

    Tristate Chip4514::computeNAND(std::vector<Tristate> values, Tristate inhibit)
    {
        if (values[0] == True || values[1] == True || inhibit == True)
            return False;
        return True;
    }
}