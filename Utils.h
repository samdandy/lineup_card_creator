#ifndef UTILS_H
#define UTILS_H
#include <string>
#include <stdexcept>
#include <vector>
#include <memory>
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

bool check_if_position_taken(const vector<shared_ptr<Player>>& players, const int& position) {
    for (const auto &player : players) {
        if (player->position == position){
            return true;
        }
    }
    return false;
}

bool check_if_number_taken(const vector<shared_ptr<Player>>& players, const int& number) {
    for (const auto &player : players) {
        if (player->number == number){
            return true;
        }
    }
    return false;
}

bool check_if_batting_order_position_taken(const vector<shared_ptr<Player>>& players, const int& batting_order_position) {
    for (const auto &player : players) {
        if (player->batting_order_position == batting_order_position){
            return true;
        }
    }
    return false;
}
#endif 