#include "stdafx.h"
#include "Win32Utils/ComUtils.h"

#include <atlbase.h>

using namespace testing;

class Testee : public CUnknownImpl, public IPersist {
public:
	Testee(bool checkDtor, bool iPersist = false)
		: checkDtor(checkDtor), iPersist(iPersist) {}
	~Testee() { if (checkDtor) dtor(m_refCount); }

	IUNKNOWN_METHODS;

	virtual HRESULT STDMETHODCALLTYPE GetClassID(
		/* [out] */ __RPC__out CLSID *pClassID) { return S_OK; }

	MOCK_METHOD1(dtor, void(UINT));

	static const QITAB qitab[];
	virtual const QITAB* getQITAB() const { return iPersist ? qitab : NULL; }

	using CUnknownImpl::m_refCount;
	const bool checkDtor, iPersist;
};

const QITAB Testee::qitab[] = {
	QITABENT(Testee, IPersist),
	{0}
};

TEST(CUnknownImplTest, AddRef_Release)
{
	Testee* testee = new Testee(true);

	EXPECT_CALL(*testee, dtor(0)).Times(1);

	EXPECT_EQ(1, testee->AddRef());
	EXPECT_EQ(2, testee->AddRef());
	EXPECT_EQ(1, testee->Release());
	EXPECT_EQ(0, testee->Release());
}

TEST(CUnknownImplTest, CComPtr)
{
	Testee* testee = new Testee(true);

	EXPECT_CALL(*testee, dtor(0)).Times(1);

	{
		CComPtr<IPersist> p(testee);

		EXPECT_EQ(1, testee->m_refCount);
	}
}

TEST(CUnknownImplTest, IUnknown_QueryInterface)
{
	Testee* testee = new Testee(false, false);

	IUnknown* unk = NULL;

	EXPECT_EQ(S_OK, testee->QueryInterface(IID_PPV_ARGS(&unk)));
	EXPECT_EQ((CUnknownImpl*)testee, unk);

	IPersist* persist = (IPersist*)1;
	EXPECT_EQ(E_NOINTERFACE, testee->QueryInterface(IID_PPV_ARGS(&persist)));
	EXPECT_EQ(NULL, persist);

	EXPECT_EQ(0, testee->Release());
}

TEST(CUnknownImplTest, IPersist_QueryInterface)
{
	Testee* testee = new Testee(false, true);

	IUnknown* unk = NULL;

	EXPECT_EQ(S_OK, testee->QueryInterface(IID_PPV_ARGS(&unk)));
	EXPECT_EQ((IPersist*)testee, unk);		// First entry of QITAB is IPersist

	IPersist* persist = (IPersist*)1;
	EXPECT_EQ(S_OK, testee->QueryInterface(IID_PPV_ARGS(&persist)));
	EXPECT_EQ((IPersist*)testee, persist);

	IPersistStream* stream = (IPersistStream*)1;
	EXPECT_EQ(E_NOINTERFACE, testee->QueryInterface(IID_PPV_ARGS(&stream)));
	EXPECT_EQ(NULL, stream);

	EXPECT_EQ(1, testee->Release());
	EXPECT_EQ(0, testee->Release());
}
