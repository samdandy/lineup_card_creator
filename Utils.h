#ifndef UTILS_H
#define UTILS_H
#include <string>
#include <stdexcept>
#include <vector>
#include <memory>
using namespace std;

struct lineup_card_headers {
    string date;
    string opponent;
    string venue;
};

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

vector<shared_ptr<Player>> sort_batting_order(const vector<shared_ptr<Player>>& players) {
    vector<shared_ptr<Player>> sorted_players = players;
    for (const auto &player: players) {
        for (size_t i = 0; i < sorted_players.size() - 1; ++i) {
            if (sorted_players[i]->batting_order_position > sorted_players[i + 1]->batting_order_position) {
                swap(sorted_players[i], sorted_players[i + 1]);
            }
        }
    }
    return sorted_players;
}

lineup_card_headers prompt_for_card_headers() {
        lineup_card_headers headers;
        cout << "Enter date (YYYY-MM-DD): ";
        getline(cin, headers.date);
        cout << "Enter opponent team name: ";
        getline(cin, headers.opponent);
        cout << "Enter venue: ";
        getline(cin, headers.venue);
        return headers;
    }

string prompt_for_player_last_name() {
    cout << "Enter player last name: ";
    string input;
    getline(cin, input);
    return input;
}

int prompt_for_player_number(const vector<shared_ptr<Player>>& players) {
    string input;
    int number;
    while (true) {
        cout << "Enter player number: ";
        getline(cin, input);
        try {
            number = string_to_int(input);
            if ((number >= 0 && number <100) && !check_if_number_taken(players, number)) {
                break;
            }
            cout << "Invalid number. Please enter a positive integer and ensure it is not already taken.\n";
        } catch (const invalid_argument& e) {
            cout << "Invalid input. Please enter a positive integer.\n";
        }
    }
    return number;
    }

int prompt_for_player_fielding_position(const vector<shared_ptr<Player>>& players) {
    string input;
    int fielding_pos = 0;
    while (true) {
        cout << "Enter player position 1-10 10=DH(or leave blank for substitute): ";
        getline(cin, input);
        if (input.empty()) {
            break;
        }
        try {
            fielding_pos = string_to_int(input);
            if ((fielding_pos >= 1 && fielding_pos <= 10) && !check_if_position_taken(players, fielding_pos)) {
                break;
            }
            cout << "Invalid position. Must be between 1 and 10 (DH) and not already taken.\n";
        } catch (const invalid_argument& e) {
            cout << "Invalid input. Please enter a number between 1 and 10 (DH).\n";
        }
    }
    return fielding_pos;
}

int prompt_for_player_batting_order_position(const vector<shared_ptr<Player>>& players) {
    string input;
    int batting_order_pos = 0;
    while (true) {
            cout << "Enter batter order position 1-9: ";
            getline(cin, input);
            if (input.empty()) {
                break;
            }
            try {
                batting_order_pos = string_to_int(input);
                if ((batting_order_pos >= 1 && batting_order_pos <= 9) && !check_if_batting_order_position_taken(players, batting_order_pos)) {
                    break;
                }
                cout << "Invalid batting order. Must be between 1 and 9 and not already taken.\n";
            } catch (const invalid_argument& e) {
                cout << "Invalid input. Please enter a number between 1 and 9.\n";
            }
        }
    return batting_order_pos;
}



void startup_art(){
    cout << "======================================" << endl;
    cout << "     SHUM'S LINEUP CARD APP          " << endl;
    cout << "======================================" << endl;
}

bool check_position_input(const string& type, const int& input) {
    if (type == "batting_order_position" || type == "fielding_position") {
        return input >= 1 && input <= 9;
    }
    return false;
}


#endif 