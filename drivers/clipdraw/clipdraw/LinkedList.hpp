#pragma once

#include "krnl/main.hpp"
#include "krnl/terminal.hpp"
#include "krnl/physmgr.hpp"
#include "thr/prcssthr.hpp"
#include "sys/syscalls.hpp"
#include "hal/intctrl.hpp"
#include "hw/acpi.hpp"
#include "fs/vfs.hpp"
#include "krnl/kheap.hpp"
#include <hal/video.hpp>

// from here: https://gist.github.com/Amadeeus/1c6dc6f5ea3d7b84bb979f7482b70342
//
// TODO: get rid of it all, it doesn't have a license

#pragma GCC optimize ("O0")

template <typename T>
struct Node
{
    T data;
    Node* next;
};

template <typename T>
class LinkedList2
{
public:
    int length_;
    Node<T>* head_;
    Node<T>* tail_;

    LinkedList2();
    ~LinkedList2();

    bool isEmpty()
    {
        return this->head_ == nullptr;
    }
    int length()
    {
        return this->length_;
    }
    void prependNode(T data);
    void appendNode(T data);
    void deleteNodeAt(int idx);
    void deleteNodesByValue(T value);
};

template <typename T>
LinkedList2<T>::LinkedList2()
{
    this->length_ = 0;
    this->head_ = nullptr;
    this->tail_ = nullptr;
}

template <typename T>
LinkedList2<T>::~LinkedList2()
{
    Node<T>* next = this->head_;
    Node<T>* curr = nullptr;
    while (next != nullptr) {
        curr = next;
        next = next->next;
        delete curr;
    }
}

template <typename T>
void LinkedList2<T>::prependNode(T data)
{
    Node<T>* node = new Node<T>;
    node->data = data;
    node->next = this->head_;
    if (isEmpty()) {
        this->tail_ = node;
    }
    this->head_ = node;
    this->length_++;
}

template <typename T>
void LinkedList2<T>::appendNode(T data)
{
    Node<T>* node = nullptr;
    if (isEmpty()) {
        node = new Node<T>;
        this->head_ = node;
    } else {
        node = this->tail_;
        node->next = new Node<T>;
        node = node->next;
    }
    node->data = data;
    node->next = nullptr;
    this->tail_ = node;
    this->length_++;
}

template <typename T>
void LinkedList2<T>::deleteNodeAt(int idx)
{
    if ((idx < 0) || (idx >= this->length_)) {
        KePanic("abort");

    } else {
        Node<T>* node = this->head_;
        if (idx == 0) {  // Update head
            this->head_ = node->next;
            delete node;
            if (isEmpty()) {
                this->tail_ = nullptr;
            }
        } else {
            for (int i = 0; i < idx - 1; i++) {
                node = node->next;
            }
            Node<T>* tmp = node->next;
            node->next = node->next->next;
            delete tmp;
            if (idx == this->length_ - 1) {  // Update tail to point to end node
                this->tail_ = node;
            }
        }
        this->length_--;
    }
}

template <typename T>
void LinkedList2<T>::deleteNodesByValue(T value)
{
    int num_deleted = 0;
    Node<T>* curr = this->head_;
    Node<T>* tmp;
    while (!isEmpty() && curr->data == value) {
        tmp = curr;
        this->head_ = curr->next;
        curr = curr->next;
        delete tmp;
        num_deleted++;
    }
    while (!isEmpty() && curr && curr->next != nullptr) {
        if (curr->next->data == value) {
            tmp = curr->next;
            curr->next = curr->next->next;
            delete tmp;
            if (curr->next == nullptr) {  // Update tail
                this->tail_ = curr;
            }
            num_deleted++;
        }
        curr = curr->next;
    }
    if (isEmpty()) {
        this->tail_ = nullptr;
    }
}