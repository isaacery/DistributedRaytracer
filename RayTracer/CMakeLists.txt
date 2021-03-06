cmake_minimum_required(VERSION 2.8)

include(CMakePrintHelpers)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-pthread")

cmake_print_variables(CMAKE_BUILD_TYPE)

project("Ray Tracer" C CXX)

include_directories(
parsers
math)


file (GLOB rapidjson_headers
parsers/rapidjson/*.h
)

file (GLOB source
main/*.cpp
core/*.cpp
cameras/*.cpp
lights/*.cpp
shapes/*.cpp
materials/*.cpp
textures/*.cpp
)


#raytracer executable
add_executable(raytracer ${source} math/geometry.h ${rapidjson_headers})

#json example executable
add_executable(jsonexample examples/jsonExample.cpp ${rapidjson_headers})

#vector example executable
add_executable(vectorexample examples/vecMatrixExample.cpp math/geometry.h)
