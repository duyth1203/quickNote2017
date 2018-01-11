#pragma once

#include <string>
#include <vector>

using namespace std;

class tag
{
private:
	wstring tagName;
	vector<unsigned int> noteIds;
public:
	tag();
	tag(wstring tn, vector<unsigned int> ni);
	~tag();

	wstring getTagName();
	vector<unsigned int> getNoteIds();

	void setTagName(wstring tn);
	void setNoteIds(vector<unsigned int> ni);

	tag& operator=(tag aTag);
};