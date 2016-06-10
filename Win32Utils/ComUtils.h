#pragma once

#include <combaseapi.h>
#include <Shlwapi.h>

#define IUNKNOWN_METHODS \
	HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, _COM_Outptr_ void __RPC_FAR *__RPC_FAR * ppvObject)	\
				{ return CUnknownImpl::QueryInterface(riid, ppvObject); }										\
	ULONG STDMETHODCALLTYPE AddRef(void) { return CUnknownImpl::AddRef(); }										\
	ULONG STDMETHODCALLTYPE Release(void) { return CUnknownImpl::Release(); }

class CUnknownImpl : public IUnknown {
public:
	CUnknownImpl() : m_refCount(0) {}
	virtual ~CUnknownImpl() {}

	STDMETHODIMP QueryInterface(
		/* [in] */ REFIID riid,
		/* [iid_is][out] */ _COM_Outptr_ void __RPC_FAR *__RPC_FAR *ppvObject);

	STDMETHODIMP_(ULONG) AddRef(void);

	STDMETHODIMP_(ULONG) Release(void);

protected:
	virtual const QITAB* getQITAB() const { return NULL; }
	LONG m_refCount;
};

#define HR_ASSERT(exp, hr) { HRESULT _hr = (exp) ? S_OK : hr; if(FAILED(_hr)) return hrCheck(_hr, _T(#exp)); }
#define HR_ASSERT_OK(exp) { HRESULT _hr = exp; if(FAILED(_hr)) return hrCheck(_hr, _T(#exp)); }
#define HR_EXPECT(exp, hr) hrCheck((exp) ? S_OK : hr, _T(#exp));
#define HR_EXPECT_OK(exp) hrCheck(exp, _T(#exp));

HRESULT hrCheck(HRESULT expre, LPCTSTR exprStr);
