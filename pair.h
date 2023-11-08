#ifndef AED_PROYECT_PAIR_H
#define AED_PROYECT_PAIR_H

template<typename TK, typename TV>
struct Pair {
    TK key;
    TV value;

    Pair() : key(TK()), value(TV()) {}

    Pair(TK key, TV value) : key(key), value(value) {}
};

#endif //AED_PROYECT_PAIR_H
