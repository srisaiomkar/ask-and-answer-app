#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
using namespace std;

struct User
{
    int id;
    string name;
    string password;
    string email_id;

    string ToString()
    {
        ostringstream sout;
        sout << id << "," << name << "," << password << "," << email_id << ",";
        return sout.str();
    }
};
struct Common
{
    vector<string> ReadFileLines(const string &path)
    {
        string line;
        vector<string> lines;
        ifstream fin(path);
        if (fin.fail())
        {
            cout << "Could not Open the file";
            return lines;
        }

        while (getline(fin, line))
        {
            if (line.size() == 0)
            {
                continue;
            }
            lines.push_back(line);
        }

        fin.close();
        return lines;
    }
    void WriteLinesToFile(string path, vector<string> lines)
    {
    }

    // vector<User> LinesToUsers(vector<string> lines){

    // }
};

struct UserManager
{
    map<string, User> username_user_map;

    void Usermenu()
    {
    }
    void Login()
    {
        string username, password;
        while (true)
        {
            cout << "Enter your username:\n";
            cin >> username;

            if (!username_user_map.count(username))
            {
                cout << "User Does not exists. Please Signup First\n";
                break;
            }
            cout << "Enter your password:\n";
            cin >> password;
            if (username_user_map[username].password != password)
            {
                cout << "incorrect password. Try again\n";
                continue;
            }
            // UserMenu();
        }
    }

    void SignUp()
    {
        User user;
        while (true)
        {
            cout << "Enter your username:\n";
            cin >> user.name;
            if (username_user_map.count(user.name))
            {
                cout << "User already exists. Please Login.\n";
                break;
            }
            cout << "Enter your desired password:\n";
            cin >> user.password;
            cout << "Enter your email:\n";
            cin >> user.email_id;
            username_user_map[user.name] = user;
            UpdateDatabase(user);
            break;
        }
    }
    void UpdateDatabase(User &user)
    {
        string line = user.ToString();
        vector<string> lines;
        lines.push_back(line);
        // c.WriteLinesToFile("Users.txt", lines);
    }
};
struct QAndASystem
{
    int Menu(const vector<string> &menu_items)
    {
        int choice;
        for (int id = 0; id < (int)menu_items.size(); id++)
        {
            cout << id + 1 << ". " << menu_items[id] << endl;
        }
        cin >> choice;
        return choice;
    }

    void Start()
    {
        vector<string> menu_items;
        UserManager user_manager;
        menu_items.push_back("Login");
        menu_items.push_back("Signup");
        while (true)
        {
            int choice = Menu(menu_items);

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
    QAndASystem system;
    system.Start();
    return 0;
}