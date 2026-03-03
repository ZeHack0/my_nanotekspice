/*
** EPITECH PROJECT, 2026
** nanotekspice
** File description:
** AComponents
*/

#include "../include/Components/AComponents.hpp"
#include "../include/nts/Exceptions.hpp"

nts::AComponent::AComponent(std::size_t nbPins) : _pins(nbPins, nts::Undefined) {}

void nts::AComponent::simulate(std::size_t tick) {
    (void)tick;
}

void nts::AComponent::setLink(std::size_t pin, IComponent &other, std::size_t otherPin) {
    if (pin == 0 || pin > _pins.size())
        throw NtsException("Invalid pin number");

    if (_links.find(pin) == _links.end()) {
        _links[pin] = Link(other, otherPin);
        other.setLink(otherPin, *this, pin);
    }
}

nts::Tristate nts::AComponent::getLink(std::size_t pin) {
    auto it = _links.find(pin);
    if (it == _links.end())
        return nts::Undefined;
    return it->second.component->compute(it->second.pin);
}
