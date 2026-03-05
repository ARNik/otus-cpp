#include "version.h"
#include <gtest/gtest.h>

// https://www.youtube.com/watch?v=aDQabfxQwfM

// Проверяем что версия определена и не пустая
TEST(test_version, VersionDefined)
{
	const char* ver = GIT_VERSION;
	ASSERT_NE(ver, nullptr);
	ASSERT_STRNE(ver, "");
}

// Проверяем размер строки версии
TEST(test_version, VersionSize)
{
	EXPECT_GT(std::string(GIT_VERSION).size(), 4);
}
