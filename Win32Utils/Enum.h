#pragma once

#include <vector>
#include <string>

#ifdef _UNICODE
typedef std::wstring tstring;
#else
typedef std::string tstring;
#endif

#define ENUM(T, ...) \
	class T : public CEnum {					\
	public:										\
		enum {__VA_ARGS__,						\
				MAX_VALUE, INVALID_VALUE = -1};	\
												\
		T() : CEnum(_T(#__VA_ARGS__)),			\
				CLASS_NAME(_T(#T)) {}			\
		LPCTSTR const CLASS_NAME;				\
	}

class CEnum {
public:
	CEnum(LPCTSTR names);

	LPCTSTR toString(int value) const;
	bool isValid(int value) const;
	int count() const;

protected:
	std::vector<tstring> m_names;
};
