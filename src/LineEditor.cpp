//
// Created by Jay on 2023-01-21.
//

#include <fstream>
#include <sstream>
#include <regex>
#include "LineEditor.h"

LineEditor::LineEditor(const std::string& file_name) {
    m_current_line = 0;
    m_file_name = file_name;
    m_last_line = 0;
}

LineEditor::LineEditor(LinkedList& list, const std::string& file_name) {
    m_file_name = file_name;
    auto node = list.m_start;
    int i = 1;
    while (node != nullptr ) {
        node = node->m_next;
        m_last_line = i;
        i++;
        m_current_line = i;
    }

}

void LineEditor::run(const std::string& file_name) {

    // create a new linked list
    LinkedList list;
    std::stringstream();
    std::ifstream in_file; // declare the input and output stream
    std::ofstream out_file;

    // open the file for input, handle any exception that may occur
    try{
        in_file.open(file_name);
        if(!in_file.is_open()){
            throw std::exception();
        }
    }

    catch(...){
        std::cout << "Exception has occurred trying to open your file!" << std::endl;
    }

    std::string result, text;
    // read the file one line at a time
    try{

        while(getline(in_file, text)){
            for(char i : text)
            {
                std::string fileChar = std::string(1,i);
                result += fileChar;
            }
            list.add(result);
            result = "";
        }
    }

    catch(...){
        std::cout << "Could not read/write to file." << std::endl;
    }

    try{
        in_file.close();
    }
    catch(...){
        std::cout << "Could not close file." << std::endl;
    }

    LineEditor le(list, file_name);
    std::cout << list << le.m_current_line << ">";
    std::string input;
    getline(std::cin, input);

    char command;
    int start, end;

    bool dont_list = false;

    while(input != "E"){
        std::stringstream ss;
        ss << input;
        ss >> command >> start >> end;
        if(!ss){
            ss.clear();
            ss << input;
            ss >> command >> start;
            if(!ss){
                // potential command with no indices
                if(input == "L"){
                    std::cout << list;
                    dont_list = true;
                }else if(input == "D"){
                    list.remove_line(le.m_current_line);
                    le.m_last_line -=1;
                    le.m_current_line = le.m_last_line + 1;
                }
                else if(regex_match(input, std::regex("^(I [1-9]+)"))){

                    if(start < le.m_last_line){
                        le.m_current_line = start;
                        dont_list = true;
                    }
                }else{
                    // regular text
                    list.insert(input, le.m_current_line);
                    le.m_current_line += 1;
                    le.m_last_line += 1;
                }
            }else{
                // command with one index
                if(regex_match(input, std::regex("^(D [1-9]+)"))){
                    list.remove_line(start);
                    le.m_last_line -= 1;
                    le.m_current_line = le.m_last_line + 1;
                }
                else if(regex_match(input, std::regex("^(I [1-9]+)"))){
                    if(start < le.m_last_line){
                        le.m_current_line = start;
                        dont_list = true;
                    }
                }
            }
        }else{
            //command with two parameters
            if(regex_match(input, std::regex("^(D [1-9]+ [1-9]+)"))){
                int difference = end - start;
                for (int i = 0; i <= difference; i++) {
                    list.remove_line(start);
                    le.m_last_line -= 1;
                    le.m_current_line = le.m_last_line + 1;
                }
            }
        }

        if(!dont_list){
            std::cout << list;
        }

        dont_list = false;
        std::cout << le.m_current_line << ">";
        getline(std::cin, input);
    }

    save(list, file_name);
}




