message(STATUS "2020")
add_compile_definitions(CMAKE_CURRENT_SOURCE_DIR="${CMAKE_CURRENT_SOURCE_DIR}")

foreach(d d01 d02 d03 d04 d05 d06 d07 d08 d09 d10 d11 d12 d13 d14 d15 d16 d17 d18 d18_2 d19 d20 d21 d22 d23)
    add_executable(2020-${d} ${d}.cpp ../common.h)
endforeach()
