add_compile_definitions(CMAKE_CURRENT_SOURCE_DIR="${CMAKE_CURRENT_SOURCE_DIR}")

foreach(d d1 d2 d3 d4 d5)
    add_executable(2015-${d} ${d}.cpp ../common.h)
endforeach()
