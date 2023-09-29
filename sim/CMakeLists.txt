add_library(sim lectura_archivo.cpp funciones_fisicas.cpp)
target_include_directories(sim PUBLIC ..)

#target_link_libraries(sim PRIVATE Microsoft.GSL::GSL)