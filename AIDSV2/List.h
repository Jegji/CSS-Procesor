#pragma once
#include <iostream>
template<typename T>
class Node {
public:
    T* data;
    Node* prev;
    Node* next;

    Node(T* value) {
        data = value;
        prev = nullptr;
        next = nullptr;
    }
    Node() {
        data = nullptr;
        prev = nullptr;
        next = nullptr;        
    }
};

template<typename T>
class List {
private:
    Node<T>* head;
    Node<T>* tail;
    Node<T>* nodebyid(int id);
    size_t size;
public:
    List();
    ~List();
    int length();
    void insertFront(T* value);
    void insertBack(T* value);
    void removeFront(); 
    void removeBack();
    void printList();
    void remove(int id);
    T* getbyid(int id);
};

template<typename T>
inline Node<T>* List<T>::nodebyid(int id)
{
    if (id >= size)return nullptr;
    Node<T>* temp = head;
    for (int i = 0; i < id; i++)
        temp = temp->next;
    return temp;
}

template<typename T>
inline List<T>::List()
{
    head = nullptr;
    tail = nullptr;
    size = 0;
}

template<typename T>
inline List<T>::~List()
{
    if (head != nullptr) {
        Node<T>* temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
            delete temp->prev;
        }delete temp, head, tail;
    }
}

template<typename T>
inline int List<T>::length()
{
    return size;
}

template<typename T>
inline void List<T>::insertFront(T* value)
{
    Node<T>* newNode = new Node<T>(value);

    if (head == nullptr) {
        head = newNode;
        tail = newNode;
    }
    else {
        head->prev = newNode;
        newNode->next = head;
        head = newNode;
    }
}

template<typename T>
inline void List<T>::insertBack(T* value)
{
    Node<T>* newNode = new Node<T>(value);
    size++;
    if (tail == nullptr) {
        head = newNode;
        tail = newNode;
    }
    else {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }
}

template<typename T>
inline void List<T>::removeFront()
{
    if (head == nullptr) {
        return;
    }

    Node<T>* temp = head;
    head = head->next;

    if (head == nullptr) {
        tail = nullptr;
    }
    else {
        head->prev = nullptr;
    }

    delete temp;
}

template<typename T>
inline void List<T>::removeBack()
{
    if (tail == nullptr) {
        return;
    }

    Node<T>* temp = tail;
    tail = tail->prev;

    if (tail == nullptr) {
        head = nullptr;
    }
    else {
        tail->next = nullptr;
    }

    delete temp;
}

template<typename T>
inline void List<T>::printList()
{
    Node<T>* current = head;

    while (current != nullptr) {
        std::cout << current->data << " ";
        current = current->next;
    }

    std::cout << std::endl;
}

template<typename T>
inline void List<T>::remove(int id)
{
    Node<T>* temp = nodebyid(id);
    if (temp->next == nullptr) {
        tail = temp->prev;
    }
    else {
        temp->next->prev = temp->prev;
    }
    if (temp->prev == nullptr) {
        head = temp->next;
    }
    else {
        temp->prev->next = temp->next;
    }
    size--;
}

template<typename T>
inline T* List<T>::getbyid(int id)
{
    if (size > id) {
        return nodebyid(id)->data;
    }return nullptr;
}
