//
// Created by danil on 04.11.2020.
//

#ifndef LAB1OOP_TRITSET_H
#define LAB1OOP_TRITSET_H

#include "trit.h"
#include <iostream>
#include <vector>
#include <unordered_map>
namespace Tritset {
    class Tritset {
    private:
        std::vector<uint> arr_;
        uint size_;

        Trit::Trit getTrit(uint index) const;

        void setTrit(size_t index, Trit::Trit trit);

    public:

        explicit Tritset(int capacity = 0);

        uint size();

        void print();

        void shrink();

        size_t cardinality(Trit::Trit value);

        std::unordered_map<Trit::Trit, int, std::hash<int>> cardinality();

        void trim(size_t lastIndex);

        size_t length();

        class reference {
        private:
            Tritset &set_;
            size_t pos_;
        public:
            reference(Tritset &set, int index) : set_(set), pos_(index) {};

            reference &operator=(Trit::Trit trit);

            reference &operator=(const reference &ref_);

            explicit operator Trit::Trit();
        };


        reference operator[](int index);

        Tritset operator&(Tritset &a);

        Tritset operator|(Tritset &a);


        Tritset operator!();
    };
}
#endif //LAB1OOP_TRITSET_H

