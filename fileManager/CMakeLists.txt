#Daniel Khomyakov y Eduardo Sebastian de Erice

cmake_minimum_required (VERSION 2.8.11)

project (fileManager)

add_executable (fileManager main_fm.cpp filemanager.cpp filemanager.h)

project(mainCliente LANGUAGES CXX)
add_executable(mainCliente mainCliente.cpp 
				filemanager_stub.h filemanager_stub.cpp
				filemanager.h filemanager.cpp
				utils.h utils.cpp
)
target_link_libraries(mainCliente pthread)

project(mainServidor LANGUAGES CXX)
add_executable(mainServidor mainServidor.cpp 
				filemanager_imp.h filemanager_imp.cpp
				filemanager.h filemanager.cpp
				utils.h utils.cpp
)
target_link_libraries(mainServidor pthread)