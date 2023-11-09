#ifndef AED_PROYECT_HASHTABLE_OPENADDRESSING_H
#define AED_PROYECT_HASHTABLE_OPENADDRESSING_H


#include "HashCommonFunctions.cpp"
using namespace std;


template<typename TK, typename TV>
class HashTable_OpenAddressing {
    float maxFillFactor{};
    int size{};
    int capacity{};
    int numberReHashes{};
    Pair<TK, TV>* table;

    int getIndex(TK key, int _capacity);
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

bool isPrimeOpenAddressing(int n) {
    for (int i = 2; i < n; i++) {
        if (n%i == 0) {
            return false;
        }
    }
    return true;
}

int getNewCapacityOpenAddressing(int capacity) {
    int newCapacity = capacity*2;
    while (!isPrimeOpenAddressing(newCapacity)) {
        newCapacity++;
    }
    return newCapacity;
}

template<typename TK, typename TV>
int HashTable_OpenAddressing<TK, TV>::getIndex(TK key, int _capacity) {
    std::hash<TK> hashFunction;
    return hashFunction(key) % _capacity;
}

template<typename TK, typename TV>
HashTable_OpenAddressing<TK, TV>::~HashTable_OpenAddressing() {
    delete[] this->table;
}

template<typename TK, typename TV>
int HashTable_OpenAddressing<TK, TV>::getNumberReHashes() {
    return this->numberReHashes;
}

template<typename TK, typename TV>
void HashTable_OpenAddressing<TK, TV>::print() {
    for (int i = 0; i < this->capacity; i++) {
        if (this->table[i].key != TK()) {
            cout << "Bucket N°" << i << ": "
                 << this->table[i].key << " " << this->table[i].value << endl;
        } else {
            cout << "Bucket N°" << i << ": " << "Empty" << endl;
        }
    }
}

template<typename TK, typename TV>
bool HashTable_OpenAddressing<TK, TV>::search(TK key) {
    int index = getIndex(key, this->capacity);
    int firstIndex = index;
    while (this->table[index].key != TK() && this->table[index].key != key) {
        index++;
        if (index == firstIndex-1) {
            return false;
        } else if (index >= this->capacity) {
            index = 0;
        }
    }

    if (this->table[index].key == key) {
        return true;
    }

    return false;
}

template<typename TK, typename TV>
TV HashTable_OpenAddressing<TK, TV>::get(TK key) {
    int index = getIndex(key, this->capacity);
    int firstIndex = index;
    while (this->table[index].key != TK() && this->table[index].key != key) {
        index++;
        if (index == firstIndex-1) {
            throw std::out_of_range("Key not found");
        } else if (index >= this->capacity) {
            index = 0;
        }
    }

    if (this->table[index].key == key) {
        return this->table[index].value;
    }

    return TV();
}

template<typename TK, typename TV>
void HashTable_OpenAddressing<TK, TV>::remove(TK key) {
    int index = getIndex(key, this->capacity);
    int firstIndex = index;
    while (this->table[index].key != TK() && this->table[index].key != key) {
        index++;
        if (index == firstIndex-1) {
            throw std::out_of_range("Key not found");
        } else if (index >= this->capacity) {
            index = 0;
        }
    }

    if (this->table[index].key == key) {
        this->table[index] = Pair<TK, TV>();
        this->size--;
    }
}

template<typename TK, typename TV>
void HashTable_OpenAddressing<TK, TV>::insert(TK key, TV value) {
    if (this->size > this->capacity * this->maxFillFactor) {
        rehash();
    }

    int index = getIndex(key, this->capacity);
    while (this->table[index].key != TK() && this->table[index].key != key) {
        index++;
        if (index >= this->capacity) {
            index = 0;
        }
    }

    this->table[index] = Pair<TK, TV>(key, value);
    this->size++;
}

template<typename TK, typename TV>
HashTable_OpenAddressing<TK, TV>::HashTable_OpenAddressing(float maxFillFactor, int capacity) {
    this->maxFillFactor = maxFillFactor;
    this->size = 0;
    this->capacity = capacity;
    this->table = new Pair<TK, TV>[capacity];
    this->numberReHashes = 0;
}

template<typename TK, typename TV>
HashTable_OpenAddressing<TK, TV>::HashTable_OpenAddressing() {
    this->maxFillFactor = 0.75;
    this->size = 0;
    this->capacity = 11;
    this->table = new Pair<TK, TV>[this->capacity];
    this->numberReHashes = 0;
}

template<typename TK, typename TV>
void HashTable_OpenAddressing<TK, TV>::rehash() {
    this->numberReHashes++;
    int newCapacity = getNewCapacityOpenAddressing(this->capacity);
    auto* newTable = new Pair<TK, TV>[newCapacity];
    for (int i = 0; i < this->capacity; i++) {
        if (this->table[i].key != TK()) {
            int index = getIndex(this->table[i].key, newCapacity);
            while (newTable[index].key != TK()) {
                index++;
            }
            newTable[index] = this->table[i];
        }
    }
    delete[] this->table;
    this->table = newTable;
    this->capacity = newCapacity;
}


#endif //AED_PROYECT_HASHTABLE_OPENADDRESSING_H
