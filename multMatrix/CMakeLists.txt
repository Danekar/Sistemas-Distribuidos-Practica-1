cmake_minimum_required (VERSION 2.8.11)

project (multMatrix)

add_executable (multMatrix main_multMatrix.cpp multmatrix.cpp multmatrix.h)

project(mainClienteMultMatrix LANGUAGES CXX)
add_executable(mainClienteMultMatrix mainClientMultMatrix.cpp 
				multMatrix_stub.h multMatrix_stub.cpp
				utils.h utils.cpp
)
target_link_libraries(mainClienteMultMatrix pthread)

project(mainServerMultMatrix LANGUAGES CXX)
add_executable(mainServerMultMatrix mainServerMultMatrix.cpp 
				multMatrix_imp.h multMatrix_imp.cpp
				utils.h utils.cpp
)
target_link_libraries(mainServerMultMatrix pthread)