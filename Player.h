
#ifndef PLAYER_H
#define PLAYER_H
#include <iostream>
#include <string>
#include <vector>
#include <memory>
using namespace std;


class Player {
    public:
        string first_name;
        string last_name;
        int number;
        int position;
        int batting_order_position;
    
        Player(const string &fn, const string &ln, const int num, const int &pos, const int &bat_pos): first_name(fn), last_name(ln), number(num), position(pos), batting_order_position(bat_pos) {}
        Player() : first_name(""), last_name(""), number(0), position(0), batting_order_position(0) {}
        Player(const Player &p){
            cout << "Copied Player" << endl;
            first_name = p.first_name;
            last_name = p.last_name;
            number = p.number;
            position = p.position;
        } 

    string get_full_name() {
        return first_name + " " + last_name;
    }

    string get_player_info() {
        return "Name: " + get_full_name() + ", Number: " + to_string(number) + ", Position: " + to_string(position) + ", Batting Order Position: " + to_string(batting_order_position);
    }

    void set_position(const int &pos) {
        position = pos;
    }

    void set_number(const int &num) {
        number = num;
    }
    void set_first_name(const string &fn) {
        first_name = fn;
    }
    void set_last_name(const string &ln) {
        last_name = ln;
    }
    void set_batting_order_position(const int &bat_pos) {
        batting_order_position = bat_pos;
    }

};

#endif