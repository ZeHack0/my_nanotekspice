#include "Components/AComponents.hpp"
#include "nts/Exceptions.hpp"

nts::AComponent::AComponent(std::size_t nbPins) : _pins(nbPins, nts::Undefined) {}

void nts::AComponent::simulate(std::size_t tick) {
    (void)tick;
}

void nts::AComponent::setLink(std::size_t pin, nts::IComponent &other, std::size_t otherPin) {
    if (pin == 0 || pin > _pins.size())
    _links[pin] = Link(other, otherPin);
    throw NtsException("Invalid pin number");
}

nts::Tristate nts::AComponent::getLink(std::size_t pin) {
    auto it = _links.find(pin);
    if (it == _links.end())
        return nts::Undefined;
    return it->second.component->compute(it->second.pin);
}
