#include "stdafx.h"
#include "ComUtils.h"

HRESULT CUnknownImpl::QueryInterface(REFIID riid, void ** ppvObject)
{
	return E_NOTIMPL;
}

ULONG CUnknownImpl::AddRef(void)
{
	return InterlockedIncrement((LONG*)&m_refCount);
}

ULONG CUnknownImpl::Release(void)
{
	LONG refCount = InterlockedDecrement((LONG*)&m_refCount);
	if (refCount == 0) delete this;
	return refCount;
}

HRESULT hrCheck(HRESULT exp, LPCTSTR expStr)
{
	if (FAILED(exp)) {

	}
	return exp;
}

HRESULT t(void* p)
{
	HR_ASSERT_OK(E_ABORT);
	HR_ASSERT(p != NULL, E_POINTER);

	HRESULT hr = HR_EXPECT(false, E_INVALIDARG);
	return HR_EXPECT_OK(E_POINTER);
}
