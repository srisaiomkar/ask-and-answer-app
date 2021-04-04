#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
using namespace std;

struct Helper
{
    int Menu(const vector<string> &menu_items)
    {
        int choice;
        for (int id = 0; id < (int)menu_items.size(); id++)
        {
            cout << id + 1 << ". " << menu_items[id] << endl;
        }
        cin >> choice;
        return choice;
    }
    vector<string> SplitString(string s, string delimeter = ",")
    {
        vector<string> strings;
        int pos = 0;
        while (true)
        {
            pos = (int)s.find(delimeter);
            if (pos == -1)
                break;
            string substring = s.substr(0, pos);
            strings.push_back(substring);
            s.erase(0, pos + (int)delimeter.length());
        }
        strings.push_back(s);
        return strings;
    }
    vector<string> ReadLinesFromFile(const string &path)
    {
        string line;
        vector<string> lines;
        ifstream fin(path);
        if (fin.fail())
        {
            cout << "Could not Open the file";
            return lines;
        }

        while (getline(fin, line))
        {
            if (line.size() == 0)
            {
                continue;
            }
            lines.push_back(line);
        }

        fin.close();
        return lines;
    }
    void WriteLinesToFile(string path, vector<string> lines, bool append = true)
    {

        auto status = ios::in | ios::out | ios ::app;
        if (!append)
            auto status = ios::in | ios::out | ios ::app;
        fstream file_handler(path, status);

        if (file_handler.fail())
        {
            cout << "Could not open the file\n";
            return;
        }
        for (string line : lines)
        {
            file_handler << line << endl;
        }
        file_handler.close();
    }
    int ToInt(string s)
    {
        istringstream sin(s);
        int i;
        sin >> i;
        return i;
    }
};

struct User
{
    int id{};
    string name;
    string password;
    string email_id;

    string GetString()
    {
        ostringstream sout;
        sout << id << "," << name << "," << password << "," << email_id;
        return sout.str();
    }
};

struct Question
{
    int id;
    string question_from;
    string question_to;
    string description;
    string answer;
    bool is_anonyonus;

    string GetString()
    {
        ostringstream sout;
        sout << id << "," << (is_anonyonus ? "anonymous" : question_from) << "," << question_to << ","
             << description << "," << answer;
        return sout.str();
    }
};

struct QuestionManager
{
    int previous_question_id = 0;
    Helper helper;
    void AskQuestion(string &username)
    {
        Question question;
        cout << "Whom do you want to ask the question?\n";
        cin >> question.question_to;
        cout << "Please enter the question:\n";
        cin >> ws;
        getline(cin, question.description);
        cout << "So you want to send the question anonymously?(1 for yes, 0 for no)\n";
        cin >> question.is_anonyonus;
        question.question_from = username;
        question.id = previous_question_id + 1;
        AddQuestionToDB(question);
    }

    void AddQuestionToDB(Question &question)
    {
        vector<string> questions_s;
        questions_s.push_back(question.GetString());
        helper.WriteLinesToFile("QAndA.txt", questions_s);
    }
};
struct UserManager
{
    Helper helper;
    User current_user;
    QuestionManager question_manager;
    map<string, User> username_user_map;

    void UserMenu(string username)
    {
        int choice;
        vector<string> menu_items;
        menu_items.push_back("1. Ask a question");
        menu_items.push_back("2. Answer a question");
        menu_items.push_back("3. Delete a question");
        menu_items.push_back("4. Questions from me");
        menu_items.push_back("5. Questions to me");
        menu_items.push_back("6. Questions answered by me");
        menu_items.push_back("7. Print all the users");
        menu_items.push_back("8. Logout");
        while (true)
        {
            choice = helper.Menu(menu_items);
            switch (choice)
            {
            case 1:
                question_manager.AskQuestion(username);
                break;

            default:
                break;
            }
        }
    }
    void Login()
    {
        LoadDataBase();
        string username, password;
        while (true)
        {
            cout << "Enter your username:\n";
            cin >> username;

            if (!username_user_map.count(username))
            {
                cout << "User Does not exists. Please Signup First\n";
                break;
            }
            cout << "Enter your password:\n";
            cin >> password;
            if (username_user_map[username].password != password)
            {
                cout << "incorrect password. Try again\n";
                continue;
            }
            current_user = username_user_map[username];
            UserMenu(current_user.name);
        }
    }

    void SignUp()
    {
        User user;
        while (true)
        {
            cout << "Enter your username:\n";
            cin >> user.name;
            if (username_user_map.count(user.name))
            {
                cout << "User already exists. Please Login.\n";
                break;
            }
            cout << "Enter your desired password:\n";
            cin >> user.password;
            cout << "Enter your email:\n";
            cin >> user.email_id;
            UpdateDatabase(user);
            break;
        }
    }
    vector<User> UsersFromStrings(vector<string> lines)
    {
        vector<User> users;
        char ch;
        for (string line : lines)
        {
            vector<string> user_details = helper.SplitString(line);
            User user;
            user.id = helper.ToInt(user_details[0]);
            user.name = user_details[1];
            user.password = user_details[2];
            user.email_id = user_details[3];
            users.push_back(user);
        }
        return users;
    }
    void LoadDataBase()
    {
        username_user_map.clear();
        vector<User> users;
        users = UsersFromStrings(helper.ReadLinesFromFile("Users.txt"));
        for (User user : users)
        {
            username_user_map[user.name] = user;
        }
    }
    void UpdateDatabase(User &user)
    {
        string line = user.GetString();
        vector<string> lines;
        lines.push_back(line);
        helper.WriteLinesToFile("Users.txt", lines);
    }
};
struct AskAndAnswerSystem
{
    Helper helper;
    void Start()
    {
        vector<string> menu_items;
        UserManager user_manager;
        menu_items.push_back("Login");
        menu_items.push_back("Signup");
        while (true)
        {
            int choice = helper.Menu(menu_items);

            switch (choice)
            {
            case 1:
                user_manager.Login();
                break;
            case 2:
                user_manager.SignUp();
                break;
            default:
                cin.clear();
                cin.ignore();
                cout << "Please enter a valid option\n";
                break;
            }
        }
    }
};

int main()
{
    AskAndAnswerSystem system;
    system.Start();
    return 0;
}