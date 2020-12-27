//
// Created by danil on 04.11.2020.
//

#include "Tritset.h"
#include <iostream>
#include <vector>
#include <cmath>
#include <unordered_map>

typedef unsigned int uint;

inline uint getArrSize(size_t capacity) {
    return ceil(capacity * 2.0 / (8.0 * sizeof(uint)));
}

void Tritset::Tritset::setTrit(size_t index, Trit::Trit trit) {
    size_t setIndex = (index * 2) / (sizeof(uint) * 8);
    uint offset = (sizeof(uint) * 8 - 2 * (index + 1));
    uint mask = ~((uint) 3 << offset);
    arr_[setIndex] &= (mask);
    arr_[setIndex] |= ((uint) trit << offset);
}

Trit::Trit Tritset::Tritset::getTrit(uint index) const {
    if (index >= this->size_)
        return Trit::Unknown;

    uint arrIndex = (index * 2) / (sizeof(uint) * 8);
    uint offset = sizeof(uint) * 8 - 2 * (index + 1);
    int result = 3 & (arr_[arrIndex] >> offset);
    switch (result) {
        case 0:
            return Trit::Unknown;
        case 1:
            return Trit::False;
        case 2:
            return Trit::True;
        default:
            return Trit::Unknown;
    }
}

Tritset::Tritset::Tritset(int capacity) {
    int arrCapacity = getArrSize(capacity);
    arr_.resize(arrCapacity);
    size_ = capacity;
}


uint Tritset::Tritset::size() {
    return size_;
}

void Tritset::Tritset::print() {
    for (uint i = 0; i < this->size_; i++) {
        uint res = getTrit(i);
        switch (res) {
            case Trit::True:
                std::cout << "True ";
                break;
            case Trit::False:
                std::cout << "False ";
                break;
            case Trit::Unknown:
                std::cout << "Unknown ";
                break;
            default:
                std::cout << "Unknown";
        }
    }
    std::cout << std::endl;
};

void Tritset::Tritset::shrink() {
    int lastSetTritIndex = -1;
    for (size_t i = 0; i < this->size_; i++) {
        if (getTrit(i) != Trit::Unknown) lastSetTritIndex = i;
    }

    size_t requiredArrSize = getArrSize(lastSetTritIndex);
    arr_.resize(requiredArrSize);
    size_ = lastSetTritIndex + 1;
    arr_.shrink_to_fit();
}

size_t Tritset::Tritset::cardinality(Trit::Trit value) {
    size_t count = 0;
    if (value != Trit::Unknown) {
        for (uint i = 0; i < this->size_; i++) {
            if (getTrit(i) == value) count++;
        }
    } else {
        int lastSetIndex = this->size() - 1;
        while(this->getTrit(lastSetIndex) == Trit::Unknown) lastSetIndex--;
        for(int j = lastSetIndex; j >= 0; j--) {
            if(getTrit(j) == Trit::Unknown) count++;
        }
    }
    return count;
}

std::unordered_map<Trit::Trit, int, std::hash<int>> Tritset::Tritset::cardinality() {
    std::unordered_map<Trit::Trit, int, std::hash<int>> map;
    map[Trit::False] = this->cardinality(Trit::False);
    map[Trit::True] = this->cardinality(Trit::True);
    map[Trit::Unknown] = this->cardinality(Trit::Unknown);
    return map;
}

void Tritset::Tritset::trim(size_t lastIndex) {
    if (lastIndex > size_) return;

    size_t newArrSize = getArrSize(lastIndex);
    size_t capacity = (newArrSize * sizeof(uint) * 8) / 2;
    for (size_t i = lastIndex + 1; i < capacity; i++) {
        this->Tritset::operator[](i) = Trit::Unknown;
    }

    this->size_ = lastIndex + 1;
    this->arr_.resize(lastIndex + 1);
    this->arr_.shrink_to_fit();
}

size_t Tritset::Tritset::length() {
    int lastSetIndex = -1;
    for (int i = 0; i < this->size(); i++) {
        if (getTrit(i) != Trit::Unknown) {
            lastSetIndex = i;
        }
    }
    return lastSetIndex + 1;
}


Tritset::Tritset::reference& Tritset::Tritset::reference::operator=(Trit::Trit trit) {
    if (pos_ < set_.size_) {
        set_.setTrit(pos_, trit);
    } else if (trit != Trit::Unknown && pos_ >= set_.size_) {
        set_.arr_.resize(getArrSize(pos_ + 1));
        set_.size_ = pos_ + 1;
        set_.setTrit(pos_, trit);
    }
    return *this;
};


Tritset::Tritset::reference& Tritset::Tritset::reference::operator=(const Tritset::reference& ref_) {
    Trit::Trit newValue = ref_.set_.getTrit(ref_.pos_);
    this->set_.setTrit(this->pos_,newValue);
    return *this;
}



Tritset::Tritset::reference Tritset::Tritset::operator[](int index) {
    return reference{*this, index};
}

Tritset::Tritset::reference::operator Trit::Trit() {
    return this->set_.getTrit(this->pos_);
}

Tritset::Tritset Tritset::Tritset::operator&(Tritset &a) {
    uint requiredSize = this->size() > a.size() ? this->size() : a.size();
    Tritset res(requiredSize);
    for (uint i = 0; i < requiredSize; i++) {
        res[i] = this->getTrit(i) & a.getTrit(i);
    }
    return res;
}

Tritset::Tritset Tritset::Tritset::operator|(Tritset &a) {
    uint requiredSize = this->size() > a.size() ? this->size() : a.size();
    Tritset res(requiredSize);

    for (uint i = 0; i < requiredSize; i++) {
        res[i] = this->getTrit(i) | a.getTrit(i);
    }
    return res;
}


Tritset::Tritset Tritset::Tritset::operator!() {
    Tritset res(this->size());
    for (uint i = 0; i < this->size(); i++) {
        res[i] = !this->getTrit(i);
    }
    return res;
};
