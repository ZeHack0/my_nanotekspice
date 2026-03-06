/*
** EPITECH PROJECT, 2026
** nanotekspice
** File description:
** Chip4514
*/

#pragma once

#include "../AComponents.hpp"
#include "../../nts/Exceptions.hpp"

namespace nts {

    class Chip4514 : public AComponent {
        public:
            Chip4514();
            ~Chip4514() override = default;
            Tristate compute(std::size_t pin) override;
            [[nodiscard]] std::string getType() const override { return "4514"; }

            class Latch {
                protected:
                    Tristate _S;
                    Tristate _R;
                    Tristate _Q;
                    Tristate _Q_bar;

                public:
                    Latch() = default;
                    ~Latch() = default;

                    void computeLATCH(std::vector<Tristate> values);
            }
        
        protected:
            Latch latch_1;
            Latch latch_2;
            Latch latch_3;
            Latch latch_4;
                
        private:
            Tristate computeAND(std::size_t pinA, std::size_t pinB);
            Tristate computeNAND(std::vector<Tristate> values, Tristate inhibit);
            Tristate computeNOT(Tristate value);
            std::vector<Tristate> computeFirstGates(std::size_t pin);
            std::vector<Tristate> get_vector(std::size_t pin);
        };
}
