#Daniel Khomyakov y Eduardo Sebastian de Erice

cmake_minimum_required(VERSION 3.5)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project (multMatrix)

add_executable (multMatrix main_multMatrix.cpp multmatrix.cpp multmatrix.h)

project(mainClienteMultMatrix LANGUAGES CXX)
add_executable(mainClienteMultMatrix mainClienteMultMatrix.cpp 
				multmatrix_stub.h multmatrix_stub.cpp
				multmatrix.h multmatrix.cpp
				utils.h utils.cpp
)
target_link_libraries(mainClienteMultMatrix pthread)

project(mainServidorMultMatrix LANGUAGES CXX)
add_executable(mainServidorMultMatrix mainServidorMultMatrix.cpp 
				multmatrix_imp.h multmatrix_imp.cpp
				multmatrix.h multmatrix.cpp
				utils.h utils.cpp
)
target_link_libraries(mainServidorMultMatrix pthread)