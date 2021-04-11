#include "User.h"
#include <string>
#include <sstream>
#include <iostream>
using namespace std;
User::User() {
    id = 0;
}
string User::GetString()const
{
    ostringstream sout;
    sout << id << "," << name << "," <<password << "," <<email_id;
    return sout.str();
}

void User::Print()const {
    cout << name << " " << email_id << endl;
}