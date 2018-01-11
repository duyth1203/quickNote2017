#pragma once

#include <string>
#include <vector>

using namespace std;

class note
{
private:
	unsigned int id;
	wstring content;
	vector<wstring> tags;
public:
	note();
	note(const unsigned int & i, wstring ct, vector<wstring> tg);
	~note();

	unsigned int getId();
	wstring getContent();
	vector<wstring> getTags();

	void setId(const unsigned int & i);
	void setContent(wstring ct);
	void setTags(vector<wstring> tg);
};