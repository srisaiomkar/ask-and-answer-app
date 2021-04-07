#ifndef USER_H_
#define USER_H_
#include<string>
using namespace std;
struct User
{
    int id;
    string name;
    string password;
    string email_id;
    User();
    string GetString();
};

#endif