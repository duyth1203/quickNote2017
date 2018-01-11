#include "stdafx.h"
#include "listview.h"

void initNoteLsvColumn(HWND hwnd)
{
	LVCOLUMN lvCol;
	lvCol.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT;

	// First column
	lvCol.fmt = LVCFMT_LEFT;
	lvCol.cx = 251;
	lvCol.pszText = wsToWc(L"Tóm tắt");
	SendMessage(hwnd, LVM_INSERTCOLUMN, 0, (LPARAM)&lvCol);
}

void addItmToNoteLsv(HWND hwnd, const int & nRow, note aNote)
{
	LVITEM lvItm;
	lvItm.mask = LVIF_TEXT;
	lvItm.iItem = nRow;
	lvItm.cchTextMax = 256;
	lvItm.iSubItem = 0;
	lvItm.pszText = wsToWc(aNote.getContent());
	SendMessage(hwnd, LVM_INSERTITEM, nRow, (LPARAM)&lvItm);
}

void initTagLsvColumn(HWND hwnd)
{
	LVCOLUMN lvCol;
	lvCol.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT;

	// First column
	lvCol.fmt = LVCFMT_LEFT;
	lvCol.cx = 171;
	lvCol.pszText = wsToWc(L"Nhãn");
	SendMessage(hwnd, LVM_INSERTCOLUMN, 0, (LPARAM)&lvCol);

	// Second column
	lvCol.fmt = LVCFMT_LEFT;
	lvCol.cx = 80;
	lvCol.pszText = wsToWc(L"Số ghi chú");
	SendMessage(hwnd, LVM_INSERTCOLUMN, 1, (LPARAM)&lvCol);
}

void addItmToTagLsv(HWND hwnd, const int & nRow, tag aTag)
{
	LVITEM lvItm;
	lvItm.mask = LVIF_TEXT;
	lvItm.iItem = nRow;
	lvItm.cchTextMax = 256;
	lvItm.iSubItem = 0;
	lvItm.pszText = wsToWc(aTag.getTagName());
	SendMessage(hwnd, LVM_INSERTITEM, nRow, (LPARAM)&lvItm); // LVM_SETITEM not LVM_INSERTITEM starting from the second addition
	lvItm.iSubItem++;
	lvItm.pszText = iToWc(aTag.getNoteIds().size());
	SendMessage(hwnd, LVM_SETITEM, nRow, (LPARAM)&lvItm);
}
