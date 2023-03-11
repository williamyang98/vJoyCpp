cmake_minimum_required(VERSION 3.21)
project(vjoy)

set(SRC_DIR ${CMAKE_CURRENT_LIST_DIR})

# Select correct dll for x86 or x64
add_library(vjoy_c SHARED IMPORTED GLOBAL)  
if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    set_target_properties(vjoy_c PROPERTIES 
        IMPORTED_IMPLIB_RELEASE   ${SRC_DIR}/bin/x64/vJoyInterface.lib
        IMPORTED_LOCATION_RELEASE ${SRC_DIR}/bin/x64/vJoyInterface.dll
    )
elseif(CMAKE_SIZEOF_VOID_P EQUAL 4)
    set_target_properties(vjoy_c PROPERTIES 
        IMPORTED_IMPLIB_RELEASE   ${SRC_DIR}/bin/x86/vJoyInterface.lib
        IMPORTED_LOCATION_RELEASE ${SRC_DIR}/bin/x86/vJoyInterface.dll
    )
else()
    message(FATAL_ERROR "vJoy only supports x86/x64")
endif()

add_library(vjoy STATIC ${SRC_DIR}/src/vjoy.cpp)
target_include_directories(vjoy PUBLIC ${SRC_DIR}/include)
target_link_libraries(vjoy PRIVATE vjoy_c)
set_target_properties(vjoy PROPERTIES CXX_STANDARD 14)
