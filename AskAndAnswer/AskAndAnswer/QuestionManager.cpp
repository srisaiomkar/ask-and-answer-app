#include<iostream>
#include<map>
#include "QuestionManager.h"

QuestionManager::QuestionManager() {
    previous_question_id = 0;
}

void QuestionManager::AskQuestion(string& username,map<string,User> &username_user_map)
{
    string description_temp;
    string question_to_temp;
    LoadQuestionDB();
    Question question;
    while (true) {
        cout << "Whom do you want to ask the question?\n";
        cin >> question_to_temp;
        if (username_user_map.count(question_to_temp) > 0) {
            question.question_to = question_to_temp;
            break;
        }
        else {
            cout << "User does not exist. Please choose another user\n";
        }
    }
    while (true) {
        cout << "Please enter the question (no commas please:) )\n";
        cin >> ws;
        getline(cin, description_temp);
        if (!helper.contains_comma(description_temp)) {
            question.description = description_temp;
            break;
        }
    }

    cout << "So you want to send the question anonymously?(1 for yes, 0 for no)\n";
    cin >> question.is_anonyonus;
    question.question_from = username;
    question.id = previous_question_id + 1;
    AddQuestionToDB(question);
}

void QuestionManager::AnswerQuestion(string& username) {
    string temp;
    QuestionsToMe(username);
    int q_id;
    while (true) {
        cout << "Enter the question Id of the question which u want to answer\n";
        cin >> q_id;
        for (Question &question : questions) {
            if (question.question_to == username && question.id == q_id) {
                while (true) {
                    cout << "Enter the answer\n";
                    cin >> ws;
                    getline(cin, temp);
                    if (!helper.contains_comma(temp)) {
                        question.answer = temp;
                        UpdateQuestionsDB();
                        return;
                    }
                }
            }
        }
        cout << "Question does not exist or you do not have to permission to answer the question\n";
    }
}


void QuestionManager::AddQuestionToDB(Question& question)
{
    vector<string> questions_s;
    questions_s.push_back(question.GetString());
    helper.WriteLinesToFile("C:\\Ask And Answer\\QAndA.txt", questions_s);
}


void QuestionManager::LoadQuestionDB()
{
    Question q;
    questions.clear();
    vector<string> questions_s = helper.ReadLinesFromFile("C:\\Ask And Answer\\QAndA.txt");
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

void QuestionManager::UpdateQuestionsDB()
{
    vector<string> lines;
    for (const Question& question : questions) {
        lines.push_back(question.GetString());
    }
    helper.WriteLinesToFile("C:\\Ask And Answer\\QAndA.txt", lines,false);
}

void QuestionManager::DeleteQuestion(string &username) {
    int q_id;
    LoadQuestionDB();
    QuestionsByMe(username);
    cout << "Enter the question of the question which you want to delete";
    cin >> q_id;
    for (int i = 0; i < (int)questions.size();i++) {
        if (questions[i].id == q_id && questions[i].question_from == username) {
            questions.erase(questions.begin() + i);
            UpdateQuestionsDB();
            return;
        }
    }
}


void QuestionManager::QuestionsByMe(const string& username)
{
    LoadQuestionDB();

    for (const Question& question : questions)
    {
        if (question.question_from == username)
        {
            question.Print();
        }
    }
}

void QuestionManager::QuestionsAnsweredByMe(const string& username) {
    LoadQuestionDB();
    for (const Question &question : questions) {
        if (question.question_to == username && question.answer != "No Answer yet") {
            question.Print();
        }
    }
}

void QuestionManager::QuestionsUnansweredByMe(const string& username) {
    LoadQuestionDB();
    for (const Question& question : questions) {
        if (question.question_to == username && question.answer == "No Answer yet") {
            question.Print();
        }
    }
}

void QuestionManager::QuestionsToMe(const string& username)
{
    LoadQuestionDB();
    for (const Question& question : questions)
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
    for (const Question& question : questions)
    {
        question.Print();
    }
}