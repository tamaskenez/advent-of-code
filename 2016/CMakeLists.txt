add_compile_definitions(CMAKE_CURRENT_SOURCE_DIR="${CMAKE_CURRENT_SOURCE_DIR}")

foreach(d d01 d02 d03 d04 d05 d06 d07 d08 d09 d10 d11 d11b d12
d13 d14 d14b d15 d16 d17 d18 d19 d20 d20b d21 d22 d22b d23 d24 d25)
    add_executable(2016-${d} ${d}.cpp ../common.h)
endforeach()
