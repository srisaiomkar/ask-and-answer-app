#include "Helper.h"
#include<iostream>
#include<vector>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;
int Helper::Menu(const vector<string>& menu_items)
{
    int choice;
    for (int id = 0; id < (int)menu_items.size(); id++)
    {
        cout << id + 1 << ". " << menu_items[id] << endl;
    }
    cin >> choice;
    return choice;
}

vector<string> Helper::SplitString(string s, string delimeter)
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
vector<string> Helper::ReadLinesFromFile(const string& path)
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
void Helper::WriteLinesToFile(string path, vector<string> lines, bool append)
{

    auto status = ios::in | ios::out | ios::app;
    if (!append)
        auto status = ios::in | ios::out | ios::app;
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
int Helper::ToInt(string s)
{
    istringstream sin(s);
    int i;
    sin >> i;
    return i;
}