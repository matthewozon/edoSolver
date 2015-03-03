cmake_minimum_required(VERSION 2.6)

#Configuration du projet
project(equationSolver)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BUILD_TYPE})

#Inclusion de Boost
include_directories(.)
link_directories(.)

#Configuration de l'exécutable
file(
	GLOB
	source_files
	*.h *.cpp
)
add_executable(
        equationSolver
	${source_files}
)

#Configuration de l'édition de liens
target_link_libraries(
        equationSolver
        #pthread
)
