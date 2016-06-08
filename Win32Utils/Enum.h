#pragma once

#include <vector>
#include <string>

#ifdef _UNICODE
typedef std::wstring tstring;
#else
typedef std::string tstring;
#endif

#define ENUM(T, ...) \
	class T : public CEnum<T> {				\
	public:									\
		enum Values {__VA_ARGS__,			\
				COUNT, INVALID_VALUE = -1};	\
											\
		T() : CEnum(_T(#__VA_ARGS__)),		\
				CLASS_NAME(_T(#T)) {}		\
		LPCTSTR const CLASS_NAME;			\
	};										\
	std::vector<tstring> CEnum<T>::m_names

template<class T>
class CEnum {
public:
	CEnum(LPCTSTR names);

	LPCTSTR toString(int value) const;
	bool isValid(int value) const;
	int count() const;

protected:
	static std::vector<tstring> m_names;
};

template<class T>
CEnum<T>::CEnum(LPCTSTR names)
{
	if (m_names.empty()) {
		LPTSTR buff = _tcsdup(names);
		LPTSTR context = NULL;
		for (LPTSTR p = buff; NULL != (p = _tcstok_s(p, _T(", "), &context)); p = NULL) {
			m_names.push_back(p);
		}
		free(buff);
	}
}

template<class T>
LPCTSTR CEnum<T>::toString(int value) const
{
	return isValid(value) ? m_names[value].c_str() : _T("UNKNOWN");
}

template<class T>
bool CEnum<T>::isValid(int value) const
{
	return (0 <= value) && (value < count());
}

template<class T>
int CEnum<T>::count() const
{
	return m_names.size();
}
