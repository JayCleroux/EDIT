#include <string>
#include "LineEditor.h"

int main(int argc, char* argv[]) {
    if (argc < 1) return 1;
    std::string file_name = "F:\\";
    file_name += (std::string)argv[1];

    LineEditor le(file_name);

    LineEditor::run(file_name);

}

