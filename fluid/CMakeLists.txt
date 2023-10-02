add_executable(fluid fluid.cpp
        fluid.hpp)
target_link_libraries(fluid sim)
target_include_directories(fluid PUBLIC ../common)