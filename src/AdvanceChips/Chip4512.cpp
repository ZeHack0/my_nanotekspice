/*
** EPITECH PROJECT, 2026
** nanotekspice
** File description:
** Chip4081
*/

#include "../../include/Components/AdvanceChips/Chip4514.hpp"
#include "../../include/nts/Exceptions.hpp"

namespace nts {
    Tristate Chip4514::compute(std::size_t pin)
    {
        Tristate C = getLink(13);
        Tristate B = getLink(12);
        Tristate A = getLink(11);

        if (pin != 14)
            throw NtsException("Invalid pin for compute or not an output pin");
        if (getLink(15) == True)
            return Undefined;
        if (getLink(10) == True)
            return False;
        if (C == False && B == False && A == False)
            return getLink(1);
        if (C == False && B == False && A == True)
            return getLink(2);
        if (C == False && B == True && A == False)
            return getLink(3);
        if (C == False && B == True && A == True)
            return getLink(4);
        if (C == True && B == False && A == False)
            return getLink(5);
        if (C == True && B == False && A == True)
            return getLink(6);
        if (C == True && B == True && A == False)
            return getLink(7);
        if (C == True && B == True && A == True)
            return getLink(9);
    }
}