cmake_minimum_required(VERSION 3.10)
project(ip_filter)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Генерация версии пакета (при конфигурации)
execute_process(
	COMMAND git describe --tags --always --dirty --abbrev=8
	COMMAND awk -F_ "{print $NF}"	# версия находится в последнем поле после _
	COMMAND sed "s/-g/-/"			# удаляем g из хеша коммита
	WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
	OUTPUT_VARIABLE PACKAGE_VERSION
	OUTPUT_STRIP_TRAILING_WHITESPACE
	ERROR_QUIET
)
message(STATUS "Package version: ${PACKAGE_VERSION}")

# Генерация версии билда (при каждой сборке)
set(VERSION_HEADER ${CMAKE_BINARY_DIR}/version.h)
add_custom_target(
	GITVERSION
	COMMAND ${CMAKE_COMMAND} -E echo "#pragma once" > ${VERSION_HEADER}
	COMMAND git describe --tags --always --dirty --abbrev=8 |
			awk -F_ "{print $NF}" | sed "s/-g/-/" |
			xargs printf "#define GIT_VERSION \"%s\"" >> ${VERSION_HEADER}
	VERBATIM
)

# Основные таргеты
add_executable(ip_filter main.cpp)
add_dependencies(ip_filter GITVERSION)
target_include_directories(ip_filter PRIVATE "${CMAKE_BINARY_DIR}")

# Установка и пакетирование
install(TARGETS ip_filter RUNTIME DESTINATION bin)
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

add_executable(tests tests.cpp)
add_dependencies(tests GITVERSION)
target_include_directories(tests PRIVATE "${CMAKE_BINARY_DIR}")
target_link_libraries(tests GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(tests)