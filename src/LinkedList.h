#ifndef ASSIGNMENT1_LINKEDLIST_H
#define ASSIGNMENT1_LINKEDLIST_H

#include <iostream>
#include <string>
#include <utility>

class LinkedListNode {
public:
    std::string m_data;
    LinkedListNode* m_next;
};

class LinkedList {
    friend class LineEditor;
private:
    LinkedListNode* m_start;
public:
    LinkedList();
    virtual ~LinkedList();
    static void list_one(int line, LinkedList& list);
    void add(std::string str);
    void insert(std::string str, int position);
    void remove_line(int line);
    friend std::ostream& operator<<(std::ostream& output, LinkedList& list);
    friend void save(LinkedList& list, const std::string& file_name);
};

#endif //ASSIGNMENT1_LINKEDLIST_H
