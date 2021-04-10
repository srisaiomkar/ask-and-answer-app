#include<string>
#include<sstream>
#include<iostream>

#include "Question.h"

using namespace std;

Question::Question()
{
    id = 0;
    is_anonyonus = 0;
}

string Question::GetString()
{
    ostringstream sout;
    sout << id << "," << (is_anonyonus ? "anonymous" : question_from) << "," << question_to << ","
        << description << "," << (answer.length() ? answer : "No Answer yet");
    return sout.str();
}

void Question::Print()
{
    cout << "Question Id: " << id << "\n\tAsked By: " << question_from
        << "\n\tAsked To: " << question_to << "\n\tQ: " << description
        << "\n\tA: " << answer << "\n\n";
}
