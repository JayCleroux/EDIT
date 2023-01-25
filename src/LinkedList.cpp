#include <fstream>
#include "LinkedList.h"
// output operator overload to display the list with std::cout
std::ostream& operator<<(std::ostream& output, LinkedList& list) {
    auto node = list.m_start;
    int i = 1;
    // format the output with the data of each node
    while (node != nullptr ) {
        output << i << "> " << node->m_data << "\n";
        node = node->m_next;
        i++;
    }
    return output;
}
// destructor to delete each node in the linked list
LinkedList::~LinkedList() {
    auto node = m_start;
    while (node != nullptr) {
        auto temp = node;
        node = node->m_next;
        delete temp;
    }
}

LinkedList::LinkedList() : m_start(nullptr) {}
// method to list one line in the linked list
void LinkedList::list_one(int line, LinkedList& list) {
    auto node = list.m_start;
    int i = 1;
    // iterate through the list until you find the desired line
    while (node != nullptr ) {
        if(line == i){ // output the line
            std::cout << i << "> " << node->m_data << "\n";
            return;
        }
        node = node->m_next;
        i++;
    }
}
// method to save the linked list to a file
void save(LinkedList& list, const std::string& file_name) {

    std::ofstream out_file;
    try{ // try to open the file
        out_file.open(file_name);
        if(!out_file.is_open()){
            std::cout << "Could not open file\n";
        }
    }

    catch(...){
        std::cout << "Exception has occurred trying to open your file!" << std::endl;
    }

    LinkedListNode *node;
    node = list.m_start;
    // while the node is not a null pointer, save the data into the file
    while (node != nullptr ) {
        out_file << node->m_data << "\n";
        node = node->m_next;
    }

    delete node;

    try{
        out_file.close();
    }

    catch(...){
        out_file << "Could not close file." << std::endl;
    }
}
// method to add string as a line in the linked list
void LinkedList::add(std::string str) {
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
// method to insert string into the linked list with a given position
void LinkedList::insert(std::string str, int position) {
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
// method to remove a single line from the linked list
void LinkedList::remove_line(int line) {
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