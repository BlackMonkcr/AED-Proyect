#ifndef AED_PROYECT_HASHTABLE_CHAINING_H
#define AED_PROYECT_HASHTABLE_CHAINING_H

#include "pair.h"
#include "ForwardList.h"
#include "HashCommonFunctions.cpp"

template<typename TK, typename TV>
class HashTable_Chaining {
    size_t capacity{};
    size_t size{};
    int numberReHashes{};
    const int MAX_COLLISION = 5;
    ForwardList<Pair<TK, TV>>* table = nullptr;

    void rehash(size_t newCapacity);
    int getIndex(TK key, size_t _capacity);

public:
    /*Constructors
    ---------------------------------------------------------------------------*/
    HashTable_Chaining();
    explicit HashTable_Chaining(size_t capacity);

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
    ~HashTable_Chaining();
};

bool isPrimeChaining(size_t n) {
    for (int i = 2; i < n; i++) {
        if (n%i == 0) {
            return false;
        }
    }
    return true;
}

size_t getNewCapacityChaining(size_t capacity) {
    size_t newCapacity = capacity*2;
    while (!isPrimeChaining(newCapacity)) {
        newCapacity++;
    }
    return newCapacity;
}

template<typename TK, typename TV>
int HashTable_Chaining<TK, TV>::getNumberReHashes() {
    return numberReHashes;
}

template<typename TK, typename TV>
int HashTable_Chaining<TK, TV>::getIndex(TK key, size_t _capacity) {
    std::hash<TK> hashFunction;
    return hashFunction(key) % _capacity;
}


template<typename TK, typename TV>
void HashTable_Chaining<TK, TV>::rehash(size_t newCapacity) {
    ForwardList<Pair<TK, TV>>* newTable = new ForwardList<Pair<TK, TV>>[newCapacity];
    for (int i = 0; i < capacity; i++) {
        if (table[i].getSize() > 0) {
            Node<Pair<TK, TV>>* temp = table[i].front();
            while (temp != nullptr) {
                int index = getIndex(temp->data.key, newCapacity);
                newTable[index].push_front(temp->data);
                temp = temp->next;
                cout << temp << endl;
                if (newTable[index].getSize() > MAX_COLLISION) {
                    delete[] newTable;
                    newCapacity = getNewCapacityChaining(newCapacity);
                    rehash(newCapacity);
                    return;
                }
            }
        }
    }

    delete[] table;
    table = newTable;
    capacity = newCapacity;
    numberReHashes++;
}

template<typename TK, typename TV>
HashTable_Chaining<TK, TV>::HashTable_Chaining() {
    capacity = 11;
    size = 0;
    numberReHashes = 0;
    table = new ForwardList<Pair<TK, TV>>[capacity];
}

template<typename TK, typename TV>
HashTable_Chaining<TK, TV>::HashTable_Chaining(size_t capacity) {
    this->capacity = capacity;
    size = 0;
    numberReHashes = 0;
    table = new ForwardList<Pair<TK, TV>>[capacity];
}

template<typename TK, typename TV>
void HashTable_Chaining<TK, TV>::insert(TK key, TV value) {
    int index = getIndex(key, capacity);
    if (table[index].getSize() > MAX_COLLISION) {
        size_t newCapacity = getNewCapacityChaining(capacity);
        rehash(newCapacity);
        insert(key, value);
        return;
    }
    table[index].push_front(Pair<TK, TV>(key, value));
    size++;
}

template<typename TK, typename TV>
void HashTable_Chaining<TK, TV>::remove(TK key) {
    int index = getIndex(key, capacity);
    Node<Pair<TK, TV>>* temp = table[index].front();
    int i = 0;
    while (temp != nullptr) {
        if (temp->data.key == key) {
            table[index].remove(i);
            size--;
            return;
        }
        temp = temp->next;
        i++;
    }
    throw std::out_of_range("Key not found");
}

template<typename TK, typename TV>
TV HashTable_Chaining<TK, TV>::get(TK key) {
    int index = getIndex(key, capacity);
    Node<Pair<TK, TV>>* temp = table[index].front();
    while (temp != nullptr) {
        if (temp->data.key == key) {
            return temp->data.value;
        }
        temp = temp->next;
    }
    throw std::out_of_range("Key not found");
}

template<typename TK, typename TV>
bool HashTable_Chaining<TK, TV>::search(TK key) {
    int index = getIndex(key, capacity);
    Node<Pair<TK, TV>>* temp = table[index].front();
    while (temp != nullptr) {
        if (temp->data.key == key) {
            return true;
        }
        temp = temp->next;
    }
    return false;
}

template<typename TK, typename TV>
void HashTable_Chaining<TK, TV>::print() {
    for (int i = 0; i < capacity; i++) {
        std::cout << i << ": ";
        table[i].print("-> ");
        std::cout << std::endl;
    }
}

template<typename TK, typename TV>
HashTable_Chaining<TK, TV>::~HashTable_Chaining() {
    delete[] table;
}


#endif //AED_PROYECT_HASHTABLE_CHAINING_H
