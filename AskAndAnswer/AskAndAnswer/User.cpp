#include "User.h"
#include <string>
#include <sstream>
using namespace std;
User::User() {
    id = 0;
}
string User::GetString()
{
    ostringstream sout;
    sout << id << "," << name << "," <<password << "," <<email_id;
    return sout.str();
}