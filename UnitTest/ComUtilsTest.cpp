#include "stdafx.h"
#include "Win32Utils/ComUtils.h"

using namespace testing;

class ClassChecker {
public:
	MOCK_METHOD0(ctor, void());
	MOCK_METHOD0(dtor, void());
};

class Testee : public CUnknownImpl {
public:
	Testee(ClassChecker& classChecker) : classChecker(classChecker) {}
	~Testee() { classChecker.dtor(); }

	IUNKNOWN_METHODS;

	using CUnknownImpl::m_refCount;
	ClassChecker& classChecker;
};

TEST(test, test)
{
	ClassChecker classChecker;
	Testee* testee = new Testee(classChecker);

	EXPECT_CALL(classChecker, dtor()).Times(1);

	ASSERT_EQ(1, testee->AddRef());
	ASSERT_EQ(2, testee->AddRef());
	ASSERT_EQ(1, testee->Release());
	ASSERT_EQ(0, testee->Release());
}
