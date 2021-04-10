#include<iostream>

#include "UserManager.h"
using namespace std;

void UserManager::UserMenu(string username)
{
    int choice;
    vector<string> menu_items;
    menu_items.push_back("Ask a question");
    menu_items.push_back("Answer a question");
    menu_items.push_back("Delete a question");
    menu_items.push_back("Questions asked by me");
    menu_items.push_back("Questions asked to me");
    menu_items.push_back("Questions answered by me");
    menu_items.push_back("Print all the users");
    menu_items.push_back("Print all the Q and A");
    menu_items.push_back("Logout");
    while (true)
    {
        choice = helper.Menu(menu_items);
        switch (choice)
        {
        case 1:
            question_manager.AskQuestion(username);
            break;
        case 2:
            // question_manager.AnswerQuestion(username);
            break;
        case 3:
            // question_manager.AnswerQuestion(username);
            break;
        case 4:
            question_manager.QuestionsByMe(username);
            break;
        case 5:
            question_manager.QuestionsToMe(username);
            break;
        case 8:
            question_manager.PrintAllQuestions(username);
            break;

        default:
            break;
        }
    }
}
void UserManager::Login()
{
    LoadDataBase();
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
        current_user = username_user_map[username];
        UserMenu(current_user.name);
    }
}

void UserManager::SignUp()
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
        UpdateDatabase(user);
        break;
    }
}
vector<User> UserManager::UsersFromStrings(vector<string> lines)
{
    vector<User> users;
    char ch;
    for (string line : lines)
    {
        vector<string> user_details = helper.SplitString(line);
        User user;
        user.id = helper.ToInt(user_details[0]);
        user.name = user_details[1];
        user.password = user_details[2];
        user.email_id = user_details[3];
        users.push_back(user);
    }
    return users;
}
void UserManager::LoadDataBase()
{
    username_user_map.clear();
    vector<User> users;
    users = UsersFromStrings(helper.ReadLinesFromFile("C:\\Ask And Answer\\Users.txt"));
    for (User user : users)
    {
        username_user_map[user.name] = user;
    }
}
void UserManager::UpdateDatabase(User& user)
{
    string line = user.GetString();
    vector<string> lines;
    lines.push_back(line);
    helper.WriteLinesToFile("Users.txt", lines);
}