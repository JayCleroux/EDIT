//
// Created by Jay on 2023-01-21.
//

#ifndef ASSIGNMENT1_LINKEDLIST_H
#define ASSIGNMENT1_LINKEDLIST_H

#include <iostream>
#include <string>
#include <utility>

class LinkedListNode {
public:
    std::string m_data {-1};
    LinkedListNode* m_next {nullptr};
};

class LinkedList {
    friend class LineEditor;
private:
    LinkedListNode* m_start {nullptr};

public:
    LinkedList() : m_start(nullptr) {}
    virtual ~LinkedList() {
        auto node = m_start;
        while (node != nullptr) {
            auto temp = node;
            node = node->m_next;
            delete temp;
        }
    }

    void add(std::string str) {
        // create a new node
        auto new_node = new LinkedListNode();
        new_node->m_data = std::move(str);

        if (m_start == nullptr) {
            // attach it to the start of the linked list
            m_start = new_node;
        } else {
            // attach it the end of an existing chain
            auto node = m_start;
            LinkedListNode* prev = nullptr;
            // find the last node
            while (node != nullptr) {
                prev = node;
                node = node->m_next;
            }
            // attach new node to the node at the end of the chain
            prev->m_next = new_node;
        }
    }

    void insert(std::string str, int position) {

        // create a new node
        auto new_node = new LinkedListNode();
        new_node->m_data = std::move(str);

        // locate node to insert before
        auto node = m_start;
        LinkedListNode* prev = nullptr;

        int curr_pos = 1;
        while (node != nullptr) {
            if (curr_pos++ == position) {
                break;
            }
            prev = node;
            node = node->m_next;
        }

        // is this the first node?
        if (prev == nullptr) {
            // first node
            new_node->m_next = m_start;
            m_start = new_node;
        } else {
            // other node
            new_node->m_next = prev->m_next;
            prev->m_next = new_node;
        }
    }

    void remove_line(int line) {
        // find the last node in the chain
        auto node = m_start;
        LinkedListNode* prev = nullptr;
        int i = 1;
        while (node != nullptr) {

            // find the node with the right data
            if (i == line) {
                break;
            }
            i++;
            prev = node;
            node = node->m_next;
        }

        // did we find the node we want to delete?
        if (node != nullptr) {
            // determine first or other node
            if (prev == nullptr) {
                // deleting the first node
                m_start = node->m_next;
            } else {
                // a different node in the chain
                prev->m_next = node->m_next;
            }

            delete node;
        }
    }

    friend std::ostream& operator<<(std::ostream& output, LinkedList& list);
    friend void save(LinkedList& list, const std::string& file_name);
};

#endif //ASSIGNMENT1_LINKEDLIST_H
