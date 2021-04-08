#include<iostream>

#include "QuestionManager.h"

QuestionManager::QuestionManager() {
    previous_question_id = 0;
}

void QuestionManager::AskQuestion(string& username)
{
    LoadQuestionDB();
    Question question;
    cout << "Whom do you want to ask the question?\n";
    cin >> question.question_to;
    cout << "Please enter the question(no commas please:) )\n";
    cin >> ws;
    getline(cin, question.description);
    cout << "So you want to send the question anonymously?(1 for yes, 0 for no)\n";
    cin >> question.is_anonyonus;
    question.question_from = username;
    question.id = previous_question_id + 1;
    AddQuestionToDB(question);
}

void QuestionManager::AddQuestionToDB(Question& question)
{
    vector<string> questions_s;
    questions_s.push_back(question.GetString());
    helper.WriteLinesToFile("QAndA.txt", questions_s);
}

void QuestionManager::LoadQuestionDB()
{
    Question q;
    questions.clear();
    vector<string> questions_s = helper.ReadLinesFromFile("C:\\Users\\srisa\\source\\repos\\srisaiomkar\\ask-and-answer-app\\AskAndAnswer\\AskAndAnswer\\QAndA.txt");
    for (string question_s : questions_s)
    {
        vector<string> question_details = helper.SplitString(question_s);
        q.id = helper.ToInt(question_details[0]);
        q.question_from = question_details[1];
        q.question_to = question_details[2];
        q.description = question_details[3];
        q.answer = question_details[4];
        questions.push_back(q);
    }
    previous_question_id = q.id;
}

void QuestionManager::QuestionsByMe(const string& username)
{
    LoadQuestionDB();

    for (Question question : questions)
    {
        if (question.question_from == username)
        {
            question.Print();
        }
    }
}

void QuestionManager::QuestionsToMe(const string& username)
{
    LoadQuestionDB();
    for (Question question : questions)
    {
        if (question.question_to == username)
        {
            question.Print();
        }
    }
}

void QuestionManager::PrintAllQuestions(const string& username)
{
    LoadQuestionDB();
    for (Question question : questions)
    {
        question.Print();
    }
}