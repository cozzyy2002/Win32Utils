#include "stdafx.h"
#include "Win32Utils/Enum.h"

using namespace testing;

class EnumTest : public Test {
public:
};

ENUM(Colors, RED, GREEN, BLUE);

ENUM(WeekDays, SUN, MON, TUE, WED, THU, FRI, SAT);

TEST_F(EnumTest, Colors)
{
	const Colors colors;

	EXPECT_EQ(0, Colors::RED);
	EXPECT_EQ(0, colors.RED);

	Colors::Values c = Colors::BLUE;
	EXPECT_STREQ(_T("BLUE"), colors.toString(c));
}

TEST_F(EnumTest, WeekDays)
{
	const WeekDays d1;
	const WeekDays d2;

	EXPECT_EQ(7, WeekDays::COUNT);
	EXPECT_EQ(d1.COUNT, d2.COUNT);
	EXPECT_STREQ(d1.toString(WeekDays::FRI), d2.toString(WeekDays::FRI));
}