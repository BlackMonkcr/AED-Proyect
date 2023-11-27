#ifndef AED_PROYECT_HASHTABLE_CUCKOO_H
#define AED_PROYECT_HASHTABLE_CUCKOO_H

#include <iostream>
#include <unordered_set>
#include "pair.h"
#include "HashCommonFunctions.cpp"
#include "Node.h"
using namespace std;

template<typename TK, typename TV>
class HashTable_Cuckoo {
    size_t capacity{};
    size_t size{};
    int numberReHashes{};
    const float maxFill_Factor = 0.70;
    Pair<TK, TV>* primary_table = nullptr;
    Pair<TK, TV>* secondary_table = nullptr;

    size_t getIndex_secondary(TK key, size_t _capacity) {
        std::hash<TK> hashFunction;
        return hashFunction(key) % _capacity;
    }

    size_t getIndex_primary(TK key, size_t _capacity) {
        std::hash<TK> hashFunction;
        return (hashFunction(key) / _capacity) % _capacity;
    }

    void rehash(size_t newCapacity);

    void insertHelper(TK key, TV value, int typeHashing, int cont, bool isRehashing = false);

public:
    /*Constructors
    ---------------------------------------------------------------------------*/
    HashTable_Cuckoo();
    explicit HashTable_Cuckoo(size_t capacity);

    /* Methods
    ---------------------------------------------------------------------------*/
    void insert(TK key, TV value, bool isRehashing = false);
    void remove(TK key);
    TV get(TK key);
    bool search(TK key);
    void print();
    int getNumberReHashes();
    size_t getSize() { return this->size; }
    size_t getCapacity() { return this->capacity; }

    /* Destructor
    ---------------------------------------------------------------------------*/
    ~HashTable_Cuckoo();
};

bool isPrimeCuckoo(size_t n) {
    for (int i = 2; i < n; i++) {
        if (n%i == 0) {
            return false;
        }
    }
    return true;
}

size_t getNewCapacityCuckoo(size_t capacity) {
    size_t newCapacity = capacity*2;
    while (!isPrimeCuckoo(newCapacity)) {
        newCapacity++;
    }
    return newCapacity;
}

template<typename TK, typename TV>
void HashTable_Cuckoo<TK, TV>::insertHelper(TK key, TV value, int typeHashing, int cont, bool isRehashing) {
    if (size >= capacity * 2 * maxFill_Factor || cont >= size/2 || cont >= 10000) {
        rehash(getNewCapacityCuckoo(capacity));
        cont = 0;
    }
    if (typeHashing == 0) {
        size_t index_primary = getIndex_primary(key, capacity);
        size_t index_secondary = getIndex_secondary(key, capacity);

        if (this->primary_table[index_primary].key == key) {
            this->primary_table[index_primary].value = value;
            return;
        } else if (this->secondary_table[index_secondary].key == key) {
            this->secondary_table[index_secondary].value = value;
            return;
        } else if (this->primary_table[index_primary].key == TK()) {
                this->primary_table[index_primary].key = key;
                this->primary_table[index_primary].value = value;
                return;
        } else if (this->primary_table[index_primary].key != TK()) {
            Pair<TK, TV> temp = this->primary_table[index_primary];
            this->primary_table[index_primary] = Pair<TK, TV>(key, value);
            insertHelper(temp.key, temp.value, 1, cont+1);
            return;
        }
    } else {
        size_t index_secondary = getIndex_secondary(key, capacity);
        size_t index_primary = getIndex_primary(key, capacity);

        if (this->secondary_table[index_secondary].key == key) {
            this->secondary_table[index_secondary].value = value;
            return;
        } else if (this->primary_table[index_primary].key == key) {
            this->primary_table[index_primary].value = value;
            return;
        } else if (this->secondary_table[index_secondary].key == TK()) {
            this->secondary_table[index_secondary].key = key;
            this->secondary_table[index_secondary].value = value;
            return;
        } else if (this->secondary_table[index_secondary].key != TK()) {
            Pair<TK, TV> temp = this->secondary_table[index_secondary];
            this->secondary_table[index_secondary] = Pair<TK, TV>(key, value);
            insertHelper(temp.key, temp.value, 0, cont+1);
            return;
        }
    }
}

