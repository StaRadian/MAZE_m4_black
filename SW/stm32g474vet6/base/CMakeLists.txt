cmake_minimum_required(VERSION 3.20)

#현재 폴더 이름 = 프로젝트 이름
get_filename_component(ProjectId ${CMAKE_CURRENT_SOURCE_DIR} NAME)
string(REPLACE " " "_" ProjectId ${ProjectId})
project(${ProjectId})

set(MY_PROJECT_NAME ${CMAKE_PROJECT_NAME})

project(${MY_PROJECT_NAME} C CXX ASM)

include(cmake/st-project.cmake)

add_executable(${MY_PROJECT_NAME})
add_st_target_properties(${MY_PROJECT_NAME})

#헤더 파일 주소
target_include_directories(
    ${MY_PROJECT_NAME} PRIVATE
    "$<$<AND:$<CONFIG:Debug>,$<COMPILE_LANGUAGE:C>>:${PROJECT_SOURCE_DIR}/inc>"
    "$<$<AND:$<NOT:$<CONFIG:Debug>>,$<COMPILE_LANGUAGE:C>>:${PROJECT_SOURCE_DIR}/inc>"
)