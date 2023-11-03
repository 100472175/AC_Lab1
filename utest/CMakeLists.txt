enable_testing()

add_executable(utest
        main.cpp
        vector3d_test.cpp
        calculadora_test.cpp
        progargs_test.cpp)

target_link_libraries(utest
        PRIVATE
        sim
        GTest::gtest_main
        #Microsoft.GSL::GSL
)



include(GoogleTest)
gtest_discover_tests(utest)
