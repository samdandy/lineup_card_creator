#ifndef LINEUPCARD_H
#define LINEUPCARD_H

#include <string>
#include <vector>
#include <memory>
#include "Player.h"
#include "Utils.h"
#include <fstream>
#include <iostream>
#include <mutex>
using namespace std;

struct lineup_card_headers {
    string date;
    string opponent;
    string venue;
};

mutex file_mutex;

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
    vector<shared_ptr<Player>> get_starters(const bool& sort=false) const {
        vector<shared_ptr<Player>> starters;
        for (const auto &player : players) {
            if (player->position != 0) {
                starters.push_back(player);
            }
        }
        if (sort) {
            starters = sort_batting_order(starters);
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
bool check_starting_lineup_complete(const LineupCard& lineup_card) {
    auto starters = lineup_card.get_starters();
    if (starters.size() < 9) {
        return false;
    }
    for (int pos = 1; pos <=9; pos++) {
        if (!check_if_position_taken(starters, pos)) {
            cout << "Position " << pos << " is not filled." << endl;
            return false;
        }
    }
    for (int bat_pos = 1; bat_pos <=9; bat_pos++) {
        if (!check_if_batting_order_position_taken(starters, bat_pos)) {
            cout << "Batting order position " << bat_pos << " is not filled." << endl;
            return false;
        }
    }
    return true;
}
vector<shared_ptr<Player>> prompt_for_players() {
    vector<shared_ptr<Player>> players;
    string input;
    while (true) {
        cout << "Enter player first name (or 'done' to finish): ";
       
        getline(cin, input);
        if (input == "done") {
            bool starters_complete = check_starting_lineup_complete(LineupCard(header, players));
            if (!starters_complete) {
                cout << players.size() << " players added so far.\n";
                cout << "Warning: Starting lineup is not complete. Please ensure 9 unique fielding positions are filled.\n";
            }
            else {
                break;
            }
            cout << "Enter player first name (or 'done' to finish): ";
            getline(cin, input);
            if (input == "done") {
                break;
        }
     }
        
        string first_name = input;
        string last_name = prompt_for_player_last_name();
        int number = prompt_for_player_number(players);
        int fielding_pos = prompt_for_player_fielding_position(players);
        int batting_order_pos = 0;
        if (fielding_pos != 0) {
            batting_order_pos = prompt_for_player_batting_order_position(players);
        }
        
        players.push_back(make_shared<Player>(first_name, last_name, number, fielding_pos, batting_order_pos));
    }

    return players;
   }

   void write_lineup_card_to_file(const string& filename) {
        lock_guard<mutex> lock(file_mutex);
        ofstream file(filename);
        if (!file) {
            throw runtime_error("Unable to open file: " + filename);
        }
        file << "Date: " << header.date << endl;
        file << "Opponent: " << header.opponent << endl;
        file << "Venue: " << header.venue << endl;
        file << "-------------------------------------------------------------------------------------------" << endl;
        file << "Batting Order| Player Name           | Number | Position" << endl;
        file << "-------------------------------------------------------------------------------------------" << endl;
        auto starters = get_starters(true);
        for (const auto &player : starters) {
            file << "      " << player->batting_order_position << "      | " 
                 << player->get_full_name() << string(22 - player->get_full_name().length(), ' ') << "| "
                 << player->number << string(7 - to_string(player->number).length(), ' ') << "| "
                 << player->position << endl;
        }
        auto subs = get_substitutes();
        if (!subs.empty()) {
            file << "-------------------------------------------------------------------------------------------" << endl;
            file << "Substitutes:" << endl;
            for (const auto &player : subs) {
                file << "                | " 
                     << player->get_full_name() << string(22 - player->get_full_name().length(), ' ') << "| "
                     << player->number << string(7 - to_string(player->number).length(), ' ') << "| "
                     << "Substitute" << endl;
            }
        }
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
        string file_name;
        cout << "Enter filename to save lineup card (default 'lineup_card.txt'): ";
        getline(cin, file_name);
        if (file_name.empty()) {
            file_name = headers.date + "_" + to_lower(headers.opponent) + "_lineup_card.txt";
        }
        write_lineup_card_to_file(file_name);
    
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
