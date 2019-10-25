cmake_minimum_required( VERSION 3.10 )
project( SCPT LANGUAGES CXX )
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#add_compile_options(-O3 -Wall -Wextra -pedantic -Werror)

add_library( 1DSolver INTERFACE )
target_include_directories( 1DSolver INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/library )

add_subdirectory( ${CMAKE_CURRENT_SOURCE_DIR}/src )
