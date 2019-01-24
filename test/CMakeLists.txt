add_executable(unit_tests workTest.cpp)

target_link_libraries(unit_tests gtest_main work)

# Integrate with ctest
add_test(NAME unit COMMAND ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR}/unit_tests)
