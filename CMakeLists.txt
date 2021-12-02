cmake_minimum_required(VERSION 3.15)
project(aoc)

set(ONLY_THIS_YEAR 2021)

set(WARNINGS_AS_ERRORS 1)

if (MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
    if (WARNINGS_AS_ERRORS)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /WX")
    endif()
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wformat -Wall -Wextra -Wconversion")
    if (WARNINGS_AS_ERRORS)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror -pedantic-errors")
    else()
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pedantic")
    endif()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-sign-conversion -Wno-shorten-64-to-32 -Wno-unused-const-variable -Wno-unused-variable")
endif()

include_directories(${CMAKE_SOURCE_DIR})

set(CMAKE_CXX_STANDARD 17)

foreach(year 2015 2016 2017 2018 2019 2020 2021)
  if(NOT ONLY_THIS_YEAR OR (ONLY_THIS_YEAR STREQUAL year))
    add_subdirectory(${year})
  endif()
endforeach()
