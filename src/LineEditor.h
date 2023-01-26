#ifndef ASSIGNMENT1_LINEEDITOR_H
#define ASSIGNMENT1_LINEEDITOR_H

#include <string>
#include "LinkedList.h"

class LineEditor {
private:
    int m_current_line;
    int m_last_line;
    std::string m_file_name;

public:
    explicit LineEditor(const std::string& file_name);
    LineEditor(LinkedList& list, const std::string& file_name);
    static void run(const std::string& file_name);

};

#endif //ASSIGNMENT1_LINEEDITOR_H
