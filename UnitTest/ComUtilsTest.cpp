#include "stdafx.h"
#include "Win32Utils/ComUtils.h"

#include <atlbase.h>

using namespace testing;

class ClassChecker {
public:
	MOCK_METHOD0(ctor, void());
	MOCK_METHOD0(dtor, void());
};

class Testee : public CUnknownImpl, public IPersist {
public:
	Testee(bool checkCtor, bool checkDtor, bool iPersist)
		: checkCtor(checkCtor), checkDtor(checkDtor), iPersist(iPersist) {
		if (checkCtor) classChecker.ctor();
	}
	~Testee() { if (checkDtor) classChecker.dtor(); }

	IUNKNOWN_METHODS;

	virtual HRESULT STDMETHODCALLTYPE GetClassID(
		/* [out] */ __RPC__out CLSID *pClassID) { return S_OK; }

	static const QITAB qitab[];
	virtual const QITAB* getQITAB() const { return iPersist ? qitab : NULL; }

	using CUnknownImpl::m_refCount;
	ClassChecker classChecker;
	const bool checkCtor, checkDtor, iPersist;
};

const QITAB Testee::qitab[] = {
	QITABENT(Testee, IPersist),
	{0}
};

TEST(CUnknownImplTest, AddRef_Release)
{
	Testee* testee = new Testee(false, true, false);

	EXPECT_CALL(testee->classChecker, dtor()).Times(1);

	EXPECT_EQ(1, testee->AddRef());
	EXPECT_EQ(2, testee->AddRef());
	EXPECT_EQ(1, testee->Release());
	EXPECT_EQ(0, testee->Release());
}

TEST(CUnknownImplTest, CComPtr)
{
	Testee* testee = new Testee(false, true, false);

	EXPECT_CALL(testee->classChecker, dtor()).Times(1);

	{
		CComPtr<IPersist> p(testee);

		EXPECT_EQ(1, testee->m_refCount);
	}
}

TEST(CUnknownImplTest, IUnknown_QueryInterface)
{
	Testee* testee = new Testee(false, false, false);

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
	Testee* testee = new Testee(false, false, true);

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
