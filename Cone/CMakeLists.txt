cmake_minimum_required(VERSION 3.3)
project(Cone)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
find_library (LIBSTDCXX NAMES stdc++)
add_compile_options(-stdlib=libstdc++)
#target_link_libraries(${PROJECT_NAME} ${LIBSTDCXX} ${YOUR_OTHER_LIBRARIES})

set(SOURCE_FILES main.cpp test_code.cpp vmath.h)
add_executable(Cone ${SOURCE_FILES})