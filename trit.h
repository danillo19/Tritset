//
// Created by danil on 04.11.2020.
//

#ifndef LAB1OOP_TRIT_H
#define LAB1OOP_TRIT_H

typedef unsigned int uint;
namespace Trit {
enum Trit {
    False = 1,
    Unknown = 0,
    True = 2
};

Trit operator!(Trit t);
Trit operator&(Trit first, Trit second);
Trit operator|(Trit first, Trit second);
}

#endif //LAB1OOP_TRIT_H
