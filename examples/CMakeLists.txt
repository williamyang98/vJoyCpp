cmake_minimum_required(VERSION 3.0.0)
project(examples)

set(vjoy_DIR ${CMAKE_CURRENT_LIST_DIR}/../)
find_package(vjoy CONFIG REQUIRED)

macro(install_dlls target)
add_custom_command(
    TARGET ${target}
    POST_BUILD 
    COMMAND ${CMAKE_COMMAND} -E copy 
    $<TARGET_RUNTIME_DLLS:${target}> 
    $<TARGET_FILE_DIR:${target}>
    COMMAND_EXPAND_LISTS
)
endmacro()

set(SRC_DIR ${CMAKE_CURRENT_LIST_DIR})

add_executable(main ${SRC_DIR}/main.cpp)
target_link_libraries(main PRIVATE vjoy) 
set_target_properties(main PROPERTIES CXX_STANDARD 14)
install_dlls(main)
