enable_testing()

add_executable(ftest
        main.cpp
        ftest.cpp)

target_link_libraries(ftest
        PRIVATE
        sim
        GTest::gtest_main
        #Microsoft.GSL::GSL
)



include(GoogleTest)
gtest_discover_tests(ftest)
