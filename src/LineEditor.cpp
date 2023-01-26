#include <fstream>
#include <sstream>
#include <regex>
#include "LineEditor.h"
// constructor to receive the file
LineEditor::LineEditor(const std::string& file_name) {
    m_current_line = 0;
    m_file_name = file_name;
    m_last_line = 0;
}
// constructor to set the current and last line of the line editor
LineEditor::LineEditor(LinkedList& list, const std::string& file_name) {
    m_file_name = file_name;
    m_current_line = 0;
    m_last_line = 0;
    auto node = list.m_start;
    int i = 1;
    while (node != nullptr ) {
        node = node->m_next;
        m_last_line = i;
        i++;
        m_current_line = i;
    }
}
// this will make the file into a linked list
// it will then allow the user to edit the file line by line and save it
void LineEditor::run(const std::string& file_name) {
    LinkedList list;
    std::stringstream();
    std::ifstream in_file;
    std::ofstream out_file;
    std::string result, text;
    bool new_file_was_made = false;
    char command;
    int start, end;
    // open the file for input, handle any exception that may occur
    try{
        in_file.open(file_name);
        // if there is no file available, create one
        if(!in_file.is_open()){
            std::fstream new_file;
            new_file.open(file_name, std::ios::out);
            new_file.close();
            new_file_was_made = true;
            in_file.open(file_name);
        }
    }
    catch(...){
        std::cout << "Exception has occurred trying to open your file!";
    }

    try{ // read the file one line at a time
        while(getline(in_file, text)){
            for(char i : text){ // take each character and put it into a string
                std::string fileChar = std::string(1,i);
                result += fileChar;
            }
            list.add(result); // add the line to the linked list
            result = "";
        }
    }
    catch(...){
        std::cout << "Could not read/write to file." << std::endl;
    }

    try{ // close the file
        in_file.close();
    }
    catch(...){
        std::cout << "Could not close file." << std::endl;
    }
    // output the linked list with the current line
    LineEditor le(list, file_name);
    if(new_file_was_made || le.m_last_line <= 0){
        list.remove_line(1);
        le.m_current_line = 1;
        le.m_last_line = 0;
        std::cout << le.m_current_line << ">";
    }else{
        std::cout << list << le.m_current_line << ">";
    }

    std::string input;
    getline(std::cin, input); // allow for input, and get the line
    // E represents exit and save
    while(input != "E"){
        std::stringstream ss;
        ss << input; // put the user input into a stringstream
        ss >> command >> start >> end;
        // check if it is a potential command with 2 parameters
        if(!ss){ // if not clear the stream, grab the input again and check if
            ss.clear(); // it is a potential command with 1 parameter
            ss << input;
            ss >> command >> start;
            if(!ss){ // if not, it is a command with no parameter or plain text
                if(input == "L"){
                    std::cout << list;
                }else if(input == "D"){
                    // delete the current line only if it is less than or equal
                    // to the less line, adjust line values
                    if(le.m_current_line <= le.m_last_line){
                        list.remove_line(le.m_current_line);
                        le.m_last_line -=1;
                        le.m_current_line = le.m_last_line;
                    }
                }else if(input == "I"){ // if the input is just "I", adjust line
                    if(le.m_current_line >= 1){ // positions for input on the
                        le.m_current_line -= 1; // previous line
                    }
                }else{ // regular text
                    // insert regular text into the linked list
                    list.insert(input, le.m_current_line);
                    le.m_current_line += 1; // adjust line values
                    le.m_last_line += 1;
                }
            }else{ // command with one parameter
                if(regex_match(input, std::regex("^(D [0-9]+)"))){
                    // delete 1 line as long as the parameter is less than the
                    // last line and greater than 1
                    if(start <= le.m_last_line && start >= 1){
                        list.remove_line(start);
                        le.m_last_line -= 1; // adjust line values
                        le.m_current_line = le.m_last_line;
                    }
                }else if(regex_match(input, std::regex("^(I [0-9]+)"))){
                    // adjust line values for input on the selected line
                    // allow for input 1 line beyond the last line
                    if(start <= (le.m_last_line + 1) && start >= 1){
                        le.m_current_line = start;
                    }
                }else if(regex_match(input, std::regex("^(L [0-9]+)"))){
                    // output the line the user has requested
                    if(start <= le.m_last_line && start >= 1){
                        list.list_one(start, list);
                        le.m_current_line = start;
                    }
                }
            }
        }else{ //command with two parameters
            if(regex_match(input, std::regex("^(D [0-9]+ [0-9]+)"))){
                int difference = end - start; // get the difference
                // and use the remove line method for list
                for (int i = 0; i <= difference; i++){
                    list.remove_line(start);
                    le.m_last_line -= 1; // adjust line values
                    le.m_current_line = le.m_last_line;
                }
            }else if(regex_match(input, std::regex("^(L [0-9]+ [0-9]+)"))){
                for (int i = start; i <= end; i++){ // List each line from start
                    LinkedList::list_one(i, list); // range to end
                    le.m_current_line = end;
                }
            }
        }
        // display the current working line
        std::cout << le.m_current_line << ">";
        getline(std::cin, input); // allow for input
    }
    save(list, file_name); // exit and save
}