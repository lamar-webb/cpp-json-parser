#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>

std::unordered_map<char, std::string> acceptable_whitespaces = {
    {' ',  "space"},
    {'\t', "horizontal tab"},
    {'\n', "line feed"},
    {'\r', "carriage return"}
};

void print_chars(const std::vector<char>& json) {
    for (char c : json) {
        if (c == ' ') {
            std::cout << ' ';
        }else if (c == '\n') {
            std::cout << "//n";
        }else if (c == '\t') {
            std::cout << "//t";
        }else {
            std::cout << c;
        }
    }
    std::cout << "\n";
}

std::vector<char> check_outside_braces( std::vector<char>& raw_json) {
    bool opening_bracket_found = false;
    bool closing_bracket_found = false;

    size_t left{0};
    size_t right{raw_json.size() - 1};

    while (left < right) {
        if (raw_json[left] == '{') {
            opening_bracket_found = true;
        }else if (acceptable_whitespaces.count(raw_json[left]) == 1) {
            ++left;
        }else {
            // Invalid: first char is not an opening brace
            return {};
        }

        if (raw_json[right] == '}') {
            closing_bracket_found = true;
        }else if (acceptable_whitespaces.count(raw_json[right]) == 1) {
            --right;
        }else {
            // Invalid: last char is not an closing brace
            return {};
        }

        if (opening_bracket_found and closing_bracket_found) {
            return std::vector<char>(raw_json.begin() + left, raw_json.begin() + right + 1);

        }
    }

    return {};
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

    if (json.size() < 2) {
        // Invalid - string is less than 2 characters
        return 1;
    }

    std::vector<char> valid_braces = check_outside_braces(json);

    if (valid_braces.empty()) {
        std::cout << "Invalid: outside braces. \n";
        return 1;
    }


    print_chars(valid_braces);
    return 0;
}
