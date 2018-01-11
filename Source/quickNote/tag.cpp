#include "stdafx.h"
#include "tag.h"


tag::tag()
{
	this->setTagName(L"");
}

tag::tag(wstring tn, vector<unsigned int> ni)
{
	this->setTagName(tn);
	this->setNoteIds(ni);
}

tag::~tag()
{
}

wstring tag::getTagName()
{
	return this->tagName;
}

vector<unsigned int> tag::getNoteIds()
{
	return this->noteIds;
}

void tag::setTagName(wstring tn)
{
	this->tagName = tn;
}

void tag::setNoteIds(vector<unsigned int> ni)
{
	this->noteIds = ni;
}

tag & tag::operator=(tag aTag)
{
	this->setTagName(aTag.getTagName());
	this->setNoteIds(aTag.getNoteIds());

	return *this;
}
