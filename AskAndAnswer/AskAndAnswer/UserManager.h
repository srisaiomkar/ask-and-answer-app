#pragma once

#include<map>

#include "User.h"
#include "Helper.h"
#include "QuestionManager.h"

struct UserManager
{
    Helper helper;
    User current_user;
    QuestionManager question_manager;
    map<string, User> username_user_map;

    void UserMenu(string username);
    void Login();
    void SignUp();
    vector<User> UsersFromStrings(vector<string> lines);
    void LoadDataBase();
    void UpdateDatabase(User& user);
};