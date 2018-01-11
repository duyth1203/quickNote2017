#pragma once

#include <string>

using namespace std;

/*	
 * Return pointers of TCHAR type to the converted string
 * from a string of std::string data type.
 * Return nullptr if failed.
 */
TCHAR * wsToWc(wstring s);

/*	Return pointers of TCHAR type to the converted string
 * from a number of unsigned long long data type.
 * Return nullptr if failed.
 */
TCHAR * iToWc(const unsigned int & n);

wstring wcToWs(TCHAR * s, const unsigned int & n);