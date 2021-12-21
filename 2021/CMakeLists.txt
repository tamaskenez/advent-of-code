message(STATUS "2021")
add_compile_definitions(CMAKE_CURRENT_SOURCE_DIR="${CMAKE_CURRENT_SOURCE_DIR}")

foreach(d d21)
    add_executable(2021-${d} ${d}.cpp ../common.h)
endforeach()
