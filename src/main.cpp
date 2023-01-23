#include <string>
#include "LineEditor.h"

using namespace std;

int main(int argc, char* argv[]) {

    string file_name = "F:\\";
    file_name += (string)argv[2];

    LineEditor le(file_name);

    LineEditor::run(file_name);

}

