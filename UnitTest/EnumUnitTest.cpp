#include "stdafx.h"
#include "Win32Utils/Enum.h"

using namespace testing;

class EnumTest : public Test {
public:
	ENUM(Color, RED, GREEN, BLUE);
	ENUM(WeekDay, SUN, MON, TUE, WED, THU, FRI, SAT);
};


TEST_F(EnumTest, Color_toString)
{
	EXPECT_EQ(0, Color::Values::RED);
	EXPECT_EQ(1, Color::Values::GREEN);
	EXPECT_EQ(2, Color::Values::BLUE);
	EXPECT_STREQ(_T("RED"), ((Color)Color::RED).toString());
	EXPECT_STREQ(_T("GREEN"), ((Color)Color::GREEN).toString());
	EXPECT_STREQ(_T("BLUE"), ((Color)Color::BLUE).toString());
	EXPECT_STREQ(_T("UNKNOWN"), ((Color)Color::COUNT).toString());
	EXPECT_STREQ(_T("UNKNOWN"), ((Color)Color::INVALID).toString());
	EXPECT_STREQ(_T("UNKNOWN"), ((Color)(Color::Values)5).toString());
}

TEST_F(EnumTest, Color_methods)
{
	Color color;

	EXPECT_FALSE(color.isValid())			<< "Default constructor";
	color = Color(Color::Values::BLUE);
	EXPECT_TRUE(color.isValid())			<< "Valid value";
	color = Color::Values::INVALID;
	EXPECT_FALSE(color.isValid())			<< "Invalid value";

	// Conpare object with Values type
	Color::Values v = Color::GREEN;
	color = v;
	EXPECT_TRUE(color == v);
	EXPECT_TRUE(color != Color::RED);
	EXPECT_TRUE(v == color);
	EXPECT_TRUE(Color::RED != color);

	// Compare Objects
	EXPECT_TRUE(color == Color(color));
}

TEST_F(EnumTest, WeekDay_multiInstance)
{
	const WeekDay d1(WeekDay::Values::FRI);
	const WeekDay d2;

	EXPECT_EQ(7, WeekDay::COUNT)			<< "Count of enum";
	EXPECT_EQ(7, d1.COUNT)					<< "Count of instance 1";
	EXPECT_EQ(7, d2.COUNT)					<< "Count of instance 2";
	EXPECT_STREQ(d1.toString(), d2.toString(WeekDay::Values::FRI))	<<"instance and static toString()";

	WeekDay d3(d1);
	EXPECT_EQ(WeekDay::Values::FRI, d3)		<< "Instance created by copy constructor";
	EXPECT_STREQ("FRI", d3.toString())		 << "Instance created by copy constructor";
}
