#include <maths/vec2f.h>
#include <gtest/gtest.h>


//what values it takes -> pair of Vec2f
struct Vec2fOperationFixture : public ::testing::TestWithParam<std::pair<core::Vec2f, core::Vec2f>>
{};

//test by itself -> add
TEST_P(Vec2fOperationFixture, add)
{
	auto [v1, v2] = GetParam();
	const auto result = v1 + v2;
	EXPECT_EQ(result.x, v1.x + v2.x);
	EXPECT_EQ(result.y, v1.y + v2.y);
}

//test by itself -> sub
TEST_P(Vec2fOperationFixture, sub)
{
	//substraction
	auto [v1, v2] = GetParam();
	const auto result = v1 - v2;
	EXPECT_EQ(result.x, v1.x - v2.x);
	EXPECT_EQ(result.y, v1.y - v2.y);

	//nagative numbers
	const auto neg1 = -v1;
	const auto neg2 = -v2;
	EXPECT_EQ(neg1.x, -v1.x);
	EXPECT_EQ(neg2.x, -v2.x);
}

//test by itself -> calculate perpendicular
TEST_P(Vec2fOperationFixture, perpendicular)
{
	//substraction
	auto [v1, v2] = GetParam();
	const auto p1 = v1.Perpendicular();
	const auto p2 = v2.Perpendicular();
	EXPECT_EQ(core::Vec2f::Dot(v1, p1), 0);
	EXPECT_EQ(core::Vec2f::Dot(v2, p2), 0);
}

//instantiate tes by itself and their specific values
INSTANTIATE_TEST_SUITE_P(PositiveNumbers, Vec2fOperationFixture, testing::Values(
	std::pair{ core::Vec2f{1,3}, core::Vec2f{2,4} }));