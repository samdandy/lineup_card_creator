#include "Player.h"
#include "LineupCard.h"
#include <iostream>
#include <string>
#include <vector>
#include <memory>
using namespace std;

int main(){
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
   return 0;
}
 