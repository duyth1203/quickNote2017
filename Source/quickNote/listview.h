#pragma once

#include"resource.h"
#include <commctrl.h>
#include "note.h"
#include "tag.h"
#include "convertor.h"
#pragma comment(linker,"\"/manifestdependency:type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#pragma comment(lib, "ComCtl32.lib")

static HWND hNoteLsv;
void initNoteLsvColumn(HWND hwnd); 
void addItmToNoteLsv(HWND hwnd, const int & nRow, note aNote);

static HWND hTagLsv;
void initTagLsvColumn(HWND hwnd);
void addItmToTagLsv(HWND hwnd, const int & nRow, tag aTag);