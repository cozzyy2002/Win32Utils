// UnitTest.cpp : �R���\�[�� �A�v���P�[�V�����̃G���g�� �|�C���g���`���܂��B
//

#include "stdafx.h"

int main(int argc, TCHAR** argv)
{
	_tprintf(_T("%s\n"), argv[1]);
	::testing::InitGoogleTest(&argc, argv);
	::testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}
