#pragma once
#include<string>
struct Question
{
    int id;
    std::string question_from;
    std::string question_to;
    std::string description;
    std::string answer;
    bool is_anonyonus;

    Question();

    std::string GetString();

    void Print();
};
