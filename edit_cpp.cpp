
#include <iostream>
#include <string>

#include <util.h>
#include <readline/readline.h>
#include <readline/history.h>

bool readline_cpp(std::string prompt, std::string& line) {
    char* _line = readline(prompt.c_str());

    if (_line) {
        line = _line;
        return true;
    }

    return false;
}

bool history_expand_cpp(std::string& line) {
    trim(line);
    char* expansion;
    int result = history_expand((char*)line.c_str(), &expansion);

    if (result) std::cerr << "Bad expansion [" << line << "] gives [" << expansion << ']' << std::endl;

    if (result < 0 || result == 2) {
        delete expansion;
        return false;
    }

    //add_history(expansion);
    if (line != expansion)
        std::cout << '[' << line << "] expanded to [" << expansion << ']' << std::endl;
    line = expansion;
    delete expansion;
    return true;
}

int main(int, char**) {
    std::string line;
    int idx = 1;

    read_history(".test_history");

    for (;;) {
        if (!readline_cpp(std::to_string(idx) + "> ", line)) break;
        trim(line);

        if (line != "" && !history_expand_cpp(line)) continue;

        if (line == "quit") break;
        std::cout << "Command [" << line << ']' << std::endl;
        add_history((char*)line.c_str());
        idx++;
    }

    write_history(".test_history");
}

