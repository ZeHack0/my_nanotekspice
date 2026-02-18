#pragma once

#include <unordered_map>
#include <vector>
#include "../nts/IComponent.hpp"

namespace nts {
    struct Link {
        IComponent *component;
        std::size_t pin;

        Link() : component(nullptr), pin(0) {}
        Link(IComponent &comp, std::size_t p) : component(&comp), pin(p) {}
    };

    class AComponent : public IComponent {
        protected:
            std::unordered_map<std::size_t, Link> _links;
            std::vector<Tristate> _pins;

        public:
            AComponent(std::size_t nbPins);
            virtual ~AComponent() = default;

            virtual Tristate compute(std::size_t pin = 1) = 0;
            virtual void simulate(std::size_t tick);
            virtual void setLink(std::size_t pin, IComponent &other, std::size_t otherPin);

            Tristate getLink(std::size_t pin);
        };
}
