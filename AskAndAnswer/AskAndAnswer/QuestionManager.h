#pragma once
#include<map>

#include "Helper.h"
#include "Question.h"
#include "User.h"


struct QuestionManager
{
    int previous_question_id;
    Helper helper;
    vector<Question> questions;
    QuestionManager();

    void AskQuestion(string& username, map<string, User>& username_user_map);

    void AnswerQuestion(string& username);

    void DeleteQuestion(string& username);
    void AddQuestionToDB(Question& question);

    void LoadQuestionDB();
    void UpdateQuestionsDB();

    void QuestionsByMe(const string& username);

    void QuestionsToMe(const string& username);

    void PrintAllQuestions(const string& username);
};