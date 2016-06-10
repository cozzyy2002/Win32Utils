#include "stdafx.h"
#include "ComUtils.h"

#pragma comment(lib, "Shlwapi.lib")

HRESULT CUnknownImpl::QueryInterface(REFIID riid, void ** ppvObject)
{
	static const QITAB qitab[] = { {0} };
	const QITAB* pqitab = getQITAB();
	return QISearch(this, pqitab ? pqitab : qitab, riid, ppvObject);
}

ULONG CUnknownImpl::AddRef(void)
{
	return InterlockedIncrement(&m_refCount);
}

ULONG CUnknownImpl::Release(void)
{
	LONG refCount = InterlockedDecrement(&m_refCount);
	if (refCount == 0) delete this;
	return refCount;
}

HRESULT hrCheck(HRESULT exp, LPCTSTR expStr)
{
	if (FAILED(exp)) {

	}
	return exp;
}
