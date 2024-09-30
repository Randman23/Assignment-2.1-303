#pragma once
#ifndef SINGLE_LINKED_LIST_H
#define SINGLE_LINKED_LIST_H

#include <iostream>
#include <stdexcept>

template <typename Item_Type>
class Node {
public:
    Item_Type item;
    Node* next;

    Node(const Item_Type& item) : item(item), next(nullptr) {}
};

template <typename Item_Type>
class Single_Linked_List {
private:
    Node<Item_Type>* head;
    Node<Item_Type>* tail;
    size_t num_items;

public:
    Single_Linked_List() : head(nullptr), tail(nullptr), num_items(0) {}
    ~Single_Linked_List();

    void push_front(const Item_Type& item);
    void push_back(const Item_Type& item);
    Item_Type pop_front();
    Item_Type pop_back();
    Item_Type front() const;
    Item_Type back() const;
    bool empty() const;
    void insert(size_t index, const Item_Type& item);
    bool remove(size_t index);
    size_t find(const Item_Type& item) const;
    size_t size() const;
    void print() const;
};

template <typename Item_Type>
Single_Linked_List<Item_Type>::~Single_Linked_List() {
    while (!empty()) {
        pop_front();
    }
}

template <typename Item_Type>
void Single_Linked_List<Item_Type>::push_front(const Item_Type& item) {
    Node<Item_Type>* new_node = new Node<Item_Type>(item);
    new_node->next = head;
    head = new_node;
    if (tail == nullptr) {
        tail = new_node;
    }
    num_items++;
}

template <typename Item_Type>
void Single_Linked_List<Item_Type>::push_back(const Item_Type& item) {
    Node<Item_Type>* new_node = new Node<Item_Type>(item);
    if (tail) {
        tail->next = new_node;
    }
    else {
        head = new_node;
    }
    tail = new_node;
    num_items++;
}

template <typename Item_Type>
Item_Type Single_Linked_List<Item_Type>::pop_front() {
    if (empty()) {
        throw std::out_of_range("Pop from empty list");
    }
    Node<Item_Type>* temp = head;
    Item_Type removed_item = temp->item;
    head = head->next;
    delete temp;
    if (head == nullptr) {
        tail = nullptr;
    }
    num_items--;
    return removed_item;
}

template <typename Item_Type>
Item_Type Single_Linked_List<Item_Type>::pop_back() {
    if (empty()) {
        throw std::out_of_range("Pop from empty list");
    }
    if (head == tail) {
        Item_Type removed_item = head->item;
        delete head;
        head = tail = nullptr;
        num_items--;
        return removed_item;
    }

    Node<Item_Type>* current = head;
    while (current->next != tail) {
        current = current->next;
    }

    Item_Type removed_item = tail->item;
    delete tail;
    tail = current;
    tail->next = nullptr;
    num_items--;
    return removed_item;
}

template <typename Item_Type>
Item_Type Single_Linked_List<Item_Type>::front() const {
    if (empty()) {
        throw std::out_of_range("List is empty");
    }
    return head->item;
}

template <typename Item_Type>
Item_Type Single_Linked_List<Item_Type>::back() const {
    if (empty()) {
        throw std::out_of_range("List is empty");
    }
    return tail->item;
}

template <typename Item_Type>
bool Single_Linked_List<Item_Type>::empty() const {
    return num_items == 0;
}

template <typename Item_Type>
void Single_Linked_List<Item_Type>::insert(size_t index, const Item_Type& item) {
    if (index <= 0) {
        push_front(item);
    }
    else if (index >= num_items) {
        push_back(item);
    }
    else {
        Node<Item_Type>* new_node = new Node<Item_Type>(item);
        Node<Item_Type>* current = head;
        for (size_t i = 0; i < index - 1; i++) {
            current = current->next;
        }
        new_node->next = current->next;
        current->next = new_node;
        num_items++;
    }
}

template <typename Item_Type>
bool Single_Linked_List<Item_Type>::remove(size_t index) {
    if (index < 0 || index >= num_items) {
        return false;
    }
    if (index == 0) {
        pop_front();
        return true;
    }

    Node<Item_Type>* current = head;
    for (size_t i = 0; i < index - 1; i++) {
        current = current->next;
    }
    Node<Item_Type>* to_remove = current->next;
    if (to_remove == tail) {
        tail = current;
    }
    current->next = to_remove->next;
    delete to_remove;
    num_items--;
    return true;
}

template <typename Item_Type>
size_t Single_Linked_List<Item_Type>::find(const Item_Type& item) const {
    Node<Item_Type>* current = head;
    size_t index = 0;
    while (current != nullptr) {
        if (current->item == item) {
            return index;
        }
        current = current->next;
        index++;
    }
    return num_items;
}

template <typename Item_Type>
size_t Single_Linked_List<Item_Type>::size() const {
    return num_items;
}

template <typename Item_Type>
void Single_Linked_List<Item_Type>::print() const {
    Node<Item_Type>* current = head;
    while (current != nullptr) {
        std::cout << current->item << " ";
        current = current->next;
    }
    std::cout << std::endl;
}

#endif // SINGLE_LINKED_LIST_H
