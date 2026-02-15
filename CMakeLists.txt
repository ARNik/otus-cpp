cmake_minimum_required(VERSION 3.20)
project(helloworld)

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

add_executable(helloworld_cli main.cpp)
add_library(helloworld lib.cpp)
add_dependencies(helloworld ALWAYS)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/52eb8108c5bdec04579160ae17225d66034bd723.zip
    DOWNLOAD_EXTRACT_TIMESTAMP true
    EXCLUDE_FROM_ALL
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# set_target_properties(helloworld_cli helloworld PROPERTIES
#     CXX_STANDARD 17
#     CXX_STANDARD_REQUIRED ON
# )

target_include_directories(helloworld
    PRIVATE "${CMAKE_BINARY_DIR}"
)

target_link_libraries(helloworld_cli PRIVATE
    helloworld
)

option(WITH_BOOST_TEST "Whether to build Boost test" ON)

if(WITH_BOOST_TEST)
    find_package(Boost CONFIG COMPONENTS unit_test_framework REQUIRED)
    add_executable(test_version test_version.cpp)

    set_target_properties(test_version PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON
    )

    # target_compile_definitions(test_version PRIVATE BOOST_TEST_DYN_LINK)

    target_link_libraries(test_version
        PRIVATE
        Boost::unit_test_framework
        helloworld
    )
endif()

if (MSVC)
    target_compile_options(helloworld_cli PRIVATE /W4)
    target_compile_options(helloworld PRIVATE /W4)
    if(WITH_BOOST_TEST)
        target_compile_options(test_version PRIVATE /W4)
    endif()
else ()
    target_compile_options(helloworld_cli PRIVATE -Wall -Wextra -pedantic -Werror)
    target_compile_options(helloworld PRIVATE -Wall -Wextra -pedantic -Werror)
    if(WITH_BOOST_TEST)
        target_compile_options(test_version PRIVATE -Wall -Wextra -pedantic -Werror)
    endif()
endif()

install(TARGETS helloworld_cli RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION "${PACKAGE_VERSION}")
set(CPACK_PACKAGE_CONTACT arnik@arnik.ru)
include(CPack)

if(WITH_BOOST_TEST)
    enable_testing()
    add_test(test_version test_version)
endif()

enable_testing()

add_executable(
  test_hello
  test_hello.cpp
)

target_link_libraries(
  test_hello
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(test_hello)