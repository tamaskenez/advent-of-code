message(STATUS "2021")
add_compile_definitions(CMAKE_CURRENT_SOURCE_DIR="${CMAKE_CURRENT_SOURCE_DIR}")

foreach(d d24 d24_2 d24_3 d24_markus_himmel)
    add_executable(2021-${d} ${d}.cpp ../common.h)
endforeach()
