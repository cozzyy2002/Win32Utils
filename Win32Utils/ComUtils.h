#pragma once

#include <combaseapi.h>

#define IUNKNOWN_METHODS \
	HRESULT STDMETHODCALLTYPE QueryInterface(REFIID, _COM_Outptr_ void __RPC_FAR *__RPC_FAR *);	\
	ULONG STDMETHODCALLTYPE AddRef(void);														\
	ULONG STDMETHODCALLTYPE Release(void)

class CUnknownImpl : public IUnknown {
public:
	CUnknownImpl() : m_refCount(0) {}
	virtual ~CUnknownImpl() {}

	virtual HRESULT STDMETHODCALLTYPE QueryInterface(
		/* [in] */ REFIID riid,
		/* [iid_is][out] */ _COM_Outptr_ void __RPC_FAR *__RPC_FAR *ppvObject);

	virtual ULONG STDMETHODCALLTYPE AddRef(void);

	virtual ULONG STDMETHODCALLTYPE Release(void);

protected:
	ULONG m_refCount;
};

#define HR_ASSERT(exp, hr) { HRESULT _hr = (exp) ? S_OK : hr; if(FAILED(_hr)) return hrCheck(_hr, _T(#exp)); }
#define HR_ASSERT_OK(exp) { HRESULT _hr = exp; if(FAILED(_hr)) return hrCheck(_hr, _T(#exp)); }
#define HR_EXPECT(exp, hr) hrCheck((exp) ? S_OK : hr, _T(#exp));
#define HR_EXPECT_OK(exp) hrCheck(exp, _T(#exp));

HRESULT hrCheck(HRESULT expre, LPCTSTR exprStr);
