# General
cmake_minimum_required(VERSION 3.25)
project(fluid LANGUAGES CXX)


# Estandar
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Opciones de compilacion
add_compile_options(-Wall -Wextra -Werror -pedantic -pedantic-errors -O3)
set(CMAKE_CXX_FLAGS_RELEASE "-march=native")

include(FetchContent)

# esto relentiza compilación, se puede desactivar y activar
# ESTA LINEA NO CONSEGUIMOS QUE HAGA NADA
set(CMAKE_CXX_CLANG_TIDY clang-tidy -header-filter=.*)

# incluir todos los directorios de código
include_directories(PUBLIC .)

# Subdirectorios
add_subdirectory(sim)
add_subdirectory(fluid)

#enable_testing()
#add_subdirectory(utest)
#add_subdirectory(ftest)