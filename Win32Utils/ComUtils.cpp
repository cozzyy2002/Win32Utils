#include "stdafx.h"
#include "ComUtils.h"

HRESULT CUnknownImpl::QueryInterface(REFIID riid, void ** ppvObject)
{
	return E_NOTIMPL;
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
