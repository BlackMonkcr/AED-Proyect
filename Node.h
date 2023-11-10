#ifndef AED_PROYECT_NODE_H
#define AED_PROYECT_NODE_H

template<typename T>
struct Node {
    T data;
    Node* next;

    explicit Node(T data) : data(data), next(nullptr) {}

    ~Node() {
        delete next;
    }
};

#endif //AED_PROYECT_NODE_H
