set(CMAKE_CXX_STANDARD 20)
add_library(sim
        particle.hpp
        particle.cpp
        vector_3d.hpp
        vector_3d.cpp
        progargs.hpp
        progargs.cpp
        Malla.cpp
        constantes.hpp
        simulacion.hpp
        simulacion.cpp
)

target_include_directories(sim PUBLIC ..)
#target_link_libraries(sim PRIVATE Microsoft.GSL::GSL)