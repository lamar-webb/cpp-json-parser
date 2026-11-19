#include <iostream>
#include <fstream>
#include <string>
#include <vector>

static bool check_end_bracket(const char c1, const char c2) {
    if (c1 == '{' and c2 == '}' ) {
        return true;
    }
    return false;
}

int main(int argc, char* argv[]) {
    std::vector<std::string> args;
    for (int i{0}; i < argc; ++i){
        std::string arg = argv[i];
        args.push_back(arg);
    }

    if (argc < 2) {
        std::cerr << "Usage: cpp_json_parser <filename>\n";
        return 1;
    }

    std::vector<char>json;
    std::string file_name = args[1];
    std::ifstream file(file_name, std::ios::binary);
    if (!file.is_open()) {
        std::cout << "\nFile could not be opened\n";
        return 1;
    }
    char c;
    while (file.get(c)) {
        json.push_back(c);
    }

    if (json.size() >= 2 and
    check_end_bracket(json.front(), json.back())) {
        std::cout << "Valid\n";
        return 0;
    }

    std::cout << "Invalid\n";
    return 1;

}
