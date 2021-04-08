#include <iostream>
#include <map>
#include <fstream>
#include <sstream>
#include "Helper.h"
#include "UserManager.h"

using namespace std;



struct AskAndAnswerSystem
{
    Helper helper;
    void Start()
    {
        vector<string> menu_items;
        UserManager user_manager;
        menu_items.push_back("Login");
        menu_items.push_back("Signup");
        while (true)
        {
            int choice = helper.Menu(menu_items);

            switch (choice)
            {
            case 1:
                user_manager.Login();
                break;
            case 2:
                user_manager.SignUp();
                break;
            default:
                cin.clear();
                cin.ignore();
                cout << "Please enter a valid option\n";
                break;
            }
        }
    }
};

int main()
{
    AskAndAnswerSystem system;
    system.Start();
    return 0;
}

