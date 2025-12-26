#ifndef LINEUPCARD_H
#define LINEUPCARD_H

#include <string>
#include <vector>
#include <memory>
#include "Player.h"
#include "Utils.h"

using namespace std;

struct lineup_card_headers {
    string date;
    string opponent;
    string venue;
};


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


class LineupCard {
public:
    lineup_card_headers header;
    vector<shared_ptr<Player>> players;

    LineupCard(
        const lineup_card_headers& headers,
        const vector<shared_ptr<Player>>& players
    )
        : header(headers), players(players) {}
    LineupCard() : header({"", "", ""}), players({}) {}
    LineupCard(const LineupCard &lc){
        cout << "Copied LineupCard" <<  endl;
        header = lc.header;
        players = lc.players;
    }
    vector<shared_ptr<Player>> get_starters() const {
        vector<shared_ptr<Player>> starters;
        for (const auto &player : players) {
            if (player->position != 0) {
                starters.push_back(player);
            }
        }
        return starters;
    }

    vector<shared_ptr<Player>> get_substitutes() const {
        vector<shared_ptr<Player>> subs;
        for (const auto &player : players) {
            if (player->position == 0){
                subs.push_back(player);
            }
        }
        return subs;
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
    bool check_position_input(const string& type, const int& input) {
    if (type == "batting_order_position" || type == "fielding_position") {
        return input >= 1 && input <= 9;
    }
    return false;
}

    vector<shared_ptr<Player>> prompt_for_players() {
    vector<shared_ptr<Player>> players;
    string input;
    while (true) {
        cout << "Enter player first name (or 'done' to finish): ";
        getline(cin, input);
        if (input == "done") break;
        
        string first_name = input;
        
        cout << "Enter player last name: ";
        getline(cin, input);
        string last_name = input;
        
        int number;
        while (true) {
            cout << "Enter player number: ";
            getline(cin, input);
            try {
                number = string_to_int(input);
                if (number >= 0 && !check_if_number_taken(players, number)) {
                    break;
                }
                cout << "Invalid number. Please enter a positive integer and ensure it is not already taken.\n";
            } catch (const invalid_argument& e) {
                cout << "Invalid input. Please enter a positive integer.\n";
            }
        }
      
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
        
        int batting_order_pos = 0;
        if (fielding_pos != 0) {
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
        }
        
        players.push_back(make_shared<Player>(first_name, last_name, number, fielding_pos, batting_order_pos));
    }
    return players;
    }
        

    void create_new_lineup_card() {
        lineup_card_headers headers = prompt_for_card_headers();
        cout << "Creating lineup card for " << headers.date << " vs " << headers.opponent << " at " << headers.venue << endl;
        this->header = headers;
        auto players = prompt_for_players();
        this->players = players;
        for (const auto &player : players) {
            cout << "Added player: " << player->get_player_info() << endl;
        }
}
    
};


void lineup_card_app(){
    string operation;
    string lineup_name;
    string create_operation;
    cout << "This is a lineup card management system." << endl;
    while(true){
        cout << "Enter 'exit' to quit or press Enter to continue: ";
        getline(cin, operation);
        operation = to_lower(operation);
        if (operation == "exit") {
            break;
        }
        if (operation == "view") {
            cout << "Enter lineup card name to view: " << endl;
            getline(cin, lineup_name);
            cout << "Viewing lineup card: " << lineup_name << endl;
         
        }
        if (operation == "create"){
            cout << "Create a new lineup card from scratch or reuse an old one?";
            getline(cin, create_operation);
            if (create_operation == "new"){
                cout << "Creating a new lineup card from scratch." << endl;
                LineupCard lineup_card;
                lineup_card.create_new_lineup_card();
                
            }
        }
    }
}




#endif
