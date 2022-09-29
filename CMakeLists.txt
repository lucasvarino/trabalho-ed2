cmake_minimum_required(VERSION 3.0.0)
project(trabalho-ed2-parte1 VERSION 0.1.0)

file(GLOB SOURCES
    sources/*.cpp
)

add_executable(trabalho-ed2-parte1 ${SOURCES})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
target_include_directories(trabalho-ed2-parte1 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} / headers)
include(CPack)
