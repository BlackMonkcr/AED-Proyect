#ifndef AED_PROYECT_PAIR_H
#define AED_PROYECT_PAIR_H

#include <iostream>
using namespace std;

template<typename TK, typename TV>
struct Pair {
    TK key;
    TV value;

    friend ostream& operator<<(ostream& os, const Pair& pair) {
        os << pair.key << " " << pair.value;
        return os;
    }

    Pair() : key(TK()), value(TV()) {}

    Pair(TK key, TV value) : key(key), value(value) {}
};

#endif //AED_PROYECT_PAIR_H
