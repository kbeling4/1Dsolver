cmake_minimum_required( VERSION 3.10 )
project( SCPT LANGUAGES CXX )
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(PythonLibs REQUIRED)
find_package(Boost REQUIRED)
if ( ${Boost_FOUND} )
  include_directories( ${Boost_INCLUDE_DIRS} )
endif()


add_library( 1DSolver INTERFACE )
target_include_directories( 1DSolver INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/library )

target_link_libraries( 1DSolver INTERFACE ${PYTHON_LIBRARIES})

add_subdirectory( ${CMAKE_CURRENT_SOURCE_DIR}/src )
