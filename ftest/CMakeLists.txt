# Executable for all unit tests with list of sources
# For example, you may have one ∗_test.cpp for each ∗.cpp in sim
add_executable(ftest ftests.cpp)

target_link_libraries (ftest PRIVATE  sim  GTest::gtest_main)

# Discover all tests and add them to the test driver
include(GoogleTest)
gtest_discover_tests(ftest)