//
// Created by danil on 04.11.2020.
//
#include "trit.h"

typedef unsigned int uint;

Trit::Trit Trit::operator!(Trit t) {
    if (t == Trit::True) {
        return Trit::False;
    } else if (t == Trit::False) {
        return Trit::True;
    } else
        return Trit::Unknown;
}

Trit::Trit Trit::operator&(Trit first, Trit second) {
    switch (first) {
        case Trit::False:
            return Trit::False;
        case Trit::True:
            switch (second) {
                case Trit::True:
                    return Trit::True;
                case Trit::False:
                    return Trit::False;
                case Trit::Unknown:
                    return Trit::Unknown;
            }
        case Trit::Unknown:
            switch (second) {
                case Trit::True:
                    return Trit::Unknown;
                case Trit::False:
                    return Trit::False;
                case Trit::Unknown:
                    return Trit::Unknown;
            }
        default:
            return Trit::Unknown;
    }
}

Trit::Trit Trit::operator|(Trit first, Trit second) {
    Trit res = Trit::Unknown;
    switch (first) {
        case Trit::True:
            return Trit::True;
        case Trit::Unknown:
            switch (second) {
                case Trit::True:
                    return Trit::True;
                case Trit::Unknown:
                    return Trit::Unknown;
                case Trit::False:
                    return Trit::Unknown;
            }
        case Trit::False:
            switch (second) {
                case Trit::False:
                    return Trit::False;
                case Trit::Unknown:
                    return Trit::Unknown;
                case Trit::True:
                    return Trit::True;
            }
        default:
            return Trit::Unknown;
    }
}
