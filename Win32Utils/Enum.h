#pragma once

#include <vector>
#include <string>

#ifdef _UNICODE
typedef std::wstring tstring;
#else
typedef std::string tstring;
#endif

#define ENUM(T, ...) \
	class T : public CEnum<T> {		\
	public:							\
		typedef enum {				\
					__VA_ARGS__,	\
					COUNT,			\
					INVALID = -1	\
		} Values;					\
	\
		T(Values value = INVALID) : CEnum(_T(#__VA_ARGS__), value) {}	\
		T(const T& other) : CEnum(_T(#__VA_ARGS__), other.m_value) {}	\
		T& operator=(Values value) { m_value = value; return *this; }	\
	}

template<class T, typename V = int>
class CEnum {
public:
	CEnum(LPCTSTR names, typename V value) : m_value(value) { init(names); }

	static LPCTSTR toString(typename V value) { return isValid(value) ? m_names[value].c_str() : _T("UNKNOWN"); }
	static bool isValid(typename V value) { return (0 <= value) && (value < (V)count()); }
	static size_t count() { return m_names.size(); }

	LPCTSTR toString() const { return toString(m_value); }
	bool isValid() const { return isValid(m_value); }
	bool operator==(typename V value) const { return m_value == value; }
	operator V() const { return m_value; }

protected:
	V m_value;
	static std::vector<tstring> m_names;

	void init(LPCTSTR names);
};

template<class T, typename V>
/*static*/ std::vector<tstring> CEnum<T, V>::m_names;

template<class T, typename V>
void CEnum<T, V>::init(LPCTSTR names)
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

template<class T, typename V = int>
bool operator==(typename V value, const CEnum<T>& obj)
{
	return obj.operator==(value);
}
