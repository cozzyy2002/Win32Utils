#include "stdafx.h"
#include "Enum.h"

void CEnum_init(std::vector<tstring>& names, LPCTSTR values)
{
	if (names.empty()) {
		LPTSTR buff = _tcsdup(values);
		LPTSTR context = NULL;
		for (LPTSTR p = buff; NULL != (p = _tcstok_s(p, _T(", "), &context)); p = NULL) {
			names.push_back(p);
		}
		free(buff);
	}
}
