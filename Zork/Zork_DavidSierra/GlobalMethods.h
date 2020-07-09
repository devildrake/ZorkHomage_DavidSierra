#pragma once
#include <vector>
#include <string>

using namespace std;

void TranslateToArguments(const string&line, vector<string>&arguments);
bool CompareCharInsensitive(const char & c1, const char & c2);
bool CompareStrings(const string & str1, const string &str2);
bool CompareStrings(const string&str1, const string* str2);
const char* GetPreferredArticle(const string& str1);
void Println(const string& str1);
