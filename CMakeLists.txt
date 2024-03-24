cmake_minimum_required(VERSION 3.18)
project(swigproject)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_BUILD_TYPE Release)

set(SWIG_EXECUTABLE C:/DKFZ/Python_work/swigwin-4.2.0/swig.exe)
find_package(SWIG REQUIRED)
include(${SWIG_USE_FILE})

find_package(Python REQUIRED COMPONENTS Development)
include_directories(pyShape ${Python_INCLUDE_DIRS} ${CMAKE_SOURCE_DIR}/shape)

set_property(SOURCE shape/shape.i PROPERTY CPLUSPLUS ON)
swig_add_library(pyShape TYPE MODULE LANGUAGE python SOURCES shape/shape.i shape/shape.cpp shape/shape.h)
target_link_libraries(pyShape PUBLIC ${Python_LIBRARIES})
execute_process(COMMAND ${SWIG_EXECUTABLE} -python -external-runtime ${CMAKE_SOURCE_DIR}/swigpyrun.h)

add_executable(pyTest main.cpp)
add_library(Shape ${CMAKE_SOURCE_DIR}/shape/shape.cpp)
target_link_directories(pyTest PRIVATE ${CMAKE_SOURCE_DIR}/../build/shape/)
target_include_directories(pyTest PRIVATE ${Python_INCLUDE_DIRS})
target_link_libraries(pyTest PRIVATE Shape PRIVATE ${Python_LIBRARIES})


message(Python_LIBRARIES="${Python_LIBRARIES}")
message(SWIG_EXECUTABLE="${SWIG_EXECUTABLE}")
message(Python_INCLUDE_DIRS="${Python_INCLUDE_DIRS}")