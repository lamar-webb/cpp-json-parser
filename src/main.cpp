#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>


enum class TokenType {
    LeftBrace,    // {
    RightBrace,   // }
    LeftBracket,  // [
    RightBracket, // ]
    Colon,        // :
    Comma,        // ,
    String,       // "hello"
    Number,       // 123, -45.67
    True,         // true
    False,        // false
    Null          // null
};

struct Token {
    TokenType token;
    std::string value;
};

bool is_white_space(char c) {
    return c == ' ' || c == '\t' || c == '\n' || c == '\r';
}

std::vector<Token> tokenize(const std::vector<char>& raw_json) {
        std::vector<Token> tokens;

    for (size_t i{0}; i < raw_json.size(); ++i) {
        char current_char = raw_json[i];
        if (is_white_space(current_char)) {
            //skip white spaces
            continue;
        }

        // single character cases
        if (raw_json[i] == '{') {
            Token left_brace;
            left_brace.token = TokenType::LeftBrace;
            left_brace.value = raw_json[i];
            tokens.push_back(left_brace);
        }else if (raw_json[i] == '}') {
            Token right_brace;
            right_brace.token = TokenType::RightBrace;
            right_brace.value = raw_json[i];
            tokens.push_back(right_brace);
        }else if (raw_json[i] == '[') {
            Token right_bracket;
            right_bracket.token = TokenType::RightBracket;
            right_bracket.value = raw_json[i];
            tokens.push_back(right_bracket);
        }else if (raw_json[i] == ']') {
            Token left_bracket;
            left_bracket.token = TokenType::LeftBracket;
            left_bracket.value = raw_json[i];
            tokens.push_back(left_bracket);
        }else if (raw_json[i] == ':') {
            Token colon;
            colon.token = TokenType::Colon;
            colon.value = raw_json[i];
            tokens.push_back(colon);
        }else if (raw_json[i] == ',') {
            Token comma;
            comma.token = TokenType::Comma;
            comma.value = raw_json[i];
            tokens.push_back(comma);
        }else if (raw_json[i] == '"') {
            Token string;
            std::string parse_string = "";
            ++i; // Step past the opening quote

            while (i < raw_json.size() and raw_json[i] != '"') {
                if (raw_json[i] == '\\' and i + 1 < raw_json.size()){
                    char escaped_char = raw_json[i + 1];
                    if (escaped_char == '"') {
                        parse_string += escaped_char;
                        i += 2;
                        continue;
                    }
                    if (escaped_char == 'n') {
                        parse_string += '\n';
                        i += 2;
                        continue;
                    }
                    if (escaped_char == 't') {
                        parse_string += '\t';
                        i += 2;
                        continue;
                    }
                    if (escaped_char == 'r') {
                        parse_string += '\r';
                        i += 2;
                        continue;
                    }
                }
                parse_string += raw_json[i];
                ++i;
            }

            string.token = TokenType::String;
            string.value = parse_string;
            tokens.push_back(string);

        }else if (std::isdigit(raw_json[i]) or raw_json[i] == '-'){
            Token num;
            std::string num_string = "";
            while (i < raw_json.size() && (std::isdigit(raw_json[i]) or
                               raw_json[i] == '.' or
                               raw_json[i] == 'e' or
                               raw_json[i] == 'E' or
                               raw_json[i] == '+' or
                               raw_json[i] == '-')) {

                num_string += raw_json[i];
                ++i;
                               }
            num.token = TokenType::Number;
            num.value = num_string;
            tokens.push_back(num);
            --i; // go back one so next iteration of outer loop gets the char after the number

        }else if (raw_json[i] == 't') {
            Token truth;
            std::string truth_string;
            if (i + 3 < raw_json.size()) {
                if (raw_json[i + 1] == 'r' and raw_json[i + 2] == 'u' and raw_json[i + 3] == 'e') {
                    truth_string = "true";
                    truth.token = TokenType::True;
                    truth.value = truth_string;
                    tokens.push_back(truth);
                    i += 3; //jump past the 'r', 'u', and 'e'
                }else {

                    throw std::runtime_error("Error: Invalid character detected");
                }
            }
        }else if (raw_json[i] == 'f') {
            Token lies;
            std::string lie_string;
            if (i + 4 < raw_json.size()) {
                if (raw_json[i + 1] == 'a' and raw_json[i + 2] == 'l' and raw_json[i + 3] == 's' and raw_json[i + 4] == 'e') {
                    lie_string = "false";
                    lies.token = TokenType::False;
                    lies.value = lie_string;
                    tokens.push_back(lies);
                    i += 4; //jump past the 'a', 'l', 's' and 'e'
                }else {

                    throw std::runtime_error("Error: Invalid character detected");
                }
            }
        }else if (raw_json[i] == 'n') {
            Token null;
            std::string null_string;
            if (i + 3 < raw_json.size()) {
                if (raw_json[i + 1] == 'u' and raw_json[i + 2] == 'l' and raw_json[i + 3] == 'l') {
                    null_string = "null";
                    null.token = TokenType::Null;
                    null.value = null_string;
                    tokens.push_back(null);
                    i += 3; //jump past the 'u', 'l' and 'l'
                }else {

                    throw std::runtime_error("Error: Invalid character detected");
                }
            }
        }else {
            throw std::runtime_error("Error: Invalid character detected");
        }

    }
        return tokens;

}

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

std::string token_type_to_string(TokenType type) {
    switch (type) {
        case TokenType::LeftBrace: return "LeftBrace";
        case TokenType::RightBrace: return "RightBrace";
        case TokenType::LeftBracket: return "LeftBracket";
        case TokenType::RightBracket: return "RightBracket";
        case TokenType::Colon: return "Colon";
        case TokenType::Comma: return "Comma";
        case TokenType::String: return "String";
        case TokenType::Number: return "Number";
        case TokenType::True: return "True";
        case TokenType::False: return "False";
        case TokenType::Null: return "Null";
        default: return "Unknown";
    }
}

std::vector<char> check_outside_braces( std::vector<char>& raw_json) {
    bool opening_bracket_found = false;
    bool closing_bracket_found = false;

    size_t left{0};
    size_t right{raw_json.size() - 1};

    while (left < right) {
        if (raw_json[left] == '{') {
            opening_bracket_found = true;
        }else if (is_white_space(raw_json[left])) {
            ++left;
        }else {
            // Invalid: first char is not an opening brace
            return {};
        }

        if (raw_json[right] == '}') {
            closing_bracket_found = true;
        }else if (is_white_space(raw_json[right])) {
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


    // Run the tokenizer
    std::vector<Token> tokens = tokenize(valid_braces);

    //  Print the results
    std::cout << "--- TOKENIZER OUTPUT ---\n";
    for (const Token& t : tokens) {
        std::cout << "[" << token_type_to_string(t.token) << "] " << t.value << "\n";
    }

    return 0;
}