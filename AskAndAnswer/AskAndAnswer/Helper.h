#pragma once
#ifndef Helper_H_
#define Helper_H_

#include <string>
#include <vector>

using namespace std;
struct Helper
{
    int Menu(const vector<string>& menu_items);
    vector<string> SplitString(string s, string delimeter = ",");
    vector<string> ReadLinesFromFile(const string& path);
    void WriteLinesToFile(string path, vector<string> lines, bool append = true);
    int ToInt(string s);
    bool contains_comma(string s);
};

#endif