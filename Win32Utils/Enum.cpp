#include "stdafx.h"
#include "Enum.h"

inline CEnum::CEnum(LPCTSTR names)
{
	LPTSTR buff = _tcsdup(names);
	LPTSTR context = NULL;
	for (LPTSTR p = buff; NULL != (p = _tcstok_s(p, _T(", "), &context)); p = NULL) {
		m_names.push_back(p);
	}
	free(buff);
}

LPCTSTR CEnum::toString(int value) const
{
	return isValid(value) ? m_names[value].c_str() : _T("UNKNOWN");
}

bool CEnum::isValid(int value) const
{
	return (0 <= value) && (value < count());
}

int CEnum::count() const
{
	return int(m_names.size());
}
