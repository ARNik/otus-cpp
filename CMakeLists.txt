cmake_minimum_required(VERSION 3.20)
project(helloworld)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Генерация версии пакета (при конфигурации)
execute_process(
	COMMAND git describe --tags --always --dirty --abbrev=8
	WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
	OUTPUT_VARIABLE PACKAGE_VERSION
	OUTPUT_STRIP_TRAILING_WHITESPACE
	ERROR_QUIET
)
message(STATUS "Package version: ${PACKAGE_VERSION}")

# Генерация версии билда (при каждой сборке)
set(VERSION_HEADER ${CMAKE_BINARY_DIR}/version.h)
add_custom_target(
	ALWAYS
	COMMAND ${CMAKE_COMMAND} -E echo "#pragma once" > ${VERSION_HEADER}
	COMMAND git describe --tags --always --dirty --abbrev=8 |
			xargs printf "#define GIT_VERSION \"%s\"" >> ${VERSION_HEADER}
	VERBATIM
)

# Основные таргеты
add_executable(helloworld_cli main.cpp)
add_library(helloworld_lib lib.cpp)
add_dependencies(helloworld_lib ALWAYS)

target_include_directories(helloworld_lib PRIVATE "${CMAKE_BINARY_DIR}")

target_link_libraries(helloworld_cli PRIVATE helloworld_lib)

# Установка и пакетирование
install(TARGETS helloworld_cli RUNTIME DESTINATION bin)
set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION "${PACKAGE_VERSION}")
set(CPACK_PACKAGE_CONTACT arnik@arnik.ru)
include(CPack)

# Тесты https://google.github.io/googletest/
enable_testing()

include(FetchContent)
FetchContent_Declare(
	googletest
	URL https://github.com/google/googletest/archive/52eb8108c5bdec04579160ae17225d66034bd723.zip
	DOWNLOAD_EXTRACT_TIMESTAMP true
	EXCLUDE_FROM_ALL
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(test_version test_version.cpp)
target_link_libraries(test_version helloworld_lib GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(test_version)