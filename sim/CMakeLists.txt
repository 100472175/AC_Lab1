set(CMAKE_CXX_STANDARD 20)
add_library(sim lectura_archivo.cpp
        funciones_fisicas.cpp
        particle.cpp
        vector_3d.cpp
        progargs.cpp
        progargs.hpp
        Malla.cpp
        constantes.hpp
        constantes.cpp
)

target_include_directories(sim PUBLIC ..)
#target_link_libraries(sim PRIVATE Microsoft.GSL::GSL)