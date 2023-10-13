enable_testing()

add_executable(utest
        fluid_test.cpp)

add_executable(vector3d_test
        vector3d_test.cpp)

target_link_libraries(utest
        PRIVATE
        sim
        GTest::gtest_main
        #Microsoft.GSL::GSL
)

target_link_libraries(vector3d_test
        PRIVATE
        sim
        GTest::gtest_main
        #Microsoft.GSL::GSL
        )



include(GoogleTest)
gtest_discover_tests(utest)
gtest_discover_tests(vector3d_test)