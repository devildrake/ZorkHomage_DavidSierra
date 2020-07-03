#include "GlobalMethods.h"
#include <cctype>


void TranslateToArguments(const string&input, vector<string>&resultingArgs) {
	int i = 0;
	string tmp = "";
	while (i < input.length()) {
		if (input[i] != ' ') {
			tmp += input[i];
		}
		else {
			resultingArgs.push_back(tmp);
			tmp = string("");
		}
		i++;
	}
	if (tmp.length() > 0) {
		resultingArgs.push_back(tmp);
	}
}

bool CompareCharInsensitive(const char & c1, const char & c2)
{
	if (c1 == c2)
		return true;
	else if (std::toupper(c1) == std::toupper(c2))
		return true;
	return false;
}

bool CompareStrings(const string & str1, const string &str2)
{
	return ((str1.size() == str2.size()) &&
		std::equal(str1.begin(), str1.end(), str2.begin(), &CompareCharInsensitive));
}

bool CompareStrings(const string&str1, const string* str2) {

	for (size_t i = 0; i < str2->length(); i++)
	{
		if (CompareStrings(str1, str2[i])) {
			return true;
		}
	}
	return false;
}

