add_executable(solver solver.cpp)
set_target_properties(solver PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
)
target_link_libraries(solver PUBLIC 1DSolver)
