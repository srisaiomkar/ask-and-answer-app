#pragma once
#include "Helper.h"
#include "Question.h"


struct QuestionManager
{
    int previous_question_id;
    Helper helper;
    vector<Question> questions;
    QuestionManager();

    void AskQuestion(string& username);

    void AddQuestionToDB(Question& question);

    void LoadQuestionDB();

    void QuestionsByMe(const string& username);

    void QuestionsToMe(const string& username);

    void PrintAllQuestions(const string& username);
};