#include "stdafx.h"
#include "convertor.h"

TCHAR * wsToWc(wstring wsStr)
{
	TCHAR * wcStr = new TCHAR[wsStr.size() + 1];
	if (wcStr)
	{
		copy(wsStr.begin(), wsStr.end(), wcStr);
		wcStr[wsStr.size()] = 0;
	}
	return wcStr;
}

TCHAR * iToWc(const unsigned int & n)
{
	wstring sNum = to_wstring(n);
	return wsToWc(sNum);
}

wstring wcToWs(TCHAR * s, const unsigned int & n)
{
	wstring wsStr = L"";
	for (int i = 0; i < n; i++)
	{
		wsStr += s[i];
	}
	wsStr += L'\n';
	return wsStr;
}
