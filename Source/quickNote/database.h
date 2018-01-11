#pragma once

#include <string>
#include <fstream>
#include <vector>
#include <fcntl.h> // _O_WTEXT
#include <io.h>    // _setmode()
#include <codecvt> // possible C++11?
#include <locale>
#include "convertor.h"
#include "note.h"
#include "tag.h"

using namespace std; 

typedef basic_istringstream<wchar_t> wistringstream;

static locale loc(locale(), new codecvt_utf8<wchar_t>);  // UTF-8

unsigned int greatestId(vector<note> eNote);

unsigned int idGenerator(vector<note> eNote);

int isExistedTag(vector<tag> eTag, wstring tagName);

bool isInTouchedTags(const int & key, vector<int> touchedTags);

vector<wstring> wsToWSETag(wstring wsTags);

// HOW A NOTE FILE LOOKS LIKE
/*
====================================================================
endl
[id]
1
[content]
whatever
[tag]
tag1,tag2,tag3
[id]
2
[content]
whatsoever
[tag]
tag2,tag5
====================================================================
*/

vector<note> readNoteDB(const char * fname);
int writeNoteDB(const char * fname, note aNote);

// HOW A TAG FILE LOOKS LIKE
/*
====================================================================
endl
atagname 1 3 6 21 4269
anothertagname 1 4 6 99
====================================================================
*/

vector<tag> readTagDB(const char * fname);
int writeTagDB(const char * fname, note aNote, vector<tag> eTag);