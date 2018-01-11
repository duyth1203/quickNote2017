#include "stdafx.h"
#include "note.h"
#include <time.h>
note::note()
{
	this->setId(0);
	this->setContent(L"");
}

note::note(const unsigned int & i,wstring ct, vector<wstring> tg)
{
	this->setId(i);
	this->setContent(ct);
	this->setTags(tg);
}

note::~note()
{
}

unsigned int note::getId()
{
	return this->id;
}

wstring note::getContent()
{
	return this->content;
}

vector<wstring> note::getTags()
{
	return this->tags;
}

void note::setId(const unsigned int & i)
{
	this->id = i;
}

void note::setContent(wstring ct)
{
	this->content = ct;
}

void note::setTags(vector<wstring> tg)
{
	this->tags = tg;
}