#ifndef AED_PROYECT_FORWARDLIST_H
#define AED_PROYECT_FORWARDLIST_H

#include <iostream>
#include <Node.h>
using namespace std;

template<typename T>
class ForwardList {
    Node<T> *head = nullptr;
    int size{};

public:
    /* Constructors
     ---------------------------------------------------------------------------*/
    ForwardList();
    explicit ForwardList(T data);

    /* Methods
     ---------------------------------------------------------------------------*/
    Node<T>* front() {
        return head;
    }
    void push_front(T data);
    void pop_front();
    void remove(int index);
    void print(string separator = " ");
    int getSize();
    T operator[](int index);

    /* Destructor
     ---------------------------------------------------------------------------*/
    ~ForwardList();
};

template<typename T>
void ForwardList<T>::remove(int index) {
    if (index >= size) {
        throw out_of_range("Index out of range");
    }

    if (index == 0) {
        pop_front();
        return;
    }

    Node<T>* temp = head;
    for (int i = 0; i < index - 1; i++) {
        temp = temp->next;
    }

    Node<T>* temp2 = temp->next;
    temp->next = temp2->next;
    delete temp2;
    size--;
}

template<typename T>
T ForwardList<T>::operator[](int index) {
    Node<T>* temp = head;
    if (index >= size) {
        throw out_of_range("Index out of range");
    }

    for (int i = 0; i < index; i++) {
        temp = temp->next;
    }

    return temp->data;
}

template<typename T>
ForwardList<T>::ForwardList() {
    head = nullptr;
    size = 0;
}

template<typename T>
ForwardList<T>::ForwardList(T data) {
    head = new Node<T>(data);
    size = 1;
}

template<typename T>
void ForwardList<T>::push_front(T data) {
    if (head == nullptr) {
        head = new Node<T>(data);
        size = 1;
        return;
    }
    auto* newNode = new Node<T>(data);
    newNode->next = head;
    head = newNode;
    size++;
}

template<typename T>
void ForwardList<T>::pop_front() {
    if (head != nullptr) {
        Node<T>* temp = head;
        head = head->next;
        delete temp;
        size--;
    }
}


template<typename T>
void ForwardList<T>::print(string separator) {
    Node<T>* temp = head;
    while (temp != nullptr) {
        cout << temp->data << separator;
        temp = temp->next;
    }
    cout << endl;
}

template<typename T>
int ForwardList<T>::getSize() {
    return size;
}

template<typename T>
ForwardList<T>::~ForwardList() {
    delete head;
}

#endif //AED_PROYECT_FORWARDLIST_H
