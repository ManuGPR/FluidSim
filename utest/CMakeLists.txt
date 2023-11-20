# Executable for all unit tests with list of sources
# For example, you may have one ∗_test.cpp for each ∗.cpp in sim
add_executable(utest
        utests.cpp
        progargs_test.cpp
        block_test.cpp
        calculos_test.cpp
        file_test.cpp
)

target_link_libraries (utest
        PRIVATE
        sim
        GTest::gtest_main)

# Discover all tests and add them to the test driver
include(GoogleTest)
gtest_discover_tests(utest)