#include <gtest/gtest.h>
#include "lib.h"

// https://www.youtube.com/watch?v=aDQabfxQwfM

// Проверяем что версия определена и не пустая
TEST(test_version, VersionDefined) {
	const char* ver = version();
	ASSERT_NE(ver, nullptr);
	ASSERT_STRNE(ver, "");
}

// Проверяем размер строки версии
TEST(test_version, VersionSize) {
	EXPECT_GT(std::string(version()).size(), 4);
}

