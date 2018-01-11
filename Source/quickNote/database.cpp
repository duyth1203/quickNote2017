#include "stdafx.h"
#include "database.h"

unsigned int greatestId(vector<note> eNote)
{
	unsigned int id = eNote[0].getId();
	for (int i = 1; i < eNote.size(); i++)
	{
		if (eNote[i].getId() > id)
		{
			id = eNote[i].getId();
		}
	}
	return id;
}

unsigned int idGenerator(vector<note> eNote)
{
	unsigned int gId = greatestId(eNote);
	for (int i = 0; i < gId; i++)
	{
		int j;
		for (j = 0; j < eNote.size(); j++)
		{
			if (eNote[j].getId() == i)
			{
				j = eNote.size() + 1; // to break this loop as I'm so scared breaking the outer loop
			}
		}
		if (eNote.size() == j)
		{
			return i;
		}
	}

	return gId + 1;
}

int isExistedTag(vector<tag> eTag, wstring tagName)
{
	for (int i = 0; i < eTag.size(); i++)
	{
		if (eTag[i].getTagName() == tagName)
		{
			return i;
		}
	}
	return -1;
}

bool isInTouchedTags(const int & key, vector<int> touchedTags)
{
	for (int i = 0; i < touchedTags.size(); i++)
	{
		if (key == touchedTags[i])
			return true;
	}

	return false;
}

vector<wstring> wsToWSETag(wstring wsTags)
{
	vector<wstring> wsETag;

	int i = -1;
	do
	{
		i = wsTags.find(L",", 0);
		if (-1 != i)
		{
			wsETag.push_back(wsTags.substr(0, i));
			wsTags.erase(0, i + 1);
		}
		else
		{
			wsETag.push_back(wsTags);
		}
	} while (-1 != i);

	return wsETag;
}

vector<note> readNoteDB(const char * fname)
{
	vector<note> eNote;

	wifstream fi(fname);
	if (fi.is_open())
	{
		_setmode(_fileno(stdin), _O_WTEXT); // needed for input
		locale loc(locale(), new codecvt_utf8<wchar_t>); // UTF-8
		fi.imbue(loc);
		fi.seekg(0, fi.beg);

		wstring aLine = L"";
		getline(fi, aLine);

		while (!fi.eof())
		{
			// reset data every new loop
			wstring wsId = L"",
				wsContent = L"",
				wsTag = L"";

			// read raw note
			getline(fi, aLine); // [id]
			// id
			getline(fi, wsId);
			// content
			getline(fi, aLine); // [content]
			getline(fi, aLine);
			while (L"[tag]" != aLine)
			{
				wsContent += aLine + L"\n";
				getline(fi, aLine);
			}
			// tag
			getline(fi, wsTag);
			
			eNote.push_back(note::note(stoi(wsId), wsContent, wsToWSETag(wsTag)));
		}
		fi.close();
	}

	return eNote;
}

int writeNoteDB(const char * fname, note aNote)
{
	wofstream fo;
	fo.open(fname, ios::out | ios::app);
	if (fo.is_open())
	{
		_setmode(_fileno(stdout), _O_WTEXT); // needed for output
		locale loc(locale(), new codecvt_utf8<wchar_t>); // UTF-8
		fo.imbue(loc);

		fo << endl << L"[id]" << endl << aNote.getId() << endl;
		fo << L"[content]" << endl << aNote.getContent() << endl;
		fo << L"[tag]" << endl;
		for (int i = 0; i < aNote.getTags().size() - 1; i++)
		{
			fo << aNote.getTags()[i] << L",";
		}
		fo << aNote.getTags()[aNote.getTags().size() - 1];
		fo.close();
		return 0;
	}

	return -1;
}

vector<tag> readTagDB(const char * fname)
{
	vector<tag> eTag;

	wifstream fi(fname);
	if (fi.is_open())
	{
		_setmode(_fileno(stdin), _O_WTEXT); // needed for input
		locale loc(locale(), new codecvt_utf8<wchar_t>); // UTF-8
		fi.imbue(loc);

		wstring aLine;
		getline(fi, aLine); // skip first line

		while (!fi.eof())
		{
			wstring tagName = L"";
			vector<unsigned int> noteIds;

			getline(fi, aLine);
			if (aLine.length() > 2) // minimum length of a vlid tag line is 3, ex: a 0
			{
				int i = aLine.find(L" ", 0);
				tagName = aLine.substr(0, i);
				aLine.erase(0, i + 1);
				// now aLine contains only note ids
				do
				{
					i = aLine.find(L" ", 0);
					if (-1 != i)
					{
						noteIds.push_back(stoi(aLine.substr(0, i)));
						aLine.erase(0, i + 1);
					}
					else
					{
						noteIds.push_back(stoi(aLine));
					}
				} while (-1 != i);

				eTag.push_back(tag::tag(tagName, noteIds));
			}
		}
		fi.close();
	}

	return eTag;
}

int writeTagDB(const char * fname, note aNote, vector<tag> eTag)
{
	wofstream fo(L"tmp.db");

	if (fo.is_open())
	{
		_setmode(_fileno(stdout), _O_WTEXT); // needed for output
		locale loc(locale(), new codecvt_utf8<wchar_t>); // UTF-8
		fo.imbue(loc);
		vector<int> touchedTags;

		for (int i = 0; i < aNote.getTags().size(); i++)
		{
			int j = isExistedTag(eTag, aNote.getTags()[i]);
			if (-1 == j)
			{
				fo << endl << aNote.getTags()[i] << L" " << aNote.getId();
			}
			else
			{
				fo << endl << eTag[j].getTagName();
				for (int k = 0; k < eTag[j].getNoteIds().size(); k++)
				{
					fo << L" " << eTag[j].getNoteIds()[k];
				}
				fo << L" " << aNote.getId();
				// This tag has been touched
				touchedTags.push_back(j);
			}
		}

		// Write remaining untouched tags (not in vector touchedTags) to database
		for (int i = 0; i < eTag.size(); i++)
		{
			if (!isInTouchedTags(i, touchedTags))
			{
				fo << endl << eTag[i].getTagName();
				for (int j = 0; j < eTag[i].getNoteIds().size() - 1; j++)
				{
					fo << L" " << eTag[i].getNoteIds()[j];
				}
				fo << L" " << eTag[i].getNoteIds()[eTag[i].getNoteIds().size() - 1];
			}
		}

		fo.close();
		remove(fname);
		rename("tmp.db", fname);
		return 0;
	}

	return -1;
}