cmake_minimum_required (VERSION 3.8)

project ("XMLResource")

set(CMAKE_CXX_STANDARD 17) # установка стандарта C++17
set(CMAKE_CXX_STANDARD_REQUIRED ON) # требование использования стандарта
set(CMAKE_CXX_EXTENSIONS OFF) # отключение расширений компилятора

add_executable(XMLResource main.cpp)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/resource.xml ${CMAKE_BINARY_DIR}/resource.xml COPYONLY)
