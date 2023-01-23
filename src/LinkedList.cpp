//
// Created by Jay on 2023-01-21.
//

#include <fstream>
#include "LinkedList.h"

std::ostream& operator<<(std::ostream& output, LinkedList& list) {
    auto node = list.m_start;
    int i = 1;

    while (node != nullptr ) {
        output << i << "> " << node->m_data << "\n";
        node = node->m_next;
        i++;
    }

    return output;
}

void save(LinkedList& list, const std::string& file_name) {
    std::ofstream out_file;
    try{
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