template<typename TK, typename TV>
void HashTable_Cuckoo<TK, TV>::rehash(size_t newCapacity) {
    auto* old_primary_table = this->primary_table;
    auto* old_secondary_table = this->secondary_table;
    int old_capacity = this->capacity;

    this->primary_table = nullptr;
    this->secondary_table = nullptr;
    this->primary_table = new Pair<TK, TV>[newCapacity];
    this->secondary_table = new Pair<TK, TV>[newCapacity];
    this->capacity = newCapacity;

    for (int i = 0; i < old_capacity; i++) {
        if (old_primary_table[i].key != TK()) {
            insert(old_primary_table[i].key, old_secondary_table[i].value, true);
            size--;
        }
        if (old_secondary_table[i].key != TK()) {
            insert(old_secondary_table[i].key, old_secondary_table[i].value, true);
            size--;
        }
    }

    delete[] old_primary_table;
    delete[] old_secondary_table;

    this->numberReHashes++;
}

template<typename TK, typename TV>
HashTable_Cuckoo<TK, TV>::HashTable_Cuckoo() {
    this->capacity = 11;
    this->size = 0;
    this->numberReHashes = 0;
    this->primary_table = new Pair<TK, TV>[capacity];
    this->secondary_table = new Pair<TK, TV>[capacity];
}

template<typename TK, typename TV>
HashTable_Cuckoo<TK, TV>::HashTable_Cuckoo(size_t capacity) {
    this->capacity = capacity;
    this->size = 0;
    this->numberReHashes = 0;
    this->primary_table = new Pair<TK, TV>[capacity];
    this->secondary_table = new Pair<TK, TV>[capacity];
}

template<typename TK, typename TV>
void HashTable_Cuckoo<TK, TV>::insert(TK key, TV value, bool isRehashing) {
    this->size++;
    insertHelper(key, value, 0, 0);
}

template<typename TK, typename TV>
void HashTable_Cuckoo<TK, TV>::remove(TK key) {
    auto index_primary = getIndex_primary(key, capacity);
    auto index_secondary = getIndex_secondary(key, capacity);

    if (this->primary_table[index_primary].key == key) {
        this->primary_table[index_primary].key = TK();
        this->primary_table[index_primary].value = TV();
        size--;
        return;
    } else if (this->secondary_table[index_secondary].key == key) {
        this->secondary_table[index_secondary].key = TK();
        this->secondary_table[index_secondary].value = TV();
        size--;
        return;
    }
    throw std::invalid_argument("Key not found");
}

template<typename TK, typename TV>
TV HashTable_Cuckoo<TK, TV>::get(TK key) {
    auto index_primary = getIndex_primary(key, capacity);
    auto index_secondary = getIndex_secondary(key, capacity);

    if (this->primary_table[index_primary].key == key) {
        return this->primary_table[index_primary].value;
    } else if (this->secondary_table[index_secondary].key == key) {
        return this->secondary_table[index_secondary].value;
    }
    throw std::invalid_argument("Key not found");
}

template<typename TK, typename TV>
bool HashTable_Cuckoo<TK, TV>::search(TK key) {
    auto index_primary = getIndex_primary(key, capacity);
    auto index_secondary = getIndex_secondary(key, capacity);

    if (this->primary_table[index_primary].key == key) {
        return true;
    } else if (this->secondary_table[index_secondary].key == key) {
        return true;
    }

    return false;
}

template<typename TK, typename TV>
void HashTable_Cuckoo<TK, TV>::print() {
    for (int i = 0; i < capacity; i++) {
        std::cout << i << ": ";
        std::cout << this->primary_table[i] << " ";
        std::cout << this->secondary_table[i] << " ";
        std::cout << std::endl;
    }

    std::cout << "Size: " << size << std::endl;
}

template<typename TK, typename TV>
int HashTable_Cuckoo<TK, TV>::getNumberReHashes() {
    return this->numberReHashes;
}

template<typename TK, typename TV>
HashTable_Cuckoo<TK, TV>::~HashTable_Cuckoo() {
    delete[] this->primary_table;
    delete[] this->secondary_table;
}

#endif //AED_PROYECT_HASHTABLE_CUCKOO_H
