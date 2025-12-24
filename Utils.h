#ifndef UTILS_H
#define UTILS_H
#include <string>
#include <stdexcept>
using namespace std;

int string_to_int(const string& input) {
    try {
        int value = stoi(input);
        return value;
    } catch (const exception& e) {
        throw invalid_argument("Invalid input: " + input);
    }
}

string to_lower(string& str){
    for (char &c : str) {
        c = tolower(c);
    }
    return str;
}

#endif 