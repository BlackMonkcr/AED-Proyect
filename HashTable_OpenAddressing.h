#ifndef AED_PROYECT_HASHTABLE_OPENADDRESSING_H
#define AED_PROYECT_HASHTABLE_OPENADDRESSING_H

#include "pair.h"
#include <iostream>
#include <unordered_set>
using namespace std;


template<typename TK, typename TV>
class HashTable_OpenAddressing {
    float maxFillFactor{};
    int size;
    int capacity{};
    int numberReHashes{};
    Pair<TK, TV>* table;

    friend bool isPrime(int n);
    int getIndex(TK key, int _capacity);
    int getNewCapacity();
    void rehash();

public:
    /*Constructors
    ---------------------------------------------------------------------------*/
    HashTable_OpenAddressing();
    explicit HashTable_OpenAddressing(float maxFillFactor, int capacity = 10);

    /* Methods
    ---------------------------------------------------------------------------*/
    void insert(TK key, TV value);
    void remove(TK key);
    TV get(TK key);
    bool search(TK key);
    void print();
    int getNumberReHashes();

    /* Destructor
    ---------------------------------------------------------------------------*/
    ~HashTable_OpenAddressing();
};

bool isPrime(int n) {
    for (int i = 2; i < n; i++) {
        if (n%i == 0) {
            return false;
        }
    }
    return true;
}

template<typename TK, typename TV>
HashTable_OpenAddressing<TK, TV>::~HashTable_OpenAddressing() {
    delete[] table;
}

template<typename TK, typename TV>
int HashTable_OpenAddressing<TK, TV>::getNumberReHashes() {
    return numberReHashes;
}

template<typename TK, typename TV>
void HashTable_OpenAddressing<TK, TV>::print() {
    for (int i = 0; i < capacity; i++) {
        if (table[i].key != TK()) {
            cout << "Bucket N°" << i << ": "
                 << table[i].key << " " << table[i].value << endl;
        } else {
            cout << "Bucket N°" << i << ": " << "Empty" << endl;
        }
    }
}

template<typename TK, typename TV>
bool HashTable_OpenAddressing<TK, TV>::search(TK key) {
    int index = getIndex(key, capacity);
    int firstIndex = index;
    while (table[index].key != TK() && table[index].key != key) {
        index++;
        if (index == firstIndex-1) {
            return false;
        } else if (index >= capacity) {
            index = 0;
        }
    }

    if (table[index].key == key) {
        return true;
    }

    return false;
}

template<typename TK, typename TV>
TV HashTable_OpenAddressing<TK, TV>::get(TK key) {
    int index = getIndex(key, capacity);
    int firstIndex = index;
    while (table[index].key != TK() && table[index].key != key) {
        index++;
        if (index == firstIndex-1) {
            cout << "Key not found" << endl;
            throw std::exception();
        } else if (index >= capacity) {
            index = 0;
        }
    }

    if (table[index].key == key) {
        return table[index].value;
    }

    return TV();
}

template<typename TK, typename TV>
void HashTable_OpenAddressing<TK, TV>::remove(TK key) {
    int index = getIndex(key, capacity);
    int firstIndex = index;
    while (table[index].key != TK() && table[index].key != key) {
        index++;
        if (index == firstIndex-1) {
            cout << "Key not found" << endl;
            throw std::exception();
        } else if (index >= capacity) {
            index = 0;
        }
    }

    if (table[index].key == key) {
        table[index] = Pair<TK, TV>();
        size--;
    }
}

template<typename TK, typename TV>
void HashTable_OpenAddressing<TK, TV>::insert(TK key, TV value) {
    if (size > capacity * maxFillFactor) {
        rehash();
    }

    int index = getIndex(key, capacity);
    while (table[index].key != TK() && table[index].key != key) {
        index++;
        if (index >= capacity) {
            index = 0;
        }
    }

    table[index] = Pair<TK, TV>(key, value);
    size++;
}

template<typename TK, typename TV>
HashTable_OpenAddressing<TK, TV>::HashTable_OpenAddressing(float maxFillFactor, int capacity) {
    this->maxFillFactor = maxFillFactor;
    size = 0;
    this->capacity = capacity;
    table = new Pair<TK, TV>[capacity];
    numberReHashes = 0;
}

template<typename TK, typename TV>
HashTable_OpenAddressing<TK, TV>::HashTable_OpenAddressing() {
    maxFillFactor = 0.75;
    size = 0;
    capacity = 10;
    table = new Pair<TK, TV>[capacity];
    numberReHashes = 0;
}

template<typename TK, typename TV>
void HashTable_OpenAddressing<TK, TV>::rehash() {
    numberReHashes++;
    int newCapacity = getNewCapacity();
    auto* newTable = new Pair<TK, TV>[newCapacity];
    for (int i = 0; i < capacity; i++) {
        if (table[i].key != TK()) {
            int index = getIndex(table[i].key, newCapacity);
            while (newTable[index].key != TK()) {
                index++;
            }
            newTable[index] = table[i];
        }
    }
    delete[] table;
    table = newTable;
    capacity = newCapacity;
}

template<typename TK, typename TV>
int HashTable_OpenAddressing<TK, TV>::getNewCapacity() {
    int newCapacity = capacity * 2;
    while (!isPrime(newCapacity)) {
        newCapacity++;
    }
    return newCapacity;
}

template<typename TK, typename TV>
int HashTable_OpenAddressing<TK, TV>::getIndex(TK key, int _capacity) {
    return std::hash<TK>{}(key)%_capacity;
}


#endif //AED_PROYECT_HASHTABLE_OPENADDRESSING_H
